#include "gmock/gmock.h"
#include "../messageServer/zparser.h"
#include "../messageServer/zvalidator.h"
#include "../../global/message_globals.h"
#include "../global/data_globals.h"


using std::string;
using namespace ::testing;

class ZValidatorTest : public Test
{
public:
    ZValidator validator;
};

TEST_F(ZValidatorTest, ValidateNotCorrectFunctionName)
{
    ZData zdata;
    ZParser::Parse("anyFunction;90,100;110;", zdata);
    EXPECT_THAT(validator.Validate(zdata), Eq(MESS_ERR_FUNCTION_NAME));
}

TEST_F(ZValidatorTest, ValidateCorrectFunctionName)
{
    ZData zdata;
    ZParser::Parse("addEmployeeToJob;90,100;110;", zdata);
    EXPECT_THAT(validator.Validate(zdata), Eq(MESS_OK));
}
