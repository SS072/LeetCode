struct TreeNode* ConvToBST(int *nums, int beg, int end){
    if(end < beg)
        return NULL ;
    int mid = (beg + end)/2 ;
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = nums[mid];
    root->left = ConvToBST(nums, beg, mid-1);
    root->right = ConvToBST(nums, mid+1, end);
    return root;
}
struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    if(numsSize <= 0)
        return NULL;
    else
        return ConvToBST(nums, 0, numsSize-1);
}