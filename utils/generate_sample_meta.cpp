#include <fstream>
#include <filesystem>
#include <cstdint>
#include <iostream>

int main() {
    std::ofstream out("db1.db", std::ios::binary);

    // First 4 bytes: number 69
    uint32_t a = 69;
    out.write(reinterpret_cast<const char*>(&a), sizeof(a));

    // Next 4 bytes: number 20
    uint32_t b = 2000;
    out.write(reinterpret_cast<const char*>(&b), sizeof(b));

    // Next 20 chunks of 4 bytes: numbers 1 to 20
    for (uint32_t i = 1; i <= 1021; ++i) {
        out.write(reinterpret_cast<const char*>(&i), sizeof(i));
    }
    
    int x = 2;
    out.write(reinterpret_cast<const char *>(&x), sizeof(x));

    for (uint32_t i = 0; i < 1024; ++i) {
        int y = 0;
        out.write(reinterpret_cast<const char *>(&y), sizeof(x));
    }

    for (uint32_t i = 1022; i <= 2000; ++i) {
        out.write(reinterpret_cast<const char*>(&i), sizeof(i));
    }






    out.close();
    return 0;
}