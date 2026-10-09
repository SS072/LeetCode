#define MIN(a,b) (a < b ? a : b)
int minSubArrayLen(int target, int* nums, int numsSize) {
    int left = 0, right = 0, sum = 0, ans = INT_MAX;
    while(right < numsSize) {
        sum += nums[right];
        while((sum - nums[left]) >= target) {
            sum -= nums[left];
            left++;
        }
        right++;
        if(sum >= target) {
            ans = MIN(right - left , ans);
        } 
    }
    if(ans == INT_MAX) return 0;
    return ans;
}