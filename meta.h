//
// Created by alexb on 2025-05-11.
//

#ifndef META_H
#define META_H
#include <vector>

// Describes page 0 in db to restore state (of freelist) upon restart

// Page structure is:
// ----------------------------------------------------------------------------------
// |  maxPage  | length of freeList | freelist entry 1 | freelist entry 2 | ...     |
// ----------------------------------------------------------------------------------
class meta {
    int maxPage;
    int numEntries;

public:
    std::tuple<int, int, std::vector<int>> loadFreeList();
    void writeFreeList(int maxPage, int numEntries, std::vector<int>& entries);

};


#endif //META_H
