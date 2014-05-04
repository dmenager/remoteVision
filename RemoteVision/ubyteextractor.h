#ifndef UBYTEEXTRACTOR_H
#define UBYTEEXTRACTOR_H

#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <byteswap.h>
#include <arpa/inet.h>

class UbyteExtractor
{
    public:
          UbyteExtractor();
          virtual ~UbyteExtractor();
          void convert();
    private:
          void build(std::fstream& fin, std::fstream& fin2, std::ofstream& fout, std::ofstream& log);

};

#endif // UBYTEEXTRACTOR_H
