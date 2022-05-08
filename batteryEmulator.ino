#include <Wire.h>

// First 4 chars are cut off
#define BATTERY_MODEL "LNV-Version 2"
#define BATTERY_VENDOR "HACKED"
#define CHARGE_VOLTAGE 12600
#define BATTERY_VOLTAGE 10800
#define SERIAL 420

#define V_HIGH 12.1

// 20% above where the battery actually dies. This is because on load my T420 can pull the voltage down 20%.
// If you're using a non-modified T420 you can probably use 10.2-10.3 here and get 10% more battery life.
#define V_LOW 10.52

// mAh, uses BATTERY_VOLTAGE when calculating Wh
#define BATTERY_CAPACITY 15000
#define BATTERY_CAPACITY_DESIGN 15000

byte command;

// 0 - Charging
// 1 - Battery Powered
int mode = 1;

void splitNum(int num, int* upper, int* lower) {
  *lower = (num & 0xff00) >> 8;
  *upper = num & 0x00ff;
}

bool needsLength(int type) {
  return (type == 0x20 ||
      type == 0x21 ||
      type == 0x22 ||
      type == 0x23 ||
      type == 0x30 ||
      type == 0x3C ||
      type == 0x37 ||
      type == 0x2F);
}

void iterateCRC(bool CRC[8], int currentByte) {
  for (int y = 0; y < 8; ++y) {
    bool currentBit = (currentByte >> (7-y)) & 0x01;
    bool invert = currentBit ^ CRC[7];

    CRC[7] = CRC[6];
    CRC[6] = CRC[5];
    CRC[5] = CRC[4];
    CRC[4] = CRC[3];
    CRC[3] = CRC[2];
    CRC[2] = CRC[1] ^ invert;
    CRC[1] = CRC[0] ^ invert;
    CRC[0] = invert;
  }
}

// CRC function, used as a checksum for the data send to the laptop
int genCRC(byte* arr, int len, int replyTo)
{
  bool CRC[8];
  bool addLength = needsLength(replyTo);
  
  for (int i = 0; i < 8; ++i) CRC[i] = 0;
  
  iterateCRC(CRC, 22);
  iterateCRC(CRC, replyTo);
  iterateCRC(CRC, 23);
  
  if (addLength)
    iterateCRC(CRC, len);

  for (int x = 0; x < len; ++x) {
    int currentByte = arr[x];
    iterateCRC(CRC, currentByte);
  }

  int final = 0;

  for (int x = 0; x < 8; ++x)
    final += (0x01 << x) * CRC[x];

  // Serial.println(final);
  return final;
}

// Function signature for callbacks
// Takes byte array for a buffer and returns the number of bytes written to it
typedef byte (*smbusCallback)(byte*);

byte reply0x00(byte *buff) {
  buff[0] = 24;
  buff[1] = 0;
  return 2;
}

byte reply0x01(byte *buff) {
  buff[0] = 44;
  buff[1] = 1;
  return 2;
}

byte reply0x02(byte *buff) {
  buff[0] = 30;
  buff[1] = 0;
  return 2;
}

byte reply0x03(byte *buff) {
  buff[0] = 132;
  buff[1] = 128;

  return 2;
}

byte reply0x04(byte *buff) {
  buff[0] = 0;
  buff[1] = 0;
  return 2;
}

// 0x05

byte reply0x06(byte *buff) {
  buff[0] = 100;
  buff[1] = 0;

  return 2;
}

// 0x07

byte reply0x08(byte *buff) {
  buff[0] = 137;
  buff[1] = 11;

  return 2;
}

byte reply0x09(byte *buff) {
  int lower, higher;

  // Values of the resistors used in the voltage divider
  float r1 = 9.89;
  float r2 = 3.39;

  // Read the voltage divider input on analog pin that has a range of 3.33v to 0v, and output a number from 0 to 1024
  float voltageIn = analogRead(3) * (3.33 / 1024.0);
  float vin = voltageIn / (r2/(r1+r2)); 
  int Vinoff = vin * 1000;

  if (vin < 0)
    vin = 0;

  splitNum(Vinoff, &lower, &higher);
  buff[0] = lower;
  buff[1] = higher;

  return 2;
}

byte reply0x0a(byte *buff) {
  if (mode == 0) {
    buff[0] = 0;
    buff[1] = 0;
  } else {
    buff[0] = 0xF8;
    buff[1] = 0xFC;
  }

  return 2;
}

byte reply0x0b(byte *buff) {
  if (mode == 0) {
    buff[0] = 0;
    buff[1] = 0;
  } else {
    buff[0] = 0xF6;
    buff[1] = 0xFC;
  }

  return 2;
}

byte reply0x0c(byte *buff) {
  buff[0] = 0x00;
  buff[1] = 0x00;

  return 2;
}

