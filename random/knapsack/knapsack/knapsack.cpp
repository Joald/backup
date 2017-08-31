// knapsack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


vector<pair<int, int>> neiList(pair<int, int> x) {
	vector<pair<int, int>> v;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i || j) {
				v.push_back(make_pair(x.first + i, x.second + j));
			}
		}
	}
	return v;
}

int dfs(vector<vector<pair<bool, bool>>>& grid, int i, int j) {
	queue<pair<int, int>> q;
	q.push(make_pair(i, j));
	grid[i][j].second = 1;
	int count = 0;
	while (!q.empty()) {
		auto a = q.front();
		q.pop();
		count++;
		for (auto i : neiList(a)) {
			if (i.first < 0 || i.first >= grid.size() || i.second < 0 || i.second > grid[0].size()) {
				continue;
			}
			auto c = grid[i.first][i.second];
			if (c.first && !c.second) {
				c.second = true;
				q.push(i);
			}
		}
	}
	return count;
}
int get_biggest_region(vector<vector<pair<bool, bool>>>& grid) {
	int maks = 0;
	int ii = 0;
	for (auto i : grid) {
		int jj = 0;
		for (auto j : i) {
			if (j.first && !j.second) {
				maks = max(dfs(grid, ii, jj), maks);
			}
			jj++;
		}
		ii++;
	}
	return maks;
}

int main() {
	int n;
	cin >> n;
	int m;
	cin >> m;
	vector<vector<pair<bool, bool>>> grid(n, vector<pair<bool, bool>>(m, make_pair(0, 0)));
	for (int grid_i = 0; grid_i < n; grid_i++) {
		for (int grid_j = 0; grid_j < m; grid_j++) {
			cin >> grid[grid_i][grid_j].first;
		}
	}
	cout << get_biggest_region(grid) << endl;
	return 0;
}
