//
// Created by alexb on 2025-05-10.
//

#include "page.h"

#include <vector>

page::page(int pageSize) {
    this->pageNum = -1; // indicates unset page
    this->pageSize = pageSize;
    this->data = std::vector<uint8_t>(pageSize, 0);
}


