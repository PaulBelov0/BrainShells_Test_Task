cmake_minimum_required(VERSION 3.16)

project(BrainShells_TestTask VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(LibArchive REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        main_window.cpp
        main_window.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)

    qt_add_executable(BrainShells_TestTask
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Widgets/file_selector.h Widgets/file_selector.cpp
        resources.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BrainShells_TestTask APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BrainShells_TestTask SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BrainShells_TestTask
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BrainShells_TestTask PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(BrainShells_TestTask PRIVATE ${LibArchive_INCLUDE_DIRS})
target_link_libraries(BrainShells_TestTask PRIVATE ${LibArchive_LIBRARIES})
target_link_libraries(BrainShells_TestTask PRIVATE Qt6::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BrainShells_TestTask)
endif()
set_target_properties(BrainShells_TestTask PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS BrainShells_TestTask
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BrainShells_TestTask)
endif()
