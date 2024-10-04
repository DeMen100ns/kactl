/**
 * Author: DeMen100ns
 * Date: 2024-01-01
 * Description: Custom bitset
 * Usage: bitset<len> in your function.
 */

template <int len = 1>
int calc(int n) {
    if (n > len) {
        return calc<min(len*2, N)>(n);
    }
    //bitset<len> :thonk:
}
