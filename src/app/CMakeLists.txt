file(GLOB_RECURSE SRC *.h *.hpp *.cpp)

add_executable(bulk ${SRC})

target_link_libraries(bulk PRIVATE
	bulk_lib
)
