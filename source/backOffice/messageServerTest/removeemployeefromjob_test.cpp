#include "basetestclass.hpp"
#include "../messageServer/zparser.h"
#include "../messageServer/zvalidator.h"
#include "../messageServer/removeemployeefromjob.h"
#include "../messageServer/zrpc.h"

class RemoveEmployeeFromJobTest : public BaseTestClass
{
public:
    virtual void SetUp()
    {
        _ob = new RemoveEmployeeFromJob(employeeToJobCompany, false);

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
    }
protected:
    RemoveEmployeeFromJob* _ob;
};


TEST_F(RemoveEmployeeFromJobTest, Remove90EmployeeFromJob100)
{
    // count of map need to be 3
    int nRet = GetMapCount();
    EXPECT_EQ(nRet, 3);

    nRet = ZParser::Parse("removeEmployeeFromJob;90;100;110;", _zdata);
    EXPECT_EQ(nRet, MESS_OK);

    bool bExists = IsEmployeeInMap(90);
    EXPECT_TRUE(bExists);

    nRet = _ob->Dojob(_zdata);
    ASSERT_THAT(nRet, Eq(MESS_OK));

    // check really was deleted?
    nRet = GetMapCount();
    EXPECT_EQ(nRet, 2);

}

TEST_F(RemoveEmployeeFromJobTest, Remove100EmployeeFromJob210)
{
    // count of map need to be 3
    int nRet = GetMapCount();
    EXPECT_EQ(nRet, 3);

    // and count of jobs for employee 100 must be 2
    nRet = GetJobCount(100);
    EXPECT_EQ(nRet, 2);

    nRet = ZParser::Parse("removeEmployeeFromJob;100;210;300;", _zdata);
    EXPECT_EQ(nRet, MESS_OK);

    nRet = _ob->Dojob(_zdata);
    ASSERT_THAT(nRet, Eq(MESS_OK));

    // count of map must be 3 again
    nRet = GetMapCount();
    EXPECT_EQ(nRet, 3);

    // but count of job for employee 100 must be 1
    nRet = GetJobCount(100);
    EXPECT_EQ(nRet, 1);
}
