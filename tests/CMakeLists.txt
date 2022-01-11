set(CATCH_MAIN_SRC main.cpp)

set (TEST_TARGETS
	00-error
	10-ipv4-server
	11-ipv4-client
)

message(STATUS "nio: Enabled tests")

add_library(NioCatchMain OBJECT ${CATCH_MAIN_SRC})

foreach(target ${TEST_TARGETS})
	add_executable(${target} ${target}.cpp)
	target_link_libraries(${target} NioCatchMain NioStatic)
endforeach()
