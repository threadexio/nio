set(TEST_INCLUDE_DIR ../../)

set(CATCH_MAIN_SRC main.cpp)

set (TEST_TARGETS
	00-buffer
	01-error
)

message(STATUS "nio: Enabled tests")

add_library(NioCatchMain OBJECT ${CATCH_MAIN_SRC})

foreach(target ${TEST_TARGETS})
	add_executable(${target} ${target}.cpp)
	target_include_directories(${target} PRIVATE ${TEST_INCLUDE_DIR})
	target_link_libraries(${target} NioCatchMain NioStatic)
endforeach()
