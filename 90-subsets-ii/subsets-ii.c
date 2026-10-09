#define MAX_LEN (10)
#define RANGE (21)
#define NUM2INDEX(n) (n + 10)
#define INDEX2NUM(i) (i - 10)

// Macro to return the nth bit of i
#define LSB(i, n) (!!((i) & (1 << (n))))

// Function to get number of set bits
int getSetBitsCount(int n) {
    int count = 0;
    while (n != 0) {
        count += n & 1;
        n >>= 1;
    }

    return count;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsetsWithDup(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    // Bitmasking with duplicate filtering
    // Key Insight: sort the array
    // If a repeated element is selected, all its previous duplicate elements must be selected for the selection / subset to be valid

    int maxNumSubset = (1 << numsSize);
    int numSubsets = 0;

    // Allocate size for the array of pointers (2D array)
    // Initially assign space assuming no duplicates, we will free remaining space later
    int **powerSet = (int**) malloc(sizeof(int*) * maxNumSubset);
    int *columnSizes = (int*) malloc(sizeof(int) * maxNumSubset);
    // We will allocate space for each of the subsets as we need them

    // Map to store whether a number is repeated
    // Since the range of the elements is very small, we can use counting sort
    int freqMap[RANGE] = {0};

    // Go through the array and fill the frequency map
    for (int i = 0; i < numsSize; ++i) {
        ++freqMap[NUM2INDEX(nums[i])];
    }

    // Apply counting sort
    int numIndex = 0;
    // Iterate over every number in range
    for (int i = 0; i < RANGE; ++i) {
        for (int j = 0; j < freqMap[i]; ++j) {
            nums[numIndex++] = INDEX2NUM(i); 
        }
    }

    // Loop over all possible bitmasks for selection of subsets
    for (int i = 0; i < maxNumSubset; ++i) {
        // For each bitmask, get the corresponding subset (only if it is valid)

        // Temporary variables to store the subset under consideration
        int subsetSize = 0;
        int subset[getSetBitsCount(i) + 1];
        bool isSubsetValid = 1;

        // Iterate over numns to fetch the selected elements to build the subset
        for (int j = 0; j < numsSize; ++j) {

            // If element not selected, continue
            if (!LSB(i, j)) {
                continue;
            }

            // If the number is a repeated number
            if (freqMap[NUM2INDEX(nums[j])] > 1) {
                // Check if all the previous duplicates are selected
                for (int k = j; k >= 0 && nums[k] == nums[j]; --k) {
                    if (!LSB(i, k)) {
                        isSubsetValid = 0;
                        break;
                    }
                }
            }

            // If a subset is not valid stop constructing this subset
            if (!isSubsetValid) {
                break;
            }

            // Add the element to the subset
            subset[subsetSize++] = nums[j];
        }

        // Only if the subset is valid, we add it to the pwer set
        if (isSubsetValid) {
            powerSet[numSubsets] = (int*) malloc(sizeof(int) * subsetSize);
            columnSizes[numSubsets] = subsetSize;
            memcpy(powerSet[numSubsets++], subset, subsetSize * sizeof(int));
        }
    }

    // Free extra pointers allocated with the assumption of no duplicates
    powerSet = realloc(powerSet, numSubsets * sizeof(int*));
    columnSizes = realloc(columnSizes, numSubsets * sizeof(int));

    *returnColumnSizes = columnSizes;
    *returnSize = numSubsets;
    return powerSet;

}