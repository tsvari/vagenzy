#include "zeroparser.h"
#include "../../global/message_globals.h"

ZeroParser::ZeroParser(){} // empty constructor, then call parse

ZeroParser::ZeroParser(const char* sMessage)
{
    int nRet = Parse(sMessage);
    if(nRet != MESS_OK)
        throw nRet;
}

unsigned int ZeroParser::Parse(const char* sMessage)
{
    if(!sMessage) return MESS_ERR_ZERO_PARSING;

    string strMsg(sMessage);

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
    _name_functiion = sub_str;

    // parse emploee
    foundStart = foundEnd + 1;
    foundEnd = strMsg.find(";", foundStart);
    if (foundEnd == std::string::npos)
        return MESS_ERR_EMPLOYEE;
    sub_str = strMsg.substr(foundStart,foundEnd-foundStart);
    if(sub_str.length() == 0)
        return MESS_ERR_EMPLOYEE;
    _num_employee = atoi(sub_str.c_str());

    // parse job
    foundStart = foundEnd + 1;
    foundEnd = strMsg.find(";", foundStart);
    if (foundEnd == std::string::npos)
        return MESS_ERR_JOB;
    sub_str = strMsg.substr(foundStart,foundEnd-foundStart);
    if(sub_str.length() == 0)
        return MESS_ERR_JOB;
    _num_job = atoi(sub_str.c_str());

    // parse company
    foundStart = foundEnd + 1;
    foundEnd = strMsg.find(";", foundStart);
    if (foundEnd == std::string::npos)
        return MESS_ERR_COMPANY;
    sub_str = strMsg.substr(foundStart,foundEnd-foundStart);
    if(sub_str.length() == 0)
        return MESS_ERR_COMPANY;
    _num_company = atoi(sub_str.c_str());

    return MESS_OK;
}
