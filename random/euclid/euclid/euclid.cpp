// euclid.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	
	int tab[3][1<<14];
	int i = 0;
	tab[i][0] = 1;
	tab[i][1] = 0;
	tab[i][2] = 4043;
	++i;
	tab[i][0] = 0;
	tab[i][1] = 1;
	tab[i][2] = 166361;
	++i;
	
	while (tab[i][2]) {
		int cur = tab[i - 2][2] / tab[i - 1][2];
		for (int j = 0; j < 3; ++j) {
			tab[i][j] = tab[i - 2][j] - cur * tab[i - 1][j];
		}
	}
	return 0;
}

