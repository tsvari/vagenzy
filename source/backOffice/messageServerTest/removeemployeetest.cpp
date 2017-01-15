#include "basetestclass.hpp"
#include "../messageServer/zparser.h"
#include "../messageServer/zvalidator.h"
#include "../messageServer/removeemployee.h"
#include "../messageServer/zrpc.h"

class RemoveEmployeeTest : public BaseTestClass
{
public:
    virtual void SetUp()
    {
        _ob = new RemoveEmployee(employeeToJobCompany, false);

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
    RemoveEmployee* _ob;
};

TEST_F(RemoveEmployeeTest, RemoveEmployeesStepByStep)
{
    // count of map need to be 3
    int nRet = GetMapCount();
    EXPECT_EQ(nRet, 3);

    nRet = ZParser::Parse("removeEmployee;90;0;110;", _zdata);
    EXPECT_EQ(nRet, MESS_OK);

    nRet = _ob->Dojob(_zdata);
    ASSERT_THAT(nRet, Eq(MESS_OK));

    // count of map must be 2
    nRet = GetMapCount();
    EXPECT_EQ(nRet, 2);

    // now delete 100
    //-------------------------------------------------------
    nRet = ZParser::Parse("removeEmployee;100;0;300;", _zdata);
    EXPECT_EQ(nRet, MESS_OK);

    nRet = _ob->Dojob(_zdata);
    ASSERT_THAT(nRet, Eq(MESS_OK));

    // count of map must be 2
    nRet = GetMapCount();
    EXPECT_EQ(nRet, 1);

    // try to delete 100 again
    //-------------------------------------------------------
    nRet = ZParser::Parse("removeEmployee;100;0;300;", _zdata);
    EXPECT_EQ(nRet, MESS_OK);

    nRet = _ob->Dojob(_zdata);
    ASSERT_THAT(nRet, Eq(MESS_ERR_EMPLOYEE));

    // count of map must be 1 again
    nRet = GetMapCount();
    EXPECT_EQ(nRet, 1);

    // try to delete last 110
    //-------------------------------------------------------
    nRet = ZParser::Parse("removeEmployee;110;0;300;", _zdata);
    EXPECT_EQ(nRet, MESS_OK);

    nRet = _ob->Dojob(_zdata);
    ASSERT_THAT(nRet, Eq(MESS_OK));

    // count of map must be 0
    nRet = GetMapCount();
    EXPECT_EQ(nRet, 0);
}
