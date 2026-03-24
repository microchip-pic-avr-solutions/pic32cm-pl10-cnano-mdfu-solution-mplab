# Microchip Firmware Update Image Specification for 32-bit Devices

Specification version: 1.0.0

## Overview
This document defines the application file format for 32-bit devices.

## General Rules
- A TOML file will be used to communicate the configurations needed by the formatter tool (pyfwimagebuilder)
- Every block will remain the same size and the size will be defined by the WRITE_BLOCK_SIZE given by the configuration file and the block header data used.
- The block payload size should equal the WRITE_BLOCK_SIZE.
- Header data is understood as little endian.

## Block Header
|Block Length|Block Type|
|--------    |-------   |
|2 byte      |1 byte    |

### Block Length
This value defines the number of bytes in each block, including the length of this field.

### Block Type
This value defines the type of data housed in the block.

|Metadata Block   |Flash Block   |EEPROM Block   |
|--------         |-------       |-----------    |
|   0x01          |   0x02       |  0x03         |
|[Metadata Block](#Metadata-Block)|[Flash Block](#Flash-Block)|[EEPROM Block](#EEPROM-Block)|

## Metadata Block
The metadata block is used as a form of pre-image validation. The metadata block will contain information that the bootloader must process and return a success code for otherwise the rest of the update is aborted.

*Note: Each metadata entry will be little endian*

|Block Header |Image Format Version|Device ID |Write Size (in bytes) |App Start Address |
|--------     |-------             |-------   |-----------           |-----------       |
|3 bytes      |3 bytes             |4 bytes   |2 bytes               |4 bytes           |

### Image Format Version
3 Byte Sematic Versioning
#### Versioning Rules
1. A major revision of the image format means that past versions of the bootloader handler will be unable to understand the new data orientation because of a few different reasons:
- A value in the image format changed sizes. *Ex. Data Length being changed from 16bit to 8bit would break the version.* 
- One or more values in the image format changed locations in the payload. *Ex. Data Length is moved to byte 2 and 3 (after the block type).*
- Anytime the metadata changes. This is because we always want to validate the new information and any past versions of the file format will not be able to verify new versions of the metadata block.
2. A minor revision of the image format means that the updated version added additional information that is optional into one or more of the operational blocks but **did not** change the size or orientation of the previous revisions format. For example, a bootloader that was originally designed to work on version 1.1 of the image format should also be able to support loading a image that is using version 1.0 of the image format. Since no information that was previously understood changed locations or sizes, we can still fully understand the format given in 1.0. The new optional features simply will not be used. 
3. A patch version in the file format would indicate that there was some error in documentation that created problems but the bootloader functionality and file data did not change.

### Device ID
This value will define the ID of the device that this image is meant to be booted with.

### Write Size
This value will define the maximum size **in bytes** that the bootloader can write at one time.

### App Start Address
This value will define the start address of the image that will be booted.

## Flash or EEPROM Write Block
Operational write blocks are blocks that should be passed to the bootloader for processing.

|Block Header |Block Start Address |Data Payload                |
|--------     |-----------         |-------                     |
|3 bytes      |4 bytes             |WRITE_BLOCK_SIZE bytes      |

### Start Address
This value will define the start address of the data held in this block.

## Configuration TOML Overview
In order for the image builder tool to understand how it can create these blocks and headers, we must provide some form of input to the tool. The agreed upon format that we will use to communicate the bootloader configuration to the image builder tool is through a TOML file. This TOML file will contain information needed by the image builder tool to parse over the hex file and create the necessary blocks in the output image file. TOML configuration parts will be described below:

### Bootloader Configurations

|Configuration Name         |Description |
|--------                   |-------     |
|ARCH                       |This string defined the architecture that was configured in the bootloader. |
|IMAGE_FORMAT_VERSION       |Semantic version value of the image format given in string format. e.g. "1.0.0"|
|DEVICE_ID                  |32-bit device id value to be used in the metadata block. |
|WRITE_BLOCK_SIZE           |The size that the bootloader is able to write **in bytes**.|
|FLASH_START                |This address defines the first address that we are wanting to include in the output binary image.|
|FLASH_END                  |This address defines the address that we will stop the update at. |
|EEPROM_START               |This address defines the first address of the EEPROM range. |
|EEPROM_END                 |This address defines the end of the EEPROM range. |
|CONFIG_START               |This address defined the start of the configuration bits / FUSEs range. |
|CONFIG_END                 |This address defined the end of the configuration bits / FUSEs range. |