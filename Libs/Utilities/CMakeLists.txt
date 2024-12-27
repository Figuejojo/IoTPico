cmake_minimum_required(VERSION 3.12)

set(Utils_SRC
    log_system.c
)

add_library(Utils ${Utils_SRC})

target_include_directories(Utils PUBLIC
    .
    ../)

target_link_libraries(Utils PUBLIC
    pico_stdlib 
    freertos  
    hardware_i2c
)

