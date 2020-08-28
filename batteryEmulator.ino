
#include <Wire.h>

// #include <stdio.h>
// #include <SoftwareSerial.h>
// SoftwareSerial Monitor(5, 4);

#define BATTERY_MODEL "LNV-Version 2"
#define BATTERY_VENDOR "HACKED"
#define CHARGE_VOLTAGE 12600
#define BATTERY_VOLTAGE 10800
#define SERIAL 420

#define V_HIGH 12.6
#define V_LOW 10.6

// mAh, uses BATTERY_VOLTAGE when calculating Wh
#define BATTERY_CAPACITY 10000
#define BATTERY_CAPACITY_DESIGN 10000

byte command;

// 0 - Charging
// 1 - Battery Powered
int mode = 1;

struct CommandReply {
  byte replyTo;
  byte (*reply)(byte*);
};

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

// Write to buff, return length
byte reply0x1A(byte *buff) {
  buff[0] = 49;
  return 1;
}

byte reply0x00(byte *buff) {
  buff[0] = 24;
  buff[1] = 0;
  return 2;
}

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

byte reply0x1B(byte *buff) {
  buff[0] = 156;
  buff[1] = 61;
  return 2;
}

byte reply0x1C(byte *buff) {
  int lower, higher;
  
  splitNum(SERIAL, &lower, &higher);
  buff[0] = lower;
  buff[1] = higher;
  
  return 2;
}

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

byte reply0x03(byte *buff) {
  buff[0] = 132;
  buff[1] = 128;

  return 2;
}

byte reply0x21(byte *buff) {
  char *battery_model = BATTERY_MODEL;

  for (int x = 0; x < strlen(battery_model); ++x) {
    buff[x] = battery_model[x];
  }

  return strlen(battery_model);
}

byte reply0x22(byte *buff) {
  buff[0] = 76;
  buff[1] = 73;
  buff[2] = 79;
  buff[3] = 78;

  return 4;
}

byte reply0x35(byte *buff) {
  buff[0] = 64;
  buff[1] = 0;

  return 2;
}

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

byte reply0x2F(byte *buff) {
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

byte reply0x3C(byte *buff) {
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

byte reply0x3E(byte *buff) {
  buff[0] = 1;
  buff[1] = 0;

  return 2;
}

byte reply0x3F(byte *buff) {
  buff[0] = 47;
  buff[1] = 79;

  return 2;
}

byte reply0x16(byte *buff) {
  buff[0] = 224;
  buff[1] = 192;

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

byte reply0x08(byte *buff) {
  buff[0] = 137;
  buff[1] = 11;

  return 2;
}

byte reply0x3B(byte *buff) {
  buff[0] = 135;
  buff[1] = 11;

  return 2;
}

byte reply0x09(byte *buff) {
  buff[0] = 79;
  buff[1] = 48;

  return 2;
}

byte reply0x0F(byte *buff) {
  int lower, higher;

  float r1 = 9.1;
  float r2 = 3.0;

  float sensorLow = V_LOW * (r2/(r1+r2));
  float sensorHigh = V_HIGH * (r2/(r1+r2));

  // Assume linear voltage -> battery capacity coorelation (this isn't perfect)
  float m = 1/(sensorHigh - sensorLow);
  float b = -sensorLow*m;

  float voltageIn = analogRead(3) * (3.33 / 1023.0);
  int batteryVoltage = (m*voltageIn + b)*BATTERY_CAPACITY;

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

byte reply0x0A(byte *buff) {
  if (mode == 0) {
    buff[0] = 0;
    buff[1] = 0;
  } else {
    buff[0] = 0xF8;
    buff[1] = 0xFC;
  }

  return 2;
}

byte reply0x11(byte *buff) {
  buff[0] = 60;
  buff[1] = 0;

  return 2;
}

byte reply0x0B(byte *buff) {
  if (mode == 0) {
    buff[0] = 0;
    buff[1] = 0;
  } else {
    buff[0] = 0xF6;
    buff[1] = 0xFC;
  }

  return 2;
}

byte reply0x13(byte *buff) {
  buff[0] = 255;
  buff[1] = 255;

  return 2;
}

byte reply0x12(byte *buff) {
  buff[0] = 255;
  buff[1] = 255;

  return 2;
}

byte reply0x17(byte *buff) {
  buff[0] = 20;
  buff[1] = 5;

  return 2;
}

byte reply0x0C(byte *buff) {
  buff[0] = 0;
  buff[1] = 0;

  return 2;
}

byte reply0x0D(byte *buff) {
  buff[0] = 245;
  buff[1] = 155;

  return 2;
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

byte reply0x3D(byte *buff) {
  buff[0] = 136;
  buff[1] = 11;

  return 2;
}

byte reply0x06(byte *buff) {
  buff[0] = 100;
  buff[1] = 0;

  return 2;
}

byte (* funMap [])(byte*) = {
  reply0x00,
  NULL,
  NULL,
  reply0x03,
  NULL,
  NULL,
  reply0x06,
  NULL,
  reply0x08,
  reply0x09,
  reply0x0A,
  reply0x0B,
  reply0x0C,
  reply0x0D,
  NULL,
  reply0x0F,
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
  reply0x1A,
  reply0x1B,
  reply0x1C,
  NULL,
  NULL,
  NULL,
  reply0x20,
  reply0x21,
  reply0x22,
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
  NULL,
  reply0x2F,
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
  reply0x3B,
  reply0x3C,
  reply0x3D,
  reply0x3E,
  reply0x3F
};
  
CommandReply **commandList;
int commandCount = 0;

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
  
  delay(100);
}

void receiveEvent (uint8_t howMany)
{
  command = Wire.read();

  for (int x = 0; x < howMany-1; x++)
    Wire.read();
}

// needs byte length
// 0x20, 0x21, 0x22, 0x23, 0x30, 0x3C, 0x37, 0x2F, 

void requestEvent () {
  int len = funMap[command](buffGlobal);

  if (needsLength(command))
    Wire.write(len);
      
  for (int y = 0; y < len; ++y) {
    Wire.write(buffGlobal[y]);
  }
    
  Wire.write(genCRC(buffGlobal, len, command));
}
