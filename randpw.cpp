#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <map>

// int getopt(int argc, char * const argv[],const char *optstring) glibc

const char *optstring = "l:h";

std::map<char,std::string> cmdArgs;

int init()
{
    srand(static_cast<unsigned int>(std::time(nullptr)));
    cmdArgs.clear();
}

void parseArgs(int argc, char **argv)
{
    printf("optind:%d opterr:%d\n",optind,opterr);
    char ch;
    while((ch = getopt(argc, argv, optstring)) != -1)
    {
        switch(ch)
        {
        case 'l':
            cmdArgs.insert(std::make_pair('l', optarg));
            break;
        case 'h':
            cmdArgs.insert(std::make_pair('h', optarg));
            break;
        case '?':
            printf("Unknown option: %c\n", (char)optopt);
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    parseArgs(argc, argv);

    return 0;
}