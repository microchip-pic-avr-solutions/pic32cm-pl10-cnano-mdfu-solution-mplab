REM - @file: run.bat
REM - @description: Batch script that demonstrates the CLI call to initiate a
REM -               DFU using the pymdfu host tool
REM -
REM - @requirements:  python, pymdfu
REM ----------------------------------------------------------------------------
pymdfu update --tool mcp2221a --interface i2c -v debug --image PL10_App_I2C.img --clk-speed 50000 --address 32