#include<iostream>
#include<vector>
#include<sstream>

int Intcode(std::vector<int> &instructions) {
    int opcode_position = 0;
    while(true || opcode_position > instructions.size()) {
        int opcode = instructions[opcode_position];
        if(opcode == 99) {
            opcode_position++;
            break;
        }
        int input_1_postition = instructions[opcode_position + 1],
            input_2_postition = instructions[opcode_position + 2],
            output_postition = instructions[opcode_position + 3];

        if(opcode == 1) {
            int input_1 = instructions[input_1_postition],
                input_2 = instructions[input_2_postition];

            instructions[output_postition] = input_1 + input_2;
            opcode_position += 4;
        }
        else if(opcode == 2) {
            int input_1 = instructions[input_1_postition],
                input_2 = instructions[input_2_postition];

            instructions[output_postition] = input_1 * input_2;
            opcode_position += 4;
        }

        else {
            opcode_position++;
            continue;
        }
    }
    return instructions[0];
}

int main() {
    std::vector<int> instructions;
    int result;

    std::string input;
    std::cin >> input;
    std::stringstream input_stream (input);
    for(int instruction; input_stream >> instruction; ) {
        instructions.push_back(instruction);
        if(input_stream.peek() == ',')
            input_stream.ignore();
    }
    
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

    std::cout << result << std::endl;
    
    //Function for part 1
    //instructions[1] = 12;
    //instructions[2] = 2;

    //std::cout<<Intcode(instructions);
}