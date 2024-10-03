/**
 * Author: DeMen100ns
 * Description: Calculate every multiplicative function value $f(1) \rightarrow f(n)$, with only know $f(p^k)$ in $O(T)$ with given prime $p$ and integer $k$. 
 * Time: $O(n \times T)$, with $O(T)$ as the complexity of calculate $f(p^k)$.
 */

vector <int> sieve (int n) {
    vector <int> prime, is_composite, func, cnt;
    vector <vector<int>> primepow;

    auto powpk = [&](int p, int k) -> int{
        return primepow[p][k];
    };

    auto f = [&](int p, int k) -> int{
        //calculate f(p^k)
    };

    is_composite.resize(n, 0);
    func.resize(n, 0);
    cnt.resize(n, 0);
    primepow.resize(n);

	func[1] = 1;
	for (int i = 2; i < n; ++i) {
		if (!is_composite[i]) {
			prime.push_back (i);
            for(int a = 1, pw = 0; a < n; a *= i, pw++){
                primepow[i].push_back(a);
            }
			func[i] = f(i, 1); cnt[i] = 1;
		}
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0) {
                //f(i * prime[j]) = f(i / prime[j] ^ cnt[i]) * f(prime[j] ^ (cnt[i] + 1))
				func[i * prime[j]] = func[i / powpk(prime[j], cnt[i])] * f(prime[j], cnt[i] + 1);
				cnt[i * prime[j]] = cnt[i] + 1;
				break;
			} else {
                //f(i * prime[j]) = f(i) * f(prime[j])
				func[i * prime[j]] = func[i] * func[prime[j]];
				cnt[i * prime[j]] = 1;
			}
		}
	}
    return func;
}
