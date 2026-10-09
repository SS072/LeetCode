#include <stdlib.h>

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int left = 0;
    int right = numbersSize - 1;

    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));

    while (left < right) {
        int current_sum = numbers[left] + numbers[right];

        if (current_sum == target) {
            result[0] = left + 1;   // 1-based indexing
            result[1] = right + 1;
            return result;
        }
        else if (current_sum < target) {
            left++;
        }
        else {
            right--;
        }
    }

    return result;
}