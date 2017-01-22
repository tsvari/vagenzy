#include "../global/data_globals.h"
#include "configfile.h"
#include "dbjobsloader.h"

DBJobsLoader::DBJobsLoader(IConfigFile* config):
    _config(config)
{

}

bool DBJobsLoader::LoadJobsFromDB(zdataArr& /*arr*/)
{
    // TODO
    // get connection-string from ConfigFile
    // connect to database and get Resultset of new jobs
    // loop Resultset and fill zdataArr by ZData* objects
    return false;
}
