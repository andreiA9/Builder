#ifndef PRJ_MAKE_TARGET_H
#define PRJ_MAKE_TARGET_H

// local project headers
// ----------------------
#include "Target.h"

// standard C/C++ headers
// ----------------------
#include <QString>

class PrjmakeTarget : public Target
{
public:
    void build() override {};
};

#endif // PRJ_MAKE_TARGET_H
