int compare(int*nums1,int i,int len1,int*nums2,int j,int len2){
    while(i<len1&&j<len2&&nums1[i]==nums2[j]){
        i++;
        j++;
    }
    return j==len2||(i<len1&&nums1[i]>nums2[j]);
}

int*maxSubsequence(int*nums,int numsSize,int k){
    int*stack=(int*)malloc(sizeof(int)*k);
    int top=-1;
    int toRemove=numsSize-k;
    for(int i=0;i<numsSize;i++){
        while(top>=0&&stack[top]<nums[i]&&toRemove>0){
            top--;
            toRemove--;
        }
        if(top+1<k){
            stack[++top]=nums[i];
        }else{
            toRemove--;
        }
    }
    return stack;
}

void merge(int*subseq1,int len1,int*subseq2,int len2,int*result){
    int i=0,j=0,r=0;
    while(i<len1||j<len2){
        if(compare(subseq1,i,len1,subseq2,j,len2)){
            result[r++]=subseq1[i++];
        }else{
            result[r++]=subseq2[j++];
        }
    }
}

int*maxNumber(int*nums1,int nums1Size,int*nums2,int nums2Size,int k,int*returnSize){
    int*maxCombo=(int*)malloc(sizeof(int)*k);
    memset(maxCombo,0,sizeof(int)*k);
    for(int i=fmax(0,k-nums2Size);i<=fmin(k,nums1Size);i++){
        int j=k-i;
        int*subseq1=maxSubsequence(nums1,nums1Size,i);
        int*subseq2=maxSubsequence(nums2,nums2Size,j);
        int*candidate=(int*)malloc(sizeof(int)*k);
        merge(subseq1,i,subseq2,j,candidate);
        if(compare(candidate,0,k,maxCombo,0,k)){
            memcpy(maxCombo,candidate,sizeof(int)*k);
        }
        free(subseq1);
        free(subseq2);
        free(candidate);
    }
    *returnSize=k;
    return maxCombo;
}