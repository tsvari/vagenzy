#ifndef ZRPC_H
#define ZRPC_H

struct ZData;

class ZRPC
{
public:
    static int CallProc(const ZData& zdata);

};

#endif // ZRPC_H
