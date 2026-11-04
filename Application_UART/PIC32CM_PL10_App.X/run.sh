# - @file: run.sh
# - @description: Shell script that demonstrates the CLI call to initiate a
# -               DFU using the pymdfu host tool
# -
# - @requirements:  python, pymdfu
# ----------------------------------------------------------------------------
pymdfu update -v debug --tool serial --port <Port Name> --baudrate 115200 --image PIC32CM_TestApp.img