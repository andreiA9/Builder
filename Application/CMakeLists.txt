cmake_minimum_required(VERSION 2.8)

set(Qt5_Application_Components Core Widgets REQUIRED)
find_package(Qt5 COMPONENTS ${Qt5_Application_Components})


# headers included in both[Qt Widgests/Qt QML]
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})

set(MainWindow_RES
    Resources/resources.qrc
    )

add_executable(${PROJECT_NAME} WIN32
    # add the RESOURCES
    # RESURSELE doar aici merg
    ${MainWindow_RES}
    main.cpp
    )

target_link_libraries(${PROJECT_NAME} PUBLIC
    MainWindow_static
    Qt5::Core           # -> Core
    )

# this will alllow INDEXING of RESOURCES=icons
# NU ESTE NEVOIE de asta daca ai
# qt5_add_resources()
set(CMAKE_AUTORCC ON)



install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Resources/
    DESTINATION ${PROJECT_BINARY_DIR}/Application/Resources/
    )


# expose values to c++ files
set(PROJECT_VERSION 1.0)
set(PROJECT_BUNDLE_NAME AppName)
target_compile_definitions(${PROJECT_NAME} PRIVATE
        CMAKE_DEF_PROJECT_VERSION="${PROJECT_VERSION}"
        CMAKE_DEF_APP_NAME="${PROJECT_BUNDLE_NAME}"
)

