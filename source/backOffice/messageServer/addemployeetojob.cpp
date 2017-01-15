#include "../global/data_globals.h"
#include "addemployeetojob.h"
#include "../../global/message_globals.h"
////////////////////////////////////////
/// \brief AddEmployeeToJob::AddEmployeeToJob
/// \param employeeToJobCompany
/// \param lock_mode
///
AddEmployeeToJob::AddEmployeeToJob(messMAP& employeeToJobCompany, bool lock_mode):
    ZBase(employeeToJobCompany, lock_mode)
{

}

/////////////////////////////////////////////
/// \brief AddEmployeeToJob::Dojob
/// \param zdata
/// \return
///
int AddEmployeeToJob::Dojob(ZData& zdata)
{
    // start read lock
    if(_lock_mode)
        pthread_rwlock_rdlock(&_rwlock);

    messMAP::iterator itEmployee = _employeeToJobCompany.find( zdata._employee);

    if(itEmployee != _employeeToJobCompany.end())
    {   // employee already exists in list (has anothernot closed job)
        // change from read mode to write mode
        if(_lock_mode)
        {
            pthread_rwlock_unlock(&_rwlock); // unlock read lock
            pthread_rwlock_wrlock(&_rwlock); // write lock
        }

        std::map<int,int> &jobCompanyMap = itEmployee->second;
        jobCompanyMap.insert(std::pair<int,int>( zdata._job, zdata._company));
    }
    else
    {   // no employee there
        // change from read mode to write mode
        if(_lock_mode)
        {
            pthread_rwlock_unlock(&_rwlock); // unlock read lock
            pthread_rwlock_wrlock(&_rwlock); // write lock
        }

        // make insert of new pair
        std::map<int,int> jobCompanyPair;
        jobCompanyPair.insert(std::pair<int,int>( zdata._job, zdata._company));
        _employeeToJobCompany[ zdata._employee]=jobCompanyPair;
    }
    // unloack anyway
    if(_lock_mode)
        pthread_rwlock_unlock(&_rwlock); // unlock read/write lock

    return MESS_OK;
}
