set(SOURCE_FILES main.cpp)

find_package(SDL2 REQUIRED)
add_compile_options(-Wall -D_REENTRANT)

add_executable(game ${SOURCE_FILES})

target_include_directories(game PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(game ${SDL2_LIBRARIES})