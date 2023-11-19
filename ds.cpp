#include "ds.h"
#include <functional>

SYM_table::SYM_table() {
    label = "";
    address = 0;
    length = 0;
    err_flag = false;
}

SYM_table::SYM_table(std::string label, unsigned int address) {
    this->label = label;
    this->address = address;
    length = 0;
    err_flag = false;
}

bool SYM_table::operator<(const SYM_table& b) const {
    return this->label < b.label;
}

SYM_table& SYM_table::operator=(const SYM_table& b) {
    this->label = b.label;
    this->address = b.address;
    this->length = b.length;
    this->err_flag = b.err_flag;
    return *this;
}

hash_table::hash_table() {
    cnt = 0;
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

BST::BST() {
    cnt = 0;
    last = 1;
}

void BST::insert(std::string label, unsigned int address) {
    unsigned int index = 1;
    SYM_table tmp(label, address);

    if (last == 1) {
        arr[1] = tmp;
        ++cnt;
        ++last;
        return;
    }

    while (index < last && arr[index].label != "") {
        if (tmp < arr[index]) {
            index = index * 2;
        } else {
            index = index * 2 + 1;
        }
    }
    arr[index] = tmp;
    ++cnt;
    if (index >= last) {
        last = index + 1;
    }
}

unsigned int BST::find(std::string label) {
    unsigned int index = 1;
    while (index < last) {
        if (label  == arr[index].label) {
            return index;
        } else if (label < arr[index].label) {
            index = index * 2;
        } else {
            index = index * 2 + 1;
        }
    }
    return 0;
}

unsigned int BST::size() {
    return cnt;
}