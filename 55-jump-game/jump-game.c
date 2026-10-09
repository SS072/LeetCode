bool canJump(int* nums, int numsSize){
    int jump = 0;
    for (int i = 0; i < numsSize; i++) {
        if (jump < i) {
            break;
        }
        if (jump < i + nums[i]) {
            jump = i + nums[i];
        }
        if (jump >= numsSize - 1) {
            return true;
        }
    }
    return false;
}