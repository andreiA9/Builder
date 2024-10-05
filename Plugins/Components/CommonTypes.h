#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

// local project headers
// ----------------------

// standard C/C++ headers
// ----------------------

// VEZI ca ASTA exista deja in Simulators/Constants.h
// VEZI ca ai adaugat recent Edit + Export
enum BuildRequest
{
    NoRequest = 0,
    ExecuteCompileFile = 1,
    ExecuteRecompileFile = 2,
    ExecuteBuildDirectory = 3,
    ExecuteGenerateLib = 4,
    ExecuteCommand = 5,
};

#endif // COMMON_TYPES_H
