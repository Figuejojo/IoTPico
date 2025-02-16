# Add the Unity testing framework
add_subdirectory(unity)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/unity/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Make sure common libraries are available for all tests
link_libraries(
    pico_stdlib 
    freertos  
    hardware_i2c
    Utils
)

# Create a function to add test targets
function(add_unit_test test_name test_source)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name} unity)
    
    # Set properties for Pico target
    pico_add_extra_outputs(${test_name})
    
    # Add as a test
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

# Add test directories for each library
add_subdirectory(libs)