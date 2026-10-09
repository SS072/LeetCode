int removeDuplicates(int* nums, int numsSize){
    // Special case...
    if (numsSize <= 2)
        return numsSize;
    int prev = 1;       // point to previous
    int curr = 2;       // point to current
    // Traverse all elements through loop...
    while (curr < numsSize) {
        // If the curr index matches the previous two elements, skip it...
        if (nums[curr] == nums[prev] && nums[curr] == nums[prev - 1]) {
            curr++;
        }
        // Otherwise, count that element and update...
        else {
            prev++;
            nums[prev] = nums[curr];
            curr++;
        }
    }
    return prev + 1;     // Return k after placing the final result in the first k slots of nums...
}