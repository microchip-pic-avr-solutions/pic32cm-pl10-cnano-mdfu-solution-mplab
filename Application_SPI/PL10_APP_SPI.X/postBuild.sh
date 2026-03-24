# - File: postBuild.sh
# - Description: Shell script that can be executed in the MPLAB X post build
# -               step to build the application binary image.
# - 
# - Requirements: python, pyfwimagebuilder, hexmate
# - Arguments:
# -     $1 - the INPUT_IMAGE_PATH argument is passed by the MPLAB post build step and it holds the output image path. (.hex or .elf normally)
# -     $2 - the IS_DEBUG argument is passed by the MPLAB post build step to identify if the application is being built to a hex file (for production) or an elf file (for debugging).
# ----------------------------------------------------------------------------

# - Create variables from given script arguments
INPUT_IMAGE_PATH=$1
IS_DEBUG=$2
OUTPUT_IMAGE_PATH="PL10_App_SPI.img"
# - Relative path to client config file
CONFIG_FILE_PATH="../../Bootloader_SPI/src/config/default/bootloader/configurations/bootloader_configuration.toml"

if [ "$IS_DEBUG" = false ]; then
    # - Fill the empty application data
    hexmate r0-FFFFFFFF,$INPUT_IMAGE_PATH -O$INPUT_IMAGE_PATH -FILL=w2:0xFFFF@0xC002000:0xC00FFFF -format=inhx32

    # - Calculate the CRC32 over the application space 
    hexmate $INPUT_IMAGE_PATH -O$INPUT_IMAGE_PATH +-CK=C002000-C00FFFB@C00FFFC+FFFFFFFFg-5w-4p04C11DB7 -format=inhx32

    # - Build the application binary
    pyfwimagebuilder build -i $INPUT_IMAGE_PATH -c $CONFIG_FILE_PATH -o $OUTPUT_IMAGE_PATH
else
    # - When building in debug mode we cannot run hexmate operations
    echo "Warning - Post Build Process was Skipped."
    echo "Warning - Application is being built in Debug mode."
fi