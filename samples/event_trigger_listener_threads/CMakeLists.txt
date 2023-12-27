add_executable(sample_event_trigger_listener_threads
    src/main.cpp
)

target_include_directories(sample_event_trigger_listener_threads PUBLIC
    src
    #../../shared/include
)

target_include_directories(sample_event_trigger_listener_threads PUBLIC
    #../../extern/SDL2-2.28.5/x86_64-w64-mingw32/include/SDL2
    #../../extern/SDL2_net-2.2.0/x86_64-w64-mingw32/include/SDL2
)

target_link_directories(sample_event_trigger_listener_threads PUBLIC
    #../../extern/SDL2-2.28.5/x86_64-w64-mingw32/lib
    #../../extern/SDL2_net-2.2.0/x86_64-w64-mingw32/lib
)

target_link_libraries(sample_event_trigger_listener_threads PUBLIC
    #SDL2
    #SDL2_net
)
