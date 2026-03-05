#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h> 

bool read_input(const std::string &filename, int &homes, int &maxCandy, std::vector<int> &candy) {
    std::ifstream file(filename);

    if (!file) return false;

    file >> homes;
    file >> maxCandy;

    candy.resize(homes);
    for (int i = 0; i < homes; i++)
        file >> candy[i];

    return true;
}

bool best_sequence_parallel(const std::vector<int> &candy, int homes, int maxCandy,
                            int &bestStart, int &bestEnd, int &bestSum) {

    bestSum = -1;
    bestStart = -1;
    bestEnd = -1;

    // OpenMP parallel region
    #pragma omp parallel
    {
        int localBestSum = -1;
        int localStart = -1;
        int localEnd = -1;

        // Distribute starting indices across threads
        #pragma omp for //schedule(dynamic)
        for (int i = 0; i < homes; i++) {

            int sum = 0;

            for (int j = i; j < homes; j++) {

                sum += candy[j];

                // Early exit if the sum exceeds maxCandy
                if (sum > maxCandy)
                    break;

                if (sum > localBestSum) {
                    localBestSum = sum;
                    localStart = i;
                    localEnd = j;
                }

                // Early exit if we reach maxCandy exactly
                // (Adding further homes would iply that the next homes give zero candy but it does not improve the result)
                if (sum == maxCandy)
                    break;
            }
        }

        // Manual reduction to update the global best result
        // If there is a tie on sum, choose the sequence with the smaller starting index
        #pragma omp critical
        {
            if (localBestSum > bestSum ||
                (localBestSum == bestSum && localStart < bestStart)) {

                bestSum = localBestSum;
                bestStart = localStart;
                bestEnd = localEnd;
            }
        }
    }

    return (bestSum != -1);
}

void print_result(int bestStart, int bestEnd, int bestSum) {
    if (bestSum == -1) {
        std::cout << "Don't go here\n";
    } else {
        std::cout << "Start at home " << (bestStart + 1) << " and go to home " << (bestEnd + 1) << " getting " << bestSum << " pieces of candy\n";
    }
}