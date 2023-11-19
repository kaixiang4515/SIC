#ifndef DS_H
#define DS_H
#include <string>

struct OP_table{
    std::string value;
};

struct SYM_table{
    std::string label;
    unsigned int address = 0;
    unsigned int length = 0;
    bool err_flag = false;
    bool operator<(const SYM_table& b) const;
};

class hash_table {
public:
    hash_table();
    unsigned int hash(std::string key);
    void insert(std::string key, std::string value);
    bool find(std::string key);
    std::string at(std::string key);
    unsigned int size();
private:
    OP_table arr[1500];
    unsigned int cnt;
};

class BST {
public:
    BST();
    void insert(std::string label, unsigned int address);
    unsigned int find(std::string lebel); // return index of the array
    unsigned int size();
private:
    SYM_table arr[1500];
    unsigned int cnt;
    unsigned int last;
};

#endif // DS_H