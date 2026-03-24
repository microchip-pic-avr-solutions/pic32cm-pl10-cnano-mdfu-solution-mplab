# - @file: run.sh
# - @description: Shell script that demonstrates the CLI call to initiate a
# -               DFU using the pymdfu host tool
# -
# - @requirements:  python, pymdfu
# ----------------------------------------------------------------------------
pymdfu update --tool mcp2221a --interface i2c -v debug --image PL10_App_I2C.img --clk-speed 50000 --address 32