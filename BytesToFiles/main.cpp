#include <iostream>
#include <fstream>
#include "music.h"


int main() {

    unsigned long long nSize = sizeof(music::������Ե);

    std::fstream file("./music.mp3", std::ios::out | std::ios::binary | std::ios::trunc);
    auto str = music::������Ե;
    if (file.is_open())
        for (unsigned long long i = 0; i < nSize; i++, str++)
            file << *str;

    file.close();

    return 0;
}