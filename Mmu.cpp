#include "Mmu.h"
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <climits>

MMU::MMU(int pageSize, int logicalAddressSize, int physicalMemorySize, int replacementAlgorithm) {
    this->pageSize = pageSize;
    this->logicalAddressSize = logicalAddressSize;
    this->physicalMemorySize = physicalMemorySize;

    this->virtualPageNumberBits = int (logicalAddressSize - log2(pageSize));
    this->physicalMemory = new Page[physicalMemorySize];
    this->time = 0;

    this->replacementAlgorithm = replacementAlgorithm;
}

MMU::~MMU() {
    delete []physicalMemory;
}

bool MMU::find(std::string virtualAddress) {
    int pageNumber = std::stoi(virtualAddress.substr(0, virtualPageNumberBits), nullptr, 2);
    for(int i = 0; i < physicalMemorySize; ++i) {
        if(physicalMemory[i].number == pageNumber) {
            std::cout << "Page " << pageNumber << " found!\n";
            if(replacementAlgorithm == SECOND_CHANCE)
                physicalMemory[i].secondChance = true;
            else if(replacementAlgorithm == LRU) {
                physicalMemory[i].accessTime = time;
                ++time;
            }
            return true;
        }
    }
    std::cout << "Page fault: " << pageNumber << "!\n";
    return false;
}

void MMU::replace(std::string virtualAddress) {
    int pageNumber = std::stoi(virtualAddress.substr(0, virtualPageNumberBits), nullptr, 2);
    if(replacementAlgorithm == LRU)
        lru(pageNumber);
    else if(replacementAlgorithm == SECOND_CHANCE)
        secondChance(pageNumber);
}

void MMU::secondChance(int key) {
    static int pointer = 0;
    while(true) {
        if(!physicalMemory[pointer].secondChance) {
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
    for(int i = 0; i < physicalMemorySize; ++i) {
        if(physicalMemory[i].accessTime < lru) {
            lru = physicalMemory[i].accessTime;
            replacedPage = i;
        }
    }
    physicalMemory[replacedPage] = Page(key, time);
    ++time;
}