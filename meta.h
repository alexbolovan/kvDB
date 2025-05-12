//
// Created by alexb on 2025-05-11.
//

#ifndef META_H
#define META_H

// Describes page 0 in db to restore state (of freelist) upon restart

// Page structure is:
// ----------------------------------------------------------------------------------
// |  maxPage  | length of freeList | freelist entry 1 | freelist entry 2 | ...     |
// ----------------------------------------------------------------------------------
class meta {
    int maxPage;
    int numEntries;

public:
    void loadFreeList();
    void writeFreeList();

};


#endif //META_H
