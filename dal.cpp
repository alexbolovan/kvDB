//
// Created by alexb on 2025-05-10.
//

#include "dal.h"
#include "freelist.h"
#include "meta.h"
#include <fstream>
#include <filesystem>
#include <iostream>


dal::dal(const std::string& fileName, int pageSize) {
    // DB file does not exist
    if (!std::filesystem::exists(fileName)) {
        std::cout << fileName << " created" << std::endl;
        std::ofstream touch(fileName);
        this->db.open(fileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);

        if (!this->db.is_open()) {
            throw std::runtime_error("Can't open dal file: " + fileName);
        }

        this->pageSize = pageSize;
        this->fl = freeList();
    } else { // Load existing db file
        this->db.open(fileName, std::ios::in | std::ios::out | std::ios::binary);
        if (!this->db.is_open()) {
            throw std::runtime_error("Can't open dal file: " + fileName);
        }

        this->pageSize = pageSize;

        std::tuple<uint32_t, std::vector<uint32_t>> metaData = std::move(loadMeta());
        this->fl.maxPage = std::get<0>(metaData);
        this->fl.freePages = std::get<1>(metaData); // Could use move?




    }

}

dal::~dal() {
    // Write to update meta page upon next restore
    this->writeMeta();
    dal::db.close();
    std::cout << "DAL closed" << std::endl;
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
    // Prevent accidental deletion of data by writing it back to memory
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

std::tuple<uint32_t, std::vector<uint32_t>> dal::loadMeta() {
    // Start at root page
    uint32_t currPage = 0;

    uint32_t maxPage = 0;
    std::vector<uint32_t> freeList;


    // Retrieving maxPage
    db.seekg(0, std::ios::beg);
    db.read(reinterpret_cast<char *>(&maxPage), 4);


    // Retrieving size of freeList
    // Cast size to uint32_t to ensure consistent serialization
    uint32_t freeListSize = 1; // So Intellisense doesn't bitch, should be set to 0
    db.read(reinterpret_cast<char *>(&freeListSize), sizeof(uint32_t));

    // Retrieve freelist
    int remainingInPage = (this->pageSize - (3 * sizeof(uint32_t))) / sizeof(uint32_t);
    int offset = 8;
    std::cout << "Page 0" << std::endl;
    for (uint32_t i = 0; i < freeListSize; i++) {

        // Read the next entry and store it in the freelist
        uint32_t freeListEntry = 0;
        db.read(reinterpret_cast<char *>(&freeListEntry), sizeof(uint32_t));
        freeList.push_back(freeListEntry);


        --remainingInPage;

        if (remainingInPage == 0) {
            // Read the value of the next page and calculate the offset and move the seek to it
            db.read(reinterpret_cast<char *>(&currPage),sizeof(uint32_t));
            std::cout << "Page " << std::to_string(currPage) << std::endl;
            offset = currPage * this->pageSize;
            db.seekg(offset, std::ios::beg);
            remainingInPage = (this->pageSize - 4) / 4;
        }
    }

    std::cout << "Max Page: "  << std::to_string(static_cast<uint32_t>(maxPage)) << std::endl;
    for (auto &x : freeList) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return std::make_tuple(maxPage, freeList);

}

void dal::writeMeta() {
    // Start by calculating the number of additional pages we need to store all freelist data

    //db.seekg(0, std::ios::beg);
    //db.write(reinterpret_cast<char *>((this->fl.freePages).data()), this->pageSize);
}







