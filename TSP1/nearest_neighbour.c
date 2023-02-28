#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

struct node {
    int x, y;
    int v; // 0 if not visited, 1 if visited
};

// double d(int x1,int y1,int x2,int y2){
//     return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
// }

int main(){
    int N, i;
 
    FILE *f;
    f = fopen("random_graph.txt","r");

    fscanf(f,"%d",&N);
    struct node nodes[N];
    
    if(nodes==NULL){
        printf("Error when allocating memory for the points\n");
        exit;
    }

    for(i=0;i<N;i++){
        fscanf(f,"%d\t%d",&nodes[i].x,&nodes[i].y);
    }

    fclose(f);

    printf("%d\n",N);
    printf("(%d,%d)\n",nodes[N-1].x,nodes[N-1].y);
    nodes[N-1].y = 3;
    printf("(%d,%d)\n",nodes[N-1].x,nodes[N-1].y);
 
    return 0;
}