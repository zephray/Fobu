Fobu
====

Fobu is a key fob sized open-source FPGA + ARM handheld device (formerly VerilogBoy Handheld). The intended usages are portable FPGA retro gaming system (FPGA-based implementation, ARM-based emulation, or both) and portable audio (both general format such as mp3, FLAC, etc. via ARM core and retro VGM such as FM, SSG, etc. via FPGA implementation) player. However, the architecture should allow other usages as well.

# Hardware

## Block Diagram

![Hardware-Architecture](https://github.com/zephray/Fobu/raw/master/assets/block_diagram.png)

## Photos

The photo of an Fobu r0.2 prototype:

![VBH-r0p2](https://github.com/zephray/Fobu/raw/master/assets/demo_vbh_r0p2.jpg)

# Software

The following third-party middlewares are used in the project:

 * Amazon FreeRTOS Operating System (MIT)
 * id3v2lib by Lorenzo Ruiz (BSD 2-Clause)
 * minimp3 by lieff (Public Domain)
 * FatFs by ChaN (See source file)
 * tjpgd by ChaN (See source file)

# License

If not otherwise specified, all the materials provided in this repository are licensed under MIT license.
