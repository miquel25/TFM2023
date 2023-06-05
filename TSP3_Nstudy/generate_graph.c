#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>


float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void generate_points(int *x, int *y, double d, int N){
    srand(time(0));
    int i;
    x[0]=0.0;
    y[0]=0.0;
    float phi;
    for(i=1;i<N;i++){
        phi = RandomFloat(0,2*M_PI);
        x[i]=i*d*sin(phi);
        y[i]=i*d*cos(phi);
        // printf("(%d,%d)\n",x[i],y[i]);
    }
}


int main(int argc, char *argv[]){
    int N = 10;
    double d = 10;
    if(argc>1) N = atoi(argv[1]);
    if(argc>2) d = atof(argv[2]);
    int *x, *y;
    int i;
    x = (int *) malloc(N*sizeof(int));
    y = (int *) malloc(N*sizeof(int));

    if(x==NULL || y==NULL){
        printf("Error when allocating memory for the points\n");
        return 1;
    }

    generate_points(x,y,d,N);

    FILE *f;
    char name[150];
    snprintf(name,150,"graph/random_graph_%d-%.lf.txt",N,d);

    f = fopen(name,"w");
    fprintf(f,"%d\n",N);
    for(i=0;i<N;i++)
        fprintf(f,"%d\t%d\n",x[i],y[i]);
    
    fclose(f);
    return 0;
}