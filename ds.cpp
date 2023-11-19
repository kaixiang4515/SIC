#include "ds.h"
#include <functional>
#include <iostream>
hash_table::hash_table() {
    cnt = 0;
    for(int i = 0; i < 1500; ++i) {
        arr[i].value = "";
    }
}

unsigned int hash_table::hash(std::string key) {
    return (unsigned int)(int(std::hash<std::string>{}(key))%691+700);
}

void hash_table::insert(std::string key, std::string value) {
    arr[hash(key)].value = value;
    ++cnt;
}

bool hash_table::find(std::string key) {
    return arr[hash(key)].value != "";
}

std::string hash_table::at(std::string key) {
    return arr[hash(key)].value;
}

unsigned int hash_table::size() {
    return cnt;
}