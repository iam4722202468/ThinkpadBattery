# ThinkpadBattery
Open source Thinkpad T420 battery design

http://beta.aceparent.me/#/battery


## What is this?

This is a fully open source T420 laptop battery design. The design uses an attiny85, which can reply to the T420 motherboard's SMBUS requests.

## Setup

### Configurable Constants

- BATTERY_CAPACITY | Your battery capacity in mAH
- V_HIGH | The highest output voltage of your battery, normally 12.6v
- V_LOW | The cutoff for when the battery will stop working, normally around 10.8v

### Creating your own

Parts Needed
- Arduino Uno (for programming the attiny85)
- 12v Lithium-Ion battery pack
- 3S Lithium-Ion BMS
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


## Future Plans

### 3D Printable Case

When my current battery becomes unusable, I'm going to create a 3d printable model to house nine 21700 cells that can be attached to the laptop.
