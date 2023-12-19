add_executable(wait_for_events_sample
    src/main.cpp
)

target_include_directories(wait_for_events_sample PUBLIC
    src
    ../../shared/include
)

target_include_directories(wait_for_events_sample PUBLIC
    ../../extern/SDL2-2.28.5/x86_64-w64-mingw32/include/SDL2
    ../../extern/SDL2_net-2.2.0/x86_64-w64-mingw32/include/SDL2
)

target_link_directories(wait_for_events_sample PUBLIC
    ../../extern/SDL2-2.28.5/x86_64-w64-mingw32/lib
    ../../extern/SDL2_net-2.2.0/x86_64-w64-mingw32/lib
)

target_link_libraries(wait_for_events_sample PUBLIC
    SDL2
    SDL2_net
)