// Relative state of charge
byte reply0x0d(byte *buff) {
  buff[0] = 0x5b;
  buff[1] = 0x00;

  return 2;
}

// 0x0e

byte reply0x0f(byte *buff) {
  int lower, higher;

  float r1 = 9.89;
  float r2 = 3.39;

  float sensorLow = V_LOW * (r2/(r1+r2));
  float sensorHigh = V_HIGH * (r2/(r1+r2));

  // Assume linear voltage -> battery capacity coorelation (this isn't perfect)
  // y = mx + b
  float m = 1/(sensorHigh - sensorLow);
  float b = -sensorLow*m;

  float voltageIn = analogRead(3) * (3.33 / 1024.0);
  int batteryVoltage = (m*voltageIn + b)*BATTERY_CAPACITY;

  if (batteryVoltage < 0)
    batteryVoltage = 0;

  splitNum(batteryVoltage, &lower, &higher);
  buff[0] = lower;
  buff[1] = higher;

  return 2;
}

byte reply0x10(byte *buff) {
  int lower, higher;
  
  splitNum(BATTERY_CAPACITY, &lower, &higher);
  buff[0] = lower;
  buff[1] = higher;
  
  return 2;
}

// Run time to empty
byte reply0x11(byte *buff) {
  buff[0] = 60;
  buff[1] = 0x00;

  return 2;
}

byte reply0x12(byte *buff) {
  buff[0] = 255;
  buff[1] = 255;

  return 2;
}

byte reply0x13(byte *buff) {
  buff[0] = 255;
  buff[1] = 255;

  return 2;
}

// 0x14-0x16

byte reply0x17(byte *buff) {
  buff[0] = 20;
  buff[1] = 5;

  return 2;
}

byte reply0x14(byte *buff) {
  buff[0] = 228;
  buff[1] = 12;

  return 2;
}

byte reply0x15(byte *buff) {
  int lower, higher;
  
  splitNum(CHARGE_VOLTAGE, &lower, &higher);
  buff[0] = lower;
  buff[1] = higher;

  return 2;
}

byte reply0x16(byte *buff) {
  buff[0] = 224;
  buff[1] = 192;

  return 2;
}

// 0x17

byte reply0x18(byte *buff) {
  int lower, higher;
  
  splitNum(BATTERY_CAPACITY_DESIGN, &lower, &higher);
  buff[0] = lower;
  buff[1] = higher;
  
  return 2;
}

byte reply0x19(byte *buff) {
  int lower, higher;
  
  splitNum(BATTERY_VOLTAGE, &lower, &higher);
  buff[0] = lower;
  buff[1] = higher;
  
  return 2;
}

byte reply0x1a(byte *buff) {
  buff[0] = 49;
  return 1;
}

byte reply0x1b(byte *buff) {
  buff[0] = 156;
  buff[1] = 61;
  return 2;
}

byte reply0x1c(byte *buff) {
  int lower, higher;
  
  splitNum(SERIAL, &lower, &higher);
  buff[0] = lower;
  buff[1] = higher;
  
  return 2;
}

// 0x1d-0x1f

byte reply0x20(byte *buff) {
  char *battery_vendor = BATTERY_VENDOR;

  for (int x = 0; x < strlen(battery_vendor); ++x) {
    buff[x] = battery_vendor[x];
  }

  int end = strlen(battery_vendor);
  
  buff[end + 0] = 0;
  buff[end + 1] = 49;
  buff[end + 2] = 49;

  return strlen(battery_vendor) + 3;
}

byte reply0x21(byte *buff) {
  char *battery_model = BATTERY_MODEL;

  for (int x = 0; x < strlen(battery_model); ++x) {
    buff[x] = battery_model[x];
  }

  return strlen(battery_model);
}

// Device chemistry
byte reply0x22(byte *buff) {
  buff[0] = 76;
  buff[1] = 73;
  buff[2] = 79;
  buff[3] = 78;

  return 4;
}

byte reply0x23(byte *buff) {
  buff[0] = 0x42;
  buff[1] = 0x0a;
  buff[2] = 0x05;
  buff[3] = 0x12;
  buff[4] = 0x86;
  buff[5] = 0x0f;
  buff[6] = 0x86;
  buff[7] = 0x0f;
  buff[8] = 0x86;
  buff[9] = 0x0f;
  buff[10] = 0x86;
  buff[11] = 0x0f;

  return 12;
}

// 0x24-0x2e

// ?
byte reply0x2f(byte *buff) {
  buff[0] = 49;
  buff[1] = 90;
  buff[2] = 74;
  buff[3] = 51;
  buff[4] = 74;
  buff[5] = 49;
  buff[6] = 49;
  buff[7] = 77;
  buff[8] = 49;
  buff[9] = 50;
  buff[10] = 88;

  return 11;
}

