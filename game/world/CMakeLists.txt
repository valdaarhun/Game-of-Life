add_library(world_lib world.cpp)
target_include_directories(world_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../bit_operations/
)
target_link_libraries(world_lib PRIVATE bits_lib)