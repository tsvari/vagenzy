#include "gmock/gmock.h"
#include "../global/data_globals.h"
#include "../messageServer/checkjob.h"
#include "../messageServer/removeemployee.h"
#include "../messageServer/removeemployeefromjob.h"
#include "../messageServer/addemployeetojob.h"

messMAP employeeToJobCompany;
std::map<std::string, ZBase*> globalDriverData;

int main(int argc, char *argv[])
{
    globalDriverData.insert(std::pair<std::string, ZBase*>("checkJob", new CheckJob(employeeToJobCompany, false)));
    globalDriverData.insert(std::pair<std::string, ZBase*>("addEmployeeToJob", new AddEmployeeToJob(employeeToJobCompany,false)));
    globalDriverData.insert(std::pair<std::string, ZBase*>("removeEmployeeFromJob", new RemoveEmployeeFromJob(employeeToJobCompany, false)));
    globalDriverData.insert(std::pair<std::string, ZBase*>("removeEmployee", new RemoveEmployee(employeeToJobCompany, false)));

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
