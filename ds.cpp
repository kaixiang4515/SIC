#include "ds.h"
#include <functional>
#include <iostream>
hash_table::hash_table() {
    cnt = 0;
    for(int i = 0; i < 1500; ++i) {
        arr[i] = "";
    }
}

void hash_table::insert(std::string key, std::string value) {
    int t = int(std::hash<std::string>{}(key))%691+700;
    arr[t] = value;
    ++cnt;
}

std::string hash_table::at(std::string key) {
    int t = int(std::hash<std::string>{}(key))%691+700;
    return arr[t];
}

unsigned int hash_table::size() {
    return cnt;
}