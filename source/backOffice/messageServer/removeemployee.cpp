#include "../global/data_globals.h"
#include "removeemployee.h"
#include "../../global/message_globals.h"

RemoveEmployee::RemoveEmployee(messMAP& employeeToJobCompany, bool lock_mode):
    ZBase(employeeToJobCompany, lock_mode)
{

}

int RemoveEmployee::Dojob(const ZData& zdata)
{
    // start read lock
    if(_lock_mode)
        pthread_rwlock_rdlock(&_rwlock);

    messMAP::iterator itEmployee = employeeToJobCompany.find(zdata._employee);
    if(itEmployee == employeeToJobCompany.end()) // no employee there
    {
        // unloack map
        if(_lock_mode)
            pthread_rwlock_unlock(&_rwlock);
        return MESS_ERR_EMPLOYEE;
    }

    // change from read mode to write mode
    if(_lock_mode)
    {
        pthread_rwlock_unlock(&_rwlock); // unlock read lock
        pthread_rwlock_wrlock(&_rwlock); // write lock
    }
    // remove job-company pair associated to this employee
    std::map<int,int>& jobCompanyMap = itEmployee->second;
    std::map<int,int>::iterator itJobCompany = jobCompanyMap.begin();

    while(itJobCompany != jobCompanyMap.end())
    {
        if(itJobCompany->second == zdata._company)
        {
            std::map<int,int>::iterator itToErase = itJobCompany;
            jobCompanyMap.erase(itToErase);
        }

        ++itJobCompany;
    }

    // if job-company MAP is empty delete employee too
    if(jobCompanyMap.empty())
        employeeToJobCompany.erase(itEmployee);

    // unloack anyway
    if(_lock_mode)
        pthread_rwlock_unlock(&_rwlock); // unlock read/write lock

    return MESS_OK;
}
