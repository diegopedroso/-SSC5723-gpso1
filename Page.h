#ifndef _PAGE_H_
#define _PAGE_H_

class Page {
public:
    int number;
    int accessTime;
    bool secondChance;

    Page();
    Page(int number);
    Page(int number, int time);
};

#endif