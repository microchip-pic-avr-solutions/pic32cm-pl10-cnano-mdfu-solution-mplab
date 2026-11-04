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
REM - pyfwimagebuilde
REM - hexmate

REM Command: .${_/_}postBuildSigning${ShExtension} ${ImageDir} ${ProjectName} ${IsDebug} $(MP_CC_DIR)
REM Post-build script arguments
REM      %1 = IMAGE DIRECTORY
REM      %2 = PROJECT NAME
REM      %3 = IsDebug
REM      %4 = xc32 objcopy directory
REM ============================================================================
set IS_DEBUG=%3

set INPUT_IMAGE_PATH=%1\%2.X.production.hex

REM Output firmware image
set OUTPUT_IMAGE_PATH="PIC32CM_TestApp.img"

REM Bootloader configuration (memory layout, signature offsets)
set CONFIG_FILE_PATH="..\..\Bootloader_MIARB\src\config\default\bootloader\configurations\bootloader_configuration.toml"

REM ----------------------------------------------------------------------
REM Address Variables (multi-image layout - Slot A: 24KB)
REM ----------------------------------------------------------------------
set APP_START=0C004000
set APP_END=0C009FBB
set SIGNATURE_START=C009FBC
set SIGNATURE_END=C009FFB
set CRC_ADDR=C009FFC
set FLASH_END=C009FFF


if %IS_DEBUG% == false (

REM ----------------------------------------------------------------------------
REM Extract application region used for verification/signature
REM ----------------------------------------------------------------------------
hexmate r%APP_START%-%APP_END%,%INPUT_IMAGE_PATH% -O%1\temp_original_copy.X.production.hex

REM ----------------------------------------------------------------------------
REM Fill application region for hash
REM ----------------------------------------------------------------------------
hexmate r0-FFFFFFFF,%1\temp_original_copy.X.production.hex -O%1\temp_original_copy.X.production.hex -FILL=w2:0xFFFF@0x%APP_START%:0x%APP_END% -format=inhx32

REM ----------------------------------------------------------------------------
REM Convert application HEX to binary
REM ----------------------------------------------------------------------------
"%~4\bin\pic32c-objcopy.exe" --remove-section=.gnu.sgstubs -I ihex -O binary %1\temp_original_copy.X.production.hex %1\%2.X.production.bin

REM ----------------------------------------------------------------------------
REM Generate SHA-256 hash of application binary
REM ----------------------------------------------------------------------------
openssl dgst -sha256 -binary %1\%2.X.production.bin > %1\hash.bin

REM ----------------------------------------------------------------------------
REM Sign application binary (DER encoded signature)
REM ----------------------------------------------------------------------------
openssl dgst -sha256 -sign .\private_key.pem %1\%2.X.production.bin > %1\%2.X.production.bin.signature.der

REM ----------------------------------------------------------------------------
REM Verify signature using public key (optional sanity check)
REM ----------------------------------------------------------------------------
openssl dgst -sha256 -verify "public_key.pem" -signature %1\%2.X.production.bin.signature.der %1\%2.X.production.bin

REM ----------------------------------------------------------------------------
REM Convert DER signature to raw binary format (bootloader expects raw)
REM ----------------------------------------------------------------------------
python "signature_der_to_bin.py" %1\%2.X.production.bin.signature.der %1\%2.X.production.bin.signature.bin

REM ----------------------------------------------------------------------------
REM Convert raw signature binary to HEX
REM ----------------------------------------------------------------------------
"%~4\bin\pic32c-objcopy.exe" --remove-section=.gnu.sgstubs -I binary -O ihex %1\%2.X.production.bin.signature.bin %1\%2.X.production.bin.signature.hex

REM ----------------------------------------------------------------------------
REM Merge signature into application header
REM ----------------------------------------------------------------------------
hexmate r0-3Fs%SIGNATURE_START%,%1\%2.X.production.bin.signature.hex r%APP_START%-%APP_END%,%INPUT_IMAGE_PATH% r%CRC_ADDR%-%FLASH_END%,%INPUT_IMAGE_PATH% -O%1\combined.hex

REM ----------------------------------------------------------------------------
REM Final flash fill and enforce INHX32 format
REM ----------------------------------------------------------------------------
hexmate r0-FFFFFFFF,%1\combined.hex -O%INPUT_IMAGE_PATH% -FILL=w2:0xFFFF@0x%APP_START%:0x%FLASH_END% -format=inhx32

REM ----------------------------------------------------------------------------
REM Calculate and store the CRC32 Hash
REM ----------------------------------------------------------------------------
hexmate %INPUT_IMAGE_PATH% -O%INPUT_IMAGE_PATH% +-CK=%APP_START%-%SIGNATURE_END%@%CRC_ADDR%+FFFFFFFFg-5w-4p04C11DB7 -format=inhx32
    
REM ----------------------------------------------------------------------------
REM Build final bootloader-compatible image
REM ---------------------------------------------------------------------------
pyfwimagebuilder build -i %INPUT_IMAGE_PATH% -c %CONFIG_FILE_PATH% -o %OUTPUT_IMAGE_PATH%

REM ----------------------------------------------------------------------------
REM Delete generated files
REM ---------------------------------------------------------------------------
del %1\temp_original_copy.X.production.hex
del %1\%2.X.production.bin.signature.der
del %1\%2.X.production.bin.signature.bin
del %1\%2.X.production.bin.signature.hex
del %1\%2.X.production.bin
del %1\combined.hex
del %1\hash.bin

) else (
    REM - When building in debug mode we cannot run hexmate operations
    echo "Warning - Post Build Process was Skipped."
    echo "Warning - Application is being built in Debug mode."
)