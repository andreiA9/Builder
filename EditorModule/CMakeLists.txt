set(Qt5_Application_Components Core Widgets REQUIRED)
find_package(Qt5 COMPONENTS ${Qt5_Application_Components})

set(EditorModule_SRC
    EditorModule.cpp
    EditorModule.h
    ProjectsView.cpp
    ProjectsView.h
    EditorView.cpp
    EditorView.h
    TextEditor.cpp
    TextEditor.h
    SessionModule.cpp
    SessionModule.h
    )


add_library(EditorModule_static
    ${EditorModule_SRC}
)

target_link_libraries(EditorModule_static
    Qt5::Widgets        # -> Widgets
    Qt5::Core           # -> Core
    BuildManager_static
    ProjectManager_static
    )

target_include_directories(EditorModule_static
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    )

