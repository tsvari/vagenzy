#include "configfile.h"
//#include "../../global/Markup.h"

ConfigFile::ConfigFile(const char* file):
    _file(file)
{

}

bool ConfigFile::Load()
{
    // TODO [vakho] add loading and parsing here later
    //CMarkup mrkp;
    //if(!mrkp.Load(_file))
    //return false;

    return false;
}

bool ConfigFile::GetValue(const std::string& param, std::string& out_value)
{
    std::map<std::string, std::string>::iterator it = _map_param.find(param);
    if(it==_map_param.end())
        return false;

    out_value = static_cast<std::string>(it->second);

    return true;
}

std::string ConfigFile::GetConnectionString() const
{
    return std::string("");
}
