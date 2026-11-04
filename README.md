![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)

# Microchip Device Firmware Update (MDFU) Bootloader Solution for PIC32CM-PL10 Curiosity Nano Evaluation Kit

## Project Overview

This repository provides an optimized MDFU bootloader client for the PIC32CM-PL10 Curiosity Nano. It shows firmware update workflows using the MDFU protocol over Universal Asynchronous Receiver/Transmitter (UART), Serial Peripheral Interface (SPI), and Inter-Integrated Circuit (I<sup>2</sup>C) interfaces. All code is standalone, containing required drivers generated via MPLAB® Harmony 3 but Harmony is not mandatory for operation.

- [Microchip  32-bit Microcontrollers (MCUs)](https://www.microchip.com/design-centers/32-bit)
- [Microchip 32-bit MPUs](https://www.microchip.com/design-centers/32-bit-mpus)
- [MPLAB® X IDE](https://www.microchip.com/mplab/mplab-x-ide)
- [MPLAB® Harmony v3](https://www.microchip.com/mplab/mplab-harmony)

**Included Projects**
- MDFU Bootloader over UART, SPI, and I<sup>2</sup>C
- Example test applications (LED blink, console output) for each interface

## Folder Structure and Contents

| Folder            | Description                                                   |
| ----------------- | ------------------------------------------------------------- |
| Bootloader_UART   | MDFU client with UART communication interface                 |
| Application_UART  | Example app for UART bootloader                               |
| Bootloader_SPI    | MDFU client with SPI communication interface                  |
| Application_SPI   | Example app for SPI bootloader                                |
| Bootloader_I2C    | MDFU client with I<sup>2</sup>C communication interface       |
| Application_I2C   | Example app for I<sup>2</sup>C bootloader                     |
| Bootloader_Secure | MDFU client with signature and hash verification schemes      |
| Application_Secure| Example app that produces a signed image                      |
| Bootloader_MIARB  | MDFU client with secure features, multi-image and anti-rollback support|
| Application_MIARB | Example app for multi-image support                           |
| docs              | API documentation, Doxygen configs                            |

---
## Related Documentation
For additional information, refer to the following resources:

- [Microchip Device Firmware Update (MDFU) Protocol Specification 1.0.0](https://onlinedocs.microchip.com/oxy/GUID-58904FDA-338A-488F-A88D-766D29B27E37-en-US-1/index.html)
- [PIC32CM PL10 Family Data sheet](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/PIC32CM6408PL10-028-032-048-064-DataSheet-DS40002667.pdf)
- [Microchip Firmware Update Image Specification for 32-bit Devices](./docs/FirmwareUpdateFileFormat.md)

---

## Software and Hardware Requirements

### Software Requirements

- [MPLAB® X IDE](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)
- [XC32 C/C++ Compiler v5.10 or newer](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers/xc32)
- [pymdfu v2.5.1.9 or newer](https://pypi.org/project/pymdfu/)
- [pyfwimagebuilder v1.3.0.16 or newer](https://pypi.org/project/pyfwimagebuilder/)

### Hardware Requirements

- [PIC32CM PL10 Curiosity Nano Evaluation Kit](https://www.microchip.com/en-us/development-tool/ev10p22a)

### Pin Configuration

#### UART Interface (CDC)
| Signal | Pin  | Description                    |
|--------|------|--------------------------------|
| TX     | PB00 | UART Transmit                  |
| RX     | PB01 | UART Receive                   |

#### SPI Interface
| Signal | Pin  | Description                    |
|--------|------|--------------------------------|
| MOSI   | PA04 | SPI Host Out Client In        |
| MISO   | PA07 | SPI Host In Client Out        |
| SCK    | PA05 | SPI Clock                      |
| SS     | PA06 | SPI Client Select (Chip Select) |

#### I²C Interface
| Signal | Pin  | Description                    |
|--------|------|--------------------------------|
| SDA    | PA00 | I²C Data (Address: 0x20/32)    |
| SCL    | PA01 | I²C Clock                      |

#### Common Pins
| Signal | Pin  | Description                    |
|--------|------|--------------------------------|
| LED0   | PB02 | Status LED (Bootloader/App)    |
| SW0    | PB03 | User Button (Bootloader Entry) |

---

## Bootloader and Application Features

**Bootloader Features (UART/SPI/I<sup>2</sup>C)**
- MDFU protocol file transfer (UART, SPI, and I<sup>2</sup>C) 
- CRC-32 via the Direct Memory Access (DMA) peripheral
- Software re-entry via the RAM region
- Button press detection at startup to force bootloader entry
- LED status indicator (LED ON = Bootloader mode, LED blinking = application running)

> **Note:** This content does not require MPLAB Harmony 3 and uses a custom start-up code and linker script that are not generated by Harmony. Ensure this logic is not overwritten if the user intends to generate new code using Harmony.

**Application Features (UART/SPI/I<sup>2</sup>C)**
- LED blink using timer interrupt (0.5s toggle period)
- Bootloader mode re-entry by switch press with system reset
- 3-second startup delay for initialization
- Default application image for direct flashing (`PL10_App_UART.img`, `PL10_App_SPI.img`, or `PL10_App_I2C.img`)

> **Note:** A default application image has been generated and included in the repo for testing purposes. If the user does not intend to build the image using the steps below, the default test image can be used for testing the client update logic.

--- 

## Getting Started and Operation

### General Steps
The following steps use the UART as an example, but the same procedures apply to all communication protocols available in this repository (I<sup>2</sup>C, SPI, Secure, etc.). If the UART is not being used, substitute the appropriate protocol folder path (i.e., Bootloader/I<sup>2</sup>C instead of Bootloader/UART) when opening the projects.

1. Open MPLAB X IDE.
2. Open the desired bootloader project (`/Bootloader_UART...`).
    - Open the bootloader project by navigating to _File>Open Project..._ and select the bootloader project from the file system navigator, `<repository path>/Bootloader_UART/<bootloader_project_name>.X`
3. Set bootloader project as main, clean and build the project, and program the device.
    - In the **Projects** tab, right click the Bootloader project folder and select Set as Main Project
    - From the **Projects** tab, right click again the Bootloader project folder and select Clean and Build
    - Right click the Bootloader project folder again and select Make and Program Device
    - The bootloader lights the on-board LED to indicate that it is running and ready to receive an image
4. **(Secure and MI_ARB projects only)** Generate an ECDSA key pair and provision the secure element with the public key before programming the bootloader.

    > **Important:** Secure and MI_ARB (Multi-Image, Anti-Rollback) solutions require an external secure element for ECDSA and SHA256 verification. Refer to the *Secure MPLAB Code Configurator (MCC) MDFU Client Library Provision Workflow Example* documentation for key pair generation ([section 1.1](https://onlinedocs.microchip.com/oxy/GUID-1D8916F8-A6DA-4CDD-9079-AEB87E9AE7B7-en-US-2/GUID-3882CF3C-97B4-4920-A943-E804B119C5E2.html)) and secure element provisioning ([section 1.2](https://onlinedocs.microchip.com/oxy/GUID-1D8916F8-A6DA-4CDD-9079-AEB87E9AE7B7-en-US-2/GUID-5ECE7345-2A0A-4D67-A7A0-F6FF695C0404.html)).

    This step does not apply to the UART, SPI, or I<sup>2</sup>C (non-secure) projects.

5. Open the example application project (`/Application_UART...`) and clean and build the project.
    - Open the application project by navigating to _File>Open Project..._ and select the application project from the file system navigator: `<repository path>/Application_UART/<application_project_name>.X`
    - Navigate to the Project Properties, select the **Building** tab, and enable the `Execute this line after build` option then, select "Ok"
    - From the **Projects** tab, right click the Application project folder again and select Clean and Build

6. Edit and run the update script for the user platform.
    - In the **Projects** pane, expand `PIC32CM_PL10_APP > Important Files` and open `run.bat` on Windows or `run.sh` on Mac or Linux
    - If using UART, update `<Port Name>` in the script to the correct port for the board. Note that the Secure and MI_ARB projects also communicate over UART.
    - If using SPI, the `<SS PIN NUMBER>` corresponds to the `GP` pin on the mcp2210
    - Right click the script and select Run

> **Note:** This process will execute the `pymdfu` update command through an MPLAB X console and print the output within IDE. If the user does not have access to the Python environment within MPLAB X, the user can copy the command from the script into any terminal with access to the `pymdfu` Python tool.

7. Test bootloader re-entry (optional). This confirms the application can hand control back to the bootloader and accept a second update.
    - Open `app.c` in the application project under the **Source Files** tab, locate the `APP_LED_COUNTER` macro, and change the value from `500` to `100`. The SysTick interrupt period is 1 ms, so this shortens the LED toggle period from 500 ms to 100 ms, making the new image easy to identify.
    - Right click the Application project folder and select Clean and Build to generate the updated image. The `Execute this line after build` option enabled in Step 4 regenerates the image automatically.
    - Press the on-board **SW0** button. The LED changes from blinking to solid, indicating the device has reset into bootloader mode and is ready to receive an image.
    - Run the `run.bat` or `run.sh` script again. Once the update completes, the LED blinks at the faster rate, confirming the new image is running.

    > **Note:** For the Secure and MI_ARB projects, rebuilding re-runs the signing script, which requires the key pair from Step 5 to be present in the application project directory.

#### Operation by Interface

<details>
<summary><strong>UART</strong></summary>

- Bootloader project path: `<repository>/Bootloader_UART/PL10_MDFU_UART.X`
- Application project path: `<repository>/Application_UART/PL10_APP_UART.X`
- UART pins: TX–PB00, RX–PB01 (CDC)
- Run script example:
  ```bash
  pymdfu update -v debug --tool serial --port <Port Name> --baudrate 115200 --image PL10_App_UART.img
  ```
  > **Tip:** Use MPLAB Data Visualizer to identify the correct COM port name.

</details>

<details>
<summary><strong>SPI</strong></summary>

- Bootloader project path: `<repository>/Bootloader_SPI/PL10_MDFU_SPI.X`
- Application project path: `<repository>/Application_SPI/PL10_APP_SPI.X`
- SPI pins: MOSI–PA04, MISO–PA07, SCK–PA05, SS–PA06
- Run script example:
  ```bash
  pymdfu update -v debug --tool mcp2210 --image PL10_App_SPI.img --clk-speed 500000 --chip-select <SS PIN NUMBER>
  ```
  > **Note:** Replace `<SS PIN NUMBER>` with the appropriate chip select pin number for the MCP2210 setup.
</details>

<details>
<summary><strong>I<sup>2</sup>C</strong></summary>

- Bootloader project path: `<repository>/Bootloader_I2C/PL10_MDFU_I2C.X`
- Application project path: `<repository>/Application_I2C/PL10_APP_I2C.X`
- I²C pins: SDA–PA00, SCL–PA01
- I²C address: 0x20 (decimal 32)
- Run script example:
  ```bash
  pymdfu update --tool mcp2221a --interface i2c --image PL10_App_I2C.img --clk-speed 50000 --address 32
  ```
</details>

<details>
<summary><strong>Secure</strong></summary>

- Bootloader project path: `<repository>/Bootloader_Secure/PIC32CM_PL10_Boot.X`
- Application project path: `<repository>/Application_Secure/PIC32CM_PL10_App.X`
- Communication interface: UART (TX–PB00, RX–PB01)
- Run script example:
  ```bash
  pymdfu update -v debug --tool serial --port <Port Name> --baudrate 115200 --image PIC32CM_TestApp.img
  ```
  > **Note:** Requires the secure element to be provisioned with the public key beforehand — see Step 5 under General Steps.

</details>

<details>
<summary><strong>MI_ARB (Multi-Image, Anti-Rollback)</strong></summary>

- Bootloader project path: `<repository>/Bootloader_MIARB/PIC32CM_PL10_Boot.X`
- Application project path: `<repository>/Application_MIARB/PIC32CM_PL10_App.X`
- Communication interface: UART (TX–PB00, RX–PB01)
- Run script example:
  ```bash
  pymdfu update -v debug --tool serial --port <Port Name> --baudrate 115200 --image PIC32CM_TestApp.img
  ```
  > **Note:** Requires the secure element to be provisioned with the public key beforehand — see Step 5 under General Steps.

</details>

</details>

## Debugging Tips
- Useful `pymdfu` commands
```
$ > pymdfu -V
pymdfu version 2.5.1.9
MDFU protocol version 1.2.0

$ > pymdfu update --tool serial --port COM3 --baudrate 115200 --image PL10_App_UART.img
Upgrade finished successfully
```

- Adding the CLI flag `-v debug` at the end of the pymdfu command will enable debug logging for the Python tool, allowing the user to see the data transfers in more detail

**General Tips**
- Use the MPLAB Data Visualizer to confirm the correct COM port for UART interface
- On-board LED indicates the bootloader status:
  - LED ON (solid): Bootloader mode—ready to receive firmware update
  - LED Blinking: Application running normally
- Entering Bootloader Mode:
  - At startup: Hold the **SW0** button and press the **RESET** button (or power cycle)
  - From the application: Press the **SW0** button—this triggers a system reset with a bootloader entry flag set in RAM
- All three interfaces (UART, SPI, and I<sup>2</sup>C) use consistent bootloader entry methods and LED indicators

---
[Back to Top](#microchip-device-firmware-update-mdfu-bootloader-solution-for-pic32cm-pl10-curiosity-nano-evaluation-kit)