# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)

# initialize the SDK directly
set(PICO_SDK_PATH "..\\pico-sdk") 
include(pico_sdk_import.cmake)

set(PICO_BOARD pico_w CACHE STRING "Board type")

project(PicoIoT ASM CXX C)

add_subdirectory(FreeRTOS freertos)
add_subdirectory(Libs/Utilities)

# Include Project folders
add_subdirectory(Projects/SandBox)