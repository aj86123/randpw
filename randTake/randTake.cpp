
#include "randTake.h"

/**
 * @author gpt3.5 
 */
uint32 generateRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32> dis;

    return dis(gen);
}

/**
 * @author gpt3.5 
 */
int highestNonZeroBit(uint32_t num) {
    if (num == 0) {
        return -1; // 如果输入为0，则没有非零位
    }

    int position = 0;
    while (num >>= 1) {
        position++;
    }

    return position;
}

/**
 * @author aj86123
 */
uint32 RandTake::Take(int bitlen)
{
    while(left <= bitlen)
    {
        value = generateRandomNumber();
        left = highestNonZeroBit(value);
        // std::cout << "get new value of " << value << ", total" << left << " bit len" << std::endl; 
    }
    uint32 ret = value & ((1 << bitlen) - 1);
    value >>= bitlen;
    left -= bitlen;
    return ret;
}