#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include "Instruction.h"

using namespace std;


bool legv8Flag [4] = {false, false, false, false}; // [Negative, Zero, Overflow, Carry]
vector<uint8_t> MEM(1000000); // About 1MB of Memory
vector<string> types{"ADD", "MUL", "ADDS", "ADDI", "ADDIS", "SUB", "SUBS", "SUBI", "SUBIS",
                     "LDUR", "LDURH", "LDURB", "STUR", "STURH", "STURB", "AND", "ANDS", "ANDI", "ANDIS",
                     "CBZ", "CBNZ", "B", "BL", "BR", "B.EQ", "B.NE", "B.HS", "B.LO", "B.MI",
                    "B.PL", "B.VS", "B.HI", "B.LS", "B.GE", "B.LT", "B.GT", "B.LE",
                    "LSL", "LSR", "EOR", "EORI", "ORR", "ORRI", "LDURW", "STURW"}; // Put all instruction types here so they can easily be checked




void SetFlags(bool sub, long long int source1, long long int source2, long long int result){
    long long int _source2;
    if(sub)  _source2 = -source2;
    else _source2 = source2;
    //NEGATIVE
    legv8Flag[0] = result < 0;
    //ZERO
    legv8Flag[1] = result == 0;
    //OVERFLOW
    if(source1 > 0 && _source2 > 0 && result < 0)
        legv8Flag[2] = true;
    else
        legv8Flag[2] = source1 < 0 && _source2 < 0 && result > 0;
    //CARRY
    if(source1 < 0 && _source2 < 0)
        legv8Flag[3] = true;
    else
        legv8Flag[3] = (source1 < 0 || _source2 < 0) && result >= 0;
}

void MUL(bool typeR, long long int &source1, long long int &source2, long long int &destination, bool flag) {
  destination = source1 * source2;
}

void ADD(bool typeR, long long int &source1, long long int &source2, unsigned long long int immediate, long long int &destination, bool flag){
    if(typeR){
        destination = source1 + source2;
        if(flag)
            SetFlags(false, source1, source2, destination);
    }else{
        destination = source1 + immediate;
        if(flag)
            SetFlags(false, source1, immediate, destination);
    }

}

void SUB(bool typeR, long long int &source1, long long int &source2, unsigned long long int immediate, long long int &destination, bool flag){
    if(typeR){
        destination = source1 - source2;
        if(flag)
            SetFlags(true, source1, source2, destination);
    }else{
        destination = source1 - immediate;
        if(flag)
            SetFlags(true, source1, immediate, destination);
    }
}

void AND(bool typeR, long long int &source1, long long int &source2, unsigned long long int immediate, long long int &destination, bool flag){
    if(typeR){
        destination = source1 & source2;
    }else{
        destination = source1 & immediate;
    }
    if(flag){
        //NEGATIVE
        legv8Flag[0] = destination < 0;
        //ZERO
        legv8Flag[1] = destination == 0;
        //OVERFLOW
        legv8Flag[2] = false;
        //CARRY
        legv8Flag[3] = false;
    }
}

void ORR(bool typeR, long long int &source1, long long int &source2, unsigned long long int immediate, long long int &destination){
    if(typeR){
        destination = source1 | source2;
    }else{
        destination = source1 | immediate;
    }
}

void EOR(bool typeR, long long int &source1, long long int &source2, unsigned long long int immediate, long long int &destination){
    if(typeR){
        destination = source1 ^ source2;
    }else{
        destination = source1 ^ immediate;
    }
}

void LSL(long long int &source1, unsigned long long int shamt, long long int &destination){
    unsigned long long int temp = source1;
    destination = temp << shamt;
}

void LSR(long long int &source1, unsigned long long int shamt, long long int &destination){
    long long int temp = source1;
    if (temp >= 0) {
       destination = temp >> shamt;}
    else {
       destination = temp >> shamt;
       long long int temp1 = 1;
       for (int j = 1; j < shamt; j++)
          temp1 = (temp1 << 1) + 1;
       temp1 = temp1 << (64-shamt);
       destination -= temp1;
    }
}

void STUR(int size, long long int &source1, long long int addr, long long int &destination){
    uint8_t eightBit = 0;
    for(int i = 0; i < size; i++){
        eightBit = destination >> 8*i;
        MEM[source1 + addr - i] = eightBit;
    }
}

void LDUR(int size, long long int &source1, long long int addr, long long int &destination){
    destination = 0;
    unsigned long long int tempEight = 0;
    unsigned long long int temp = 0;
    for(int i = 0; i < size; i++){
        tempEight = MEM[source1 + addr - i];
        temp += tempEight << (8*i);
    }
    destination = temp;
}

