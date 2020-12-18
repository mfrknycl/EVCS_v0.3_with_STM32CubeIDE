# EV Charging Station

The proposed EVCS provides a single-phase home used EVCS, which means EV can be charged with 230VAC, 10-30A power source. A 24kWh battery with a 3.3kW (15 A) charger would take less than 8 hours to fully charge.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

You will need to install **STM32CubeIDE** and **MinGW** for this project.


### Installing

- Installing STM32CubeIDE for Windows
  + [STM32CubeIDE Windows Installer](https://www.st.com/en/development-tools/stm32cubeide.html)
- Installing compiler (GCC) for host (Windows)
  + [MinGW - Minimalist GNU for Windows](https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe/)
  + When you see the Installation Manager Window, go to Basic Setup > right click on mingw32-gcc++.bin & msys-base-bin > Mark for Installation.
  + After that, go to Installation > Apply Changes > Apply
  + After Installing close the Installer
  + Go to Control Panel > System and Security > System > Advanced system settings > Advanced >
  Environment Variables > Under user varibles choose Path and click Edit
  + After that copy the path of your MinGW Installation ex: 'C:\MinGW\bin' and 'C:\MinGW\msys\1.0\bin'


