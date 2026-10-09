int maxProfit(int* prices, int pricesSize) {
    if (pricesSize == 0) return 0;

    int buy = prices[0];
    int profit = 0;

    for (int i = 1; i < pricesSize; i++) {
        if (prices[i] < buy) {
            buy = prices[i];
        } else if (prices[i] - buy > profit) {
            profit = prices[i] - buy;
        }
    }

    return profit;
}