#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include "header.h"

using namespace std;

// Function to print elements of an array
void VirtualMachine::printArray(const unsigned char *arr, int size) // Prints out all the elements of the given array
{
    for (int i = 0; i < size; ++i) {
        cout << setw(2) << setfill('0') << static_cast<int>(arr[i]) << " ";
    }
    cout << endl;
}

// Function to print memory in a formatted way
void VirtualMachine::printMemory(const unsigned char *arr, int size) // Prints out all the elements of the given array
{
    for (int i = 0; i < size; ++i) {
        if (i % 8 == 0)
            cout << endl;
        cout << setw(2) << setfill('0') << static_cast<int>(arr[i]) << " ";
    }
    cout << endl;
}

// Function to trim characters from the left of a string
void VirtualMachine::lefttrim(string &s, char a) // Trims all occurrences of specified character to the left of the string
{
    while (s[0] == a) {
        s.erase(0, 1);
    }
}

// Function to trim characters from the right of a string
void VirtualMachine::righttrim(string &s, char a) // Trims all occurrences of specified character to the left of the string
{
    while (s[s.length() - 1] == a) {
        s.erase(s.length() - 1, 1);
    }
}

// Function to trim characters from both sides of a string
void VirtualMachine::trim(string &s, char a) // Trims all occurrences of specified character to the left and right of the string
{
    righttrim(s, a);
    lefttrim(s, a);
}

// Function to update flags based on a value
void VirtualMachine::updateFlags(int a) // Checks if specified value raises any flags
{
    overflow = overflow || (a > 255);
    carryflag = carryflag || (a > 255);
    underflow = underflow || (a < 0);
    zeroflag = zeroflag || (a == 0);
}

// Function to clean and extract register index from a string
int VirtualMachine::cleanparameter(string str) // Removes any trailing brackets and letters from the string and returns it as an integer
{                              // e.g., [R6] is converted to 6
    trim(str, '[');
    trim(str, ']');
    trim(str, 'R');
    return stoi(str);
}

// Function to convert decimal to binary string
string VirtualMachine::decimalToBinary(int decimal) // Converts a decimal integer into a binary string
{
    string binary;
    for (int i = 7; i >= 0; i--) {
        if ((decimal / static_cast<int>(pow(2 ,i))) > 0){
            binary.push_back('1');
        }
        else
            binary.push_back('0');
        decimal = decimal % static_cast<int>(pow(2 ,i));
    }
    return binary;
}

// Function to convert binary string to decimal
int VirtualMachine::binaryToDecimal(string binary) // Converts a binary string into a decimal integer
{
    int decimal = 0;
    int binaryLength = binary.length();

    for (int i = (binaryLength - 1); i >= 0; i--) {
        char currentBit = binary[binaryLength-1-i];
        if (currentBit == '1') {
            decimal += pow(2,i);
        } 
    }

    return decimal;
}

// Function to print flags
void VirtualMachine::printFlags()
{
    cout << "OF = " << overflow << "    UF = " << underflow << "    ZF = " << zeroflag << "    CF = " << carryflag << endl;
}

// Input operation
void VirtualMachine::in(string destination) // Takes an integer input from the user and stores it in the specified register
{
    int inputInteger, destIndex;
    cout << "Enter the value you wish to input to " << destination << endl;
    cin >> inputInteger;
    updateFlags(inputInteger);
    destIndex = cleanparameter(destination);
    reg[destIndex] = inputInteger;
}

// Output operation
void VirtualMachine::out(string source) // Prints out the value stored in the specified register
{
    int srcIndex;
    srcIndex = cleanparameter(source);
    cout << "The value of " << source << " is ";
    cout << static_cast<int>(reg[srcIndex]) << endl;
}

