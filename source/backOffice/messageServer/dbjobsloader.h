#ifndef DBJOBSLOADER_H
#define DBJOBSLOADER_H

#include <vector>

struct ZData;
class IConfigFile;
class ConfigFile;
class ConfigFileMock;

typedef std::vector<ZData*> zdataArr;


class DBJobsLoader
{
public:
    explicit DBJobsLoader(IConfigFile* config);
    virtual bool LoadJobsFromDB(zdataArr& /*arr*/);

protected:
    IConfigFile* _config;
};

class FakeDBJobsLoader : public DBJobsLoader
{
public:
    explicit FakeDBJobsLoader(IConfigFile* config):DBJobsLoader(config){}
    virtual bool LoadJobsFromDB(zdataArr& arr);

};

#endif // DBJOBSLOADER_H
