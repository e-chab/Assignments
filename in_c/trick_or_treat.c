#include <stdio.h>
#include <stdlib.h>
#include <time.h>



/*
 Reads a file and fills the candy array.
 Parameters:
   - filename : name of the input file
   - homes    : pointer to the number of houses
   - maxCandy : pointer to the maximum allowed candy
   - candy    : pointer to the candy array
 Returns:
   0  if successful
  -1  if an error occurred
*/
int read_input(const char *filename, int *homes, int *maxCandy, int **candy) {
    
    FILE *f = fopen(filename, "r");

    if (!f) {
        printf("Error : cannot open %s\n", filename);
        return -1;
    }

    fscanf(f, "%d", homes);
    fscanf(f, "%d", maxCandy);

    if (*homes <= 0) {
        fclose(f);
        return 0;
    }

    *candy = (int*) malloc((*homes) * sizeof(int));
    if (!*candy) {
        printf("Error : memory allocation failed\n");
        fclose(f);
        return -1;
    }

    for (int i = 0; i < *homes; i++)
        fscanf(f, "%d", &((*candy)[i]));

    fclose(f);
    return 0;
}



/*
 Finds the best sequence of consecutive houses to visit to collect the maximum candy without exceeding maxCandy.
 Parameters:
   - candy     : array of candies per house
   - homes     : number of houses
   - maxCandy  : maximum allowed candy
   - bestStart : pointer to the index of the first house
   - bestEnd   : pointer to the index of the last house
   - bestSum   : pointer to the maximum sum found
 Returns:
   1 if a sequence is found
   0 otherwise
*/
int best_sequence(int *candy, int homes, int maxCandy, int *bestStart, int *bestEnd, int *bestSum) {

    *bestSum = -1;
    *bestStart = -1;
    *bestEnd = -1;

    if (homes <= 0) return 0;

    int sum = 0;
    int start = 0;

    for (int end = 0; end < homes; end++) {
        sum += candy[end];

        // Shrink the window (on the side of the houses with the lowest index) if sum exceeds maxCandy
        while (sum > maxCandy && start <= end) {
            sum -= candy[start];
            start++;
        }

        // Update if the sum is strictly greater than bestSum and is correct 
        if (sum <= maxCandy && sum > *bestSum && start <= end) {

            *bestSum = sum;
            *bestStart = start;
            *bestEnd = end;

            // If we reach exactly maxCandy, we can stop, we won't find a better solution starting at a lower house index
            if (*bestSum == maxCandy)
                return 1;
        }
    }

    return (*bestSum != -1) ? 1 : 0;
}



/*
 Prints the final result.
 Parameters:
   - bestStart : index of the first house
   - bestEnd   : index of the last house
   - bestSum   : total candy collected
*/
void print_result(int bestStart, int bestEnd, int bestSum) {
    if (bestSum == -1) {
        printf("Don't go here\n");
    } else {
        // The houses indexes that from 1, so we add 1 to convert the indexes
        printf("Start at home %d and go to home %d getting %d pieces of candy\n",
               bestStart + 1, bestEnd + 1, bestSum);
    }
}


