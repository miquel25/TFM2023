#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define N 5

void generate_points(int *x, int *y){
    srand(time(0));
    int i;
    for(i=0;i<N;i++){
        x[i]=rand()%100;
        y[i]=rand()%100;
        // printf("(%d,%d)\n",x[i],y[i]);
    }
}

double d(int x1,int y1,int x2,int y2){
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

int main(){
    int *x, *y;
    x = (int *) malloc(N*sizeof(int));
    y = (int *) malloc(N*sizeof(int));

    if(x==NULL || y==NULL){
        printf("Error when allocating memory for the points\n");
        return 1;
    }

    generate_points(x,y);





    return 0;
}