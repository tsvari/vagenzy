#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

#include <map>

#if defined(_WIN32)
#define HAVE_STRUCT_TIMESPEC
#endif

#include <pthread.h>


typedef std::map<int,std::map<int, int>> messMAP;

struct ZData;

class ZBase
{
public:
    ZBase(messMAP& employeeToJobCompany, bool lock_mode);
    virtual ~ZBase(){}

    virtual int Dojob(ZData& /*zdata*/);

protected:
    messMAP& _employeeToJobCompany;
    bool _lock_mode;

    pthread_rwlock_t _rwlock;
};

#endif // MESSAGEBASE_H
