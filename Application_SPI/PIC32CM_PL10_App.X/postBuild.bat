@echo off

REM ============================================================================
REM - File: postBuild.bat
REM - Description: Batch script that can be executed in the MPLAB X post build
REM -               step to build the application binary image.

REM Contents:
REM - Normalizes flash contents
REM - Hashes and signs application binary
REM - Injects signature into application header
REM - Generates final bootloader image

REM Requirements: 
REM - python
REM - pyfwimagebuilder
REM - hexmate

REM Command: .${_/_}postBuild${ShExtension} ${ImageDir} ${ProjectName} ${IsDebug}
REM Post-build script arguments
REM      %1 = IMAGE DIRECTORY
REM      %2 = PROJECT NAME
REM      %3 = IsDebug     
REM ============================================================================
set IS_DEBUG=%3

set INPUT_IMAGE_PATH=%1\%2.X.production.hex

REM Output firmware image
set OUTPUT_IMAGE_PATH="PIC32CM_TestApp.img"

REM Bootloader configuration (memory layout, signature offsets)
set CONFIG_FILE_PATH="..\..\Bootloader_SPI\src\config\default\bootloader\configurations\bootloader_configuration.toml"

REM ----------------------------------------------------------------------
REM Address Variables (multi-image layout - Slot A: 24KB)
REM ----------------------------------------------------------------------
set APP_START=0C004000
set APP_END=C00FFFB
set CRC_ADDR=C00FFFC
set FLASH_END=C00FFFF

if %IS_DEBUG% == false (

REM ----------------------------------------------------------------------------
REM Final flash fill and enforce INHX32 format
REM ----------------------------------------------------------------------------
hexmate r0-FFFFFFFF,%INPUT_IMAGE_PATH% -O%INPUT_IMAGE_PATH% -FILL=w2:0xFFFF@0x%APP_START%:0x%FLASH_END% -format=inhx32

REM ----------------------------------------------------------------------------
REM Calculate and store the CRC32 Hash
REM ----------------------------------------------------------------------------
hexmate %INPUT_IMAGE_PATH% -O%INPUT_IMAGE_PATH% +-CK=%APP_START%-%APP_END%@%CRC_ADDR%+FFFFFFFFg-5w-4p04C11DB7 -format=inhx32
    
REM ----------------------------------------------------------------------------
REM Build final bootloader-compatible image
REM ---------------------------------------------------------------------------
pyfwimagebuilder build -i %INPUT_IMAGE_PATH% -c %CONFIG_FILE_PATH% -o %OUTPUT_IMAGE_PATH%

) else (
    REM - When building in debug mode we cannot run hexmate operations
    echo "Warning - Post Build Process was Skipped."
    echo "Warning - Application is being built in Debug mode."
)