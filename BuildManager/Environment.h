#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QString>

// NUMELE.acestea NU se vor SCHIMBA
// < PENTRU CA asa sunt in BuildEnvironment din QtCreator
static QString QT5_DIR = "/usr/lib/x86_64-linux-gnu/qt5";
static QString HOME = "/home/andrei";
static QString SHELL = "/bin/bash";

// !!!!
// THIS ENVIRONMENT VARIABLES only for the Projects loaded in the Builder application
class Environment
{
public:
};

#endif // ENVIRONMENT_H
