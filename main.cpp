#include <iostream>
#include "dal.h"

constexpr int PAGESIZE = 4096;

int main() {
    dal dalInstance("db1.db", PAGESIZE);
    auto p = dalInstance.allocateEmptyPage();
    p->pageNum = dalInstance.fl->getNextPage();

    std::string sample1 = "hello";
    p->data.assign(sample1.begin(), sample1.end());

    auto p2 = dalInstance.allocateEmptyPage();
    p2->pageNum = dalInstance.fl->getNextPage();

    std::string sample2 = "bye";
    p2->data.assign(sample2.begin(), sample2.end());



    dalInstance.writePage(std::move(p));
    dalInstance.writePage(std::move(p2));


}