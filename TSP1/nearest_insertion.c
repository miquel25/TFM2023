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

int * nearest_insertion(int root, int N, struct node nodes[N]){
    int i, j;
    double D=0;
    for(i=0;i<N;i++){
        nodes[i].v = 0;
    }
    nodes[root].v = 1;

    struct linked *first;
    struct linked *last;
    struct linked *temp;
    struct linked *iter;

    first = (struct linked *) malloc(sizeof(struct linked));
    last = (struct linked *) malloc(sizeof(struct linked));
    temp = (struct linked *) malloc(sizeof(struct linked)); 

    if(first==NULL || last==NULL){
        printf("Error when allocating memory for the linked lists\n");
        exit;
    }

//  FIND CLOSEST NODE TO ROOT

    double m = __DBL_MAX__;
    int r;
    for(i=0;i<N;i++){
        if (nodes[i].v==0)
            if (m>d(nodes[root].x,nodes[root].y,nodes[i].x,nodes[i].y)){
                m = d(nodes[root].x,nodes[root].y,nodes[i].x,nodes[i].y);
                r = i;
            }
    }
    
    D=m;
    nodes[r].v = 1;

    // CONSTRUCT SUB-TOUR root-next-root

    first->n = root;
    temp->n = r;
    last->n = root;
    first->next = temp;
    temp->next = last;
    last->next = NULL;

    FILE *gif = fopen("NI_gif/1.txt", "w");
    print_graph(first, gif);
    fclose(gif);

    char name[20]; 
    char num[5];
    for(j=2;j<N;j++){

        //  FIND NODE CLOSEST TO ANY ELEMENT OF SUB-TOUR

        m = __DBL_MAX__;
        for(i=0;i<N;i++){
            if(nodes[i].v==0){
                iter = first;
                while(iter!=NULL){
                    if (m>d(nodes[i].x,nodes[i].y,nodes[iter->n].x,nodes[iter->n].y)){
                        m = d(nodes[i].x,nodes[i].y,nodes[iter->n].x,nodes[iter->n].y);
                        r = i;
                    }
                    iter = iter->next;
                }
            }
        }

        

        nodes[r].v = 1;

        // FIND THE MINIMAL ARC

        iter = first;
        struct linked *iter2;
        iter2 = first->next;
        double c;
        int current;
        m = __DBL_MAX__;
        while(iter2!=NULL){
            c = d(nodes[iter->n].x,nodes[iter->n].y,nodes[r].x,nodes[r].y) + d(nodes[r].x,nodes[r].y,nodes[iter2->n].x,nodes[iter2->n].y) - d(nodes[iter->n].x,nodes[iter->n].y,nodes[iter2->n].x,nodes[iter2->n].y);
            if (m>c){
                m = c;
                current = iter->n;
            }
            iter=iter->next;
            iter2=iter2->next;
        }
        D = D + m;

        // INSERT NEW NODE

        iter = first;
        while(iter->n!=current){
            iter = iter->next;
        }
        
        temp = (struct linked *) malloc(sizeof(struct linked));
        if(temp==NULL){
            printf("Error when allocating memory for the linked lists\n");
            exit;
        }

        temp->n = r;
        temp->next = iter->next;
        iter->next = temp;

        char name[] = "NI_gif/";
        sprintf(num, "%d", j);
        strcat(name, num);
        strcat(name,".txt");
        FILE *gif = fopen(name, "w");
        print_graph(first, gif);
        fclose(gif);
    }

    FILE *f;
    f = fopen("results/TSP_NI.txt", "w");
    printf("NEAREST INSERTION\n----------------------------------------\n");

    iter = first;
    while(iter!=NULL){
        fprintf(f,"%d\n",iter->n);
        printf("%d\t",iter->n);
        iter = iter->next;
    }
    printf("\n");
    fclose(f);

    printf("Total distance: %.lf\n\n", D);
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

    nearest_insertion(0,N,nodes);

    return 0;
}