file(GLOB_RECURSE SRC *.h *.hpp *.cpp)

add_library(bulk_lib ${SRC})

target_include_directories(bulk_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
