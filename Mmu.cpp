#include "Mmu.h"
#include <cmath>
#include <iostream>
#include <climits>

MMU::MMU(int pageSize, int logicalAddressSize, int physicalMemorySize, int swapSize, int replacementAlgorithm) :
pageSize(pageSize),
logicalAddressSize(logicalAddressSize),
physicalMemorySize(physicalMemorySize),
swapSize(swapSize),
virtualPageNumberBits(int (logicalAddressSize - log2(pageSize))),
replacementAlgorithm(replacementAlgorithm) {
    this->physicalMemory = new Page[physicalMemorySize];
    this->time = 0;
    this->swapUsage = 0;
    this->nPages = 0;
}

MMU::~MMU() {
    delete []physicalMemory;
}

bool MMU::mapProcess(int id, int size) {
    // If there is free space in RAM or a process can be moved to Swap to allocate memory to incoming process
    if(swapUsage + nPages + size <= swapSize + physicalMemorySize) {
        mappedProcesses.insert(id);
        nPages += size;
        return true;
    } else { // Otherwise, the process is not created
        return false;
    }
}

bool MMU::find(std::string virtualAddress) {
    int pageNumber = std::stoi(virtualAddress.substr(0, virtualPageNumberBits), nullptr, 2);
    for(int i = 0; i < physicalMemorySize; ++i) {
        // If page is in RAM
        if(physicalMemory[i].number == pageNumber) {
            std::cout << "Page " << pageNumber << " found!\n";
            if(replacementAlgorithm == CLOCK_ALG)
                physicalMemory[i].secondChance = true;
            else if(replacementAlgorithm == LRU_ALG) {
                physicalMemory[i].accessTime = time;
                ++time;
            }
            return true;
        }
    }
    std::cout << "Page fault " << pageNumber << "!\n";
    return false;
}

void MMU::replace(std::string virtualAddress) {
    int pageNumber = std::stoi(virtualAddress.substr(0, virtualPageNumberBits), nullptr, 2);
    if(replacementAlgorithm == LRU_ALG)
        lru(pageNumber);
    else if(replacementAlgorithm == CLOCK_ALG)
        clockSecondChance(pageNumber);
}

void MMU::clockSecondChance(int key) {
    static int pointer = 0;
    while(true) {
        // Finding the page to be removed from RAM
        if(!physicalMemory[pointer].secondChance) {
            if(physicalMemory[pointer].number != -1)
                std::cout << "Page " << physicalMemory[pointer].number << " removed from RAM\n";
            physicalMemory[pointer] = Page(key);
            pointer = (pointer + 1) % physicalMemorySize;
            return;
        }
        physicalMemory[pointer].secondChance = false;
        pointer = (pointer + 1) % physicalMemorySize;
    }
}

void MMU::lru(int key) {
    int lru = INT_MAX, replacedPage;

    // Finding the least recently used page
    for(int i = 0; i < physicalMemorySize; ++i) {
        if(physicalMemory[i].accessTime < lru) {
            lru = physicalMemory[i].accessTime;
            replacedPage = i;
        }
    }

    if(physicalMemory[replacedPage].number != -1)
        std::cout << "Page " << physicalMemory[replacedPage].number << " removed from RAM\n";
    physicalMemory[replacedPage] = Page(key, time);
    ++time;
}

void MMU::printInformation() {
    std::cout << "Replacement algorithm: " << (replacementAlgorithm == CLOCK_ALG ? "Clock\n" : "LRU\n");
    std::cout << "Page size (in bits): " << pageSize << '\n';
    std::cout << "Physical memory size (in pages): " << physicalMemorySize << '\n';
    std::cout << "Swap area size (in pages): " << swapSize << '\n';
    std::cout << "Logical address size (in bits): " << logicalAddressSize << '\n';
}