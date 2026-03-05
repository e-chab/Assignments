#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>

/*
./input_generator 
 Generates random files: input_100.txt, input_500.txt, input_1000.txt, input_5000.txt, input_10000.txt
*/
int main(int argc, char** argv) {
    
    // Different sizes to generate
    std::vector<int> sizes = {100, 500, 1000, 5000, 10000};
    
    for (int homes : sizes) {
        std::string filename = "input_" + std::to_string(homes) + ".txt";
        
        std::ofstream file(filename);
        
        if (!file) {
            std::cerr << "Error: could not create file " << filename << "\n";
            continue;
        }
        
        // Write header
        file << homes << "\n";
        
        // Generate random maxCandy and random candy pieces (0 to 1000)
        for (int i = 0; i < homes + 1; ++i) {
            int candies = rand() % 1001;
            file << candies << "\n";
        }
        
        file.close();
    }
}
