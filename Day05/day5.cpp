#include <iostream>
#include <vector>
#include <sstream>
class Intcode {
    std::vector<int> instructions;
    int opcode_position;
    int opcode;
    int parameter1Mode, parameter2Mode, parameter3Mode;

    void opcode_1() {
        int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2],
            position_3 = instructions[opcode_position + 3];

        int parameter1 = parameter1Mode ? instructions[opcode_position + 1] : instructions[position_1];
        int parameter2 = parameter2Mode ? instructions[opcode_position + 2] : instructions[position_2];

        instructions[position_3] = parameter1 + parameter2;
    }

    void opcode_2() {
        int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2],
            position_3 = instructions[opcode_position + 3];

        int parameter1 = parameter1Mode ? instructions[opcode_position + 1] : instructions[position_1];
        int parameter2 = parameter2Mode ? instructions[opcode_position + 2] : instructions[position_2];

        instructions[position_3] = parameter1 * parameter2;
    }

    void opcode_3() {
        int position = instructions[opcode_position + 1];
        std::cout << "Input:";
        std::cin >> instructions[position];
    }

    void opcode_4() {
        int position = instructions[opcode_position + 1];
        std::cout << instructions[position] << std::endl;
    }

    void opcode_5() {
        int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2];

        int parameter1 = parameter1Mode ? instructions[opcode_position + 1] : instructions[position_1];
        int parameter2 = parameter2Mode ? instructions[opcode_position + 2] : instructions[position_2];

        if(parameter1 != 0)
            opcode_position = parameter2;
        else
            opcode_position +=3;
    }

    void opcode_6() {
        int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2];

        int parameter1 = parameter1Mode ? instructions[opcode_position + 1] : instructions[position_1];
        int parameter2 = parameter2Mode ? instructions[opcode_position + 2] : instructions[position_2];

        if(parameter1 == 0)
            opcode_position = parameter2;
        else
            opcode_position += 3;
    }

    void opcode_7() {
        int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2],
            position_3 = instructions[opcode_position + 3];

        int parameter1 = parameter1Mode ? instructions[opcode_position + 1] : instructions[position_1];
        int parameter2 = parameter2Mode ? instructions[opcode_position + 2] : instructions[position_2];

        instructions[position_3] = parameter1 < parameter2 ? 1 : 0;
    }

    void opcode_8() {
        int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2],
            position_3 = instructions[opcode_position + 3];

        int parameter1 = parameter1Mode ? instructions[opcode_position + 1] : instructions[position_1];
        int parameter2 = parameter2Mode ? instructions[opcode_position + 2] : instructions[position_2];

        instructions[position_3] = parameter1 == parameter2 ? 1 : 0;
    }

  public:
    Intcode(std::vector<int> i) : instructions(i), opcode_position(0) { }
    void compute() {
        int instructionMode = instructions[opcode_position];
        opcode = instructionMode % 100;

        while(opcode != 99 || opcode_position > instructions.size()) {
            int parameterModes = instructionMode / 100;
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
                default:
                    opcode_position++;
            }

            instructionMode = instructions[opcode_position];
            opcode = instructionMode % 100;
        }
    }
};

int main() {
    std::vector<int> instructions;

    std::string input;
    std::cin >> input;
    std::stringstream input_stream(input);
    for (int instruction; input_stream >> instruction;) {
        instructions.push_back(instruction);
        if (input_stream.peek() == ',')
            input_stream.ignore();
    }
    
    Intcode computer = Intcode(instructions);
    computer.compute();
}