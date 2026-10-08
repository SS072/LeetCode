
int compare(const void* a, const void* b) {
    int* nodeA = (int*)a;
    int* nodeB = (int*)b;
    return *nodeA - *nodeB;
}

void backtrack(int* candidates, int candidatesSize, int target, int* returnSize,
               int** returnColumnSizes, int** result, int* temp, int tempSize,
               int start) {
    if (target == 0) {
        result[*returnSize] = (int*)malloc(tempSize * sizeof(int));
        for (int i = 0; i < tempSize; i++) {
            result[*returnSize][i] = temp[i];
        }
        (*returnColumnSizes)[*returnSize] = tempSize;
        (*returnSize)++;
        return;
    }

    for (int i = start; i < candidatesSize; i++) {
        if (i > start && candidates[i] == candidates[i - 1])
            continue;
        if (candidates[i] > target)
            break;

        temp[tempSize] = candidates[i];
        backtrack(candidates, candidatesSize, target - candidates[i],
                  returnSize, returnColumnSizes, result, temp, tempSize + 1,
                  i + 1);
    }
}

int** combinationSum2(int* candidates, int candidatesSize, int target,
                      int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    int maxSize = 100;
    int** result = (int**)malloc(maxSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxSize * sizeof(int));

    int* temp = (int*)malloc(candidatesSize * sizeof(int));
    int tempSize = 0;

    qsort(candidates, candidatesSize, sizeof(int), compare);

    backtrack(candidates, candidatesSize, target, returnSize, returnColumnSizes,
              result, temp, tempSize, 0);

    free(temp);
    return result;
}