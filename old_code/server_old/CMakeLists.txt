add_executable(server
    src/main.cpp
    src/server_application.cpp
)

target_include_directories(server PUBLIC
    ../shared/include
)

target_include_directories(server PUBLIC
    ../extern/SDL2-2.28.5/x86_64-w64-mingw32/include/SDL2
    ../extern/SDL2_net-2.2.0/x86_64-w64-mingw32/include/SDL2
)

target_link_directories(server PUBLIC
    ../extern/SDL2-2.28.5/x86_64-w64-mingw32/lib
    ../extern/SDL2_net-2.2.0/x86_64-w64-mingw32/lib
)

target_link_libraries(server PUBLIC
    SDL2
    SDL2_net
)
