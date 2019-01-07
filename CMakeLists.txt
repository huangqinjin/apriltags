cmake_minimum_required(VERSION 3.1)
project(apriltags VERSION 1.0.0)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
 endif()

find_package(OpenCV ${OPENCV_VERSION} REQUIRED COMPONENTS core calib3d imgproc)
find_package(Eigen3 REQUIRED)

file(GLOB SOURCE_FILES "src/*.cc")
add_library(${PROJECT_NAME} ${SOURCE_FILES})

# https://stackoverflow.com/questions/225432/export-all-symbols-when-creating-a-dll
set_property(TARGET ${PROJECT_NAME} PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS ON)

# https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html
# https://stackoverflow.com/questions/25676277/cmake-target-include-directories-prints-an-error-when-i-try-to-add-the-source
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}> PRIVATE AprilTags)
target_link_libraries(${PROJECT_NAME} PUBLIC Eigen3::Eigen opencv_core PRIVATE opencv_calib3d opencv_imgproc)


include(GNUInstallDirs)
set(ConfigPackageLocation ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME})
#set(ConfigPackageLocation ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}        
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY AprilTags
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.h")

install(EXPORT ${PROJECT_NAME}-targets DESTINATION ${ConfigPackageLocation})

export(EXPORT ${PROJECT_NAME}-targets)


include(CMakePackageConfigHelpers)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake.in"
"@PACKAGE_INIT@
include(\"\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}-targets.cmake\")
if(NOT TARGET opencv_core NOT TARGET opencv_calib3d OR NOT TARGET opencv_imgproc)
    include(CMakeFindDependencyMacro)
    find_dependency(OpenCV ${OPENCV_VERSION})
endif()
if(NOT TARGET Eigen3::Eigen)
    include(CMakeFindDependencyMacro)
    find_dependency(Eigen3)
endif()
")

configure_package_config_file("${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    INSTALL_DESTINATION ${ConfigPackageLocation})

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    COMPATIBILITY AnyNewerVersion)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    DESTINATION ${ConfigPackageLocation})
