//
// Created by alexb on 2025-05-10.
//

#ifndef DAL_H
#define DAL_H

#include <fstream>
#include <memory>
#include <unordered_map>

#include "page.h"
#include "freelist.h"
#include "meta.h"


class dal {
    std::fstream db;

public:
    int pageSize;
    freeList fl;
    meta m;

    // experimental, idea is that all pages are either in the db file or in the cache
    std::unordered_map<int, std::unique_ptr<page>> cache;

    explicit dal(const std::string& fileName, int pageSize);
    ~dal();

    std::unique_ptr<page>allocateEmptyPage();
    int createPage();
    void loadPage(const int pageNum);
    void writePage(const int pageNum);
    void deletePage(const int pageNum);
    void evictPage(const int pageNum);

};


#endif //DAL_H
