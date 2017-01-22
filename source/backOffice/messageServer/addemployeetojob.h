#ifndef ADDEMPLOYEETOJOB_H
#define ADDEMPLOYEETOJOB_H

#include "../global/zbase.h"

class AddEmployeeToJob : public ZBase
{
public:
    AddEmployeeToJob(messMAP& employeeToJobCompany, bool lock_mode = false);

    virtual int Dojob(const ZData& zdata);
};

#endif // ADDEMPLOYEETOJOB_H
