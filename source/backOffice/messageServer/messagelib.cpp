#include "messagelib.h"

//typeTABLE employeeToJobCompany;

MessageLib::MessageLib()
{

}

/* ----------------------------------------------------------------------
*/
USINT MessageLib::addEmployeeToJob(const int nEmployee, const int nJob, const int nCompany)
{
    typeTABLE::iterator itEmployee = employeeToJobCompany.find(nEmployee);

    if(itEmployee != employeeToJobCompany.end())
    {   // employee already exists in list (has anothernot closed job)
        std::map<int,int> &jobCompanyMap = itEmployee->second;
        jobCompanyMap.insert(std::pair<int,int>(nJob,nCompany));
    }
    else
    {   // no employee there
        std::map<int,int> jobCompanyPair;
        jobCompanyPair.insert(std::pair<int,int>(nJob,nCompany));
        employeeToJobCompany[nEmployee]=jobCompanyPair;
    }

    return MESS_OK;
}

/* ----------------------------------------------------------------------
*/
USINT MessageLib::removeEmployeeFromJob(const int nEmployee, const int nJob)
{
    typeTABLE::iterator itEmployee = employeeToJobCompany.find(nEmployee);
    if(itEmployee == employeeToJobCompany.end()) // no employee there
        return MESS_ERR_EMPLOYEE;

    // clean job-company pair associated to this employee
    std::map<int,int> &jobCompanyMap = itEmployee->second;
    jobCompanyMap.erase(nJob);

    // if job-company AP is empty delete employee too
    if(jobCompanyMap.empty())
        employeeToJobCompany.erase(itEmployee);

    return MESS_OK;
}

/* ----------------------------------------------------------------------
*/
USINT MessageLib::removeEmployee(const int nEmployee, const int nCompany)
{
    typeTABLE::iterator itEmployee = employeeToJobCompany.find(nEmployee);
    if(itEmployee == employeeToJobCompany.end()) // no employee there
        return MESS_ERR_EMPLOYEE;

    // remove job-company pair associated to this employee
    std::map<int,int>& jobCompanyMap = itEmployee->second;
    std::map<int,int>::iterator itJobCompany = jobCompanyMap.begin();

    while(itJobCompany != jobCompanyMap.end())
    {
        if(itJobCompany->second == nCompany)
        {
            std::map<int,int>::iterator itToErase = itJobCompany;
            ++itJobCompany;
            jobCompanyMap.erase(itToErase);
        }
        else
            ++itJobCompany;
    }

    // if job-company AP is empty delete employee too
    if(jobCompanyMap.empty())
        employeeToJobCompany.erase(itEmployee);

    return MESS_OK;
}

/* ----------------------------------------------------------------------
*/
USINT MessageLib::checkJob(const int nEmployee)
{
    typeTABLE::iterator itEmployee = employeeToJobCompany.find(nEmployee);
    if(itEmployee == employeeToJobCompany.end()) // no employee and job there
        return 0;

    std::map<int,int> jobCompanyMap(itEmployee->second);

    return static_cast<USINT>(jobCompanyMap.size());
}
