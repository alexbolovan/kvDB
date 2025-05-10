//
// Created by alexb on 2025-05-10.
//

#ifndef FREELIST_H
#define FREELIST_H
#include <vector>

class freeList {
public:
    int maxPage;
    std::vector<int> freePages;

    freeList();
    int getNextPage();
    void releasePage(int pageNum);

};

#endif //FREELIST_H
