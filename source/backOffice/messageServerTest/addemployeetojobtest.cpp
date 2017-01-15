#include "gmock/gmock.h"
#include "basetestclass.hpp"
#include "../messageServer/zparser.h"
#include "../messageServer/zvalidator.h"
#include "../messageServer/addemployeetojob.h"


class AddEmployeeToJobTest : public BaseTestClass
{
public:
    virtual void SetUp()
    {
        _ob = new AddEmployeeToJob(employeeToJobCompany, false);
    }
    virtual void TearDown()
    {
        delete _ob;
    }

protected:
    AddEmployeeToJob* _ob;
};


TEST_F(AddEmployeeToJobTest, SimplyMesureSize)
{
    int nRet = GetMapCount();
    EXPECT_EQ(nRet, 0);
}

TEST_F(AddEmployeeToJobTest, AddNewEmployee)
{
    int nRet = ZParser::Parse("addEmployeeToJob;100;200;300;", _zdata);
    EXPECT_EQ(nRet, MESS_OK);

    nRet = ZValidator::Validate(_zdata);
    ASSERT_THAT(nRet, Eq(MESS_OK));

    nRet = _ob->Dojob(_zdata);
    ASSERT_THAT(nRet, Eq(MESS_OK));

    // we have now 1 employees
    nRet = GetMapCount();
    EXPECT_EQ(nRet, 1);
}

TEST_F(AddEmployeeToJobTest, AddSameJobForThisEmployeeAgain)
{
    int nRet = ZParser::Parse("addEmployeeToJob;100;200;300;", _zdata);
    EXPECT_EQ(nRet, MESS_OK);

    ASSERT_THAT(_ob->Dojob(_zdata), Eq(MESS_OK));

    // repeatedly adding same job shouldn't affect on main map size
    EXPECT_EQ(GetMapCount(), 1);

    int nCount = GetJobCount(_zdata._employee);

    // repeatedly adding same job shouldn't affect on job map size
    EXPECT_EQ(nCount, 1);
}


TEST_F(AddEmployeeToJobTest, AddNewJobForEmployee100Again)
{
    int nRet = ZParser::Parse("addEmployeeToJob;100;210;300;", _zdata);
    EXPECT_EQ(nRet, MESS_OK);

    nRet = _ob->Dojob(_zdata);
    ASSERT_THAT(nRet, Eq(MESS_OK));

    // we still have 1 employees
    nRet = GetMapCount();
    EXPECT_EQ(nRet, 1);

    // but 2 jobs for Employee-100
    nRet = GetJobCount(_zdata._employee);
    EXPECT_EQ(nRet, 2);
}


TEST_F(AddEmployeeToJobTest, AddNewEmployeeWithSameJob)
{
    int nRet = ZParser::Parse("addEmployeeToJob;110;210;300;", _zdata);
    EXPECT_EQ(nRet, MESS_OK);

    nRet = _ob->Dojob(_zdata);
    ASSERT_THAT(nRet, Eq(MESS_OK));

    // we have 2 employees now
    nRet = GetMapCount();
    EXPECT_EQ(nRet, 2);

    // Clean main map in last test
    CleanMainMap();
}

