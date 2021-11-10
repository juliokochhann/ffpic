# FFPIC

FFPIC is an open-source framework for 8-bit PIC microcontrollers.  
It strives to be minimalist and comprehensive while still powerful and flexible.  
This is an alpha release.  

## How to build

`xc8-cc @build.xc8 examples/basics/blink.c -mcpu=16F628A -o build/ffpic_project.hex`

## How to program

`/opt/microchip/mplabx/v5.50/sys/java/zulu8.40.0.25-ca-fx-jre8.0.222-linux_x64/bin/java -jar /opt/microchip/mplabx/v5.50/mplab_platform/mplab_ipe/ipecmd.jar -TPPK3 -P16F628A -F"./build/ffpic_project.hex" -M -OL -W4.5`