bool BranchCond(string cond){
    if(cond == "EQ")
        return legv8Flag[1] == 1;
    else if(cond == "NE")
        return legv8Flag[1] == 0;
    else if(cond == "HS")
        return legv8Flag[3] == 1;
    else if(cond == "LO")
        return legv8Flag[3] == 0;
    else if(cond == "MI")
        return legv8Flag[0] == 1;
    else if(cond == "PL")
        return legv8Flag[0] == 0;
    else if(cond == "VS")
        return legv8Flag[2] == 1;
    else if(cond == "VC")
        return legv8Flag[2] == 0;
    else if(cond == "HI")
        return legv8Flag[3] == 1 && legv8Flag[1] == 0;
    else if(cond == "LS")
        return !(legv8Flag[3] == 1 && legv8Flag[1] == 0);
    else if(cond == "GE")
        return legv8Flag[0] == legv8Flag[2];
    else if(cond == "LT")
        return legv8Flag[0] != legv8Flag[2];
    else if(cond == "GT")
        return legv8Flag[1] == 0 && legv8Flag[0] == legv8Flag[2];
    else if(cond == "LE")
        return !(legv8Flag[1] == 0 && legv8Flag[0] == legv8Flag[2]);
}

void CheckInstruction(Instruction* i, vector<long long int> &RFILE, long long int &pc){
    if (i->type == "ADD")
        ADD(true, RFILE[i->regs[1]], RFILE[i->regs[2]], i->imed, RFILE[i->regs[0]], false);
    else if (i->type == "MUL")
        MUL(true, RFILE[i->regs[1]], RFILE[i->regs[2]], RFILE[i->regs[0]], false);
    else if(i->type == "ADDS")
        ADD(true, RFILE[i->regs[1]], RFILE[i->regs[2]], i->imed, RFILE[i->regs[0]], true);
    else if(i->type == "ADDI")
        ADD(false, RFILE[i->regs[1]], RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]], false);
    else if(i->type == "ADDIS")
        ADD(false, RFILE[i->regs[1]], RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]], true);
    else if(i->type == "SUB")
        SUB(true, RFILE[i->regs[1]], RFILE[i->regs[2]], i->imed, RFILE[i->regs[0]], false);
    else if(i->type == "SUBS")
        SUB(true, RFILE[i->regs[1]], RFILE[i->regs[2]], i->imed, RFILE[i->regs[0]], true);
    else if(i->type == "SUBI")
        SUB(false, RFILE[i->regs[1]], RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]], false);
    else if(i->type == "SUBIS")
        SUB(false, RFILE[i->regs[1]], RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]], true);
    else if(i->type == "AND")
        AND(true, RFILE[i->regs[1]], RFILE[i->regs[2]], i->imed, RFILE[i->regs[0]], false);
    else if(i->type == "ANDS")
        AND(true, RFILE[i->regs[1]], RFILE[i->regs[2]], i->imed, RFILE[i->regs[0]], true);
    else if(i->type == "ANDI")
        AND(false, RFILE[i->regs[1]], RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]], false);
    else if(i->type == "ANDIS")
        AND(false, RFILE[i->regs[1]], RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]], true);
    else if(i->type == "B")
        pc = i->labl-1;
    else if(i->type == "BL"){
        RFILE[30] = pc;
        pc = i->labl-1;
    } else if(i->type == "BR")
        pc = RFILE[30];
    else if(i->type.substr(0,2) == "B.")
        pc = BranchCond(i->type.substr(2,2)) ? i->labl-1 : pc;
    else if(i->type == "CBZ"){
        pc = RFILE[i->regs[0]] == 0 ? i->labl-1 : pc;
    }
    else if(i->type == "CBNZ"){
        pc = RFILE[i->regs[0]] != 0 ? i->labl-1 : pc;
    }
    else if(i->type == "LSL")
        LSL(RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]]);
    else if(i->type == "LSR")
        LSR(RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]]);
    else if(i->type == "EOR")
        EOR(true, RFILE[i->regs[1]], RFILE[i->regs[2]], i->imed, RFILE[i->regs[0]]);
    else if(i->type == "EORI")
        EOR(false, RFILE[i->regs[1]], RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]]);
    else if(i->type == "ORR")
        ORR(true, RFILE[i->regs[1]], RFILE[i->regs[2]], i->imed, RFILE[i->regs[0]]);
    else if(i->type == "ORRI")
        ORR(false, RFILE[i->regs[1]], RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]]);
    else if(i->type == "LDUR")
        LDUR(8,RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]]);
    else if(i->type == "LDURW")
        LDUR(4,RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]]);
    else if(i->type == "LDURH")
        LDUR(2,RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]]);
    else if(i->type == "LDURB")
        LDUR(1,RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]]);
    else if(i->type == "STUR")
        STUR(8,RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]]);
    else if(i->type == "STURW")
        STUR(4,RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]]);
    else if(i->type == "STURH")
        STUR(2,RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]]);
    else if(i->type == "STURB")
        STUR(1,RFILE[i->regs[1]], i->imed, RFILE[i->regs[0]]);

}

