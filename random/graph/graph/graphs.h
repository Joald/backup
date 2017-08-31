#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <queue>
#include <functional>
#include <algorithm>

namespace graphs {

template <typename T>
class Vertex {
	T key;
	std::vector<Vertex<T>*> neigh;
public:
	Vertex<T>(T& t) : key(t) {
	}

	T* getKey() {
		return &key;
	}

	std::vector<T*> getNeighbours() {
		std::vector<T*> toReturn;
		toReturn.reserve(neigh.size());
		for (auto i : neigh) {
			toReturn.push_back(i->getKey());
		}
		return toReturn;
	}

	void addNeighbour(Vertex<T>* newNeighbour) {
		neigh.push_back(newNeighbour);
	}
};

template <typename T>
class Graph {
	std::map<T, Vertex<T>> vertices;

	Vertex<T>* assureOfExistence(T& query, bool shouldExist = false) {
		auto search = vertices.find(query);
		if (search == vertices.end()) {
			if (shouldExist) {
				throw - 1;
			}
			vertices.insert_or_assign(query, Vertex<T>(query));
			search = vertices.find(query);
		}
		return &(search->second);
	}

protected:
	void addDirectedEdgeInternal(T& from, T& to) {
		auto fromPtr = assureOfExistence(from);
		auto toPtr = assureOfExistence(to);
		fromPtr->addNeighbour(toPtr);
	}

public:
	virtual void addEdge(T& t1, T& t2) = 0;

	void bfs(const T& startKey, std::map<T, bool>& vis, std::function<bool(T)> pred = [](T v) {return true; }) {
		std::queue<T*> q;
		T t = startKey;
		q.push(&t);
		while (!q.empty()) {
			T currentKey = *(q.front());
			q.pop();
			Vertex<T>* current = assureOfExistence(currentKey);

			auto search = vis.find(currentKey);
			search->second = true;

			for (auto i : current->getNeighbours()) {
				T currentNeighbourKey = *i;
				auto currentNeighbour = vis.find(currentNeighbourKey);

				if (currentNeighbour->second == false && pred(currentNeighbourKey)) {
					q.push(i);
				}
			}
		}
	}

	int numberOfConnectedComponents() {
		std::map<T, bool> vis;
		for (auto& i : vertices) {
			vis.insert_or_assign(i.first, false);
		}
		int counter = 0;
		for (auto& i : vertices) {
			if (!vis.at(i.first)) {
				bfs(i.first, vis);
				counter++;
			}
		}
		return counter;
	}
};

template <typename T>
class DirectedGraph : public Graph<T> {
public:
	DirectedGraph(std::vector<std::pair<T, T>> source) {
		for (const auto& i : source) {
			addDirectedEdge(i.first, i.second);
		}
	}

	void addEdge(const T& from, const T& to) {
		addDirectedEdgeInternal(from, to);
	}
};

template <typename T>
class UndirectedGraph : public Graph<T> {
public:
	UndirectedGraph(std::vector<std::pair<T, T>> source) {
		for (auto& i : source) {
			addEdge(i.first, i.second);
		}
	}

	void addEdge(T& t1, T& t2) {
		addDirectedEdgeInternal(t1, t2);
		addDirectedEdgeInternal(t2, t1);
	}
};
	

/*
	Representation of a single-direction tree indexed by any type.
	It relies on std::unique_ptr for memory ownership. Vertices are added by copy.
	The most efficient way of adding vertices involves creating a root, then adding
	all of its sons, then for each son, get a reference to it and repeat.
*/
template <typename T>
class Tree {
	T id;
	std::vector<std::unique_ptr<Tree<T>>> sons;
	void addSonInternal(const T& sonId) {
		sons.push_back(std::make_unique<Tree<T>>(sonId));
	}
public:
	Tree(const T& newId) : id(newId) {}
	
	Tree(const std::vector<std::pair<T, T>>& v) {
		for (auto i : v) {
			addSon(i.first, i.second);
		}
	}

	Tree(Tree<T>&& movedTree) : id(movedTree.id) sons(std::move(movedTree.sons)) {}

	virtual bool addSon(const T& fatherId, const T& sonId) {
		if (id == fatherId) {
			addSonInternal(sonId);
			return true;
		}
		for (auto& i : sons) {
			auto res = i->addSon(fatherId, sonId);
			if (res) {
				return true;
			}
		}
		return false;
	}

	/*
		This method serves to make the process of adding a large
		number of sons faster.
	*/
	inline void reserveAdditionalMemory(size_t size) {
		sons.reserve(size);
	}

	T bfs(const T& accumulator, std::function<T(const T&, const T&)> operation) {
		T ret = operation(accumulator, id);
		for (auto& i : sons) {
			ret = i->bfs(ret, operation);
		}
		return ret;
	}

	const T& getId() { return id; }

	Tree& getChild(const T& childId) {
		if (childId == id) {
			return *this;
		}
		for (auto& i : sons) {
			auto subTree = getChild(childId);
			if (subTree != nullptr) {
				return subtree;
			}
		}
		return nullptr;
	}
};

template <typename T, typename V>
class AugGraph : public Graph<T> {

};

} //namespace graphs