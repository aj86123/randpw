#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <map>
#include <vector>
#include <memory>
#include "randTake.h"

using FuncPtr = uint32 (*)(int);

// int getopt(int argc, char * const argv[],const char *optstring) glibc

const char *optstring = "l:d:a:i:u:s:h";

std::map<char,std::string> cmdArgs;

const char* allSignals = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

/**
 * @param l len of the passwd
 * @param d num of digit [0-9]
 * @param a num of alpha [a-zA-Z]
 * @param i num of lowercase alpha [a-z]
 * @param u num of uppercase alpha [A-Z]
 * @param s num of signal   [!@#$%^&*()_+{}|:">?./;'[]\`~]
 */
void parseArgs(int argc, char **argv)
{
    char ch;
    while((ch = getopt(argc, argv, optstring)) != -1)
    {
        switch(ch)
        {
        case 'l':
            cmdArgs.insert(std::make_pair('l', optarg));
            break;
        case 'd':
            cmdArgs.insert(std::make_pair('d', optarg));
            break;
        case 'a':
            cmdArgs.insert(std::make_pair('a', optarg));
            break;
        case 'i':
            cmdArgs.insert(std::make_pair('i', optarg));
            break;
        case 'u':
            cmdArgs.insert(std::make_pair('u', optarg));
            break;
        case 's':
            cmdArgs.insert(std::make_pair('s', optarg));
            break;
        case 'h':
            cmdArgs.insert(std::make_pair('h', ""));
            break;
        default:
            printf("Unknown option: %c\n", (char)optopt);
            break;
        }
    }
}

std::map<char,int> checkArgs()
{
    // default value
    std::map<char,int> ret ={{'a',0},
                             {'i',0},
                             {'u',0},
                             {'l',20},
                             {'d',0},
                             {'s',0}};
    /* 
    *   a <= i + u
    *   l <= d + a + s
    */

    for(auto it : cmdArgs)
    {
        auto key = it.first;
        auto value = atoi(it.second.c_str());
        ret[key] = value;
    }

    // todo 完善各参数的实际作用

    return ret;
}

int main(int argc, char *argv[])
{
    FuncPtr getNum = RandTake::Take;        // 用来获取随机数，参数为二进制bit数

    parseArgs(argc, argv);
    if(cmdArgs.find('h') != cmdArgs.end())
    {
        printf( " * @param l len of the passwd\n"
                " * @param d num of digit [0-9]\n"
                " * @param a num of alpha [a-zA-Z]\n"
                " * @param i num of lowercase alpha [a-z]\n"
                " * @param u num of uppercase alpha [A-Z]\n"
                " * @param s num of signal   !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");
        return 0;
    }
    auto argsMap = checkArgs();
    if(argsMap.size() == 0)
    {
        printf("error total num of args\n");
        return 0;
    }

    // todo完善各参数的实际作用
    const int len = argsMap['l'];
    auto passwd = std::make_unique<char[]>(len+1);
    
    for(int i = 0;i < len;i++)
    {
        char c = ' ';
        char character_type = getNum(2);
        switch(character_type) {
            case 0x00:  // digit
                for(;!((c = getNum(4)) < 10););
                c = '0' + c;
                break;
            case 0x01:  // signal
                c = getNum(5);
                c = allSignals[c];
                break;
            case 0x02:  // lower letter
                for(;!((c = getNum(5)) < 26););
                c = 'a' + c;
                break;
            case 0x03:  // upper letter
                for(;!((c = getNum(5)) < 26););
                c = 'A' + c;
                break;
            default:
                printf("error for character_type %d\n", character_type);
                exit(-1);
        }
        passwd[i] = c;
    }
    std::cout << passwd.get() << std::endl;
    return 0;
}