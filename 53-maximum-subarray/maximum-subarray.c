#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int maxSubArray(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    
    // max_so_far: overall maximum sum
    int max_so_far = nums[0];
    
    // max_ending_here: max sum of subarray ending at current position
    int max_ending_here = nums[0];

    for (int i = 1; i < numsSize; i++) {
        // Core decision: start new or extend previous
        max_ending_here = max(nums[i], max_ending_here + nums[i]);

        // Update overall maximum
        max_so_far = max(max_so_far, max_ending_here);
    }

    return max_so_far;
}