// Move operation
void VirtualMachine::mov(string source, string destination) // Copies the value stored in the 'source' register to the 'destination' register
{
    int srcIndex, destIndex;
    srcIndex = cleanparameter(source), destIndex = cleanparameter(destination);
    if (source[0] == '[') {
        reg[destIndex] = memory[reg[srcIndex]];
    } else if (source[0] == 'R') {
        reg[destIndex] = reg[srcIndex];
    } else {
        reg[destIndex] = stoi(source);
    }
}

// Add operation
// Adds the values stored in the 'source' register to the 'destination' register
void VirtualMachine::add(string source, string destination)  
{
    int srcIndex, destIndex, sum;
    srcIndex = cleanparameter(source), destIndex = cleanparameter(destination);
    sum = reg[srcIndex] + reg[destIndex];
    updateFlags(sum);
    reg[destIndex] = sum;
}

// Subtract operation 
// Subtracts the values stored in the 'source' register from the 'destination' register
void VirtualMachine::sub(string source, string destination)  
{
    int srcIndex, destIndex, difference;
    srcIndex = cleanparameter(source), destIndex = cleanparameter(destination);
    difference = reg[destIndex] - reg[srcIndex];
    updateFlags(difference);
    reg[destIndex] = difference;
}

// Multiply operation
// Multiply the values stored in the 'source' register by the 'destination' register
void VirtualMachine::mul(string source, string destination) 
{    
    int srcIndex, destIndex, product;
    srcIndex = cleanparameter(source), destIndex = cleanparameter(destination);
    product = reg[srcIndex] * reg[destIndex];
    updateFlags(product);
    reg[destIndex] = product;
}

// Divides operation
// Divides the values stored in the 'source' register from the 'destination' register
void VirtualMachine::div(string source, string destination)  
{    
    int srcIndex, destIndex, result;
    srcIndex = cleanparameter(source), destIndex = cleanparameter(destination);
    if (reg[srcIndex] != 0){
        result = reg[destIndex] / reg[srcIndex] ;
        updateFlags(result);
        reg[destIndex] = result;
    }
    else
        cout << endl << "Error : Division by zero is not allowed" << endl;
}

// Function to handle arithmetic operations
// Checks for the command type and calls the required function
void VirtualMachine::arithmetic(string command, string source, string destination) 
{    
    if (command == "ADD")
        add(source, destination);
    if (command == "SUB")
        sub(source, destination);
    if (command == "MUL")
        mul(source, destination);
    if (command == "DIV")
        div(source, destination);
}

// Increment operation
// Adds one to the 'source' register
void VirtualMachine::inc(string source)  
{    
    int srcIndex, a;
    srcIndex = cleanparameter(source);
    a = reg[srcIndex] + 1;
    updateFlags(a);
    reg[srcIndex] = a;
}

// Decrement operation
// Subtracts one from the 'source' register
void VirtualMachine::dec(string source)  
{    
    int srcIndex, a;
    srcIndex = cleanparameter(source);
    a = reg[srcIndex] - 1;
    updateFlags(a);
    reg[srcIndex] = a;
}

// Load operation
// Loads a value from a memory location to a register
void VirtualMachine::load(string source, string destination)
{    
    int srcIndex, destIndex;
    srcIndex = cleanparameter(source), destIndex = cleanparameter(destination);
    if (destination[0] == '[') {
        reg[srcIndex] = memory[reg[destIndex]];
    } else {
        reg[srcIndex] = memory[destIndex];
    }
}

// Store operation: Stores a value from a register in a memory location
void VirtualMachine::store(string source, string destination) 
{    
    int srcIndex, destIndex;
    srcIndex = cleanparameter(source), destIndex = cleanparameter(destination);
    if (destination[0] == '[') {
        memory[reg[destIndex]] = reg[srcIndex];
    } else {
        memory[destIndex] = reg[srcIndex];
    }
}

// Rotate Left operation - Rotates all bits 'count' times to the left
void VirtualMachine::rol(string source, string countstring)
{    
    int count = stoi(countstring) % 8;
    int value = cleanparameter(source);
    string binarystring = decimalToBinary(reg[value]);

    binarystring = binarystring.substr(count) + binarystring.substr(0, count);
    reg[value] = binaryToDecimal(binarystring);

    updateFlags(reg[value]);
}

