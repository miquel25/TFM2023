#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>


int main(){
    int *x, *y;
    int N, i;
    FILE *f;
    f = fopen("random_graph.txt","r");

    fscanf(f,"%d",&N);
    printf("N = %d\n",N);
    x = (int *) malloc(N*sizeof(int));
    y = (int *) malloc(N*sizeof(int));

    if(x==NULL || y==NULL){
        printf("Error when allocating memory for the points\n");
        return 1;
    }

    for(i=0;i<N;i++){
        fscanf(f,"%d\t%d",&x[i],&y[i]);
        printf("(%d,%d)\n",x[i],y[i]);    
    }

    fclose(f);
    return 0;
}