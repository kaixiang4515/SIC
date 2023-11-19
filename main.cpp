#include "ds.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#define REP(i,n) for(int i=0;i<n;++i)

using namespace std;

vector<string> vs;
hash_table h;

int main(){
    ifstream op_in("./in/Instruction Set.txt");
    ofstream fout("./out/test.txt");
    string str,a,b;
    while(getline(op_in,str)) {
        stringstream ss(str);
        ss >> a >> b;
        fout << a << " " << b << "\n";
        vs.push_back(a);
        h.insert(a,b);
    }
    op_in.close();
    fout << "\n==============================\n";
    REP(i,int(vs.size())) {
        fout << vs[i] << " " << h.at(vs[i]) << "\n";
    }
    fout << h.size();
    fout.close();

    ifstream sic_in("./in/SIC.txt");
    while(getline(sic_in,str)) {
        cout << str << "\n";
    }
    sic_in.close();
    return 0;
}