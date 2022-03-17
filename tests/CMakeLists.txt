set(CATCH_MAIN_SRC main.cpp)

set (TEST_TARGETS
	00-error
	10-ipv4-server
	11-ipv4-client
	20-ipv6-server
	21-ipv6-client
	30-unx-server
	31-unx-client
)

message(STATUS "nio: Enabled tests")

add_library(NioCatchMain OBJECT ${CATCH_MAIN_SRC})

foreach(target ${TEST_TARGETS})
	add_executable(${target} ${target}.cpp)
	target_link_libraries(${target} NioCatchMain)
	target_include_directories(${target} PRIVATE ../include)
endforeach()
