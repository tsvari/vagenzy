#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include "gmock/gmock.h"
#include <string>
#include <map>

class IConfigFile
{
    virtual bool Load() = 0;
};

class ConfigFile : public IConfigFile
{
public:
    ConfigFile(const char* file);
    virtual bool Load();
    virtual bool GetValue(const std::string& param, std::string& out_value);
    virtual std::string GetConnectionString() const;
private:
    std::map<std::string, std::string> _map_param;
    const char* _file;
};

class ConfigFileMock : public ConfigFile
{
public:
    ConfigFileMock(const char* file):ConfigFile(file){}
    MOCK_METHOD0(Load, bool());
};
#endif // CONFIGFILE_H
