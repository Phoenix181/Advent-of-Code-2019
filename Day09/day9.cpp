#include <iostream>
#include <vector>
#include <sstream>
class Intcode {
    std::vector<long long int> instructions;
    long long int opcode_position;
    long long int opcode;
    long long int parameter1Mode, parameter2Mode, parameter3Mode;
    long long int relativeBase;

    void opcode_1() {
        long long int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2],
            position_3 = instructions[opcode_position + 3];

        long long int parameter1, parameter2;

        switch(parameter1Mode) {
            case 0: 
                parameter1 = instructions[position_1];
                break;
            case 1:
                parameter1 = instructions[opcode_position + 1];
                break;
            case 2:
                parameter1 = instructions[relativeBase + position_1];
        }
        switch(parameter2Mode) {
            case 0: 
                parameter2 = instructions[position_2];
                break;
            case 1:
                parameter2 = instructions[opcode_position + 2];
                break;
            case 2:
                parameter2 = instructions[relativeBase + position_2];
        }
        switch(parameter3Mode) {
            case 0:
                position_3 = position_3;
                break;
            case 2:
                position_3 = relativeBase + position_3;
                break;
        }

        instructions[position_3] = parameter1 + parameter2;
    }

    void opcode_2() {
        long long int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2],
            position_3 = instructions[opcode_position + 3];

        long long int parameter1, parameter2;

        switch(parameter1Mode) {
            case 0: 
                parameter1 = instructions[position_1];
                break;
            case 1:
                parameter1 = instructions[opcode_position + 1];
                break;
            case 2:
                parameter1 = instructions[relativeBase + position_1];
        }
        switch(parameter2Mode) {
            case 0: 
                parameter2 = instructions[position_2];
                break;
            case 1:
                parameter2 = instructions[opcode_position + 2];
                break;
            case 2:
                parameter2 = instructions[relativeBase + position_2];
        }
        switch(parameter3Mode) {
            case 0:
                position_3 = position_3;
                break;
            case 2:
                position_3 = relativeBase + position_3;
                break;
        }

        instructions[position_3] = parameter1 * parameter2;
    }

    void opcode_3() {
        long long int position = instructions[opcode_position + 1];
        switch (parameter1Mode) {
        case 0:
            position = position;
            break;
        case 2:
            position = relativeBase + position;
            break;
        }
        std::cout << "Input:";
        std::cin >> instructions[position];
    }

    void opcode_4() {
        long long int position = instructions[opcode_position + 1];
        long long int parameter;
        switch (parameter1Mode) {
        case 0:
            parameter = instructions[position];
            break;
        case 1:
            parameter = instructions[opcode_position + 1];
            break;
        case 2:
            parameter = instructions[relativeBase + position];
            break;
        }
        std::cout << parameter << std::endl;
    }

    void opcode_5() {
        long long int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2];

        long long int parameter1, parameter2;

        switch(parameter1Mode) {
            case 0: 
                parameter1 = instructions[position_1];
                break;
            case 1:
                parameter1 = instructions[opcode_position + 1];
                break;
            case 2:
                parameter1 = instructions[relativeBase + position_1];
        }
        switch(parameter2Mode) {
            case 0: 
                parameter2 = instructions[position_2];
                break;
            case 1:
                parameter2 = instructions[opcode_position + 2];
                break;
            case 2:
                parameter2 = instructions[relativeBase + position_2];
        }

        if(parameter1 != 0)
            opcode_position = parameter2;
        else
            opcode_position +=3;
    }

    void opcode_6() {
        long long int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2];

        long long int parameter1, parameter2;

        switch(parameter1Mode) {
            case 0: 
                parameter1 = instructions[position_1];
                break;
            case 1:
                parameter1 = instructions[opcode_position + 1];
                break;
            case 2:
                parameter1 = instructions[relativeBase + position_1];
        }
        switch(parameter2Mode) {
            case 0: 
                parameter2 = instructions[position_2];
                break;
            case 1:
                parameter2 = instructions[opcode_position + 2];
                break;
            case 2:
                parameter2 = instructions[relativeBase + position_2];
        }

        if(parameter1 == 0)
            opcode_position = parameter2;
        else
            opcode_position += 3;
    }

    void opcode_7() {
        long long int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2],
            position_3 = instructions[opcode_position + 3];

        long long int parameter1, parameter2;

        switch(parameter1Mode) {
            case 0: 
                parameter1 = instructions[position_1];
                break;
            case 1:
                parameter1 = instructions[opcode_position + 1];
                break;
            case 2:
                parameter1 = instructions[relativeBase + position_1];
        }
        switch(parameter2Mode) {
            case 0: 
                parameter2 = instructions[position_2];
                break;
            case 1:
                parameter2 = instructions[opcode_position + 2];
                break;
            case 2:
                parameter2 = instructions[relativeBase + position_2];
        }
        switch(parameter3Mode) {
            case 0:
                position_3 = position_3;
                break;
            case 2:
                position_3 = relativeBase + position_3;
                break;
        }

        instructions[position_3] = parameter1 < parameter2 ? 1 : 0;
    }

    void opcode_8() {
        long long int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2],
            position_3 = instructions[opcode_position + 3];

        long long int parameter1, parameter2;

        switch(parameter1Mode) {
            case 0: 
                parameter1 = instructions[position_1];
                break;
            case 1:
                parameter1 = instructions[opcode_position + 1];
                break;
            case 2:
                parameter1 = instructions[relativeBase + position_1];
        }
        switch(parameter2Mode) {
            case 0: 
                parameter2 = instructions[position_2];
                break;
            case 1:
                parameter2 = instructions[opcode_position + 2];
                break;
            case 2:
                parameter2 = instructions[relativeBase + position_2];
        }
        switch(parameter3Mode) {
            case 0:
                position_3 = position_3;
                break;
            case 2:
                position_3 = relativeBase + position_3;
                break;
        }

        instructions[position_3] = parameter1 == parameter2 ? 1 : 0;
    }

    void opcode_9() {
        long long int position_1 = instructions[opcode_position + 1];
        long long int parameter1;

        switch (parameter1Mode)
        {
        case 0:
            parameter1 = instructions[position_1];
            break;
        case 1:
            parameter1 = instructions[opcode_position + 1];
            break;
        case 2:
            parameter1 = instructions[relativeBase + position_1];
        }

        relativeBase+=parameter1;
    }

  public:
    Intcode(std::vector<long long int> i) : instructions(i), opcode_position(0), relativeBase(0) { 
        instructions.resize(100000);
    }
    void compute() {
        long long int instructionMode = instructions[opcode_position];
        opcode = instructionMode % 100;

        while(opcode != 99 || opcode_position > instructions.size()) {
            long long int parameterModes = instructionMode / 100;
            parameter1Mode = parameterModes % 10,
            parameter2Mode = (parameterModes / 10) % 10,
            parameter3Mode = (parameterModes / 100) % 10;

            switch(opcode) {
                case 1:
                    opcode_1();
                    opcode_position +=4;
                    break;
                case 2:
                    opcode_2();
                    opcode_position += 4;
                    break;
                case 3:
                    opcode_3();
                    opcode_position += 2;
                    break;
                case 4:
                    opcode_4();
                    opcode_position += 2;
                    break;
                case 5:
                    opcode_5();
                    break;
                case 6:
                    opcode_6();
                    break;
                case 7:
                    opcode_7();
                    opcode_position+=4;
                    break;
                case 8:
                    opcode_8();
                    opcode_position+=4;
                    break;
                case 9:
                    opcode_9();
                    opcode_position+=2;
                    break;
                default:
                    opcode_position++;
            }

            instructionMode = instructions[opcode_position];
            opcode = instructionMode % 100;
        }
    }
};

int main() {
    std::vector<long long int> instructions;

    std::string input = "";
    std::stringstream input_stream(input);
    for (long long int instruction; input_stream >> instruction;) {
        instructions.push_back(instruction);
        if (input_stream.peek() == ',')
            input_stream.ignore();
    }
    
    Intcode computer = Intcode(instructions);
    computer.compute();
}