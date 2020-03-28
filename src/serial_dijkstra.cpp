#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sys/time.h>

using namespace std;

#define N_MAX 9999

int* initializeGraf(int N, int* graf){
    int r;
    int pembatas=0;
    srand((unsigned) 13517031);
    for(int i =0; i<N; i++){
        for (int j=0; j<N-pembatas; j++){
            r = rand() % 10;
            graf[i*N + j] = r;
            graf[j*N + i] = r;
        }
        pembatas +=1;
    }
    return graf;
}

void printOutput(int* matrix, int N, string filename ){
    ofstream file;
    file.open(filename, ios::out);
    
    if(file.is_open()){
        for (int i=0; i<N; i++){
            file<<"jarak dari node "<<i<<": ";
            for (int j=0; j<N; j++){
                file<<matrix[i*N + j]<<" ";
            }
            file<<endl;
        }
    }else{
        cout<<"Error, unable to open file"<<endl;
    }
    file.close();
}

int minDist(int* array, int* included, int N, int src){
    int minIdx = 0;
    int min = N_MAX;
    for (int i = 0; i < N; i++){
        if (array[src*N + i] <= min ){
            if (included[i] == 0){
                min = array[src*N + i];
                minIdx = i;
            }
        }
    }
    return minIdx;
}

void dijkstra(int* graf, int N, int src, int* shortestDist){

    // int* shortestDist = new int[N];
    int* included = new int[N];
    int minIdx;

    if (shortestDist != NULL && included != NULL){
        for (int i = 0; i < N; i++ ){
           shortestDist[src*N + i] = N_MAX;
           included[i] = 0;
        }
        
        shortestDist[src*N + src] = 0;

        for (int i = 0; i < N -1; i++){
            minIdx = minDist(shortestDist, included, N, src);
            
            included[minIdx] = 1;

            for (int j = 0; j < N; j++){
                if (included[j] == 0 && shortestDist[src * N + minIdx] != N_MAX && graf[N * minIdx + j] != 0){
                    if (graf[minIdx * N + j] + shortestDist[src*N + minIdx] < shortestDist[src * N + j]){
                        shortestDist[src*N+j] = graf[minIdx * N + j] + shortestDist[src * N + minIdx];
                    }
                }
            }
        }

        delete[] included;
    }
}

int main(){
    int N;
    int* graf = new int[N*N];
    struct timeval start, end;

    cout<< "Enter amount of Node : ";
    cin>>N;

    graf = initializeGraf(N, graf);

    int* short_dis = new int[N*N];

    gettimeofday(&start, NULL);

    for (int i=0; i<N; i++){
        dijkstra(graf, N, i, short_dis);
    }

    gettimeofday(&end, NULL);

    printOutput(short_dis,N,"../output/serial_dijkstra.txt");

    int exectime = ((end.tv_sec - start.tv_sec) *1000000) + (end.tv_usec - start.tv_usec);
    cout<<"Execution time : "<<exectime<<" microseconds"<<endl;

    // freeMatrix(graf, N);
    delete[] graf;
    delete[] short_dis;
    return 0;
}