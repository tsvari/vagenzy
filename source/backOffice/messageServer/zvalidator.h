#ifndef ZVALIDATOR_H
#define ZVALIDATOR_H

struct ZData;

class ZValidator
{
public:
    static int Validate(const ZData& zdate);
};

#endif // ZVALIDATOR_H
