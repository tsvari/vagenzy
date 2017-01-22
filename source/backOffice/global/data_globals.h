#ifndef DATA_GLOBALS_H
#define DATA_GLOBALS_H

#include <string>
#include <map>

#include "zbase.h"

struct ZData
{
    ZData():
        _func_name(""),
        _employee(0),
        _job(0),
        _company(0){}
    ZData(const std::string& func_name,int employee,int job,int company):
        _func_name(func_name),
        _employee(employee),
        _job(job),
        _company(company){}
    explicit ZData(const ZData* pZdata):
        _func_name(pZdata->_func_name),
        _employee(pZdata->_employee),
        _job(pZdata->_job),
        _company(pZdata->_company){}

    std::string _func_name;
    int _employee;
    int _job;
    int _company;
};

typedef std::map<int,std::map<int, int>> messMAP;

extern messMAP employeeToJobCompany;

extern std::map<std::string, ZBase*> globalDriverData;

#endif // DATA_GLOBALS_H
