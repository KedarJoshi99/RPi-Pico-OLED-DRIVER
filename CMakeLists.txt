# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# initialize pico-sdk from GIT (note this can come from environment, CMake cache
# etc)
set(PICO_SDK_FETCH_FROM_GIT on)
# pico_sdk_import.cmake is a single file copied from this SDK note: this must
# happen before project()
include(pico_sdk_import.cmake)

project(picoOled C CXX ASM)
# Set the name of the project (as PROJECT_NAME) and C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
# Creates a pico-sdk subdirectory in our project for the libraries

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  pico_sdk_init()

  # List source files for the pro0ject here
  add_executable(oledTest ${CMAKE_CURRENT_LIST_DIR}/example/oledTest.c
                          ${CMAKE_CURRENT_LIST_DIR}/src/picoOled.c)

  # Link to the library functions (stdlib, etc)
  target_link_libraries(oledTest pico_stdlib hardware_i2c)

  pico_enable_stdio_usb(oledTest 1)
  pico_enable_stdio_uart(oledTest 0)

  # Create the output file
  pico_add_extra_outputs(oledTest)
else()
  set(LIB_NAME picoOled)
  add_library(${LIB_NAME} ${CMAKE_CURRENT_LIST_DIR}/src/${LIB_NAME}.c)
  target_include_directories(${LIB_NAME}
                             PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

  target_link_libraries(${LIB_NAME} pico_stdlib hardware_i2c)

endif()
