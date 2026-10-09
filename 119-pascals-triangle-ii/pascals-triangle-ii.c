long long calculateCombination(int n, int r) {
    long long result = 1;
    for (int i = 0; i < r; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

int* getRow(int rowIndex, int* returnSize) {
    // Initialize an array to represent the last row
    int* lastRow = (int*)malloc((rowIndex + 1) * sizeof(int));

    for (int j = 0; j <= rowIndex; j++) {
        // Calculate and insert the binomial coefficient (nCr) into the row
        lastRow[j] = (int)calculateCombination(rowIndex, j);
    }

    *returnSize = rowIndex + 1;

    return lastRow;
}