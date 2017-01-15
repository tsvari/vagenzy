#include "../global/data_globals.h"
#include "zvalidator.h"
#include "../../global/message_globals.h"

int ZValidator::Validate(ZData &zdate)
{
    std::map<std::string, ZBase*>::iterator it = globalDriverData.find(zdate._func_name);
    if(it != globalDriverData.end())
        return MESS_OK;

    return MESS_ERR_FUNCTION_NAME;
}
