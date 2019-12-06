#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>

int mapCheckSum(std::vector<std::string> inputs) {
    std::map<std::string, std::string> orbitChild;
    for(auto input : inputs) {
        auto positon = input.find(")");
        std::string parent = input.substr(0, positon),
                    child = input.substr(positon+1);
        
        orbitChild.insert(std::pair<std::string,std::string>(child, parent));
    }
    int totalOrbit = 0;
    for(auto& [key, value] : orbitChild) {
        std::string parent = value, child = key;
        totalOrbit++;
        while(parent != "COM") {
            child = parent;
            parent = orbitChild[child];
            totalOrbit++;
        }
    }
    std::string youParent = orbitChild["YOU"];
    std::vector<std::string> stepBodies;
    int step = 0;
    while(youParent != "COM") {
        stepBodies.push_back(youParent);
        youParent = orbitChild[youParent];
        step++;
    }

    std::string sanParent = orbitChild["SAN"]; int totalSteps = 0;
    bool foundParent = false;
    while(sanParent != "COM") {
        for(int i = 0; i < stepBodies.size(); i++) {
            if(sanParent == stepBodies[i]) {
                totalSteps+=i;
                foundParent = true;
                break;
            }
        }
        if(foundParent)
            break;
        sanParent = orbitChild[sanParent];
        totalSteps++;
    }
    std::cout << totalOrbit << std::endl << "Result_2: ";
    return totalSteps;
}

int main() {
    std::vector<std::string> inputs;
    std::ifstream inputFile("./input.txt");
    std::istream_iterator<std::string>eos, inputFileIterator (inputFile);

    while(inputFileIterator != eos) {
        inputs.push_back(*inputFileIterator);
        inputFileIterator++;
    }

    std::cout << "Result_1: "<< mapCheckSum(inputs) << std::endl;
}