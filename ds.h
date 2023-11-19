#ifndef DS_H
#define DS_H
#include <string>
struct table{
    std::string value;
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
    table arr[1500];
    unsigned int cnt;
};
#endif // DS_H