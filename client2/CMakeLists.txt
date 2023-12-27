#file(GLOB_RECURSE client2_SRC CONFIGURE_DEPENDS "src/*.hpp" "src/*.cpp")

add_executable(client2
    src/application/application.cpp
    src/main.cpp
)

target_include_directories(client2 PUBLIC
    src/
    src/interfaces
    src/application
    src/infrastructure
    ../shared/include
)

target_include_directories(client2 PUBLIC
    ../extern/SDL2-2.28.5/x86_64-w64-mingw32/include/SDL2
    ../extern/SDL2_net-2.2.0/x86_64-w64-mingw32/include/SDL2
    
)

target_link_directories(client2 PUBLIC
    ../extern/SDL2-2.28.5/x86_64-w64-mingw32/lib
    ../extern/SDL2_net-2.2.0/x86_64-w64-mingw32/lib
)

target_link_libraries(client2 PUBLIC
    shared
    SDL2
    SDL2_net
)

add_subdirectory(test)
