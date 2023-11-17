//#include <bits/stdc++.h>
#include "ds.h"
#include <vector>
#include <iostream>
#define REP(i,n) for(int i=0;i<n;++i)

using namespace std;
using LL = long long;

vector<string> vs;
//hash<string> h;
hash_table h;

int main(){
    freopen("./in/Instruction Set.txt","r",stdin);
    freopen("./out/test.txt","w",stdout);
    string a,b;
    while(cin >> a >> b) {
        cout << a << " " << b << "\n";
        vs.push_back(a);
        h.insert(a,b);
    }
    cout << "\n==============================\n";
    REP(i,int(vs.size())) {
        cout << vs[i] << " " << h.at(vs[i]) << "\n";
    }
    cout << h.size();
    return 0;
}
