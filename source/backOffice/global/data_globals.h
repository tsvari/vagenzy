#ifndef DATA_GLOBALS_H
#define DATA_GLOBALS_H

#include <string>
#include <map>

#include "zbase.h"

struct ZData
{
    std::string _func_name;
    int _employee;
    int _job;
    int _company;
};

typedef std::map<int,std::map<int, int>> messMAP;

extern messMAP employeeToJobCompany;

extern std::map<std::string, ZBase*> globalDriverData;

#endif // DATA_GLOBALS_H
