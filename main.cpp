#include <iostream>
#include <fstream>
#include "Properties.h"
#include "Mmu.h"

using namespace std;

void imprimirTraco(int q) {
    for(; q > 0; --q)
        cout << '-';
    cout << '\n';
}

int main() {
    // Setting up the MMU
    Properties props("config.cfg");
    int pageSize = stoi(props.getValue("page_size")[0]);
    int logicalAddressSize = stoi(props.getValue("logical_adress_size")[0]);
    int physicalMemorySize = stoi(props.getValue("physical_memory_size")[0]);
    int swapSize = stoi(props.getValue("swap_size")[0]);
    int algorithm = props.getValue("replacement_algorithm")[0].compare("lru") ? CLOCK_ALG : LRU_ALG;
    MMU mmu(pageSize, logicalAddressSize, physicalMemorySize, swapSize, algorithm);

    imprimirTraco(60);
    mmu.printInformation();
    imprimirTraco(60);

    // Simulating the simulation file
    ifstream file("simulation.txt");
    string line, address;
    size_t pos;
    char op;
    int processSize, processID;
    while(getline(file, line)) {
        if(!line.length() || line[0] == '#') continue;

        cout << line << "\n\n";

        op = line[3];
        processID = stoi(line.substr(1, line.find_first_of(' ') - 1));
        pos = line.find_last_of(' ');
        address = line.substr(pos + 1);
        switch(op) {
            case 'C': // create process
                processSize = stoi(line.substr(5));
                if(mmu.mapProcess(processID, processSize))
                    cout << "Process " << processID << " created successfully\n";
                else {
                    cout << "Memory is full! Process could not be created!\n";
                    cout << "Aborting...\n";
                    exit(EXIT_FAILURE);
                }
                break;
            case 'W': // memory access
            case 'R':
                cout << "Process " << processID << " accessing memory at " << address << '\n';
                if(!mmu.find(address)) {
                    mmu.replace(address);
                }
                break;
            case 'P': // Instruction fetching
                cout << "Process " << processID << " running instruction at " << address << '\n';
                if(!mmu.find(address)) {
                    mmu.replace(address);
                }
                break;
            case 'I': // I/O operation
                cout << "Process " << processID << " accessing device " << stoi(address, nullptr, 2) << '\n';
                break;
        }

        imprimirTraco(60);
        
    }

    system("pause");
}