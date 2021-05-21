# ThinkpadBattery
Open source Thinkpad battery design

## What is this?

This is a fully open source laptop battery design. The design uses an attiny85, which can reply to the T420 motherboard's SMBUS requests.

## Setup

### Configurable Constants

- BATTERY_CAPACITY | Your battery capacity in mAH
- V_HIGH | The highest output voltage of your battery, normally 12.6v
- V_LOW | The cutoff for when the battery will stop working, normally around 10.8v

### Creating your own

Parts Needed
- Arduino Uno/Mega  (for programming the attiny85, Mega needs different pin assignment)
- 12v Lithium-Ion battery pack
- 3S Lithium-Ion BMS (it might be possible to use the existing bms if specification is available but communication needs to be implemented)
- Components from schematic
- PCB from schematic


Once you have all these parts, assemble the pcb and attach a BMS to your battery pack. Solder the 12v battery output/input to the large pads on the pcb, then program the attiny85 with the included ino file. The output pins at the bottom of the PCB are a 1-1 mapping of the motherboard pin input.

### Debugging

- The laptop won't supply power to the board unless it detects there's a battery attached, meaning if you plug the board in to the battery without having an external battery to power it, it won't work.

### Libraries

Use the ATTinyCore for compiling. Without it, Wire.h won't work.


## Limitations

### Voltage Reading / Remaining battery

Currently remaining battery %'s aren't exact because I'm assuming there is a linear coorelation between voltage and capacity (Which is wrong). This is probably fixable using a battery gas gauge, I'll have to investiage more.

### MCU Power Consumption

By design, the MCU will always be on as long as a battery is connected to it. This can cause the battery to slowly run out of power if it isn't connected to a laptop. A potential fix could be to implement a low power mode for the attiny, or have a seperate disconnect switch for the battery power on the battery pack itself.


### 3D Printable Case for T420 only

The case for the cells has been completed. The case model and stl files are included in /model


## Future Plans

iam4722202468 - Design and manufacture a PCB with current,voltage and battery capacity measuring capabilities, an easily programmable microcontroller, and a 3s balanced charger

pj1976 - Find a bms that would fit, or try to talk with bq29312pw that was in the original pack

## Credits

iam4722202468 - Initial work, T420 9 cell model

pj1976 - Added support for R50
