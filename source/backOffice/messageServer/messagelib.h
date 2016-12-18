#ifndef MESSAGELIB_H
#define MESSAGELIB_H

#include <iostream>
#include <map>
#include "../../global/zmq.hpp"
#include "../../global/message_globals.h"

#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)    Sleep(n)
#endif

using namespace std;

typedef map<int,map<int, int>> typeTABLE;
typedef unsigned short int USINT;

class MessageLib
{
public:
    MessageLib();

    USINT addEmployeeToJob(const int nEmployee, const int nJob, const int nCompany);
    USINT removeEmployeeFromJob(const int nEmployee, const int nJob);
    USINT removeEmployee(const int nEmployee, const int nCompany);
    USINT checkJob(const int nEmployee);

private:

    /* map to quickly find job for employee
     * key is Employee ID and value is map with job ID as key and company as value
     * one employee may have more then one current job per company or within multi company
    */
    static typeTABLE employeeToJobCompany;

};

#endif // MESSAGELIB_H
