set(apps
    inclination
    )

foreach (executable_root ${apps})
    set(executable ri-${executable_root})
    add_executable(${executable} ${executable_root}.cpp)
    target_link_libraries(${executable} ${RiVLib_SCANLIB_LIBRARY})
    install(TARGETS ${executable} RUNTIME DESTINATION bin)
endforeach()