byte reply0x30(byte *buff) {
  buff[0] = 112;
  buff[1] = 156;
  buff[2] = 191;
  buff[3] = 25;
  buff[4] = 132;
  buff[5] = 74;
  buff[6] = 151;
  buff[7] = 0;
  buff[8] = 11;
  buff[9] = 0;

  return 10;
}

// 0x31-0x34

// ?
byte reply0x35(byte *buff) {
  buff[0] = 64;
  buff[1] = 0;

  return 2;
}

// 0x36

// ?
byte reply0x37(byte *buff) {
  buff[0] = 4;
  buff[1] = 0;
  buff[2] = 61;
  buff[3] = 94;
  buff[4] = 97;
  buff[5] = 1;
  buff[6] = 64;
  buff[7] = 1;

  return 8;
}

// 0x38-0x3a

byte reply0x3b(byte *buff) {
  buff[0] = 135;
  buff[1] = 11;

  return 2;
}

byte reply0x3c(byte *buff) {
  buff[0] = 76;
  buff[1] = 101;
  buff[2] = 110;
  buff[3] = 111;
  buff[4] = 118;
  buff[5] = 111;
  buff[6] = 32;
  buff[7] = 74;
  buff[8] = 97;
  buff[9] = 112;
  buff[10] = 97;
  buff[11] = 110;
  buff[12] = 145;
  buff[13] = 46;
  buff[14] = 93;
  buff[15] = 230;

  return 16;
}

byte reply0x3d(byte *buff) {
  buff[0] = 136;
  buff[1] = 11;

  return 2;
}

byte reply0x3e(byte *buff) {
  buff[0] = 1;
  buff[1] = 0;

  return 2;
}

byte reply0x3f(byte *buff) {
  buff[0] = 47;
  buff[1] = 79;

  return 2;
}


// Store a mapping of bytes to functions
// index 0 is used to reply to byte command 0, index 1 is used to reply to byte command 1, etc.
// NULL values are functions that are commands that are not used or have not been implemented
// See https://www.nxp.com/docs/en/application-note/AN4471.pdf for more information about what each command does

// Each of these functions will write to the global buffer and return the amount of bytes written
byte (* funMap [])(byte*) = {
  reply0x00,
  reply0x01,
  reply0x02,
  reply0x03,
  reply0x04,
  NULL,
  reply0x06,
  NULL,
  reply0x08,
  reply0x09,
  reply0x0a,
  reply0x0b,
  reply0x0c,
  reply0x0d,
  NULL,
  reply0x0f,
  reply0x10,
  reply0x11,
  reply0x12,
  reply0x13,
  reply0x14,
  reply0x15,
  reply0x16,
  reply0x17,
  reply0x18,
  reply0x19,
  reply0x1a,
  reply0x1b,
  reply0x1c,
  NULL,
  NULL,
  NULL,
  reply0x20,
  reply0x21,
  reply0x22,
  reply0x23,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  reply0x2f,
  reply0x30,
  NULL,
  NULL,
  NULL,
  NULL,
  reply0x35,
  NULL,
  reply0x37,
  NULL,
  NULL,
  NULL,
  reply0x3b,
  reply0x3c,
  reply0x3d,
  reply0x3e,
  reply0x3f
};

// Used to store replies to commands
byte buffGlobal[60];

void setup() {
  pinMode(PB3, INPUT);
  
  pinMode(PB4, OUTPUT);
  digitalWrite(PB4, LOW);
  
  command = 0;
  
  Wire.begin (0x0B);
  Wire.onReceive (receiveEvent);
  Wire.onRequest (requestEvent);
}

void loop() {
  unsigned long currentMillis = millis();
  
  delay(1);
}

// Read command send from laptop
void receiveEvent (uint8_t howMany)
{
  // Set command
  command = Wire.read();
  
  // Ignore bytes other than the first one. No commands currently require more than one byte
  for (int x = 0; x < howMany-1; x++) {
    byte a = Wire.read();
  }
}

// Write information and send it to laptop
void requestEvent () {
  // Look up the callback associated with the current command, NULL if no match is found
  smbusCallback callback = funMap[command];

  // No matching callback was found, return without further processing
  if (callback == null)
    return;

  // Call matching callback, which writes to the global buffer and returns the amount of bytes written
  int len = callback(buffGlobal);

  // Some commands require their length to be added. See needsLength function for a list of these commands
  // This length command is sent first, before all the data
  if (needsLength(command))
    Wire.write(len);
  
  // Write all bytes from the buffer
  for (int y = 0; y < len; ++y) {
    Wire.write(buffGlobal[y]);
  }

  // Generate and write the CRC. This is a checksum used to ensure communication works as intended
  Wire.write(genCRC(buffGlobal, len, command));
}
