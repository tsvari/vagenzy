#include "../global/data_globals.h"
#include "zparser.h"
#include "../../global/message_globals.h"
#include <string>

using std::string;

int ZParser::Parse(const char* message, ZData& zdata)
{
    if(!message)
        return MESS_ERR_ZERO_PARSING;

    string strMsg(message);

    if(strMsg.length() > MESS_MAX_SIZE)
        return MESS_ERR_OVERSIZE;

    string::size_type foundStart = 0;
    string::size_type foundEnd = strMsg.find(";");

    string sub_str;

    // parse fuction name
    if (foundEnd == std::string::npos)
        return MESS_ERR_FUNCTION_NAME;
    sub_str = strMsg.substr(foundStart,foundEnd);
    if(sub_str.length()<3)
        return MESS_ERR_FUNCTION_NAME;
    zdata._func_name = sub_str;

    // parse emploee
    foundStart = foundEnd + 1;
    foundEnd = strMsg.find(";", foundStart);
    if (foundEnd == std::string::npos)
        return MESS_ERR_EMPLOYEE;
    sub_str = strMsg.substr(foundStart,foundEnd-foundStart);
    if(sub_str.length() == 0)
        return MESS_ERR_EMPLOYEE;
    zdata._employee = atoi(sub_str.c_str());

    // parse job
    foundStart = foundEnd + 1;
    foundEnd = strMsg.find(";", foundStart);
    if (foundEnd == std::string::npos)
        return MESS_ERR_JOB;
    sub_str = strMsg.substr(foundStart,foundEnd-foundStart);
    if(sub_str.length() == 0)
        return MESS_ERR_JOB;
    zdata._job = atoi(sub_str.c_str());

    // parse company
    foundStart = foundEnd + 1;
    foundEnd = strMsg.find(";", foundStart);
    if (foundEnd == std::string::npos)
        return MESS_ERR_COMPANY;
    sub_str = strMsg.substr(foundStart,foundEnd-foundStart);
    if(sub_str.length() == 0)
        return MESS_ERR_COMPANY;
    zdata._company = atoi(sub_str.c_str());

    return MESS_OK;
}
