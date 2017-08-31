
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/*
inline bool poweroftwo(unsigned long long x) {
    unsigned long long c = x;
	while (!(c & 1LL)) {
		c = c >> 1LL;
	}
	bool ret = c == 1;
    cout << "Argument " << x << " is " << (ret ? "" : "not ") << "a power of two.\n";
    return ret;
}

inline unsigned long long removepoweroftwo(unsigned long long n) {
    unsigned long long ret = n ^ (1LL << (63LL - __builtin_clzll(n)));
    cout << "Argument " << n << " without the highest power of two is " << ret << endl;
    return ret;
}

bool solve(unsigned long long n) {
    cout << "Entering solve with argument " << n << endl;
    if (n == 1) {
        return 1;
    }
    cout << "Argument " << n << " != 1.\n";
    if (poweroftwo(n)) {
        return !solve(n >> 1);
    }
    return !solve(removepoweroftwo(n));
}
*/
bool hasNo0(int x) {
	while (x) {
		if (!(x % 10)) {
			return false;
		}
		x /= 10;
	}
	return true;
}

bool hasNo122(int x) {
	bool onefound = false;
	bool twofound = false;
	while (x) {
		int last = x % 10;
		if (twofound) {
			if (last == 1) {
				return false;
			} else {
				onefound = false;
				twofound = false;
				continue;
			}
		} else if (onefound) {
			if (last == 2) {
				twofound = 1;
				continue;
			} else if (last == 1) {
				continue;
			} else {
				onefound = false;
			}
		}
		if (last == 1) {
			onefound = 1;
		}
		x /= 10;
	}
	return true;
}

int main() {
    int t = 11111111;
	int counter = 0;
    while (t < 100000000) {
		if (hasNo0(t) and hasNo122(t)) {
			counter++;
			cout << t << endl;
		}
		
	}
	cout << counter <<endl;
	cout << counter;
    return 0;
}