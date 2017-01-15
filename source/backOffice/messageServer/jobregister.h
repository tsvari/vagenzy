#ifndef JOBREGISTER_H
#define JOBREGISTER_H

#include "messagebase.h"

typedef std::map<int,std::map<int, int>> messMAP;

class ZeroParser;

class JobRegister : public MessageBase
{
public:
    JobRegister(messMAP& employeeToJobCompany, ZeroParser& parser, bool lock_mode = false);

    virtual int Dojob();

};

#endif // JOBREGISTER_H
