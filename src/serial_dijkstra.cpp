#include <iostream>
#include <fstream>
#include <string>
#include <sys/time.h>

using namespace std;

#define N_MAX 9999

int** initializeGraf(int N){
    int **graf = new int*[N];
    for (int i=0; i<N; i++){
        graf[i] = new int[N];
    }

    int r;
    int pembatas=0;
    srand((unsigned) 13517031);
    for(int i =0; i<N; i++){
        for (int j=0; j<N-pembatas; j++){
            r = rand() % 10;
            graf[i][j] = r;
            graf[j][i] = r;
        }
        pembatas +=1;
    }
    return graf;
}

void freeMatrix(int ** matrix, int N){
    for (int i=0; i<N; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
}

void printOutput(int** matrix, int N, string filename ){
    ofstream file;
    file.open(filename, ios::out);
    
    if(file.is_open()){
        for (int i=0; i<N; i++){
            file<<"jarak dari node "<<i<<": ";
            for (int j=0; j<N; j++){
                file<<matrix[i][j]<<" ";
            }
            file<<endl;
        }
    }else{
        cout<<"Error, unable to open file"<<endl;
    }
    file.close();
}

//for debugging
void printMatrix(int ** matrix, int N){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

int minDist(int* array, int* included, int N){
    int minIdx = 0;
    int min = N_MAX;
    for (int i = 0; i < N; i++){
        if (array[i] <= min ){
            if (included[i] == 0){
                min = array[i];
                minIdx = i;
            }
        }
    }
    return minIdx;
}

int* dijkstra(int** graf, int N, int src){

    int* shortestDist = new int[N];
    int* included = new int[N];
    int minIdx;

    if (shortestDist != NULL && included != NULL){
        for (int i = 0; i < N; i++ ){
           shortestDist[i] = N_MAX;
           included[i] = 0;
        }
        
        shortestDist[src] = 0;

        for (int i = 0; i < N -1; i++){
            minIdx = minDist(shortestDist, included, N);
            
            included[minIdx] = 1;

            for (int j = 0; j < N; j++){
                if (included[j] == 0 && shortestDist[minIdx] != N_MAX && graf[minIdx][j] != 0){
                    if (graf[minIdx][j] + shortestDist[minIdx] < shortestDist[j]){
                        shortestDist[j] = graf[minIdx][j] + shortestDist[minIdx];
                    }
                }
            }
        }

        delete[] included;
    }
    return shortestDist;
}

int main(){
    int N;
    int ** graf;
    struct timeval start, end;

    cout<< "Enter amount of Node : ";
    cin>>N;

    graf = initializeGraf(N);

    int **short_dis = new int*[N];
    for (int i=0; i<N; i++){
        short_dis[i] = new int[N];
    }

    gettimeofday(&start, NULL);

    for (int i=0; i<N; i++){
        short_dis[i] = dijkstra(graf, N, i);
    }

    gettimeofday(&end, NULL);

    printOutput(short_dis,N,"./output/serial_dijkstra.txt");

    int exectime = ((end.tv_sec - start.tv_sec) *1000000) + (end.tv_usec - start.tv_usec);
    cout<<"Execution time : "<<exectime<<" microseconds"<<endl;

    freeMatrix(graf, N);
    freeMatrix(short_dis, N);
    return 0;
}