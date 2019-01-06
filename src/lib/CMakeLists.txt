# src/lib/CMakeLists.txt

# Find needed libraries:
find_package( OpenCV REQUIRED )

# compile the library:
add_library(rasclib
	cpp/orange-ball-detector
	cpp/movie-maker
	cpp/system-helper
)

# Define headers for this library. When PUBLIC, headers used for
# compiling the library are also added to consumers' build
# paths.
target_include_directories(rasclib PUBLIC hpp)

# link to needed libraries
target_link_libraries(rasclib
	${OpenCV_LIBS} 
	pthread
	userenv.lib
)

# This makes the project importable from the build directory
export(TARGETS rasclib FILE rasclib.cmake)

# Let's have unit tests:
add_subdirectory(tst)