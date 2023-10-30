#ifndef CMAKE_TARGET_H
#define CMAKE_TARGET_H

// local project headers
// ----------------------
#include "Target.h"

// standard C/C++ headers
// ----------------------
#include <QString>

class CmakeTarget : public Target
{
public:
    void build() override {};
};

#endif // CMAKE_TARGET_H
