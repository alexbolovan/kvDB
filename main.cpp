#include <iostream>
#include "dal.h"

constexpr int PAGESIZE = 4096;

int main() {
    dal dalInstance("db1.db", PAGESIZE);

    //int pageNum = dalInstance.createPage();
    //std::string s1 = "hello";



    //// hacky way of modifying page data
    //// will have better method, but currently unsure of what data will be inserted
    //dalInstance.cache[pageNum]->data.assign(s1.begin(), s1.end());



    //dalInstance.writePage(pageNum);









}