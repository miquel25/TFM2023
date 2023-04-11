#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

void generate_points(int *x, int *y, int N){
    srand(time(0));
    int i;
    for(i=0;i<N;i++){
        x[i]=rand()%100;
        y[i]=rand()%100;
        // printf("(%d,%d)\n",x[i],y[i]);
    }
}


int main(int argc, char *argv[]){
    int N = 10;
    if(argc>1) N = atoi(argv[1]);
    int *x, *y;
    int i;
    x = (int *) malloc(N*sizeof(int));
    y = (int *) malloc(N*sizeof(int));

    if(x==NULL || y==NULL){
        printf("Error when allocating memory for the points\n");
        return 1;
    }

    generate_points(x,y,N);

    FILE *f;
    f = fopen("results/random_graph.txt","w");
    fprintf(f,"%d\n",N);
    for(i=0;i<N;i++)
        fprintf(f,"%d\t%d\n",x[i],y[i]);
    
    fclose(f);
    return 0;
}