# IoT Pico Health
This project aims to create an IoT health monitoring device. 

## About the Project 
This IoT device contains:
- Raspberry Pi Pico w
> TBD Sensors

# Index
- [1 About the Project](#PSetup)
- [2 About the Project](#PSetup)
- [3 Development Setup](#DevSetup)
    - [3.1 Dependencies](#Dependencies)
    - [3.2 Project Configuration](#PConfig)

## Project Structure

```
Project_Folder
├── pico-sdk (Submodule)
├── main.c
├── <TBD>
└── .
```

<a  name="DevSetup"></a>
# Development Setup

The project setup consist on downloading all the project dependencies for development.
- Install the dependencies. 
- Cloning the Project repository and pico-SDK.
- Loading the Submodules.
- Building the project.

<a  name="Dependencies"></a>
## Dependencies

The following links are the direct download link. You can refer to this [link](https://vanhunteradams.com/Pico/Setup/PicoSetup.html) on how to install everything. Or check this [article](https://www.raspberrypi.com/news/raspberry-pi-pico-windows-installer/) from Raspberry Pi, where a windows installer is provided. If you are going to install everything on your own be sure to add all the paths in your environmental variables. 
- Install [ARM GCC Compiler](https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-win32.exe?rev=29bb46cfa0434fbda93abb33c1d480e6&hash=B2C5AAE07841929A0D0BF460896D6E52s) version 10.3 or check the [compiler versions](https://developer.arm.com/downloads/-/gnu-rm).
- Install [CMake](https://github.com/Kitware/CMake/releases/download/v3.27.0-rc2/cmake-3.27.0-rc2-windows-x86_64.msi) version 3.27 for Windows x86-64-bits or check the [CMake versions](https://cmake.org/download/).
- Install [GIT](https://github.com/git-for-windows/git/releases/download/v2.41.0.windows.1/Git-2.41.0-64-bit.exe) version 2.41 for Windows x86-64-bits or check the [git versions](https://git-scm.com/downloads).
- Install [Visual Studio Code (VSCode)](https://code.visualstudio.com/docs/?dv=win) or check the [VScode Versions](https://code.visualstudio.com/).
- Install [Python 3](https://www.python.org/ftp/python/3.11.4/python-3.11.4-amd64.exe) Version 3.11.4 for Windows x86-64-bits or check [Python3 versions](https://www.python.org/downloads/).
- Install [Build Tools for Visual Studio](https://aka.ms/vs/17/release/vs_BuildTools.exe) or check the [Build Tools versions](https://visualstudio.microsoft.com/es/downloads/#build-tools-for-visual-studio-2022). For the Visual Studio Tools you must check C++ Build Tools with the following elements:
    - MSCV
    - Windows 10 or 11 SDK (Depending on your computer)
    - C++ Cmake Tools for Windows
    - Testing tools core features - Build Tools
    - C++ AddressSanitizer

<a  name="PConfig"></a>
## Project Configuration

First Make sure to have all dependencies installed correctly. If not check the Windows Setup Dependencies section or the references at the end. Then, after everything has been installed correctly do as follows:
1. Clone the git repository in your desired folder using
```shell
C:\Path\YourProject> git clone https://github.com/Figuejojo/SmartAirPollutionMonitor.git
```
2. Get all the submodules clone inside the project, and run the following command inside the Smart Air Pollution Monitor Folder created above:
```shell
C:\Path\YourProject\SmartAirPollutionMonitor> git submodule update --init --recursive
```
3. Using the ***Developer Command Prompt for VS ...*** use the commands below to move inside the SmartAirPollutionMonitor folder, create a build folder, move to inside it, and generate the cmake files.  
```shell
C:\Path\YourProject\SmartAirPollutionMonitor> mkdir build
C:\Path\YourProject\SmartAirPollutionMonitor> cd build
C:\Path\YourProject\SmartAirPollutionMonitor\build> cmake -G "NMake Makefiles" ..
C:\Path\YourProject\SmartAirPollutionMonitor\build> nmake
```
4. Open Visual Studio Code (VSCode) by typing ***code*** from the ***Developer Command Prompt for VS ...*** (Do not confuse it with the normal command console).
5. Open the Smart Air Pollution Monitor project folder in VSCode
6. Choose the GCC arm-none-eabi most recent version (10.3.1 when this was written). If it didn't give you the option click where *No kit* is shown below.
7. Then click the *Build* button to build the project. If you got any issues please refer to the references section.
8. Finally if it builds correcly you must see a build folder inside the project with a file named: ```SAPM.uf2```
