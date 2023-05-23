#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <dirent.h>

// Essentials of Metaheuristics - Algorithm 13

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

void print_graph(int N, int best[N+1], FILE *gif){
    int i;
    for(i=0;i<N+1;i++)
        fprintf(gif,"%d\n",best[i]);
}

void clean_folder(){
    DIR *d;
    struct dirent *dir;
    d = opendir("SA_gif/.");
    int flag=0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".") != 0){
                char name[20] = "SA_gif/";
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

float RandomInt(int a, int b) {
    int random = (rand()%(b-a+1))+a;
    return random;
}

double Fitness(int *P, int N, struct node nodes[N]){
    int i;
    double D=0;
    for(i=1;i<N+1;i++)
        D = D + d(nodes[P[i]].x,nodes[P[i]].y,nodes[P[i-1]].x,nodes[P[i-1]].y);
    return D;
}

void RandomPath(int *P, int root, int N, struct node nodes[N]){
    int i, j, sum, next;
    P[0]=root;
    P[N]=root;
    for(i=0;i<N;i++){
        nodes[i].v = 0;
    }
    nodes[root].v = 1;

    for(i=1;i<N;i++){
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
        P[i]=next;
        nodes[next].v=1;
    }
}

void Tweak(int *S, int *R, int root, int N){
    int i, a, b;
    for(i=0;i<N+1;i++)
        R[i]=S[i];
    a = RandomInt(1,N-1);
    b = RandomInt(1,N-1);
    R[a]=S[b];
    R[b]=S[a];

}


double CoolDown(double T, int k, int itermax, double Tmax, int phase){
    if (phase==0)
        T = 1.01*T;
    if (phase==1){
        T = T - Tmax/2;
        T = 0.99*T+Tmax/2;
    }
    if (phase==2){
        T = T - Tmax/10;
        T = 0.99*T+Tmax/10;
    }
    if (phase==3)
        T = 0.99*T;
    return T;
}

int * SA(int root, int N, struct node nodes[N], int *best, int itermax){
    int i, j;
    int i2, j2;
    int k=0, k2=0;
    char name[20]; 
    char num[5];
    double m=__DBL_MAX__;
    m=5000;

    srand(time(0));

    FILE *lvst = fopen("SAlvst.txt","w");
    FILE *mvst = fopen("SAmvst.txt","w");

    int *S, *R, *aux;
    double dE;
    double random;
    double Tmax=1;
    double T=Tmax;
    int phase = 0;
    float accepted = 0;
    float total = 0;
    float accrate = 1;
    float R1 = 0.8;
    float R2 = 0.1;

    S = (int *) malloc((N+1)*sizeof(int));
    if(S==NULL){
        printf("Error when allocating memmory\n");
        exit;
    }
    
    RandomPath(S,root, N, nodes);
    best = S;
 
    int iter=1;
    while(k<itermax){
        R = (int *) malloc((N+1)*sizeof(int));
        total++;
        if(S==NULL){
            printf("Error when allocating memmory\n");
            exit;
        } 
     
        Tweak(S,R,root,N);
        dE = Fitness(S,N,nodes)-Fitness(R,N,nodes);
        if(dE > 0){
            accepted++;
            aux = S;
            S = R;
            R = aux;
            free(R);
        }
        if(dE < 0){
            random = RandomFloat(0,1);
            if (random < exp(dE/T)){
                accepted++;
                aux = S;
                S = R;
                R = aux;
                free(R);
            }
        }

        if(Fitness(S,N,nodes) < m){
            m = Fitness(S,N,nodes);
            for(i=0;i<N+1;i++)
                best[i] = S[i];
        }

        T = CoolDown(T,k,itermax,Tmax,phase);

        // if(k%(itermax/100+1)==0){
        //     char name[] = "SA_gif/";
        //     sprintf(num, "%d", iter);
        //     strcat(name, num);
        //     strcat(name,".txt");
        //     FILE *gif = fopen(name, "w");
        //     print_graph(N, best, gif);
        //     fclose(gif);
        //     iter++;
        // }
        k2++;
        k++;

        accrate = accepted/total;
        
        if(k2>500){
            accepted = 0;
            total = 0;
            k2=0;
        }


        if(accrate>R1 && phase == 0 && k2>200){
            total = 0;
            accepted = 0;
            phase=1;
            Tmax = T;
            k = 0;
            k2 = 0;
            printf("Phase 1\n");
        }

        if (phase==1 && k > itermax/2){
            phase=2;
            k = 0;
            printf("Phase 2\n");
        }

        if (phase==2 && k > itermax/2){
            phase=3;
            k = 0;
            printf("Phase 3\n");
        }

        fprintf(lvst,"%lf\n",Fitness(S,N,nodes));
        // fprintf(mvst,"%lf\n",m);
        fprintf(mvst,"%lf\n",T);
        // fprintf(mvst,"%lf\n",accrate);
    }
    fclose(lvst);

    printf("SIMULATED ANNEALING\n----------------------------------------\n");
    for(i=0;i<N+1;i++)
        printf("%d\t",best[i]);
    printf("\n");

    printf("Total distance: %.2lf\n\n", Fitness(best,N,nodes));
    printf("%d %d \n", k, k2);

    FILE *f;
    f = fopen("results/TSP_SA.txt", "w");

    for(i=0;i<N+1;i++)
        fprintf(f,"%d\n",best[i]);
    
    fclose(f);

}

int main(int argc, char *argv[]){
    int itermax = 5000;
    if(argc>1) itermax = atoi(argv[1]);
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

    SA(0,N,nodes, v, itermax);

    return 0;
}