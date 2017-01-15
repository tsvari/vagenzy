#ifndef ZEROPARSER_H
#define ZEROPARSER_H

#include <string>

using std::string;

class ZeroParser
{
public:
    ZeroParser();
    ZeroParser(const char* sMessage);

    unsigned int Parse(const char* sMessage);

    inline string&  get_function_name(){return _name_functiion;}

    inline int      get_employee(){return _num_employee;}
    inline int      get_job(){return _num_job;}
    inline int      get_company(){return _num_company;}


private:
    string   _name_functiion;

    int      _num_employee;
    int      _num_job;
    int      _num_company;

};

#endif // ZEROPARSER_H
