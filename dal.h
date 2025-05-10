//
// Created by alexb on 2025-05-10.
//

#ifndef DAL_H
#define DAL_H

#include <fstream>
#include "page.h"
#include <memory>

#include "freelist.h"

class dal {
    std::fstream db;

public:
    int pageSize;
    std::unique_ptr<freeList> fl;

    explicit dal(const std::string& fileName, int pageSize);
    ~dal();

    std::unique_ptr<page>allocateEmptyPage();
    std::unique_ptr<page> readPage(const int pageNum);
    void writePage(std::unique_ptr<page> page);

};


#endif //DAL_H
