int minimumTotal(int** triangle, int triangleSize, int* triangleColSize){
    int n=triangleSize;
    int dp[n+1];
    for(int i=0;i<=n;i++) dp[i]=0;
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<=i;j++){
            dp[j]=triangle[i][j]+(dp[j]<dp[j+1]?dp[j]:dp[j+1]);
        }
    }
    return dp[0];
}