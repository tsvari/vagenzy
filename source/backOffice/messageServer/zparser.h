#ifndef ZPARSER_H
#define ZPARSER_H


struct ZData;

class ZParser
{
public:
    static int Parse(const char* message, ZData& zdata);
};

#endif // ZPARSER_H
