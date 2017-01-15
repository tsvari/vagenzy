#ifndef BASETESTCLASS_H
#define BASETESTCLASS_H

#include "gmock/gmock.h"
#include "../../global/message_globals.h"
#include "../global/data_globals.h"
#include <string>

using std::string;
using namespace ::testing;

class BaseTestClass : public Test
{
public:
    // sizeof map
    int GetMapCount()
    {
        return employeeToJobCompany.size();
    }

    // count of jobs per employee
    int GetJobCount( int nEmployee)
    {
        messMAP::iterator it = employeeToJobCompany.find(nEmployee);
        if(it != employeeToJobCompany.end())
        {
            std::map<int, int> jobsMap = it->second;
            return jobsMap.size();
        }
        return 0;
    }

    bool IsEmployeeInMap(int nEmployee)
    {
        // looking for employee
        messMAP::iterator itEmployee = employeeToJobCompany.find(nEmployee);
        if(itEmployee != employeeToJobCompany.end()) // no employee there
            return true;

        return false;
    }

    void CleanMainMap()
    {
        employeeToJobCompany.clear();
    }

protected:
    ZData _zdata;
};

#endif // BASETESTCLASS_H
