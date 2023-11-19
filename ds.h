#ifndef DS_H
#define DS_H
#include <string>

struct OP_table{
    std::string value;
};

struct SYM_table{
    SYM_table();
    SYM_table(std::string label, unsigned int address);
    std::string label;
    unsigned int address;
    unsigned int length;
    bool err_flag;
    bool operator<(const SYM_table& b) const;
    SYM_table& operator=(const SYM_table& b);
};

class hash_table {  // hash table for opcode
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

class BST {  // binary search tree for symbol table
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