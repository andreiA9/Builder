cmake_minimum_required(VERSION 3.1)

# numele PROIECTULUI
set(PROJECT_NAME Builder)
project(${PROJECT_NAME})


## Test for supported Qt version
#set(QT_MINIMUM_VERSION 5.9.0)
#find_program(QMAKE_EXECUTABLE NAMES qmake HINTS ${QTDIR} ENV QTDIR PATH_SUFFIXES bin)
#execute_process(COMMAND ${QMAKE_EXECUTABLE} -query QT_VERSION OUTPUT_VARIABLE QT_VERSION)
#if(QT_VERSION VERSION_LESS QT_MINIMUM_VERSION)
#        MESSAGE(FATAL_ERROR "Minimum supported Qt version: ${QT_MINIMUM_VERSION}. Installed version: ${QT_VERSION}")
#endif()


# INSTRUCT CMake to call COMPILER=MOC automatically
set(CMAKE_AUTOMOC ON)
# NU SE stie de ce ai adaugat o
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)



add_subdirectory(Application)
add_subdirectory(MainWindow)
add_subdirectory(BuildModule)




