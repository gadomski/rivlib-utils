add_executable(ri-inclination
    inclination.cpp
    )

target_link_libraries(ri-inclination
    ${RiVLib_SCANLIB_LIBRARY}
    )

install(TARGETS ri-inclination
    RUNTIME DESTINATION bin
    )
