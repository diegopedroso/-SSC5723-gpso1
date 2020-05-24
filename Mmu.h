#ifndef _MMU_H_
#define _MMU_H_

#include <vector>
#include <string>
#include <set>
#include "Page.h"

#define LRU_ALG 0
#define CLOCK_ALG 1

class MMU {
public:
    const int pageSize;                 // size of page in bits
    const int logicalAddressSize;       // size of logical address
    const int physicalMemorySize;       // physical memory size in pages
    const int virtualPageNumberBits;    // number of bits to address a virtual page
    const int swapSize;                 // size of swap area in pages
    const int replacementAlgorithm;     // algorithm to page replacemente (LRU or CLOCK)

    Page * physicalMemory;              // Pages in physical memory
    std::set<int> mappedProcesses;      // Processes that are in RAM or Swap
    int time;                           // Clock time in which a page is referenced (for CLOCK algorithm)
    int swapUsage;                      // number of pages stored in Swap
    int nPages;                         // total number of pages in RAM and Swap

    MMU(int pageSize, int logicalAddressSize, int physicalMemorySize, int swapSize, int replacementAlgorithm);
    ~MMU();
    bool find(std::string virtualAddress);
    void replace(std::string virtualAddress);
    bool mapProcess(int id, int size);
    void printInformation();

private:
    // Replacement algorithms
    void clockSecondChance(int key);
    void lru(int key);
};

#endif