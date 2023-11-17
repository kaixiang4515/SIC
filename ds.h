#ifndef DS_H
#define DS_H
#include <string>
class hash_table {
public:
    hash_table();
    void insert(std::string key, std::string value);
    std::string at(std::string key);
    unsigned int size();
private:
    std::string arr[1500];
    unsigned int cnt;
};
#endif // DS_H