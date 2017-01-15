#ifndef REMOVEEMPLOYEE_H
#define REMOVEEMPLOYEE_H

#include "../global/zbase.h"

class RemoveEmployee : public ZBase
{
public:
    RemoveEmployee(messMAP& employeeToJobCompany, bool lock_mode = false);

    virtual int Dojob(ZData& zdata);
};

#endif // REMOVEEMPLOYEE_H
