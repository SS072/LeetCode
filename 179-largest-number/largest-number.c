int cmp(const void *a, const void *b) {
    char ab[22], ba[22];
    int a_num = *(int*)a;
    int b_num = *(int*)b;
    sprintf(ab, "%d%d", a_num, b_num);
    sprintf(ba, "%d%d", b_num, a_num);
    return strcmp(ba, ab);
}

char* largestNumber(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), cmp);
    char *answer = malloc(numsSize * 10 + 1);
    int k = 0, index = 0;
    
    if (nums[0] == 0) {
        answer[0] = '0';
        answer[1] = '\0';
        return answer;
    }

    for (int i = 0; i < numsSize; i++) {
        index += sprintf(answer + index, "%d", nums[i]);
    }

    return answer;
}