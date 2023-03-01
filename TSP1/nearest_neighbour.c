#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

struct node {
    int x, y;
    int v; // 0 if not visited, 1 if visited
};

double d(int x1,int y1,int x2,int y2){
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

int * nearest_neighbour(int root, int N, struct node nodes[N], int *v){
    int i, j;
    double D=0;
    for(i=0;i<N;i++){
        nodes[i].v = 0;
    }
    nodes[root].v = 1;
    v[0]=root;
    int current = root, next;
    float m;
    for(j=1;j<N;j++){
        m = __DBL_MAX__;
        for(i=0;i<N;i++){
            if (nodes[i].v==0)
                if (m>d(nodes[current].x,nodes[current].y,nodes[i].x,nodes[i].y)){
                    m = d(nodes[current].x,nodes[current].y,nodes[i].x,nodes[i].y);
                    next = i;
                }
        }
        D = D + m;
        v[j]=next;
        nodes[next].v = 1;
        current = next;
    }
    D = D + d(nodes[N-1].x,nodes[N-1].y,nodes[root].x,nodes[root].y);
    v[N]=root;

    for(i=0;i<N+1;i++)
        printf("%d\t",v[i]);
    printf("\n");

    printf("Total distance: %.2lf\n", D);

    FILE *f;
    f = fopen("TSP_NN.txt", "w");

    for(i=0;i<N+1;i++)
        fprintf(f,"%d\n",v[i]);
    
    fclose(f);
    return v;
}

int main(){
    int N, i;
 
    FILE *f;
    f = fopen("random_graph.txt","r");

    fscanf(f,"%d",&N);
    struct node nodes[N];
    
    if(nodes==NULL){
        printf("Error when allocating memory for the graph\n");
        exit;
    }

    for(i=0;i<N;i++){
        fscanf(f,"%d\t%d",&nodes[i].x,&nodes[i].y);
    }

    fclose(f);

    int *v;
    v = (int *) malloc ((N+1)*sizeof(int));
    if (v == NULL){
        printf("Error when allocating memory for the path\n");
        exit;
    }

    nearest_neighbour(0,N,nodes, v);

    return 0;
}