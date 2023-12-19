cmake_minimum_required(VERSION 3.23)

project(Schmetterling)

enable_testing()

add_subdirectory(extern/googletest)
add_subdirectory(shared)
add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(samples)