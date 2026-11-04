REM - @file: run.bat
REM - @description: Batch script that demonstrates the CLI call to initiate a
REM -               DFU using the pymdfu host tool
REM -
REM - @requirements:  python, pymdfu
REM ----------------------------------------------------------------------------

pymdfu update --tool mcp2210 --image PIC32CM_TestApp.img --clk-speed 500000 --chip-select <SS PIN NUMBER> -v debug