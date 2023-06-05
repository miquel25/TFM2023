#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <dirent.h>

struct node {
    int x, y;
    int v; // 0 if not visited, 1 if visited
};

double d(int x1,int y1,int x2,int y2){
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

void print_graph(int *v, int N, FILE *gif){
    int i;
    for(i=0;i<N;i++)
        fprintf(gif,"%d\n",v[i]);
}

void clean_folder(){
    DIR *d;
    struct dirent *dir;
    d = opendir("NN_gif/.");
    int flag=0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".") != 0){
                char name[20] = "NN_gif/";
                strcat(name,dir->d_name); 
                if (remove(name) != 0) {
                    printf("The file is not deleted.\n");
                    exit;
                }
            }
        }
        closedir(d);
    }
}

int * nearest_neighbour(int root, int N, struct node nodes[N], int *v, char *argv[]){
    time_t tinit = clock();
    int i, j;
    double D=0;
    for(i=0;i<N;i++){
        nodes[i].v = 0;
    }
    nodes[root].v = 1;
    v[0]=root;
    int current = root, next;
    float m;

    char name[20]; 
    char num[5];

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
    D = D + d(nodes[next].x,nodes[next].y,nodes[root].x,nodes[root].y);
    v[N]=root;

    printf("NEAREST NEIGHBOUR\n----------------------------------------\n");
    for(i=0;i<N+1;i++)
        printf("%d\t",v[i]);
    printf("\n");

    printf("Total distance: %.2lf\n\n", D);

    FILE *f;
    f = fopen(argv[2], "w");

    fprintf(f,"%2lf %2lf\n",D,(double)(clock()-tinit)/CLOCKS_PER_SEC);
    
    fclose(f);
    return v;
}

int main(int argc,char *argv[]){
    int N, i;
    if(argc<3){
        printf("INTRODUCE GRAPH AND DESTINATION NAME\n");
        exit;
    }

    FILE *f;
    f = fopen(argv[1],"r");

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

    nearest_neighbour(0,N,nodes, v, argv);

    return 0;
}