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
    this->db.open(fileName, std::ios::in | std::ios::out | std::ios::trunc);
    if (!this->db.is_open()) {
        throw std::runtime_error("Can't open dal file: " + fileName);
    }

    this->pageSize = pageSize;
    this->fl = std::make_unique<freeList>();

}

dal::~dal() {
    dal::db.close();
}

 std::unique_ptr<page> dal::allocateEmptyPage() {
    return std::make_unique<page>(this->pageSize);
}

// read data out from the file to a page
std::unique_ptr<page> dal::readPage(int pageNum) {
    std::unique_ptr<page> pageOut = this->allocateEmptyPage();
    int offset = pageNum * this->pageSize;
    db.seekg(offset, std::ios::beg); // seek for the offset starting at beginning
    db.read(reinterpret_cast<char *>((pageOut->data).data()), this->pageSize);
    return pageOut;

}

// write data to file from page
void dal::writePage(std::unique_ptr<page> page) {
    int offset = page->pageNum * this->pageSize;
    db.seekg(offset, std::ios::beg); // seek for the offset starting at beginning
    db.write(reinterpret_cast<char *>((page->data).data()), this->pageSize);
}




