#!/bin/bash

# ============================================================================
# - File: postBuild
# - Description: Shell script that can be executed in the MPLAB X post build
# -               step to build the application binary image.

# Contents:
# - Normalizes flash contents
# - Hashes and signs application binary
# - Injects signature into application header
# - Generates final bootloader image

# Requirements:
# - python
# - pyfwimagebuilder
# - hexmate

# Command: .${_/_}postBuildSigning${ShExtension} ${ImageDir} ${ProjectName} ${IsDebug} $(MP_CC_DIR)
# Post-build script arguments
#      $1 = IMAGE DIRECTORY
#      $2 = PROJECT NAME
#      $3 = IsDebug
#      $4 = xc32 objcopy directory
# ============================================================================
IS_DEBUG=$3

INPUT_IMAGE_PATH="$1/$2.X.production.hex"

# Output firmware image
OUTPUT_IMAGE_PATH="PIC32CM_TestApp.img"

# Bootloader configuration (memory layout, signature offsets)
CONFIG_FILE_PATH="../../Bootloader_MIARB/src/config/default/bootloader/configurations/bootloader_configuration.toml"

# ----------------------------------------------------------------------
# Address Variables (multi-image layout - Slot A: 24KB)
# ----------------------------------------------------------------------
APP_START=0C004000
APP_END=0C009FBB
SIGNATURE_START=C009FBC
SIGNATURE_END=C009FFB
CRC_ADDR=C009FFC
FLASH_END=C009FFF


if [ "$IS_DEBUG" = "false" ]; then

# ----------------------------------------------------------------------------
# Extract application region used for verification/signature
# ----------------------------------------------------------------------------
hexmate r$APP_START-$APP_END,$INPUT_IMAGE_PATH -O$1/temp_original_copy.X.production.hex

# ----------------------------------------------------------------------------
# Fill application region for hash
# ----------------------------------------------------------------------------
hexmate r0-FFFFFFFF,$1/temp_original_copy.X.production.hex -O$1/temp_original_copy.X.production.hex -FILL=w2:0xFFFF@0x$APP_START:0x$APP_END -format=inhx32

# ----------------------------------------------------------------------------
# Convert application HEX to binary
# ----------------------------------------------------------------------------
"$4/bin/pic32c-objcopy" --remove-section=.gnu.sgstubs -I ihex -O binary $1/temp_original_copy.X.production.hex $1/$2.X.production.bin

# ----------------------------------------------------------------------------
# Generate SHA-256 hash of application binary
# ----------------------------------------------------------------------------
openssl dgst -sha256 -binary $1/$2.X.production.bin > $1/hash.bin

# ----------------------------------------------------------------------------
# Sign application binary (DER encoded signature)
# ----------------------------------------------------------------------------
openssl dgst -sha256 -sign ./private_key.pem $1/$2.X.production.bin > $1/$2.X.production.bin.signature.der

# ----------------------------------------------------------------------------
# Verify signature using public key (optional sanity check)
# ----------------------------------------------------------------------------
openssl dgst -sha256 -verify "public_key.pem" -signature $1/$2.X.production.bin.signature.der $1/$2.X.production.bin

# ----------------------------------------------------------------------------
# Convert DER signature to raw binary format (bootloader expects raw)
# ----------------------------------------------------------------------------
python "signature_der_to_bin.py" $1/$2.X.production.bin.signature.der $1/$2.X.production.bin.signature.bin

# ----------------------------------------------------------------------------
# Convert raw signature binary to HEX
# ----------------------------------------------------------------------------
"$4/bin/pic32c-objcopy" --remove-section=.gnu.sgstubs -I binary -O ihex $1/$2.X.production.bin.signature.bin $1/$2.X.production.bin.signature.hex

# ----------------------------------------------------------------------------
# Merge signature into application header
# ----------------------------------------------------------------------------
hexmate r0-3Fs$SIGNATURE_START,$1/$2.X.production.bin.signature.hex r$APP_START-$APP_END,$INPUT_IMAGE_PATH r$CRC_ADDR-$FLASH_END,$INPUT_IMAGE_PATH -O$1/combined.hex

# ----------------------------------------------------------------------------
# Final flash fill and enforce INHX32 format
# ----------------------------------------------------------------------------
hexmate r0-FFFFFFFF,$1/combined.hex -O$INPUT_IMAGE_PATH -FILL=w2:0xFFFF@0x$APP_START:0x$FLASH_END -format=inhx32

# ----------------------------------------------------------------------------
# Calculate and store the CRC32 Hash
# ----------------------------------------------------------------------------
hexmate $INPUT_IMAGE_PATH -O$INPUT_IMAGE_PATH +-CK=$APP_START-$SIGNATURE_END@$CRC_ADDR+FFFFFFFFg-5w-4p04C11DB7 -format=inhx32

# ----------------------------------------------------------------------------
# Build final bootloader-compatible image
# ---------------------------------------------------------------------------
pyfwimagebuilder build -i $INPUT_IMAGE_PATH -c $CONFIG_FILE_PATH -o $OUTPUT_IMAGE_PATH

# ----------------------------------------------------------------------------
# Delete generated files
# ---------------------------------------------------------------------------
rm $1/temp_original_copy.X.production.hex
rm $1/$2.X.production.bin.signature.der
rm $1/$2.X.production.bin.signature.bin
rm $1/$2.X.production.bin.signature.hex
rm $1/$2.X.production.bin
rm $1/combined.hex
rm $1/hash.bin


else
    # - When building in debug mode we cannot run hexmate operations
    echo "Warning - Post Build Process was Skipped."
    echo "Warning - Application is being built in Debug mode."
fi
