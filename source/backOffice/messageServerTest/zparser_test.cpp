#include "gmock/gmock.h"
#include "../messageServer/zparser.h"
#include "../../global/message_globals.h"
#include "../global/data_globals.h"
#include <string>

using std::string;
using namespace ::testing;


class ZParserTest : public Test
{
public:
    ZParser parser;
};


/* ! Test for error messages
 *
*/

/* return MESS_ERR_ZERO_PARSING when null string
*/
TEST_F(ZParserTest, ParseNullMessage)
{
    ZData zdata;
    ASSERT_THAT(parser.Parse(0, zdata), Eq(MESS_ERR_ZERO_PARSING));
}

/* return MESS_ERR_OVERSIZE when more then 100 symbols
*/
TEST_F(ZParserTest, ParseOverSize)
{
    ZData zdata;
    string str(MESS_MAX_SIZE+1, 'a');
    ASSERT_THAT(parser.Parse(str.c_str(), zdata), Eq(MESS_ERR_OVERSIZE));
}

/* return MESS_ERR_FUNCTION_NAME when no first semicolon ;
*/
TEST_F(ZParserTest, ParseFunctionNameNoSamicolon)
{
    ZData zdata;
    ASSERT_THAT(parser.Parse("wrewrwe", zdata), Eq(MESS_ERR_FUNCTION_NAME));
}

/* return MESS_ERR_FUNCTION_NAME when function name is less then 3 ;
*/
TEST_F(ZParserTest, ParseFunctionNameShort)
{
    ZData zdata;
    ASSERT_THAT(parser.Parse("ww", zdata), Eq(MESS_ERR_FUNCTION_NAME));
}

/* return MESS_ERR_EMPLOYEE when no second semicolon ;
*/
TEST_F(ZParserTest, ParseEmployeeNoSamicolon)
{
    ZData zdata;
    ASSERT_THAT(parser.Parse("Func;iuiui", zdata), Eq(MESS_ERR_EMPLOYEE));
}

/* return MESS_ERR_EMPLOYEE when nothing to convert to integer
*/
TEST_F(ZParserTest, ParseEmployeeNoNumber)
{
    ZData zdata;
    ASSERT_THAT(parser.Parse("Func;;", zdata), Eq(MESS_ERR_EMPLOYEE));
}

/* return MESS_ERR_JOB when no third semicolon ;
*/
TEST_F(ZParserTest, ParseJobNoSamicolon)
{
    ZData zdata;
    ASSERT_THAT(parser.Parse("Func;iuiui;", zdata), Eq(MESS_ERR_JOB));
}

/* return MESS_ERR_JOB when nothing to convert to integer
*/
TEST_F(ZParserTest, ParseJobNoNumber)
{
    ZData zdata;
    ASSERT_THAT(parser.Parse("Func;turut;;", zdata), Eq(MESS_ERR_JOB));
}

/* return MESS_ERR_COMPANY when no forth semicolon ;
*/
TEST_F(ZParserTest, ParseCompanyNoSamicolon)
{
    ZData zdata;
    ASSERT_THAT(parser.Parse("Func;iuiui;try;rty", zdata), Eq(MESS_ERR_COMPANY));
}

/* returns MESS_ERR_COMPANY when nothing to convert to integer
*/
TEST_F(ZParserTest, ParseCompanyNoNumber)
{
    ZData zdata;
    ASSERT_THAT(parser.Parse("Func;turut;rytry;;", zdata), Eq(MESS_ERR_COMPANY));
}

/* test real semicolon message
*/
TEST_F(ZParserTest, ParseRealMessage)
{
    ZData zdata;

    EXPECT_THAT(parser.Parse("Func1;100;200;300;", zdata), Eq(MESS_OK));

    EXPECT_THAT(zdata._func_name, Eq("Func1"));
    EXPECT_THAT(zdata._employee, Eq(100));
    EXPECT_THAT(zdata._job, Eq(200));
    EXPECT_THAT(zdata._company, Eq(300));
}
