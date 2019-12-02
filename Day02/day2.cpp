#include<iostream>
#include<vector>
#include<sstream>

int Intcode(std::vector<int> &instructions) {
    int opcode_position = 0;
    int opcode = instructions[opcode_position];

    while(opcode != 99 || opcode_position > instructions.size()) {
        int input_1_postition = instructions[opcode_position + 1],
            input_2_postition = instructions[opcode_position + 2],
            output_postition = instructions[opcode_position + 3];

        int input_1 = instructions[input_1_postition],
            input_2 = instructions[input_2_postition];

        if(opcode == 1) {
            instructions[output_postition] = input_1 + input_2;
            opcode_position += 4;
        }
        else if(opcode == 2) {
            instructions[output_postition] = input_1 * input_2;
            opcode_position += 4;
        }

        else
            opcode_position++;
        
        opcode = instructions[opcode_position];
    }
    return instructions[0];
}

void part1(std::vector<int> instructions) {
    instructions[1] = 12;
    instructions[2] = 2;

    std::cout << "Part 1:" << Intcode(instructions) << std::endl;
}

void part2(std::vector<int> instructions) {
    int result;

    for(int noun = 0; noun < 100; noun++) {
        for(int verb = 0; verb < 100; verb++) {
            std::vector<int> current = instructions;
            current[1] = noun;
            current[2] = verb;

            int output = Intcode(current);

            if (output == 19690720) {
                result = 100 * noun + verb;
                break;
            }
        }
    }
    std::cout << "Part 2:" << result << std::endl;
}

int main() {
    std::vector<int> instructions;

    std::string input;
    std::cin >> input;
    std::stringstream input_stream (input);
    for(int instruction; input_stream >> instruction; ) {
        instructions.push_back(instruction);
        if(input_stream.peek() == ',')
            input_stream.ignore();
    }
    
    part1(instructions);

    part2(instructions);
}