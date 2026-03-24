REM - File: postBuild.bat
REM - Description: Batch script that can be executed in the MPLAB X post build
REM -               step to build the application binary image.
REM - 
REM - Requirements: python, pyfwimagebuilder, hexmate
REM - Arguments:
REM -     %1 - the INPUT_IMAGE_PATH argument is passed by the MPLAB post build step and it holds the output image path. (.hex or .elf normally)
REM -     %2 - the IS_DEBUG argument is passed by the MPLAB post build step to identify if the application is being built to a hex file (for production) or an elf file (for debugging).
REM ----------------------------------------------------------------------------
@echo off
REM - Create variables from given arguments
set INPUT_IMAGE_PATH=%1
set IS_DEBUG=%2
set OUTPUT_IMAGE_PATH="PL10_App_UART.img"
REM - Relative path to client config file
set CONFIG_FILE_PATH="..\..\Bootloader_UART\src\config\default\bootloader\configurations\bootloader_configuration.toml"

if %IS_DEBUG% == false (
    REM - Fill the empty application data
    hexmate r0-FFFFFFFF,%INPUT_IMAGE_PATH% -O%INPUT_IMAGE_PATH% -FILL=w2:0xFFFF@0xC002000:0xC00FFFB -format=inhx32

    REM - Calculate the CRC32 over the application space 
    hexmate %INPUT_IMAGE_PATH% -O%INPUT_IMAGE_PATH% +-CK=C002000-C00FFFB@C00FFFC+FFFFFFFFg-5w-4p04C11DB7 -format=inhx32
    
    REM - Build the application binary
    pyfwimagebuilder build -i %INPUT_IMAGE_PATH% -c %CONFIG_FILE_PATH% -o %OUTPUT_IMAGE_PATH%
) else (
    REM - When building in debug mode we cannot run hexmate operations
    echo "Warning - Post Build Process was Skipped."
    echo "Warning - Application is being built in Debug mode."
)