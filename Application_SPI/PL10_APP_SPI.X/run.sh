# - @file: run.sh
# - @description: Shell script that demonstrates the CLI call to initiate a
# -               DFU using the pymdfu host tool
# -
# - @requirements:  python, pymdfu
# ----------------------------------------------------------------------------

pymdfu update --tool mcp2210 --image PL10_App_SPI.img --clk-speed 500000 --chip-select 1 -v debug