# src/lib/tst/CMakeLists.txt

# test-config.h contains the path to the resources folder:
set(PATH_TO_TEST_DATA ${PROJECT_SOURCE_DIR}/lib/tst/res)
configure_file (
	"test-config.h.in"
	"${PROJECT_BINARY_DIR}/test-config.h"
)

# Find needed libraries:
find_package( OpenCV REQUIRED )

# Creates a new executable to contain the tests:
add_executable(rasctest
	main.cpp
	catch.hpp	

	orange-ball-detector-test
	movie-maker-test
)

target_include_directories(rasctest PRIVATE ${PROJECT_BINARY_DIR})

target_link_libraries(rasctest 
	rasclib
	${OpenCV_LIBS} 
	pthread
)

# Adds the executable to the test goal:
add_test(test rasctest)