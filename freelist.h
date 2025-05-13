//
// Created by alexb on 2025-05-10.
//

#ifndef FREELIST_H
#define FREELIST_H
#include <cstdint>
#include <vector>

class freeList {
public:
    uint32_t maxPage;
    std::vector<uint32_t> freePages;

    freeList(uint32_t maxPage = 0, std::vector<uint32_t> freePages = std::vector<uint32_t>());
    int getNextPage();
    void releasePage(int pageNum);

    // Utility methods
    void printFl();

};

#endif //FREELIST_H
