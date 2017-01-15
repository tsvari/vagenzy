#include "gmock/gmock.h"
#include "../messageServer/zparser.h"
#include "../messageServer/zrpc.h"
#include "../messageServer/zvalidator.h"
#include "../../global/message_globals.h"
#include "../global/data_globals.h"


using std::string;
using namespace ::testing;

class ZRPCTest : public Test
{
public:
    ZRPC rpc;
};

TEST_F(ZRPCTest, CallAddnewEmployee)
{
    ZData zdata;
    ZParser::Parse("addEmployeeToJob;90,100;110;", zdata);
    EXPECT_THAT(rpc.CallProc(zdata), Eq(MESS_OK));

    // Clean main map in last test
    employeeToJobCompany.clear();
}
