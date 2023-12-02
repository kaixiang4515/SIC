#include "ds.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <exception>
#define REP(i,n) for(int i=0;i<int(n);++i)

using namespace std;

vector<string> vs;
hash_table op_table;
BST sym_table;

unsigned int str_to_dec(string s) {
    unsigned int d = 0;
    stringstream ss;
    ss << s;
    ss >> hex >> d;
    return d;
}

void print_OP_table() {
    ofstream fout("./out/OP_table.txt");
    REP(i,vs.size()) {
        fout << left << setw(7) << vs[i] << " in hash_table[" << op_table.hash(vs[i]) << "] , value : " << op_table.at(vs[i]) << "\n";
    }
    fout.close();
}

void print_SYM_table(unsigned int n) {
    if(n >= sym_table.end() || sym_table.is_empty(n)) return;
    print_SYM_table(n*2);
    ofstream fout;
    fout.open("./out/SYM_table.txt",ios::app);
    fout << left << setw(10) << sym_table.get_label(n) << " in BST[" << sym_table.find(sym_table.get_label(n)) << "]\n";
    fout.close();
    print_SYM_table(n*2+1);
}

int main(){
    ifstream op_in("./in/Instruction Set.txt");
    ofstream fout("./out/test.txt");
    string str,a,b;
    stringstream ss;
    while(getline(op_in,str)) {
        ss.clear();
        ss.str(str);
        ss >> a >> b;
        fout << a << " " << b << "\n";
        vs.push_back(a);
        op_table.insert(a,b);
    }
    op_in.close();
    fout << "\n==============================\n";
    REP(i,vs.size()) {
        fout << vs[i] << " " << op_table.at(vs[i]) << "\n";
    }
    fout << op_table.size();
    fout.close();

    // Pass 1
    ifstream sic_in("./in/SIC.txt");
    ofstream pass1_out("./out/intermediate_file.txt");
    unsigned int locctr = 0;
    while(getline(sic_in,str)) {
        string arr[3];
        int cnt = 0;
        ss.clear();
        ss.str(str);
        while(ss >> arr[cnt]) {
            ++cnt;
            if(arr[0] == ".") break;  // this is a comment line
        }
        if(arr[0] == ".") continue;

        if(cnt == 3 && arr[1] == "START") {
            locctr = str_to_dec(arr[2]);
            pass1_out << uppercase << hex << locctr << "\t" << str << "\n";
            continue;
        }

        try {
            if(cnt == 3) {      // there is a symbol in the LABEL field
                if(sym_table.find(arr[0])) {  // duplicate symbol
                    sym_table.set_error(arr[0]);
                    throw "Error: duplicate symbol";
                } else {
                    sym_table.insert(arr[0],locctr);
                }
            }
        } catch (const char* msg) {
            cerr << msg << "\n";
        }

        int idx = cnt == 3 ? 1 : 0;
        if(arr[idx] != "END") 
            pass1_out << uppercase << hex << locctr << "\t" << str << "\n";
        
        try {
            if(op_table.find(arr[idx])) {
                locctr += 3;
            } else if(arr[idx] == "WORD") {
                locctr += 3;
            } else if(arr[idx] == "RESW") {
                locctr += 3 * stoi(arr[idx+1]);
            } else if(arr[idx] == "RESB") {
                locctr += stoi(arr[idx+1]);
            } else if(arr[idx] == "BYTE") {
                if(arr[idx+1][0] == 'C') {
                    locctr += arr[idx+1].length() - 3;
                } else if(arr[idx+1][0] == 'X') {
                    locctr += (arr[idx+1].length() - 3) / 2;
                }
            } else if(arr[idx] == "END") {
                pass1_out << str << "\n";
            } else {
                throw "Error: invalid operation code";
            }
        } catch (const char* msg) {
            cerr << msg << "\n";
        }
    }
    sic_in.close();
    pass1_out.close();
    print_OP_table();
    ofstream clear_symtab("./out/SYM_table.txt");
    clear_symtab.close();
    print_SYM_table(1);
    return 0;
}