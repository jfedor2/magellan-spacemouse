# RS-232 Magellan/SpaceMouse with modern software

![Magellan/SpaceMouse connected to a Raspberry Pi Pico](magellan.jpg)

This project lets you use an old serial Magellan/SpaceMouse controller with modern software on modern operating systems. It simulates a 3DConnexion SpaceMouse Compact, so it can be used with software like Fusion 360, 3ds Max, SolidWorks, Inventor, Maya and many others. No special software is required on the computer, apart from 3DxWare. From the computer's point of view, your old Magellan will look like a real SpaceMouse Compact connected over USB.

To make it work you will need:

- Raspberry Pi Pico
- [Pololu 23201a Serial Adapter](https://www.pololu.com/product/126)
- null modem adapter and DB9 gender changer (either as two separate adapters or one that does both)
- breadboard and some jumper wires

Make the following connections between the Pico and the serial adapter:

| Pico | serial adapter |
| -----: | ------ |
| 3V3 (pin 36) | VCC |
| GND (pin 23) | GND |
| GPIO20 (pin 26) | RX |
| GPIO21 (pin 27) | TX |
| GPIO26 (pin 31) | RTS |
| GPIO27 (pin 32) | CTS |

Flash the Pico with the [magellan.uf2](magellan.uf2) firmware the usual way: hold the BOOTSEL button while connecting the board to the computer, then copy the UF2 file to the USB drive that shows up.

Install 3DxWare on your computer and enjoy.

Note that since we're simulating a SpaceMouse Compact, which only has two buttons, only two of the Magellan's many buttons are passed through.

## How to compile the firmware

```
git clone https://github.com/jfedor2/magellan-spacemouse.git
cd magellan-spacemouse
git submodule update --init
mkdir build
cd build
cmake ..
make
```
