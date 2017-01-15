#include "../global/data_globals.h"
#include "checkjob.h"
#include "../../global/message_globals.h"

////////////////////////////////////////////////////////////////////
/// \brief CheckJob::CheckJob
/// \param employeeToJobCompany
/// \param lock_mode
///
CheckJob::CheckJob(messMAP& employeeToJobCompany, bool lock_mode):
    ZBase(employeeToJobCompany, lock_mode)
{

}

////////////////////////////////////////////////////////////////////////////
/// \brief CheckJob::Dojob returns job count for employee by param 'zdata._employee'
/// \param zdata
/// \return: count of jobs
///
int CheckJob::Dojob(ZData& zdata)
{
    int nMessageCount = 0;

    // start read lock
    if(_lock_mode)
        pthread_rwlock_rdlock(&_rwlock);

    // search employee by id
    messMAP::iterator itEmployee = employeeToJobCompany.find(zdata._employee);
    if(itEmployee != employeeToJobCompany.end())
        nMessageCount = (static_cast<std::map<int,int>>(itEmployee->second)).size();

    if(_lock_mode)
        pthread_rwlock_unlock(&_rwlock); // unlock read lock

    return nMessageCount;
}
