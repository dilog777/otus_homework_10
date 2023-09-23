project(bulk_server VERSION ${PROJECT_VERSION})

file(GLOB_RECURSE SRC *.h *.hpp *.cpp)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE
	${Boost_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	bulk_lib
)
