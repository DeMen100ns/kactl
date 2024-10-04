template <int len = 1>
int calc(int n) {
    if (n > len) {
        return calc<min(len*2, N)>(n);
    }
    //bitset<len> :thonk:
}
