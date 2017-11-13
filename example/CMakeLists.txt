cmake_minimum_required (VERSION 3.1)

link_libraries(apriltags)

add_executable(apriltags_demo apriltags_demo.cpp Serial.cpp)

add_executable(imu imu.cpp Serial.cpp)
