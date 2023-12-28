#include "ds.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <exception>
#define REP(i,n) for(int i=0;i<(int)(n);++i)

using namespace std;

vector<string> vs;
hash_table op_table;
BST sym_table;

unsigned int hex_to_dec(string s) {     // convert hex value in string to decimal unsigned int value
    unsigned int d = 0;
    stringstream ss;
    ss << s;
    ss >> hex >> d;
    return d;
}

string dec_to_hex(unsigned int d, int width = 4, bool Left = true) {     // convert decimal unsigned int value to hex value in string
    string s;
    stringstream ss;
    ss << hex << uppercase << setw(width) << setfill('0') << (Left ? left : right) << d;
    ss >> s;
    return s;
}

string str_to_ascii_in_hex(string s) {
    stringstream ss;
    REP(i,s.size()) {
        ss << hex << uppercase << setw(2) << setfill('0') << (int)s[i];
    }
    return ss.str();
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
    unsigned int begin_addr = 0, end_addr = 0;
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
            locctr = hex_to_dec(arr[2]);
            begin_addr = end_addr = locctr;
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
            pass1_out << uppercase << hex << left << setw(5) << locctr << "\t" << str << "\n";
        else
            pass1_out << "     \t";
        
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
                //cout << hex << uppercase << locctr << "\n";
                end_addr = locctr;
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

    // Pass 2
    ifstream pass2_in("./out/intermediate_file.txt");
    ofstream pass2_out("./out/object_code.txt");
    while(getline(pass2_in,str)) {
        string arr[4];
        string buf;
        int cnt = 0;
        ss.clear();
        ss.str(str);
        while(ss >> arr[cnt]) {
            ++cnt;
        }
        //cout << str << " cnt: " << cnt << "\n";
        if(cnt == 4 && arr[2] == "START") {
            pass2_out << "H" << setw(6) << left << arr[1] << setw(6) << setfill('0') << hex << uppercase << right << begin_addr << setw(6) << hex << uppercase << end_addr - begin_addr;
            continue;
        }
        
        int idx = cnt == 2 ? 1 : cnt - 2;
        if(idx == 1 && arr[0] == "END")
            idx = 0;
        //cout << arr[idx] << "\n";
        const string& OP = arr[idx];
        unsigned int operand_addr = 0;
        bool X = false;
        if(OP != "END") {
            if(op_table.find(OP)) {
                if(cnt > 2){    // there is a symbol in OPERAND field
                    try {
                        string OPERAND = arr[idx+1];
                        auto pos = OPERAND.find(",X");
                        if(pos != string::npos) {
                            OPERAND = string(OPERAND.begin(), OPERAND.begin()+pos);
                            X = true;
                        }
                        
                        //cout << OPERAND << " ";
                        unsigned int operand_idx = sym_table.find(OPERAND);
                        if(operand_idx) {
                            operand_addr = sym_table.get_addr(operand_idx);
                            //cout << hex << uppercase << operand_addr << "\n";
                        } else {
                            //cout << str << " ";
                            throw "Error: undefined symbol";
                        }
                    } catch (const char* msg) {
                        cerr << msg << "\n";
                    }
                }
                buf.clear();
                buf += op_table.at(OP);
                if(X) operand_addr += 1 << 15;
                buf += dec_to_hex(operand_addr);
                cout << buf << "\n";
            } else if(OP == "BYTE") {
                string OPERAND = arr[idx+1];
                string content(OPERAND.begin()+2,OPERAND.end()-1);
                if(OPERAND[0] == 'C') {
                    buf.clear();
                    buf += str_to_ascii_in_hex(content);
                    cout << buf << "\n";
                } else {
                    buf.clear();
                    buf += content;
                    cout << buf << "\n";
                }
            } else if(OP == "WORD") {
                string OPERAND = arr[idx+1];
                buf.clear();
                buf += dec_to_hex(stoi(OPERAND), 6, false);
                cout << buf << "\n";
            }
        }
    }
    return 0;
}