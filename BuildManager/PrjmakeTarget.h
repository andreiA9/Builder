#ifndef PRJ_MAKE_TARGET_H
#define PRJ_MAKE_TARGET_H

#include "Target.h"

#include <QString>

class PrjmakeTarget : public Target
{
public:
    void build() override {};
};

#endif // PRJ_MAKE_TARGET_H
