# - @file: run.sh
# - @description: Shell script that demonstrates the CLI call to initiate a
# -               DFU using the pymdfu host tool
# -
# - @requirements:  python, pymdfu
# ----------------------------------------------------------------------------

pymdfu update --tool mcp2210 --image PIC32CM_TestApp.img --clk-speed 500000 --chip-select <SS PIN NUMBER> -v debug