#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <dirent.h>

// Essentials of Metaheuristics - Algorithm 109

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

void print_graph(struct linked *first, FILE *f){
    struct linked *iter;
    iter = first;
    while(iter!=NULL){
        fprintf(f,"%d\n",iter->n);
        iter = iter->next;
    }
}

void clean_folder(){
    DIR *d;
    struct dirent *dir;
    d = opendir("NI_gif/.");
    int flag=0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".") != 0){
                char name[20] = "NI_gif/";
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

int * ACO(int root, int N, struct node nodes[N], int *v){

}

int main(){
    int N, i;
 
    clean_folder();

    FILE *f;
    f = fopen("results/random_graph.txt","r");

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