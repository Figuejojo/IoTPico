cmake_minimum_required(VERSION 3.12)

set(Sensors_SRC
    SEN0515.c
    AM2320.c
)

add_library(Sensors ${Sensors_SRC})

target_include_directories(Sensors PUBLIC
    .
    ../
)

target_link_libraries(Sensors PUBLIC
    pico_stdlib 
    freertos  
    hardware_i2c
    Utils
)

