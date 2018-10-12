# Team Lychee
## Introduction
This repo contains the firmware code for team tbd  
Platform: STM32F303 using an ARM Cortex M-4  
IDE: Eclipse  
Current Maintainer: Andrew Obatake  

## Goal
Create a environmental sensing embedded device that both collect data and pass along data from other devices

## Software Goals
- Create proper documentation for code and tutorials
- Create an easy way to add a new board to project with build definitions
- Synchronize Xbee to properly relay and transmit data
- Minimize Power Consumption through device and microcontroller sleeps

## Devices
- BME280
- SP-212
- Xbee Pro S2C/S2B

## ANDREW'S NOTES:

### General:
- lib folder is for external libraries; you need to add the includes into the project properties

### BME280:
- I2C doesn't work yet, pls remove if this changes

### SP-212:
- SP-215 not used since it needs 5.5V to be powered
- SP-212 will not show any voltage with room lights; Need to use the Powered Lamp.
- White(Red) -> Input Power;Green(Black) -> Sensor Signal;Clear(None) -> GND

WIP
===

Documentation/Tutorial
======================

## How to start programming a STM32 board

### Helpful Links/Downloads:
- [Setting up Eclipse to build STM32 files](https://www.carminenoviello.com/2014/12/28/setting-gcceclipse-toolchain-stm32nucleo-part-1/)
- [ST-Link](https://www.st.com/en/development-tools/stsw-link004.html)
- [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)

###Certain Project Properties need to defined for build to work
- C/C++ Build -> Settings -> Target Processor: Check Thumb interwork, Float ABI = Hard, FPU Type = fpv4-sp-16
- If you add a new source file make sure all the includes point to your new files

To add a new source folder: Project -> Properties -> C/C++ General -> Paths and Symbols -> Source Location -> Add Folder

