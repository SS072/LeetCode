double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    double res=0;
    int i=0,j=0;
    int sum=nums1Size+nums2Size;
    int mid=sum/2;
    int pre=0,curr=0;
    while(i+j<=mid){
        pre=curr;
        if(i>=nums1Size){
            curr=nums2[j];
            j++;
        }
        else if(j>=nums2Size){
            curr=nums1[i];
            i++;
        }
        else if(nums1[i]<nums2[j]){
            curr=nums1[i];
            i++;
        }
        else{
            curr=nums2[j];
            j++;
        }
        
    }
    if(sum%2==0){
        res=(curr+pre)/2.0;
    }
    else{
        res=curr;
    }
    return res;
}