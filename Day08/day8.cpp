#include <iostream>
#include <vector>
#include <array>
#include <string>

int countZero(std::vector<int> pixels, int width, int height) {
    std::vector<std::vector<int>> layers;
    std::vector<int> layer;
    int count = 0;
    for(int i = 0; i < pixels.size(); i++) {
        if(i % (width * height) == 0 && i != 0) {
            layers.push_back(layer);
            layer.clear();
            count++;
        }
        layer.push_back(pixels[i]);
    }

    std::vector<int> layer_0_count;
    for(auto one_layer : layers) {
        int zero_count = 0;
        for(auto digit : one_layer) {
            if(digit == 0)
                zero_count++;
        }
        layer_0_count.push_back(zero_count);
    }

    std::vector<int> lowest_layer;
    int lowest = INT32_MAX;
    for(int i = 0; i < layer_0_count.size(); i++) {
        if(layer_0_count[i] < lowest) {
            lowest = layer_0_count[i];
            lowest_layer = layers[i];
        }
    }

    int count_1, count_2;
    for(auto digit : lowest_layer) {
        if(digit == 1)
            count_1++;
        else if(digit == 2)
            count_2++;
    }

    return count_1 * count_2;
}

void decode(std::vector<int> pixels, int width, int height) {
    std::vector<std::vector<int>> layers;
    std::vector<int> layer;
    int count = 0;
    for(int i = 0; i < pixels.size(); i++) {
        if(i % (width * height) == 0 && i != 0) {
            layers.push_back(layer);
            layer.clear();
            count++;
        }
        layer.push_back(pixels[i]);
    }
    layers.push_back(layer);
    char white = '#';
    char black = ' ';
    char transparent ='_';
    
    int size = width*height;
    char message[size];
    for(int i =0; i < size; i++)
        message[i] = transparent;

    for(int j = 0; j < layers.size(); j++) {
        layer = layers[j];
        for(int i = 0; i < layer.size(); i++) {
            int digit = layer[i];
            switch(digit) {
                case 0:
                    if(message[i] == transparent)
                        message[i] = black;
                    break;
                case 1:
                    if(message[i] == transparent)
                        message[i] = white;
                    break;
            }
        }
    }

    std::cout << std::endl << std::endl;
    int row_count = 0;
    for(int _col = 0; _col < height; _col++) {
        for(int _row = 0; _row < width; _row++) {
            std::cout << message[_row + row_count];
        }
        row_count += 25;
        std::cout << std::endl;
    }
}

int main() {
    std::string input = "";
    std::vector<int> pixels;

    for(auto digit : input) {
        pixels.push_back(digit - '0');
    }

    std::cout << "Result: " << countZero(pixels, 25, 6) << std::endl;
    decode(pixels, 25, 6);
}