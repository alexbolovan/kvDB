//
// Created by alexb on 2025-05-11.
//

#include "meta.h"

std::tuple<int, int, std::vector<int>> meta::loadFreeList() {
    std::tuple<int, int, std::vector<int>> data;

    // Deserialize maxPage

    // Deserialize numEntries

    // Deserialize freelist entries

    return data;
}

void meta::writeFreeList(int maxPage, int numEntries, std::vector<int>& entries) {
    // Serialize maxPage

    // Serialize numEntries

    // Serialize freelist entries

}

