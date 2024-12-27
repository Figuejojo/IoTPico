project(SandBox ASM CXX C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# rest of your project
add_executable(SandBox
    main.c
)
# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(SandBox PUBLIC
    pico_stdlib
    freertos
    Utils
    )

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(SandBox)