#include <iostream>
#include <fstream>
#include <vector>

/*
 Reads a file and fills the candy vector.
 Parameters:
   - filename : reference to the name of the input file
   - homes    : reference to the number of houses
   - maxCandy : reference to the maximum allowed candy
   - candy    : reference to the vector of candies
 Returns:
   true if successful
   false if an error occurred
*/
bool read_input(const std::string &filename, int &homes, int &maxCandy, std::vector<int> &candy) {

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: could not open " << filename << std::endl;
        return false;
    }

    file >> homes;
    file >> maxCandy;
    if (homes <= 0) {
        file.close();
        return true;
    }

    candy.resize(homes);
    for (int i = 0; i < homes; i++) {
        file >> candy[i];
    }

    file.close();
    return true;
}

/*
 Finds the best sequence of consecutive houses to collect the maximum candy without exceeding maxCandy.
 Parameters:
   - candy     : vector of candies per house
   - homes     : number of houses
   - maxCandy  : maximum allowed candy
   - bestStart : reference to the index of the first house
   - bestEnd   : reference to the index of the last house
   - bestSum   : reference to the maximum sum found
 Returns:
   true if a sequence is found
   false otherwise
*/
bool best_sequence(const std::vector<int> &candy, int homes, int maxCandy, int &bestStart, int &bestEnd, int &bestSum) {

    bestSum = -1;
    bestStart = -1;
    bestEnd = -1;

    if (homes <= 0) return false;

    int sum = 0;
    int start = 0;

    for (int end = 0; end < homes; ++end) {
        sum += candy[end];

        while (sum > maxCandy && start <= end) {
            sum -= candy[start];
            start++;
        }

        if (sum <= maxCandy && sum > bestSum && start <= end) {
            bestSum = sum;
            bestStart = start;
            bestEnd = end;

            // optimal, so we stop here
            if (bestSum == maxCandy) 
                return true; 
        }
    }

    return (bestSum != -1);
}

/*
 Prints the final result.
 Parameters:
   - bestStart : index of the first house
   - bestEnd   : index of the last house
   - bestSum   : total candy collected
*/
void print_result(int bestStart, int bestEnd, int bestSum) {
    if (bestSum == -1) 
        std::cout << "Don't go here\n";
    else {
        std::cout << "Start at home " << (bestStart + 1) << " and go to home " << (bestEnd + 1) << " getting " << bestSum << " pieces of candy\n";
    }
}
