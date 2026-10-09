int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    int arr[m + n];
    int index = 0;

    for (int i = 0; i < m; i++) {
        arr[index++] = nums1[i];
    }
    for (int j = 0; j < n; j++) {
        arr[index++] = nums2[j];
    }

    qsort(arr, m + n, sizeof(int), cmp);

    for (int i = 0; i < m + n; i++) {
        nums1[i] = arr[i];
    }
}