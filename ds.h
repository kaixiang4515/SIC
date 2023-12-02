#ifndef DS_H
#define DS_H
#include <string>

struct OP_table{
    std::string value;
};

struct SYM_table{
    SYM_table();
    SYM_table(const std::string& label, unsigned int address);
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
    unsigned int hash(const std::string& key) const;
    void insert(const std::string& key, const std::string& value);
    bool find(const std::string& key) const;
    std::string at(const std::string& key) const;
    unsigned int size() const;
private:
    OP_table arr[1500];
    unsigned int cnt;
};

class BST {  // binary search tree for symbol table
public:
    BST();
    void insert(const std::string& label, unsigned int address);
    void set_error(const std::string& label);
    unsigned int find(const std::string& lebel) const; // return index of the array, if not found, return 0
    unsigned int size() const;
    unsigned int end() const; // return the index of the past-the-end element
    std::string get_label(unsigned int index) const;
    bool is_empty(unsigned int index) const;
private:
    SYM_table arr[1500];
    unsigned int cnt;
    unsigned int last;
};

#endif // DS_H