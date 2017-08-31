// pass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;
int main()
{
	lead:
	string s;
	cin >> s;
	const int alphabet_length = 'z' - 'a' + 1;
	for (int i = 0; i < s.size(); ++i) {
		
		char b = s[i];
		b -= 3;
		if (b < 'a') {
			b += alphabet_length;
		}
		int x = (int(b) % 10);
		switch (i % 4) {
		case 0:
			cout << char(b - 'a' + 'A');
			break;
		case 1:
			cout << char('0' + x);
			break;
		case 2:
			b += 'A' - 'a';
			
			char c;
			switch (x) {
			case 0:
				c = '+';
				break;
			
			case 1:
				c = '!';
				break;
			case 2:
				c = '@';
				break;
			case 3:
				c = '#';
				break;
			case 4:
				c = '$';
				break;
			case 5:
				c = '%';
				break;
			case 6:
				c = '^';
				break;
			case 7:
				c = '&';
				break;
			case 8:
				c = '*';
				break;
			case 9:
				c = '-';
				break;
			default:
				c = '/';
			}
			cout << c;
			break;
		case 3:
			cout << char(b + 'a');
			break;
		default:
			cout << '0';
		}

	}
	int n;
	cin >> n;
	if (n == 1) goto lead;
    return 0;
}

