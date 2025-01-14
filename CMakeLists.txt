cmake_minimum_required(VERSION 3.13)

project(TinyXVC C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

find_package(LibFTDI1 NO_MODULE REQUIRED)
include( ${LIBFTDI_USE_FILE} )

add_executable(TinyXVC
    src/txvc.c
    src/log.c
    src/driver.c
    src/alias.c
    src/server.c
    src/driver/echo.c
    src/driver/ft2232h.c
    )
set_property(TARGET TinyXVC PROPERTY C_STANDARD 11)
set_property(TARGET TinyXVC PROPERTY OUTPUT_NAME txvc)
target_include_directories(TinyXVC
    PRIVATE include/
    )
target_compile_options(TinyXVC
    PRIVATE -Wall -Wextra -Wpedantic -Werror
            -ffunction-sections -fdata-sections
    )
target_link_options(TinyXVC
    PRIVATE -Wl,--script=${CMAKE_CURRENT_LIST_DIR}/src/driver.ld
            -Wl,--gc-sections
    )
target_link_libraries(TinyXVC
    ftdi1
    )

