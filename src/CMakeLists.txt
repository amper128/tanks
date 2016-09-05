
include_directories(include)

file(GLOB_RECURSE TANK_SOURCES "*.cpp")
file(GLOB_RECURSE TANK_HEADERS "include/*.h")

add_executable(tanks ${TANK_SOURCES} ${TANK_HEADERS})
target_link_libraries(tanks pugixml GL GLU GLEW SDL asan)
