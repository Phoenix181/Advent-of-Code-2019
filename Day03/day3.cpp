#include<iostream>
#include<vector>
#include<map>
#include<cmath>

class coords {
  public:
    int x;
    int y;
    coords() {
        x = 0;
        y = 0;
    }
    coords(int _x, int _y): x(_x), y(_y) {}

    bool operator== (coords other) {
        if(x == other.x && y == other.y) {
                return true;
        }
        return false;
    }
};

void mapVert(std::vector<coords>& map, int direction, int distance) {
    coords start_pos = coords();
    if(map.size())
        start_pos = map.back();

    for(auto y = start_pos.y, i = 0; i <= distance; i++, y += direction) {
        coords current_pos = coords(start_pos.x, y);
        if(!(current_pos == start_pos))
            map.push_back(current_pos);
    }
}

void mapHori(std::vector<coords>& map, int direction, int distance) {
    coords start_pos = coords();
    if(map.size())
        start_pos = map.back();

    for(auto x = start_pos.x, i = 0; i <= distance; i++, x += direction) {
        coords current_pos = coords(x, start_pos.y);
        if(!(current_pos == start_pos))
            map.push_back(current_pos);
    }
}

auto map(std::vector<std::string> directions) -> std::vector<coords> {
    std::vector<coords> map;
    for(auto direction : directions) {
        char dir = direction[0];
        int distance = std::stoi(direction.substr(1));
        switch(dir) {
            case 'U':
                mapVert(map, +1, distance);
                break;
            case 'D':
                mapVert(map, -1, distance);
                break;
            case 'L':
                mapHori(map, -1, distance);
                break;
            case 'R':
                mapHori(map, +1, distance);
                break;
        }    
    }
    return map;
}

auto mapIntersection(std::vector<coords> wire1, std::vector<coords> wire2) -> std::vector<coords> {
    std::vector<coords> intersection;
    for(auto coord_wire1 : wire1) {
        for(auto coord_wire2 : wire2) {
            if(coord_wire1 == coord_wire2) {
                intersection.push_back(coord_wire1);
            }
        }
    }
    return intersection;
}

auto parseInput(std::string input) -> std::vector<std::string> {
    std::vector<std::string> inputs;
    std::string current;
    for(auto ch : input) {
        if(ch == ',') {
            inputs.push_back(current);
            current = "";
        }
        else {
            current += ch;
        }
    }
    inputs.push_back(current);
    return inputs;
}

/*
**********************
*           Start    *
*           of       *
*           Part 1   *
**********************
*/
int findDistance(std::vector<coords> intersection) {
    int lowest = INT32_MAX;
    for (auto inter : intersection) {
        int current = abs(inter.x) + abs(inter.y);
        if (current <= lowest)
            lowest = current;
    }
    return lowest;
}

void part1(std::vector<coords> intersections) {
    int lowestDistance = findDistance(intersections);

    std::cout <<"Result   " << lowestDistance << std::endl;
}

/*
**********************
*           Start    *
*           of       *
*           Part 2   *
**********************
*/
int findSteps(coords intersection, std::vector<coords> wire) {
    int steps = 1;
    for(auto current : wire) {
        if(current == intersection)
            break;
        steps++;
    }
    return steps;
}

long findLowestSteps(std::vector<coords> intersections,
            std::vector<coords> wire1,
            std::vector<coords> wire2 ) {
    long lowest = INT64_MAX;

    for(auto intersection : intersections) {
        int wire1_steps = findSteps(intersection, wire1);
        int wire2_steps = findSteps(intersection, wire2);
        int current = wire1_steps + wire2_steps;
        if (current <= lowest)
            lowest = current;
    }
    return lowest;
}

void part2(std::vector<coords> intersections,
            std::vector<coords> wire1,
            std::vector<coords> wire2 ) {
    long steps = findLowestSteps(intersections, wire1, wire2);

    std::cout << "Result  " << steps;
}

int main() {
    std::string input;

    std::cout << "Wire 1:";
    std::cin >> input;

    std::vector<std::string> wire1 = parseInput(input);

    std::cout << "Wire 2:";
    std::cin >> input;

    std::vector<std::string> wire2 = parseInput(input);

    std::vector<coords> wire1_coords = map(wire1),
                        wire2_coords = map(wire2);
    
    std::vector<coords> intersection = mapIntersection(wire1_coords, wire2_coords);

    
    part1(intersection);

    part2(intersection, wire1_coords, wire2_coords);


}