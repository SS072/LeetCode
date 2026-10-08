/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

void backtrack(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes,int **result,int* path,int pathSize,int start){
    if(target==0){
        result[*returnSize]=malloc(sizeof(int)*pathSize);
        for(int i=0;i<pathSize;i++){
            result[*returnSize][i]=path[i];
        }
        (*returnColumnSizes)[*returnSize]=pathSize;
        (*returnSize)++;
    }

    for(int i=start;i<candidatesSize;i++){
        if(candidates[i]>target)break;
        path[pathSize]=candidates[i];
        backtrack(candidates,candidatesSize,target-candidates[i],returnSize,returnColumnSizes,result,path,pathSize+1,i);
    }
}

int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    int cmp(const void*a,const void*b){
        return *(int*)a-*(int*)b;
    }
    qsort(candidates,candidatesSize,sizeof(int),cmp);
    int **result=malloc(sizeof(int*)*1000);
    *returnColumnSizes=malloc(sizeof(int)*1000);
    *returnSize=0;

    int *path=malloc(target*sizeof(int));
    backtrack(candidates,candidatesSize,target,returnSize,returnColumnSizes,result,path,0,0);

    free(path);
    return result;
}