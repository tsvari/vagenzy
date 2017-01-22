#ifndef CHECKJOB_H
#define CHECKJOB_H

#include "../global/zbase.h"

class CheckJob : public ZBase
{
public:
    CheckJob(messMAP& employeeToJobCompany, bool lock_mode = false);

    virtual int Dojob(const ZData& zdata);
};

#endif // CHECKJOB_H
