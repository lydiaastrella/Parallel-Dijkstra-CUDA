#include <iostream>
#include <fstream>
#include <string>
#include <sys/time.h>

using namespace std;

#define N_MAX 9999

int* initializeGraf(int N, int* graf) {
	int r;
	int pembatas = 0;
	srand((unsigned)13517031);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - pembatas; j++) {
			r = rand() % 10;
			graf[i*N + j] = r;
			graf[j*N + i] = r;
		}
		pembatas += 1;
	}
	return graf;
}