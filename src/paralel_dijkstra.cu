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

void printOutput(int* matrix, int N, std::string filename) {
	ofstream file;
	file.open(filename, ios::out);

	if (file.is_open()) {
		for (int i = 0; i < N; i++) {
			file << "jarak dari node " << i << ": ";
			for (int j = 0; j < N; j++) {
				file << matrix[i*N + j] << " ";
			}
			file << endl;
		}
	}
	else {
		cout << "Error, unable to open file" << endl;
	}
	file.close();
}