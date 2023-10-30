set(Qt5_Application_Components Core Widgets REQUIRED)
find_package(Qt5 COMPONENTS ${Qt5_Application_Components})

set(ProjectManager_src
    ProjectManager.cpp
    ProjectManager.h
    ProjectController.cpp
    ProjectController.h
    ProjectImporter.cpp
    ProjectImporter.h
    ProjectSettings.cpp
    ProjectSettings.h
    Project.cpp
    Project.h
    Document.cpp
    Document.h
    DirectoryNode.cpp
    DirectoryNode.h
    ProjectNode.cpp
    ProjectNode.h
    )


add_library(ProjectManager_static
    ${ProjectManager_src}
)

target_link_libraries(ProjectManager_static
    Qt5::Widgets        # -> Widgets
    Qt5::Core           # -> Core
    )

target_include_directories(ProjectManager_static
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    )

