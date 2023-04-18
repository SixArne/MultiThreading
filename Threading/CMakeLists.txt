set (CMAKE_CXX_STANDARD 20)

# for later including fmt.
include(FetchContent)

# Source files
add_executable(Threading main.cpp)

# Include directories
target_include_directories(Threading PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)