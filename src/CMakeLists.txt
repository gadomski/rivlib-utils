add_executable(ri-inclination
    inclination.cpp
    )

add_executable(ri-mta
    mta.cpp
    )

target_link_libraries(ri-inclination
    ${RiVLib_SCANLIB_LIBRARY}
    )
target_link_libraries(ri-mta
    ${RiVLib_SCANLIB_LIBRARY}
    /home/vagrant/src/rimta-x86-linux-gcc47/librivmta.so
    )

install(TARGETS ri-inclination
    RUNTIME DESTINATION bin
    )
install(TARGETS ri-mta
    RUNTIME DESTINATION bin
    )
