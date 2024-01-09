cmake_minimum_required(VERSION 3.13)

# initialize the SDK directly
include(./pico-sdk/pico_sdk_init.cmake)
set(PICO_BOARD pico_w)

project(IoTHealth CXX C ASM)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(IoTHealth
    main.cpp
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(IoTHealth PUBLIC
    pico_stdlib)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(IoTHealth)