set(SOURCE_FILES main.cpp)
set(LIBRARY_FILES window_lib grid_lib)

find_package(SDL2 REQUIRED)
add_compile_options(-Wall -D_REENTRANT)

add_executable(game ${SOURCE_FILES})

target_include_directories(game PUBLIC ${SDL2_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_link_libraries(game ${LIBRARY_FILES})
target_link_libraries(game ${SDL2_LIBRARIES})