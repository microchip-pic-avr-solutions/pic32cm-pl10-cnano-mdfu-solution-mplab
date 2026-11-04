#!/bin/bash

# ============================================================================
# - File: postBuild.sh
# - Description: Shell script that can be executed in the MPLAB X post build
# -               step to build the application binary image.

# Contents:
# - Normalizes flash contents
# - Calculates and stores the application CRC32
# - Generates final bootloader image

# Requirements:
# - python
# - pyfwimagebuilder
# - hexmate

# Command: .${_/_}postBuild${ShExtension} ${ImageDir} ${ProjectName} ${IsDebug}
# Post-build script arguments
#      $1 = IMAGE DIRECTORY
#      $2 = PROJECT NAME
#      $3 = IsDebug
# ============================================================================
IS_DEBUG=$3

INPUT_IMAGE_PATH="$1/$2.X.production.hex"

# Output firmware image
OUTPUT_IMAGE_PATH="PIC32CM_TestApp.img"

# Bootloader configuration (memory layout, signature offsets)
CONFIG_FILE_PATH="../../Bootloader_UART/src/config/default/bootloader/configurations/bootloader_configuration.toml"

# ----------------------------------------------------------------------
# Address Variables (multi-image layout - Slot A: 24KB)
# ----------------------------------------------------------------------
APP_START=0C004000
APP_END=C00FFFB
CRC_ADDR=C00FFFC
FLASH_END=C00FFFF

if [ "$IS_DEBUG" = "false" ]; then

# ----------------------------------------------------------------------------
# Final flash fill and enforce INHX32 format
# ----------------------------------------------------------------------------
hexmate r0-FFFFFFFF,$INPUT_IMAGE_PATH -O$INPUT_IMAGE_PATH -FILL=w2:0xFFFF@0x$APP_START:0x$FLASH_END -format=inhx32

# ----------------------------------------------------------------------------
# Calculate and store the CRC32 Hash
# ----------------------------------------------------------------------------
hexmate $INPUT_IMAGE_PATH -O$INPUT_IMAGE_PATH +-CK=$APP_START-$APP_END@$CRC_ADDR+FFFFFFFFg-5w-4p04C11DB7 -format=inhx32

# ----------------------------------------------------------------------------
# Build final bootloader-compatible image
# ---------------------------------------------------------------------------
pyfwimagebuilder build -i $INPUT_IMAGE_PATH -c $CONFIG_FILE_PATH -o $OUTPUT_IMAGE_PATH

else
    # - When building in debug mode we cannot run hexmate operations
    echo "Warning - Post Build Process was Skipped."
    echo "Warning - Application is being built in Debug mode."
fi
