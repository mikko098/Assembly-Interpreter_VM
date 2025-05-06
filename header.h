#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class VirtualMachine {
public:
    unsigned char reg[7]{};
    unsigned char memory[64]{};
    bool overflow, underflow, zeroflag, carryflag;
    int counter;

    void printArray(const unsigned char *arr, int size);
    void printMemory(const unsigned char *arr, int size);
    void lefttrim(string &s, char a);
    void righttrim(string &s, char a);
    void trim(string &s, char a);
    void updateFlags(int a);
    int cleanparameter(string str);
    string decimalToBinary(int decimal);
    int binaryToDecimal(string binary);
    void printFlags();
    void in(string destination);
    void out(string source);
    void mov(string source, string destination);
    void add(string source, string destination);
    void sub(string source, string destination);
    void mul(string source, string destination);
    void div(string source, string destination);
    void arithmetic(string command, string source, string destination);
    void inc(string source);
    void dec(string source);
    void load(string source, string destination);
    void store(string source, string destination);
    void rol(string source, string countstring);
    void ror(string source, string countstring);
    void shl(string source, string countstring);
    void shr(string source, string countstring);
    void identifyfunc(string command, string parameter1, string parameter2);
    void printFlagsAndMemory();
    void executefunc();
};

#endif