#include "ds.h"
#include <functional>

SYM_table::SYM_table() {
    label = "";
    address = 0;
    length = 0;
    err_flag = false;
}

SYM_table::SYM_table(const std::string& label, unsigned int address) {
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

unsigned int hash_table::hash(const std::string& key) const {
    return (unsigned int)(int(std::hash<std::string>{}(key))%691+700);
}

void hash_table::insert(const std::string& key, const std::string& value) {
    arr[hash(key)].value = value;
    ++cnt;
}

bool hash_table::find(const std::string& key) const {
    return arr[hash(key)].value != "";
}

std::string hash_table::at(const std::string& key) const {
    return arr[hash(key)].value;
}

unsigned int hash_table::size() const {
    return cnt;
}

BST::BST() {
    cnt = 0;
    last = 1;
}

void BST::insert(const std::string& label, unsigned int address) {
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

void BST::set_error(const std::string& label) {
    unsigned int index = 1;
    while (index < last) {
        if (label  == arr[index].label) {
            arr[index].err_flag = true;
            return;
        } else if (label < arr[index].label) {
            index = index * 2;
        } else {
            index = index * 2 + 1;
        }
    }
}

unsigned int BST::find(const std::string& label) const {
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

unsigned int BST::size() const {
    return cnt;
}