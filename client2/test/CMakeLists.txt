set(tests_include_directories
    ../../extern/googletest/googletest/include
    ../../extern/googletest/googlemock/include
    ../../extern/SDL2-2.28.5/x86_64-w64-mingw32/include/SDL2
    ../../extern/SDL2_net-2.2.0/x86_64-w64-mingw32/include/SDL2
)

set(tests_link_directories
    ../../extern/SDL2-2.28.5/x86_64-w64-mingw32/lib
    ../../extern/SDL2_net-2.2.0/x86_64-w64-mingw32/lib
)

set(tests_link_libraries
    gtest_main
    gmock
    SDL2
    SDL2_net

)

# test_renderer

add_executable(test_renderer
    test_renderer.cpp
)

target_include_directories(test_renderer PUBLIC
    ${tests_include_directories}
)

target_link_directories(test_renderer PUBLIC
    ${tests_link_directories}
)

target_link_libraries(test_renderer
    ${tests_link_libraries}
)

add_test(
    NAME test_renderer
    COMMAND $<TARGET_FILE:test_renderer>
)