# src/app/CMakeLists.txt

# Pkg_config is used to locate header and files for dependency libraries:
find_package(PkgConfig)

# Defines variables GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES.
pkg_check_modules(GTKMM gtkmm-3.0) 
link_directories( ${GTKMM_LIBRARY_DIRS} )
include_directories( ${GTKMM_INCLUDE_DIRS} )

# OpenCV can be linked in a more standard manner:
find_package( OpenCV REQUIRED )

# Compile files:
add_executable(rascapp
    cpp/main.cpp
    cpp/main-window.cpp
    cpp/camera-drawing-area.cpp
)

# Add folder with all headers:
target_include_directories(rascapp PRIVATE hpp)

# Link files:
target_link_libraries(rascapp
    rasclib
    ${GTKMM_LIBRARIES}
    ${OpenCV_LIBS}
)

# Apple requires a bundle to add a Info.plist file that contains the required
# permissions to access some restricted resources like the camera:
if (APPLE)
    set_target_properties(rascapp PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_FRAMEWORK_IDENTIFIER org.cmake.ExecutableTarget
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/res/MacOSXBundleInfo.plist.in
        
        # This property is required:
        MACOSX_BUNDLE_GUI_IDENTIFIER "rascapp-${PROJECT_VERSION}"
        
        # Those properties are not required:
        MACOSX_BUNDLE_INFO_STRING "rascapp ${PROJECT_VERSION}, by jmgonet@agl-developpement.ch"
        MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION}
        MACOSX_BUNDLE_BUNDLE_NAME "rascapp"
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    )
endif()
