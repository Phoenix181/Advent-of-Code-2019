#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

class Intcode
{
    std::vector<int> instructions;
    int phase, signal;
    int opcode_position;
    int opcode;
    int parameter1Mode, parameter2Mode, parameter3Mode;
    int output;

    bool signalAvail, phaseAvail;

    void opcode_1()
    {
        int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2],
            position_3 = instructions[opcode_position + 3];

        int parameter1 = parameter1Mode ? instructions[opcode_position + 1] : instructions[position_1];
        int parameter2 = parameter2Mode ? instructions[opcode_position + 2] : instructions[position_2];

        instructions[position_3] = parameter1 + parameter2;
    }

    void opcode_2()
    {
        int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2],
            position_3 = instructions[opcode_position + 3];

        int parameter1 = parameter1Mode ? instructions[opcode_position + 1] : instructions[position_1];
        int parameter2 = parameter2Mode ? instructions[opcode_position + 2] : instructions[position_2];

        instructions[position_3] = parameter1 * parameter2;
    }

    void opcode_3()
    {
        int position = instructions[opcode_position + 1];
        if(phaseAvail) {
            instructions[position] = phase;
            phaseAvail = false;
        }
        else if(signalAvail) {
            instructions[position] = signal;
            signalAvail = false;
        }
        /*else {
            std::cout << "Input:";
            std::cin >> instructions[position];
        }*/
    }

    void opcode_4()
    {
        int position = instructions[opcode_position + 1];
        output = instructions[position];
        //std::cout << instructions[position] << std::endl;
    }

    void opcode_5()
    {
        int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2];

        int parameter1 = parameter1Mode ? instructions[opcode_position + 1] : instructions[position_1];
        int parameter2 = parameter2Mode ? instructions[opcode_position + 2] : instructions[position_2];

        if (parameter1 != 0)
            opcode_position = parameter2;
        else
            opcode_position += 3;
    }

    void opcode_6()
    {
        int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2];

        int parameter1 = parameter1Mode ? instructions[opcode_position + 1] : instructions[position_1];
        int parameter2 = parameter2Mode ? instructions[opcode_position + 2] : instructions[position_2];

        if (parameter1 == 0)
            opcode_position = parameter2;
        else
            opcode_position += 3;
    }

    void opcode_7()
    {
        int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2],
            position_3 = instructions[opcode_position + 3];

        int parameter1 = parameter1Mode ? instructions[opcode_position + 1] : instructions[position_1];
        int parameter2 = parameter2Mode ? instructions[opcode_position + 2] : instructions[position_2];

        instructions[position_3] = parameter1 < parameter2 ? 1 : 0;
    }

    void opcode_8()
    {
        int position_1 = instructions[opcode_position + 1],
            position_2 = instructions[opcode_position + 2],
            position_3 = instructions[opcode_position + 3];

        int parameter1 = parameter1Mode ? instructions[opcode_position + 1] : instructions[position_1];
        int parameter2 = parameter2Mode ? instructions[opcode_position + 2] : instructions[position_2];

        instructions[position_3] = parameter1 == parameter2 ? 1 : 0;
    }

public:
    Intcode(std::vector<int> i, int _phase, int _signal) : instructions(i),
                                                          opcode_position(0),
                                                          output(-99),
                                                          phase(_phase),
                                                          signal(_signal),
                                                          signalAvail(true),
                                                          phaseAvail(true) {}
    int compute()
    {
        int instructionMode = instructions[opcode_position];
        opcode = instructionMode % 100;

        while (opcode != 99 || opcode_position > instructions.size())
        {
            int parameterModes = instructionMode / 100;
            parameter1Mode = parameterModes % 10,
            parameter2Mode = (parameterModes / 10) % 10,
            parameter3Mode = (parameterModes / 100) % 10;

            switch (opcode)
            {
            case 1:
                opcode_1();
                opcode_position += 4;
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
                opcode_position += 4;
                break;
            case 8:
                opcode_8();
                opcode_position += 4;
                break;
            default:
                opcode_position++;
            }

            instructionMode = instructions[opcode_position];
            opcode = instructionMode % 100;
        }
        return output;
    }
};

int amplifier(std::vector<int> instructions) {
    int range[5] = {0, 1, 2, 3, 4}; 
    int higher = 0;
    std::sort(range, range + 5);
    
    do {
        Intcode amplifier1(instructions, range[0], 0);
        int output1 = amplifier1.compute();

        Intcode amplifier2(instructions, range[1], output1);
        int output2 = amplifier2.compute();

        Intcode amplifier3(instructions, range[2], output2);
        int output3 = amplifier3.compute();

        Intcode amplifier4(instructions, range[3], output3);
        int output4 = amplifier4.compute();

        Intcode amplifier5(instructions, range[4], output4);
        int output5 = amplifier5.compute();
        
        if (output5 > higher) {
            higher = output5;
        }
    } while(std::next_permutation(range, range + 5));
    
    return higher;
}

int main() {
    std::vector<int> instructions;
    std::string input;
    std::cin >> input;
    std::stringstream input_stream(input);
    for (int instruction; input_stream >> instruction;)
    {
        instructions.push_back(instruction);
        if (input_stream.peek() == ',')
            input_stream.ignore();
    }

    std::cout << "Final Ouput to thrusters: " <<  amplifier(instructions) << std::endl;

}