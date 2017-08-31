// graph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	std::vector<std::pair<int, int>> v { {1,2}, {3, 4}, {2, 4}, {5, 6}, {7, 8}, {5, 8}, {9, 10} };
	graphs::UndirectedGraph<int> g(v);
	std::cout << "Graph 1:\n    "<< g.numberOfConnectedComponents() << std::endl;
	std::map<int, bool> m;
	for (auto i : v) {
		m.insert_or_assign(i.first, false);
		m.insert_or_assign(i.second, false);
	}
	g.bfs(1, m, [](int x) {
		std::cout << "    I'm seeing " << x << std::endl;
		return x <= 2;
	});

	std::cout << "Tree 1:\n    ";

	graphs::Tree<int> tree{ 7 };
	tree.addSon(7, 1);
	tree.addSon(7, 5);
	tree.addSon(1, 3);
	tree.addSon(3, 2);
	tree.addSon(5, 4);
	tree.addSon(5, 6);

	std::cout << "Sum equals:" << tree.bfs(0,
		[](int acc, int cur) {
		std::cout << cur << "\n    ";
		return acc + cur;
	});

	getchar();
    return 0;
}