// Rotate Right operation - Rotates all bits 'count' times to the right
void VirtualMachine::ror(string source, string countstring)
{    
    int count = stoi(countstring) % 8;
    int value = cleanparameter(source);
    string binarystring = decimalToBinary(reg[value]);

    binarystring = binarystring.substr(8 - count) + binarystring.substr(0, 8 - count);
    reg[value] = binaryToDecimal(binarystring);

    updateFlags(reg[value]);
}

// Shift Left operation - Shifts all bits 'count' times to the left
void VirtualMachine::shl(string source, string countstring)
{    
    int count = stoi(countstring) % 8; 
    int value = cleanparameter(source);
    string binarystring = decimalToBinary(reg[value]);

    binarystring = binarystring.substr(count);
    for (int i = 0; i < count; i++){
        binarystring += '0';
    }
    reg[value] = binaryToDecimal(binarystring);

    updateFlags(reg[value]);
}

// Shift Right operation - Shifts all bits 'count' times to the right
void VirtualMachine::shr(string source, string countstring)
{    
    int count = stoi(countstring) % 8; 
    int value = cleanparameter(source);
    string binarystring = decimalToBinary(reg[value]);

    binarystring = binarystring.substr(0, 8 - count);
    for (int i = 0; i < count; i++){
        binarystring.insert(binarystring.begin(),'0');
    }
    reg[value] = binaryToDecimal(binarystring);

    updateFlags(reg[value]);
}

// Function to identify and execute various operations
// Compares the string stored in 'command' and executes the required function
void VirtualMachine::identifyfunc(string command, string parameter1, string parameter2)
{    
    if (command == "IN")
        in(parameter1);
    else if (command == "OUT")
        out(parameter1);
    else if (command == "MOV")
        mov(parameter1, parameter2);
    else if ((command == "ADD") || (command == "SUB") || (command == "MUL") || (command == "DIV"))
        arithmetic(command , parameter1, parameter2);
    else if (command == "INC")
        inc(parameter1);
    else if (command == "DEC")
        dec(parameter1);
    else if (command == "ROL")
        rol(parameter1, parameter2);
    else if (command == "ROR")
        ror(parameter1, parameter2);
    else if (command == "SHL")
        shl(parameter1, parameter2);
    else if (command == "SHR")
        shr(parameter1, parameter2);
    else if (command == "LOAD")
        load(parameter1, parameter2);
    else if (command == "STORE")
        store(parameter1, parameter2);
}

// Function to print out registers, flags, program counter, and memory
void VirtualMachine::printFlagsAndMemory() {
    cout << endl << "Registers :  ";
    printArray(reg, 7);

    cout << "Flags     :  ";
    printFlags();

    cout << "PC        :  "
    << counter << endl;

    cout << endl << "Memory : ";
    printMemory(memory, 64);
}

// Function to execute the assembly code
void VirtualMachine::executefunc() {
    ifstream assemblyfile;
    string filename;
    cout << "Enter name of the file (without .asm extension) : ";
    cin >> filename;
    assemblyfile.open(filename + ".asm");
    
    if (assemblyfile.fail())
        cout << "The file does not exist in the current directory.";

    //Create a stringstream of the line to pass it into command, parameter1, and parameter2
    //Removes the commas from the parameters and get the function name, first parameter and second parameter from the stringstream
    else{
    string line, command, parameter1, parameter2;
    while (getline(assemblyfile, line)) {
        istringstream stream(line);                         
        counter++;                

        stream >> command >> parameter1 >> parameter2; 

        cout << "Line " << counter << ": ";
        cout << command << " " << parameter1 << " " << parameter2 << endl;                           

        identifyfunc(command, parameter1, parameter2);

        printArray(reg, 7);
        cout << endl;
        parameter1 = parameter2 = "";
    }
    }
};