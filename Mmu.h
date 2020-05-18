#ifndef _MMU_H_
#define _MMU_H_

#include <vector>
#include <string>
#include "Page.h"

class MMU {
public:
    int pageSize;
    int logicalAddressSize;
    int physicalMemorySize;
    // int virtualMemorySize;
    int virtualPageNumberBits;

    Page * physicalMemory;

    MMU(int pageSize, int logicalAddressSize, int physicalMemorySize);
    ~MMU();
    bool find(std::string virtualAddress);
    void replace(std::string virtualAddress);

private:
    void secondChance(int key);
};

#endif