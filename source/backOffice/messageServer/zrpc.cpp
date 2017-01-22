#include "../global/data_globals.h"
#include "zrpc.h"
#include "../../global/message_globals.h"

int ZRPC::CallProc(const ZData &zdata)
{
    std::map<std::string, ZBase*>::iterator it = globalDriverData.find(zdata._func_name);

    if(it == globalDriverData.end())
        return MESS_ERR_FUNCTION_NAME;

    ZBase* pOb = dynamic_cast<ZBase*>(it->second);
    return pOb->Dojob(zdata);
}
