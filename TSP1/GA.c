#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <dirent.h>

// Essentials of Metaheuristics - Algorithm 20

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
    d = opendir("GA_gif/.");
    int flag=0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".") != 0){
                char name[20] = "GA_gif/";
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

void crossover(int root, int N, struct node nodes[N], int *P, double p[N*(N-1)/2],float delta,float epsilon){
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
                desirability=pow(acc(p,i2,j2),delta)*pow(d(nodes[current].x,nodes[current].y,nodes[i].x,nodes[i].y),epsilon);
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
                desirability=pow(acc(p,i2,j2),delta)*pow(d(nodes[current].x,nodes[current].y,nodes[i].x,nodes[i].y),epsilon);
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
    int i, D=0;
    for(i=1;i<N+1;i++)
        D = D + d(nodes[P[i]].x,nodes[P[i]].y,nodes[P[i-1]].x,nodes[P[i-1]].y);
    return D;
}

int SelectWithReplacement(int N, int (*)P[N+1], int popsize, struct node nodes[N]){
    int i;
    int next;
    float sum=0;
    for(i=0;i<popsize;i++){
            sum=sum+Fitness(P[i], N, nodes);
    }
    next = RandomFloat(0, sum);
    sum=0;
    for(i=0;i<popsize;i++){
        sum=sum+Fitness(P[i], N, nodes);
            if(sum>=next){
                next=i;
                break;
            }
        }
    printf("%d\n",next);
    return next;
}

int * GA(int root, int N, struct node nodes[N], int *best){ //best[N+1]
    int i, j;
    int i2, j2;
    int popsize = 20;
    double m;
    char name[20]; 
    char num[5];

    for(i=0;i<N+1;i++)
        best[i]=0;
    
    double F, error=__DBL_MAX__;
    int k=0;
    // m=__DBL_MAX__;
    m=5000;
    srand(time(0));
    int P[popsize][N+1];
    
    // Initialize population
    int sum, next;
    for(i=0;i<popsize;i++){
        P[i][0]=root;
        P[i][N]=root;
        for(j=0;j<N;j++){
            nodes[j].v = 0;
        }
        nodes[root].v = 1;
        for(i2=1;i2<N;i2++){
            sum=0;
            for(j=0;j<N;j++){
                if(nodes[j].v==0)
                    sum++;
            }
            sum++;
            next = rand()%sum;
            sum=0;
            for(j=0;j<N;j++){
                if(nodes[j].v==0){
                    sum++;
                    if(sum>=next){
                        next=j;
                        break;
                    }
                }
            }
            P[i][i2]=next;
            nodes[next].v=1;
        }
    }

    while(k<2){
        // Save best individual
        for(i=0;i<popsize;i++){
            F=Fitness(P[i],N,nodes);
            if (m>F){
                printf("%.0lf -> %.0lf\n",m, F);
                m = F;
                for(j=0;j<N+1;j++)
                    best[j]=P[i][j];  
            }
        }
        int Q[popsize][N+1];
        SelectWithReplacement(N, P, popsize, nodes);

    // char name[] = "GA_gif/";
    // sprintf(num, "%d", k);
    // strcat(name, num);
    // strcat(name,".txt");
    // FILE *gif = fopen(name, "w");
    // print_graph(N, p, gif);
    // fclose(gif);
    k++;
    }

    printf("GENETIC ALGORITHM\n----------------------------------------\n");
    for(i=0;i<N+1;i++)
        printf("%d\t",best[i]);
    printf("\n");

    printf("Total distance: %.2lf\n\n", Fitness(best,N,nodes));

    FILE *f;
    f = fopen("results/TSP_GA.txt", "w");

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

    GA(0,N,nodes, v);

    return 0;
}