#ifndef _RANDTAKE_H_
#define _RANDTAKE_H_

#include <random>

typedef unsigned int uint32;
typedef unsigned long long uint64;

/**
 * @author gpt3.5 
 */
uint32 generateRandomNumber();

/**
 * @author gpt3.5 
 */
int highestNonZeroBit(uint32_t num);

class RandTake
{
    private:
        static int left;
        static uint32 value;
    private:
        RandTake() = delete;
        ~RandTake() = delete;
        RandTake(const RandTake&) = delete;
        RandTake(RandTake&&) = delete;
    public:
        static uint32 Take(int bitlen);
};

#endif