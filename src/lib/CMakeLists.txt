# src/lib/CMakeLists.txt

# Find needed libraries:
find_package( OpenCV REQUIRED )

# compile the library (some files depend on the platform):
set(RASCLIB_SOURCES 
	cpp/orange-ball-detector
	cpp/movie-maker
	cpp/capture-image-from-camera
	cpp/rate-meter
)

if (WIN32)
    set(RASCLIB_SOURCES ${RASCLIB_SOURCES} cpp/system-helper-windows)
else()
    set(RASCLIB_SOURCES ${RASCLIB_SOURCES} cpp/system-helper-nix)
endif()

add_library(rasclib ${RASCLIB_SOURCES})

# Define headers for this library. When PUBLIC, headers used for
# compiling the library are also added to consumers' build
# paths.
target_include_directories(rasclib PUBLIC hpp)

# link to needed libraries
set(RASCLIB_LIBRARIES
	${OpenCV_LIBS} 
	pthread
)

if (WIN32)
	set(RASCLIB_LIBRARIES ${RASCLIB_LIBRARIES} userenv.lib)
endif()

target_link_libraries(rasclib ${RASCLIB_LIBRARIES})

# This makes the project importable from the build directory
export(TARGETS rasclib FILE rasclib.cmake)

# Let's have unit tests:
add_subdirectory(tst)
