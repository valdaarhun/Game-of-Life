set(SOURCE_FILES main.cpp)

find_package(SDL2 REQUIRED)
add_compile_options(-Wall -std=c++1z -D_REENTRANT)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(game ${SOURCE_FILES})
target_link_libraries(game ${SDL2_LIBRARIES})