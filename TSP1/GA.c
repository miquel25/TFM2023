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

void print_graph(int N, int best[N+1], FILE *gif){
    int i;
    for(i=0;i<N+1;i++)
        fprintf(gif,"%d\n",best[i]);
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

float RandomInt(int a, int b) {
    int random = (rand()%(b-a+1))+a;
    return random;
}

void Crossover(int N, struct node nodes[N], int *P, int *Q, int a, int b, int index){
    int i, j;
    int p1, p2;
    p1 = RandomInt(1,N-1);
    p2 = RandomInt(p1,N);
    struct linked *first1 = malloc(sizeof(struct linked));
    struct linked *last1;
    struct linked *first2 = malloc(sizeof(struct linked));
    struct linked *last2;

    first1->n = -1;
    first1->next = NULL;
    last1 = first1;
    first2->n = -1;
    first2->next = NULL;
    last2 = first2;
    for(i=p1;i<=p2;i++){
        Q[2*index*(N+1)+i]=P[a*(N+1)+i];
        Q[(2*index+1)*(N+1)+i]=P[b*(N+1)+i];
    }

    int flag1=0, flag2=0;
    for(i=1;i<N;i++){
        flag1=0;
        flag2=0;
        for(j=p1;j<=p2;j++){
            if(Q[2*index*(N+1)+j]==P[b*(N+1)+i]){
                flag1=1;
            }
            if(Q[(2*index+1)*(N+1)+j]==P[a*(N+1)+i]){
                flag2=1;
            }
        }
        if(flag1==0){
            struct linked *add = malloc(sizeof(struct linked));
            add->n = P[b*(N+1)+i];
            add->next = NULL;
            last1->next = add;
            last1=add;
        }
        if(flag2==0){
            struct linked *add = malloc(sizeof(struct linked));
            add->n = P[a*(N+1)+i];
            add->next = NULL;
            last2->next = add;
            last2=add;
        }
    }

    Q[2*index*(N+1)]=0;
    Q[2*index*(N+1)+N]=0;
    Q[(2*index+1)*(N+1)]=0;
    Q[(2*index+1)*(N+1)+N]=0;
    struct linked *iter1;
    iter1 = first1->next;
    struct linked *iter2;
    iter2 = first2->next;
    for(i=1;i<p1;i++){
        Q[2*index*(N+1)+i]=iter1->n;
        Q[(2*index+1)*(N+1)+i]=iter2->n;
        iter1=iter1->next;
        iter2=iter2->next;
    }
    for(i=p2+1;i<N;i++){
        Q[2*index*(N+1)+i]=iter1->n;
        Q[(2*index+1)*(N+1)+i]=iter2->n;
        iter1=iter1->next;
        iter2=iter2->next;
    }
}

double Fitness(int *P, int N, struct node nodes[N]){
    int i;
    double D=0;
    for(i=1;i<N+1;i++)
        D = D + d(nodes[P[i]].x,nodes[P[i]].y,nodes[P[i-1]].x,nodes[P[i-1]].y);
    return D;
}

int TournamentSelection(int N, int popsize, int *P, struct node nodes[N], int t){
    int i;
    int best;
    int next;
    double m;
    best = RandomInt(0, popsize-1);
    m = Fitness(&P[best*(N+1)], N, nodes);
    for(i=2;i<t;i++){
        next = RandomInt(0,popsize-1);
        if(m>Fitness(&P[next*(N+1)], N, nodes)){
            m = Fitness(&P[next*(N+1)], N, nodes);
            best = next;
        }
    }
    return best;
}

void Mutation(int N, struct node nodes[N], int* Q, float MR, int index){
    int i;
    double p;
    int p1, p2, aux;
    for (i=0;i<2;i++){
        p = RandomFloat(0,1);
        if(p<=MR){
            p1 = RandomInt(1,N-1);
            p2 = RandomInt(1,N-1);
            aux=Q[(2*index+i)*(N+1)+p1];
            Q[(2*index+i)*(N+1)+p1]=Q[(2*index+i)*(N+1)+p2];
            Q[(2*index+i)*(N+1)+p2]=aux;
        }
    }
}

int * GA(int root, int N, struct node nodes[N], int *best){ //best[N+1]
    int i, j;
    int i2, j2;
    int popsize = 20;
    double m;
    char name[20]; 
    char num[5];
    int itermax = 10000;

    int t = 5; // Tournament size
    float MR = 0.3; // Mutation rate

    for(i=0;i<N+1;i++)
        best[i]=0;
    
    double F, error=__DBL_MAX__;
    int k=0;
    // m=__DBL_MAX__;
    m=5000;
    srand(time(0));
    int *P = malloc(popsize*(N+1)*sizeof(int));
    int *Q = malloc(popsize*(N+1)*sizeof(int));

    // Initialize population
    int sum, next;
    for(i=0;i<popsize;i++){
        P[i*(N+1)]=root;
        P[i*(N+1)+N]=root;
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
            P[i*(N+1)+i2]=next;
            nodes[next].v=1;
        }
    }

    int iter=1;
    while(k<itermax){
        // Save best individual
        for(i=0;i<popsize;i++){
            F=Fitness(&P[i*(N+1)],N,nodes);
            if (m>F){
                // printf("%.0lf -> %.0lf\n",m, F);
                m = F;
                for(j=0;j<N+1;j++)
                    best[j]=P[i*(N+1)+j];  
            }
        }
        // Select Parents

        int a, b;
        for(i=0;i<popsize/2;i++){
            a = TournamentSelection(N, popsize, P, nodes, t);
            b = TournamentSelection(N, popsize, P, nodes, t);
            Crossover(N, nodes, P, Q, a, b, i);
            Mutation(N, nodes, Q, MR, i);
        }

        int *temp = P;
        P = Q;
        Q = temp;

        
        if(k%(itermax/100+1)==0){
            char name[] = "GA_gif/";
            sprintf(num, "%d", iter);
            strcat(name, num);
            strcat(name,".txt");
            FILE *gif = fopen(name, "w");
            print_graph(N, best, gif);
            fclose(gif);
            iter++;
        }
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