void outputMem(ostream &output, vector<long long int> RFILE, int memType = 0, int value = NULL){
    if(memType == 0){
        output << "RFILE contents: " << endl;
        for(int i = 0; i < RFILE.size(); i++){
                output << "X" << i << ": " << RFILE[i] << endl;
        }
        output << "MEM contents: " << endl;
        for(int i = 0; i < MEM.size(); i++){
            if(MEM[i] != NULL)
                output << "Byte " << i << ": " << int(MEM[i]) << endl;
        }
    }
    else if(memType == 1){
        output << "X" << value << ": " << RFILE[value] << endl;
    }
    else if (memType == 2)
    {
        output << "Byte " << value << ": " << MEM[value] << endl;
    }
    
}

int main() {
    vector<long long int> RFILE(32);
    cout << "Enter the name of the instruction file: ";
    string input;
    getline(cin, input);
    string filename = input;
    fstream tempfile;
    tempfile.open(filename);
    string line;
    int lineNum = 0;
    map<string, int> labels;
    while(getline(tempfile, line)){ //Searches for and stores all labels.
        stringstream ss;
        ss << line;
        string word;
        ss >> word;
        if(word.back() == ':'){
            word.pop_back();
            labels[word] = lineNum;
        }
        lineNum++;
    }
    lineNum = 0;
    tempfile.close();
    fstream file;
    file.open(filename); //Reopen the file in a new fstream so that the buffer resets back to the beginning.
    vector<Instruction*> program;
    while(getline(file, line)){ //Parsing each instruction
        lineNum++;
        stringstream ss;
        ss << line;
        string type;
        vector<int> regs;
        long long int imed = 0;
        int lblIndex = 0;
        while(!ss.eof()){
            string word;
            ss >> word;
            if(word.back() == ':') //Skip label markings.
                continue;
            //Sanitize the input
            if((word.back() == ',') || (word.back() == ']'))
                word.pop_back();
            if(word.front() == '[')
                word = word.substr(1, word.size()-1);
            if(find(types.begin(), types.end(), word) != types.end()){ //Checks to see if its in the list of valid instruction types.
                type = word;
                continue;
            }
            if(word.front() == '#'){ //Checks if its an imediate or address offse.
                word = word.substr(1, word.size()-1);
                imed = (long long int)stoi(word);
                continue;
            }
            if(labels.find(word) != labels.end()){ //Checks to see if its a label;
                lblIndex = labels[word];
                continue;
            }
            //Handle all special register names first. 
            if(word == "SP"){
                regs.push_back(28);
                continue;
            }
            if(word == "FP"){
                regs.push_back(29);
                continue;
            }
            if(word == "LR"){
                regs.push_back(30);
                continue;
            }
            if(word == "XZR"){
                regs.push_back(31);
                continue;
            }
            if(word.front() == 'X'){ //Check if its a register.
                word = word.substr(1, word.size()-1);
                regs.push_back(stoi(word));
            }
        }
        Instruction* I = new Instruction(type, regs, imed, lblIndex);
        program.push_back(I);
    }
    file.close();
    cout << "Enter 1 to run, or 2 to step: ";
    getline(cin, input);
    while (!((input == "1") || (input == "2")))
    {
        cout << "Invalid input. Enter 1 or 2: ";
        getline(cin, input);
    }
    string stepMode = input;
    long long int pc = 0;
    RFILE[28] = MEM.size() - 1;
    RFILE[30] = program.size();
    string optionMode;
    while (pc < program.size() && optionMode != "3") {
        bool cont = true;
        if(stepMode == "2"){
            optionMode = "";
            while((optionMode != "1") && cont){
                cout << "Enter 1 to execute next instruction, 2 to show memory contents, and 3 to stop: ";
                getline(cin, optionMode);
                while (!((optionMode == "1") || (optionMode == "2") || (optionMode == "3"))){
                    cout << "Invalid input. Enter 1, 2, or 3: ";
                    getline(cin, optionMode);
                }
                if(optionMode == "1")
                    cout << "Executing " << program[pc]->type << " instruction." << endl;
                else if(optionMode == "2"){
                    cout << "Enter 1 for RFILE, or 2 for MEM: ";
                    getline(cin, input);
                    string memChoice = input;
                    while(!((memChoice == "1") || (memChoice == "2"))){
                        cout << "Invalid input. Enter 1 or 2: ";
                        getline(cin, input);
                        memChoice = input;
                    }
                    cout << "Enter the " << ((memChoice == "1") ? "register" : "byte") << " number: ";
                    getline(cin, input);
                    int value = stoi(input);
                    outputMem(cout, RFILE, stoi(memChoice), value);
                }
                else if(optionMode == "3")
                    cont = false;
            }
        }
        if(!cont)
            break;
        CheckInstruction(program[pc], RFILE, pc); //Execute instruction.
        RFILE[31] = 0; //Reset XZR to 0.
        pc++;
    }
    cout << "Instruction execution has ended." << endl;
    ofstream output;
    output.open("output.txt");
    outputMem(output, RFILE);
    cout << "Wrote memory contents to output.txt";

}
