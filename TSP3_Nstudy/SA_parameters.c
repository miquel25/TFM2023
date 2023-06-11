#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <dirent.h>
#include <unistd.h>

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

void Fitness(double *Fit, char *argv[]){
    double t;
    FILE *fFit;
    fFit = fopen(argv[3], "r");
    fscanf(fFit,"%lf %lf",Fit,&t);
    fclose(fFit);
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

void Tweak(int S1, float S2, int *R1, float *R2){
    *R1 = S1 + RandomInt(0,1000)*pow(-1,RandomInt(1,2));
    *R2 = S2 + RandomFloat(-0.05,0.05);
    if (*R1<1000) *R1 = 1000;
    if (*R2<=0) *R2 = 0.001;
    if (*R2>1) *R2 = 0.999;
}


double CoolDown(double T, int k, int itermax, double Tmax, int phase, float rate){
    if (phase==0)
        T = 1.01*T;
    if (phase==1){
        T = T - Tmax/2;
        T = rate*T+Tmax/2;
    }
    if (phase==2){
        T = T - Tmax/10;
        T = rate*T+Tmax/10;
    }
    if (phase==3)
        T = rate*T;
    return T;
}

void run_code(int param1, float param2, char *argv[]){
    char command[150];
    int error;

    FILE *fFit;
    fFit = fopen(argv[3], "w");
    fclose(fFit);

    sprintf(command, "./%s %s %s %d %f",argv[1],argv[2],argv[3],param1,param2);
    printf("%s\n",command);
    error = system(command);
}

int * SA(int root, int N, int param1, float param2, int itermax, float rate, char *argv[]){
    time_t tinit = clock();
    int i, j;
    int i2, j2;
    int k=0, k2=0;
    char name[20]; 
    char num[5];
    double m=__DBL_MAX__;

    srand(time(0));


    int S1, R1, best1;
    float S2, R2, best2;
    double dE;
    double random;
    double Tmax=1;
    double T=Tmax;
    int phase = 0;
    float accepted = 0;
    float total = 0;
    float accrate = 1;
    float Rate1 = 0.8;

    double FitS, FitR;

    S1 = param1;
    S2 = param2;

    printf("pre run\n");
    run_code(S1,S2,argv);
    printf("pre fitness\n");
    printf("\n%s\n",argv[3]);
    Fitness(&FitS,argv);
    printf("FitS: %lf\n",FitS);

    best1 = S1;
    best2 = S2;
    m = FitS;
 
    int iter=1;
    while(k<itermax){
        total++;
     
        Tweak(S1,S2,&R1,&R2);
        run_code(R1,R2, argv);
        Fitness(&FitR,argv);
        dE = FitS-FitR;
        if(dE > 0){
            accepted++;
            S1 = R1;
            S2 = R2;
        }
        if(dE < 0){
            random = RandomFloat(0,1);
            if (random < exp(dE/T)){
                accepted++;
                S1 = R1;
                S2 = R2;
            }
        }

        if(FitS < m){
            m = FitS;
            best1 = S1;
            best2 = S2;
        }

        T = CoolDown(T,k,itermax,Tmax,phase, rate);

        k2++;
        printf("k = %d\n",k);
        k++;

        accrate = accepted/total;
        printf("acc = %lf\n",accrate);

        if(k2>500){
            accepted = 0;
            total = 0;
            k2=0;
        }


        if(accrate>Rate1 && phase == 0 && k2>100){
            total = 0;
            accepted = 0;
            phase=1;
            Tmax = T;
            k = 0;
            k2 = 0;
            // printf("Phase 1\n");
        }

        if (phase==1 && k > itermax/2){
            phase=2;
            k = 0;
            // printf("Phase 2\n");
        }

        if (phase==2 && k > itermax/2){
            phase=3;
            k = 0;
            // printf("Phase 3\n");
        }

    }


    printf("PARAMETERS\n----------------------------------------\n");
    printf("%d\t%f\n",best1,best2);
    
    printf("Total distance: %.2lf\n\n", m);

    FILE *f;
    f = fopen(argv[3], "w");
    fprintf(f,"%d %f\n",best1,best2);
    fclose(f);

}

int main(int argc, char *argv[]){
    if(argc<5){
        printf("INTRODUCE ALGORITHM, GRAPH NAME, DESTINATION NAME, PARAMETER1 AND PARAMETER2\n");
        exit(-1);
    }
    int itermax = 1000;
    float rate = 0.99; 
    int param1 = 1;  
    float param2 = 2; 
    if(argc>4) param1 = atoi(argv[4]);
    if(argc>5) param2 = atof(argv[5]);
    int N, i;


    FILE *f;
    f = fopen(argv[2],"r");

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


    SA(0,N, param1, param2, itermax, rate, argv);

    return 0;
}