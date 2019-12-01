#include<iostream>
#include<vector>

//part1
int fuelReq(int mass) {
    return mass / 3 - 2;
}

//part2
int netFuelReq(int mass) {
    int fuel = fuelReq(mass);
    
    if(fuel <= 0)
        return 0;
    
    return fuel + netFuelReq(fuel);
}

int main() {
    std::vector<int> masses;
    int total = 0, input;

    std::cin >> input;
    while(input > 0) {
        masses.push_back(input);
        std::cin >> input;
    }

    for (auto mass : masses) {
        total += netFuelReq(mass);
    }
    
    std::cout << total << std::endl;
}