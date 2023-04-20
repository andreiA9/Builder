set(Qt5_Application_Components Core Widgets REQUIRED)
find_package(Qt5 COMPONENTS ${Qt5_Application_Components})

set(BuildModule_SRC
    BuildModule.cpp
    BuildModule.h
    GccInterpreter.cpp
    GccInterpreter.h
    )


add_library(BuildModule_static
    ${BuildModule_SRC}
)

target_link_libraries(BuildModule_static
    Qt5::Widgets        # -> Widgets
    Qt5::Core           # -> Core
    )

target_include_directories(BuildModule_static
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    )

