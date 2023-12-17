add_executable(client
    src/main.cpp
    src/sdl_initializer.cpp
    src/window.cpp
    src/client_application.cpp
)

target_include_directories(client PUBLIC
    src
    include
    ../shared/include
)

target_include_directories(client PUBLIC
    ../extern/SDL2-2.28.5/x86_64-w64-mingw32/include/SDL2
    ../extern/SDL2_net-2.2.0/x86_64-w64-mingw32/include/SDL2
)

target_link_directories(client PUBLIC
    ../extern/SDL2-2.28.5/x86_64-w64-mingw32/lib
    ../extern/SDL2_net-2.2.0/x86_64-w64-mingw32/lib
)

target_link_libraries(client PUBLIC
    SDL2
    SDL2_net
)
