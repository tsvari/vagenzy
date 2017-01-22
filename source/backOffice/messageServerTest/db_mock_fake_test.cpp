#include "../messageServer/dbjobsloader.h"
#include "../messageServer/configfile.h"
#include "../messageServer/zrpc.h"
#include "../../global/message_globals.h"
#include "../global/data_globals.h"
#include "gmock/gmock.h"

using ::testing::Eq;
using ::testing::Return;



bool FakeDBJobsLoader::LoadJobsFromDB(zdataArr &arr)
{
    // push to array fake data intead of DB real data
    arr.push_back(new ZData("addEmployeeToJob", 100, 200, 300));
    arr.push_back(new ZData("addEmployeeToJob", 100, 210, 300));
    arr.push_back(new ZData("addEmployeeToJob", 200, 210, 400));
    arr.push_back(new ZData("addEmployeeToJob", 300, 300, 400));

    return true;
}

// declare vector of ZDatas as global to manipulate
zdataArr arr;

TEST(ZDataLoadFromDB, Init_ConfigMock_And_FakeDb)
{

    ConfigFileMock configMock((const char*)CONFIG_FILE);
    FakeDBJobsLoader fakeLoader(&configMock);

    bool bLoad = false;
    EXPECT_CALL(configMock, Load()).
            WillOnce(Return(bLoad));

    fakeLoader.LoadJobsFromDB(arr);
}

TEST(ZDataLoadFromDB, Loop_And_Fill_Map)
{
    // loop and fill employeeToJobCompany
    for(ZData* pZdata : arr)
        EXPECT_THAT(ZRPC::CallProc(ZData(pZdata)), Eq(MESS_OK));

    // now test employeeToJobCompany
    EXPECT_THAT(employeeToJobCompany.size(), Eq(3));
}

