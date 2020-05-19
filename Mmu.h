#ifndef _MMU_H_
#define _MMU_H_

#include <vector>
#include <string>
#include "Page.h"

#define LRU 0
#define SECOND_CHANCE 1

class MMU {
public:
    int pageSize;
    int logicalAddressSize;
    int physicalMemorySize;
    int virtualPageNumberBits;

    Page * physicalMemory;
    int time;

    int replacementAlgorithm;

    MMU(int pageSize, int logicalAddressSize, int physicalMemorySize, int replacementAlgorithm);
    ~MMU();
    bool find(std::string virtualAddress);
    void replace(std::string virtualAddress);

private:
    void secondChance(int key);
    void lru(int key);
};

#endif