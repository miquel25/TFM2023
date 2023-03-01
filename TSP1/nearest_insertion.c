#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

struct node {
    int x, y;
    int v; // 0 if not visited, 1 if visited
};

struct linked {
    int n;
    struct linked *next;
};

double d(int x1,int y1,int x2,int y2){
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}



int * nearest_insertion(int root, int N, struct node nodes[N], int *v){
    int i, j;
    double D=0;
    for(i=0;i<N;i++){
        nodes[i].v = 0;
    }
    nodes[root].v = 1;

    struct linked *first = (struct linked *) malloc(sizeof(struct linked));
    struct linked *last = (struct linked *) malloc(sizeof(struct linked));
    struct linked *temp = (struct linked *) malloc(sizeof(struct linked));
    struct linked *iter;

    if(first==NULL || last==NULL){
        printf("Error when allocating memory for the linked lists\n");
        exit;
    }

//  FIND CLOSEST NODE TO ROOT

    double m = __DBL_MAX__;
    int next;
    for(i=0;i<N;i++){
        if (nodes[i].v==0)
            if (m>d(nodes[root].x,nodes[root].y,nodes[i].x,nodes[i].y)){
                m = d(nodes[root].x,nodes[root].y,nodes[i].x,nodes[i].y);
                next = i;
            }
    }

    nodes[next].v = 1;

    // CONSTRUCT SUB-TOUR root-next-root

    first->n = root;
    temp->n = next;
    last->n = root;
    first->next = temp;
    temp->next = last;
    last->next = NULL;

// això va dins d'un altre loop

    //  FIND NODE CLOSEST TO ANY ELEMENT OF SUB-TOUR

    int current;
    m = __DBL_MAX__;
    for(i=0;i<N;i++){
        if(nodes[i].v!=0){
            iter = first;
            while(iter!=NULL){
                if (m<d(nodes[i].x,nodes[i].y,nodes[iter->n].x,nodes[iter->n].y)){
                    m = d(nodes[i].x,nodes[i].y,nodes[iter->n].x,nodes[iter->n].y);
                    current = iter->n;
                    next = i;
                }
            iter = iter->next;
            }
        }
    }


    D = D + d(nodes[N-1].x,nodes[N-1].y,nodes[root].x,nodes[root].y);
    v[N]=root;

    for(i=0;i<N+1;i++)
        printf("%d\t",v[i]);
    printf("\n");

    printf("Total distance: %.lf\n", D);

    FILE *f;
    f = fopen("TSP_NI.txt", "w");

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

    nearest_insertion(0,N,nodes, v);

    return 0;
}