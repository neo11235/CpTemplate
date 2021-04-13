unsigned seed = chrono::system_clock::now().time_since_epoch().count();
linear_congruential_engine<uint_fast32_t, 1002517UL, 1001593UL, 2147483647UL> lcg(seed);
mt19937 rng(seed);
unordered_set<int> hsh;
