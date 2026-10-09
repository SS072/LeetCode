/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize) {
    int wordLengths[wordsSize];  // Local array for word lengths
    for (int i = 0; i < wordsSize; i++) {
        wordLengths[i] = strlen(words[i]);
    }

    char** result = (char**)malloc(wordsSize * sizeof(char*));
    int resultIndex = 0;
    int i = 0;

    while (i < wordsSize) {
        int lineLength = 0;
        int start = i;

        // Calculate the length of the line
        // i - start is the number of spaces
        while (i < wordsSize && lineLength + wordLengths[i] + (i - start) <= maxWidth) {
            lineLength += wordLengths[i];
            i++;
        }

        // Number of words in the current line
        int numWords = i - start;
        int totalSpaces = maxWidth - lineLength;
        int spaceSlots = numWords - 1;

        result[resultIndex] = (char*)malloc((maxWidth + 1) * sizeof(char));
        result[resultIndex][0] = '\0';  // Initialize the string

        // If we are on the last line or the line has only one word, left justify
        if (i == wordsSize || spaceSlots == 0) {
            for (int j = start; j < i; j++) {
                strcat(result[resultIndex], words[j]);
                if (j < i - 1) {
                    strcat(result[resultIndex], " ");
                }
            }
            // Add remaining spaces
            while (strlen(result[resultIndex]) < maxWidth) {
                strcat(result[resultIndex], " ");
            }
        } else {
            int spaces = totalSpaces / spaceSlots;
            int extraSpaces = totalSpaces % spaceSlots;

            for (int j = start; j < i; j++) {
                strcat(result[resultIndex], words[j]);
                if (j < i - 1) {  // If not the last word
                    for (int s = 0; s < spaces + (j - start < extraSpaces ? 1 : 0); s++) {
                        strcat(result[resultIndex], " ");
                    }
                }
            }
        }

        resultIndex++;
    }

    *returnSize = resultIndex;
    return result;
}