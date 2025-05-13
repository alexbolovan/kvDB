//
// Created by alexb on 2025-05-10.
//

#include "freelist.h"

#include <iostream>
#include <utility>
#include <vector>

freeList::freeList(uint32_t maxPage, std::vector<uint32_t> freePages) {
    this->maxPage = maxPage; // first page reserved for freelist
    this->freePages = std::move(freePages); // WARNING: not sure if move will cause issues here
}

int freeList::getNextPage() {
    // Check for any release pages we can use
    if (!this->freePages.empty()) {
        int nextPage = this->freePages.front();
        this->freePages.erase(this->freePages.begin());
        return nextPage;
    }

    this->maxPage++;
    return this->maxPage;

}

void freeList::releasePage(int pageNum) {
    // Insert new vector at correct index to ensure freelist vector remains sorted
    auto it = std::lower_bound(this->freePages.begin(), this->freePages.end(), pageNum);
    this->freePages.insert(it, pageNum);
}

void freeList::printFl() {
    for (auto &x : this->freePages) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}





