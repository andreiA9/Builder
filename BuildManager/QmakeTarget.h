#ifndef QMAKE_TARGET_H
#define QMAKE_TARGET_H

#include "Target.h"

#include <QString>

class QmakeTarget : public Target
{
public:
    void build() override {};

    void runQmake() {};

    void runMake() {};
};

#endif // QMAKE_TARGET_H
