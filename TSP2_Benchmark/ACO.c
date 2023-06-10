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

void print_graph(int N, double p[N*(N-1)/2], FILE *gif){
    int i,j;
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            if(i<j)
                fprintf(gif,"%d\t%d\t%lf\n",i,j,acc(p,i,j));
}

void clean_folder(){
    DIR *d;
    struct dirent *dir;
    d = opendir("ACO_gif/.");
    int flag=0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".") != 0){
                char name[20] = "ACO_gif/";
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

float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void antpath(int root, int N, struct node nodes[N], int *P, double p[N*(N-1)/2],float delta,float epsilon){
    int i, j;
    int i2, j2;
    for(i=0;i<N;i++){
        nodes[i].v = 0;
    }
    nodes[root].v = 1;
    P[0]=root;
    int current = root, next;
    double sum;
    int nvisited = 1;
    double desirability;
    while(nvisited<N){
        sum=1;
        for(i=0;i<N;i++){
            if (nodes[i].v==0){
                i2=current;
                j2=i;
                if(i2>j2){
                    j2=i2;
                    i2=i;
                }
                desirability=acc(p,i2,j2);//pow(acc(p,i2,j2),delta)*pow(d(nodes[current].x,nodes[current].y,nodes[i].x,nodes[i].y),epsilon);
                sum+=desirability;
            }
        }
        next=RandomFloat(0,sum);
        sum=1;
        for(i=0;i<N;i++){
            if (nodes[i].v==0){
                i2=current;
                j2=i;
                if(i2>j2){
                    j2=i2;
                    i2=i;
                }
                desirability=acc(p,i2,j2);//pow(acc(p,i2,j2),delta)*pow(d(nodes[current].x,nodes[current].y,nodes[i].x,nodes[i].y),epsilon);
                sum+=desirability;
                if(next<sum){
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
    int i;
    double D=0;
    for(i=1;i<N+1;i++)
        D = D + d(nodes[P[i]].x,nodes[P[i]].y,nodes[P[i-1]].x,nodes[P[i-1]].y);
    return D;
}

int * ACO(int N, struct node nodes[N], int *best, int itermax, int popsize, double gamma){ //best[N+1]
    time_t tinit = clock();
    int i, j, root;
    int i2, j2;
    double m;
    double e=0.05;
    float Q=1;
    // int popsize = 50;
    int n=N*(N-1)/2;
    double p[n];
    // double gamma=0.0453;
    float delta=1, epsilon=1;
    char name[20]; 
    char num[5];

    // Initialize pheromones and solution
    for(i=0;i<n;i++)
            p[i] = gamma;

    for(i=0;i<N+1;i++)
        best[i]=0;
    
    double F, error=__DBL_MAX__;
    int k=0;
    m=__DBL_MAX__;
    // m=5000;
    srand(time(0));
    int P[popsize][N+1];
    while(k<itermax){
        // printf("k = %d\n",k);
        // Get population based on pheromones
        for(i=0;i<popsize;i++){
            // root = rand()%N;
            root = 0;
            antpath(root,N,nodes,&P[i][0],p,delta,epsilon);
            F=Fitness(&P[i][0],N,nodes);

            // Save best individual
            if (m>F){
                // printf("%.0lf -> %.0lf\n",m, F);
                m = F;
                for(j=0;j<N+1;j++)
                    best[j]=P[i][j]; 
                k = 0; 
            }
        }
        // Evaporate pheromones
        for(i=0;i<n;i++){
                p[i]=(1-e)*p[i];
        }

        // Update pheromones based on the fitness

        for(i=0;i<popsize;i++){
            F=Q/Fitness(&P[i][0],N,nodes);
            for(j=1;j<N+1;j++){
                i2=P[i][j-1];
                j2=P[i][j];
                if(i2>j2){
                    j2=i2;
                    i2=P[i][j];
                }
                acc(p,i2,j2)=acc(p,i2,j2)+F;
            }
        }
        
    k++;
    }

    printf("ANT COLONY OPTIMIZATION\n----------------------------------------\n");
    printf("popsize = %d, gamma = %lf\n\n", popsize, gamma);
    for(i=0;i<N+1;i++)
        printf("%d\t",best[i]);
    printf("\n");

    printf("Total distance: %.2lf\n\n", Fitness(best,N,nodes));

    FILE *f;
    f = fopen("results/BMK_ACO.txt", "a");
    fprintf(f,"%2lf %2lf\n",Fitness(best,N,nodes),(double)(clock()-tinit)/CLOCKS_PER_SEC);
    fclose(f);

}

int main(int argc, char *argv[]){
    int itermax = 1000;
    int popsize = 140;
    double gamma = 1.9;
    int params = 0;

    if(argc>1) itermax = atoi(argv[1]);
    if(argc>2) popsize = atoi(argv[2]);
    if(argc>3) gamma = atof(argv[3]);
    if(argc>4) params = atoi(argv[4]);
    int N, i;

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

    ACO(N,nodes, v, itermax, popsize, gamma);

    if(params==1){
        FILE* param_results = fopen("ACO_param_results/ACO_params.txt", "a");
        fprintf(param_results, "%d %lf %lf\n", popsize, gamma, Fitness(v,N,nodes));
        fclose(param_results);
    }

    return 0;
}