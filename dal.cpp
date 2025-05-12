//
// Created by alexb on 2025-05-10.
//

#include "dal.h"
#include "freelist.h"
#include <fstream>
#include <filesystem>
#include <iostream>

dal::dal(const std::string& fileName, int pageSize) {
    // Creating and opening file
    if (!std::filesystem::exists(fileName)) {
        std::ofstream touch(fileName);
    }
    this->db.open(fileName, std::ios::in | std::ios::out);
    if (!this->db.is_open()) {
        throw std::runtime_error("Can't open dal file: " + fileName);
    }

    this->pageSize = pageSize;
    this->fl = freeList();

}

dal::~dal() {
    // Write to update meta page upon next restore
    this->m.writeFreeList();

    dal::db.close();
    std::cout << "DB closed" << std::endl;
}

// NOTE: should probably be set to private and callers should use methods below
 std::unique_ptr<page> dal::allocateEmptyPage() {
    return std::make_unique<page>(this->pageSize);
}

// Create page and return pageNum
int dal::createPage() {
    int pageNum = this->fl.getNextPage();
    std::unique_ptr<page> newPage = this->allocateEmptyPage();
    this->cache.insert(std::make_pair(pageNum, std::move(newPage)));
    return pageNum;

}

// read data OUT from the file to a page
void dal::loadPage(const int pageNum) {
    std::unique_ptr<page> pageOut = this->allocateEmptyPage();
    int offset = pageNum * this->pageSize;
    db.seekg(offset, std::ios::beg); // seek for the offset starting at beginning
    db.read(reinterpret_cast<char *>((pageOut->data).data()), this->pageSize);

    // Add page new page to cache
    this->cache.insert(std::make_pair(pageNum, std::move(pageOut)));

}

// write data IN to file from page
void dal::writePage(const int pageNum) {
    int offset = pageNum * this->pageSize;
    db.seekg(offset, std::ios::beg); // seek for the offset starting at beginning

    if (!cache.contains(pageNum)) {
        throw std::runtime_error("Page " + std::to_string(pageNum) + " not in cache/memory");
    }
    db.write(reinterpret_cast<char *>((cache[pageNum]->data).data()), this->pageSize);
}


// Evict page from cache
// Does NOT delete page from memory
void dal::evictPage(const int pageNum) {
    // Prevent accidential deletion of data by writing it back to memory
    writePage(pageNum);

    this->cache.erase(pageNum);
}

// Zero out page in memory and free it from freelist
void dal::deletePage(const int pageNum) {
    // Zero out page in file
    int offset = pageNum * this->pageSize;
    db.seekg(offset, std::ios::beg); // seek for the offset starting at beginning
    std::vector<uint8_t> zeroedOut(this->pageSize, 0);
    db.write(reinterpret_cast<char *>((zeroedOut).data()), this->pageSize);

    // Release Page in freelist
    this->fl.releasePage(pageNum);



}





