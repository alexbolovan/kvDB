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

    // experimental, idea is that all pages are either in the db file or in the cache
    std::unordered_map<uint32_t, std::unique_ptr<page>> cache;

    explicit dal(const std::string& fileName, int pageSize);
    ~dal();

    std::unique_ptr<page>allocateEmptyPage();
    int createPage();
    void loadPage(const int pageNum);
    void writePage(const int pageNum);
    void deletePage(const int pageNum);
    void evictPage(const int pageNum);


    // Meta structure is:
    // Root Page:
    // -----------------------------------------------------------------------------------
    // |  maxPage  | length of freeList | freelist entry 1 | freelist entry 2 |    ...   |
    // | freelist entry 1021 | next page                                                 |
    // -----------------------------------------------------------------------------------
    //
    // Linked Pages
    // ------------------------------------------------------------------------------------
    // | freelist entry 1 | freelist entry 2 | ... | freelist entry 1023 | next page      |
    // ------------------------------------------------------------------------------------
    // All fields are uint32_t -> 4 bytes

    // Returns tuple of <maxPage, freeList>
    std::tuple<uint32_t, std::vector<uint32_t>> loadMeta();
    void writeMeta();

};


#endif //DAL_H
