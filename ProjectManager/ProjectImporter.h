#ifndef PROJECT_IMPORTER_H
#define PROJECT_IMPORTER_H

// local project headers
// ----------------------
#include "Project.h"

// standard C/C++ headers
// ----------------------

// !!!!
// THIS contains a sourceFile of the project
class ProjectImporter
{
public:
    static Project* parsePrjFile(Project* project);
};

#endif // PROJECT_IMPORTER_H
