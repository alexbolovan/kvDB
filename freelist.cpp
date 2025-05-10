//
// Created by alexb on 2025-05-10.
//

#include "freelist.h"

#include <vector>

freeList::freeList() {
    this->maxPage = 0; // first page reserved for freelist
    this->freePages = std::vector<int>();
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




