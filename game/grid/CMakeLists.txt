add_library(grid_lib grid.cpp)
target_include_directories(grid_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../bit_operations/
)
target_link_libraries(grid_lib PRIVATE bits_lib)