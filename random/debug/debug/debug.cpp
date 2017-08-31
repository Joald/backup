// debug.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

template<typename T>
void print(const T& t) {
	cout << t;
}
template<typename T>
void println(const T& t) {
	cout << t << endl;
}


class foo {
public:
	string* strp;
	shared_ptr<string>guard;
	std::string s;
	foo() { cout << "constructing foo with default " << s << "\n"; }
	foo(shared_ptr<string> ptrstr) : strp(ptrstr.get()), guard(move(ptrstr)), s(*strp) {
		cout << "constructing foo with:\n"
			<< "guard containing " << *guard << "\npointer pointing to " << *strp << ".\n";
		*guard = "finalcheck";
		cout << *strp << endl << endl;
	}
	foo(const foo&& other) { s = other.s; cout << "constructing foo with " << s << "\n"; }
	~foo() { cout << "destructing foo with " << s << "\n"; }
};

int main() {
	std::vector<std::shared_ptr<foo>> guardian_;
	std::shared_ptr<foo>bar;
	{
		cout << "entering block\n";
		foo* x = new foo(make_shared<string>(string("checking")));
		bar.reset(x);
		guardian_.push_back(std::move(bar));
		cout << "leaving block\n";
	}
	cout << "finished leaving block\n";
	cout << guardian_[0]->s << " guardian contains " << guardian_.size() << " elements. \n";
	
	cout << "ending program\n";
	int n;
	cin >> n;
	print(n);
	print(guardian_);
	return 0;
}
