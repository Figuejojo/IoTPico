# Add test for sensors
add_unit_test(test_sensors test_sensors.c)
target_link_libraries(test_sensors Sensors)

# Add test for actuators
add_unit_test(test_actuators test_actuators.c)
# target_link_libraries(test_actuators Actuators)

# Add test for communication
add_unit_test(test_communication test_communication.c)
# target_link_libraries(test_communication Communication)