#ifndef _PAGE_H_
#define _PAGE_H_

class Page {
public:
    int number;         // page number
    int accessTime;     // for LRU algorithm
    bool secondChance;  // for Clock algorithm

    Page();
    Page(int number);
    Page(int number, int time);
};

#endif