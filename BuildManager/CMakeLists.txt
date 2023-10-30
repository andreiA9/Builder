set(Qt5_Application_Components Core Widgets REQUIRED)
find_package(Qt5 COMPONENTS ${Qt5_Application_Components})

set(BuildManager_src
    BuildManager.cpp
    BuildManager.h
    BuildSystem.cpp
    BuildSystem.h
    BuildConfiguration.cpp
    BuildConfiguration.h
    BuildSteps.cpp
    BuildSteps.h
    CmakeTarget.cpp
    CmakeTarget.h
    PrjmakeTarget.cpp
    PrjmakeTarget.h
    QmakeTarget.cpp
    QmakeTarget.h
	Target.cpp
    Target.h
    RunConfiguration.cpp
    RunConfiguration.h
    Process.cpp
    Process.h
    Environment.cpp
    Environment.h
    )


add_library(BuildManager_static
    ${BuildManager_src}
)

target_link_libraries(BuildManager_static
    Qt5::Widgets        # -> Widgets
    Qt5::Core           # -> Core
    )

target_include_directories(BuildManager_static
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    )

