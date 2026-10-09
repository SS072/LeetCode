/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    int *result = malloc((numsSize - k + 1) * sizeof(int));
    int *deque = malloc(numsSize * sizeof(int));

    int front = 0;
    int rear = 0;
    *returnSize = 0;

    for (int i = 0; i < numsSize; i++) {

        while (front < rear && deque[front] <= i - k) {
            front++;
        }

        while (front < rear && nums[deque[rear - 1]] <= nums[i]) {
            rear--;
        }

        deque[rear++] = i;

        if (i >= k - 1) {
            result[(*returnSize)++] = nums[deque[front]];
        }
    }

    free(deque);
    return result;
}