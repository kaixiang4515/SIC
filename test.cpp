//#include <bits/stdc++.h>
#include "ds.h"
#include <vector>
#include <iostream>
#include <sstream>
#define REP(i,n) for(int i=0;i<n;++i)

using namespace std;
using LL = long long;

vector<string> vs;
//hash<string> h;
hash_table h;

unsigned int dec_to_hex(unsigned int dec) {
    unsigned int hex = 0;
    int t = 1;
    while(dec) {
        hex += (dec % 16) * t;
        dec /= 16;
        t *= 16;
    }
    return hex;
}

unsigned int hex_to_dec(unsigned int h) {
    unsigned int d = 0;
    stringstream ss;
    ss << h;
    ss >> hex >> d;
    return d;
}

int main(){
    /*freopen("./in/Instruction Set.txt","r",stdin);
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
    cout << h.size();*/
    int a = 0x3f3f3f3f;
    cout << a << "\n";
    cout << hex << a << "\n";
    int b = 0x1000;
    cout << b << "\n";
    REP(i,20) {
        cout << hex << b << "\n";
        b += 3;
    }
    cout << "\n";
    cout << dec_to_hex(1000) << "\n";
    cout << hex_to_dec(0x1000) << "\n";
    return 0;
}
