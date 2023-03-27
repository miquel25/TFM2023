#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <dirent.h>

// Essentials of Metaheuristics - Algorithm 110

struct node {
    int x, y;
    int v;
};

struct linked {
    int n;
    struct linked *next;
};

double d(int x1,int y1,int x2,int y2){
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

#define acc( arr, exp1, exp2 )	arr[ (exp1*(exp1-1))/2+exp2  ]

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

void antpath(int root, int N, struct node nodes[N], int *P, double p[N*(N-1)/2]){
    int i, j;
    for(i=0;i<N;i++){
        nodes[i].v = 0;
    }
    nodes[root].v = 1;
    P[0]=root;
    int current = root, next;
    float epsilon;
    int nvisited =1;
    while(nvisited<N){
        epsilon=0;
        for(i=0;i<N;i++){
            if (nodes[i].v==0)
                epsilon+=acc(p,current,i);
        }
        next=rand()%(int)epsilon;
        epsilon=0;
        for(i=0;i<N;i++){
            if (nodes[i].v==0){
                epsilon+=acc(p,current,i);
                if(next<epsilon){
                    next=i;
                    break;
                }
            }
        }
        P[nvisited]=next;
        nodes[next].v = 1;
        current = next;
        nvisited++;
    }
    P[N]=root;
}

double Fitness(int *P, int N, struct node nodes[N]){
    int i, D=0;
    for(i=1;i<N+1;i++)
        D = D + d(nodes[P[i]].x,nodes[P[i]].y,nodes[P[i-1]].x,nodes[P[i-1]].y);
    return D;
}

int * ACO(int N, struct node nodes[N], int *best){ //best[N+1]
    int i, j, root;
    double m;
    double e=0.4, gamma=1;
    int popsize = 100;
    int n=N*(N-1)/2;
    double p[n];

    // Initialize pheromones and solution
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            acc(p,i,j) = gamma;

    for(i=0;i<N+1;i++)
        best[i]=0;
    
    double F, error=__DBL_MAX__;
    int k=0;
    // m=__DBL_MAX__;
    m=5000;
    srand(time(0));
    int P[popsize][N+1];
    while(k<1000){
        // Get population based on pheromones
        for(i=0;i<popsize;i++){

            root = rand()%N;

            antpath(root,N,nodes,&P[i][0],p);
            F=Fitness(&P[i][0],N,nodes);

            // Save best individual
            if (m>F){
                printf("%.0lf -> %.0lf\n",m, F);
                m = F;
                for(j=0;j<N+1;j++)
                    best[j]=P[i][j];  
                for(i=0;i<N+1;i++)
                    printf("%d\t",best[i]);
                printf("\n");      
            }
        }
        // Evaporate pheromones
        // for(i=0;i<N;i++){
        //     for(j=0;j<N;j++){
        //         acc(p,i,j)=(1-e)*acc(p,i,j);
        //     }
        // }

        // Update pheromones based on the fitness

        for(i=0;i<popsize;i++){
            F=1/Fitness(&P[i][0],N,nodes);
            for(j=1;j<N+1;j++){
                acc(p,1,3)=acc(p,1,3);
                // acc(p,P[i][j-1],P[i][j])=acc(p,P[i][j-1],P[i][j]);
            }
        }
    
    // printf("%2lf, %2lf\n",Fitness(best,N,nodes), m);
    k++;
    }

    printf("ANT COLONY OPTIMIZATION\n----------------------------------------\n");
    for(i=0;i<N+1;i++)
        printf("%d\t",best[i]);
    printf("\n");

    printf("Total distance: %.2lf\n\n", Fitness(best,N,nodes));

    FILE *f;
    f = fopen("results/TSP_ACO.txt", "w");

    for(i=0;i<N+1;i++)
        fprintf(f,"%d\n",best[i]);
    
    fclose(f);

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

    ACO(N,nodes, v);

    return 0;
}