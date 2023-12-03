cmake_minimum_required(VERSION 3.23)

project(Sample)

add_executable(Sample
    src/main.cpp
    src/application.cpp
)

target_include_directories(Sample PUBLIC
    extern/SDL2-2.28.5/x86_64-w64-mingw32/include
)

target_link_directories(Sample PUBLIC
    extern/SDL2-2.28.5/x86_64-w64-mingw32/lib
)

target_link_libraries(Sample PUBLIC
    SDL2
)