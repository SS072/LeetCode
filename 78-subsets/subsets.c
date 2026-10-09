#include <stdlib.h>

void recursion(int* nums, int numsSize, int cur_index, int* curr, int currSize, int** res, int* resSize, int** returnColumnSizes) {
    res[*resSize] = (int*)malloc(currSize * sizeof(int));
    for (int i = 0; i < currSize; i++) {
        res[*resSize][i] = curr[i];
    }
    (*returnColumnSizes)[*resSize] = currSize;
    (*resSize)++;
    
    for (int index_of_next = cur_index; index_of_next < numsSize; index_of_next++) {
        curr[currSize] = nums[index_of_next];
        recursion(nums, numsSize, index_of_next + 1, curr, currSize + 1, res, resSize, returnColumnSizes);
    }
}

int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int maxNumSubsets = 1 << numsSize;
    int** res = (int**)malloc(maxNumSubsets * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxNumSubsets * sizeof(int));
    *returnSize = 0;
    int* curr = (int*)malloc(numsSize * sizeof(int));
    
    recursion(nums, numsSize, 0, curr, 0, res, returnSize, returnColumnSizes);
    
    free(curr);
    return res;
}