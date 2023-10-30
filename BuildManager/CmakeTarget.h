#ifndef CMAKE_TARGET_H
#define CMAKE_TARGET_H

#include "Target.h"

#include <QString>

class CmakeTarget : public Target
{
public:
    void build() override {};
};

#endif // CMAKE_TARGET_H
