#ifndef REMOVEEMPLOYEEFROMJOB_H
#define REMOVEEMPLOYEEFROMJOB_H

#include "../global/zbase.h"

class RemoveEmployeeFromJob : public ZBase
{
public:
    RemoveEmployeeFromJob(messMAP& employeeToJobCompany, bool lock_mode = false);

    virtual int Dojob(ZData& zdata);
};

#endif // REMOVEEMPLOYEEFROMJOB_H
