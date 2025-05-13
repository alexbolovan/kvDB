//
// Created by alexb on 2025-05-10.
//

#ifndef PAGE_H
#define PAGE_H
#include <memory>
#include <vector>


class page {
// making public for now, unsure whether all fields should be public
public:
    int pageNum;
    int pageSize;

    // uint8_t = 1 byte
    std::vector<uint8_t> data;

    explicit page(int pageSize);
};


#endif //PAGE_H
