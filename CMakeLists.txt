cmake_minimum_required(VERSION 3.0)
project(rivlib-utils)

find_package(RiVLib COMPONENTS scanlib)

set(apps
    inclination
    meta
    time
    units
    )

foreach (executable_root ${apps})
    set(executable ri-${executable_root})
    add_executable(${executable} src/${executable_root}.cpp src/app.cpp)
    target_link_libraries(${executable} PRIVATE ${RiVLib_SCANLIB_LIBRARY})
    target_include_directories(${executable} PRIVATE ${RiVLib_INCLUDE_DIRS})
    target_compile_options(${executable} PRIVATE -std=c++11)

    install(TARGETS ${executable} RUNTIME DESTINATION bin)
endforeach()
