#include "basetestclass.hpp"
#include "../messageServer/zparser.h"
#include "../messageServer/zvalidator.h"
#include "../messageServer/checkjob.h"
#include "../messageServer/zrpc.h"

class CheckJobTest : public BaseTestClass
{
public:
    virtual void SetUp()
    {
        _ob = new CheckJob(employeeToJobCompany, false);

        ZParser::Parse("addEmployeeToJob;90;100;110;", _zdata);
        int nRet = ZRPC::CallProc(_zdata);
        ASSERT_THAT(nRet, Eq(MESS_OK));

        ZParser::Parse("addEmployeeToJob;100;200;300;", _zdata);
        nRet = ZRPC::CallProc(_zdata);
        ASSERT_THAT(nRet, Eq(MESS_OK));

        ZParser::Parse("addEmployeeToJob;100;210;300;", _zdata);
        nRet = ZRPC::CallProc(_zdata);
        ASSERT_THAT(nRet, Eq(MESS_OK));

        ZParser::Parse("addEmployeeToJob;110;210;300;", _zdata);
        nRet = ZRPC::CallProc(_zdata);
        ASSERT_THAT(nRet, Eq(MESS_OK));

        // need to check count of map members and job mambers by employee
        nRet = GetMapCount();
        EXPECT_EQ(nRet, 3);

        nRet = GetJobCount(90);
        EXPECT_EQ(nRet, 1);

        nRet = GetJobCount(100);
        EXPECT_EQ(nRet, 2);

        nRet = GetJobCount(110);
        EXPECT_EQ(nRet, 1);
    }
    virtual void TearDown()
    {
        delete _ob;
    }
protected:
    CheckJob* _ob;
};


// test object CheckJob
TEST_F(CheckJobTest, RealChekJob)
{
    int nRet = ZParser::Parse("checkJob;100;0;0;", _zdata);
    EXPECT_EQ(nRet, MESS_OK);

    nRet = _ob->Dojob(_zdata);
    EXPECT_EQ(nRet, 2);

    ZParser::Parse("checkJob;90;0;0;", _zdata);
    nRet = _ob->Dojob(_zdata);
    EXPECT_EQ(nRet, 1);

    ZParser::Parse("checkJob;110;0;0;", _zdata);
    nRet = _ob->Dojob(_zdata);
    EXPECT_EQ(nRet, 1);

    ZParser::Parse("checkJob;5;0;0;", _zdata);
    nRet = _ob->Dojob(_zdata);
    EXPECT_EQ(nRet, 0);

    // Clean main map in last test
    CleanMainMap();
}

