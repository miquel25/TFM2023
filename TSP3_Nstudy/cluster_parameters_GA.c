#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    char command[150];
    int error=0;
    int param1 = 10;
    int param1init = 10;
    int param1end = 100;
    int param1step = 10;
    double param2 = 0.1;
    double param2init = 0.1;
    double param2end = 0.9;
    double param2step = 0.1;
    double result;
   
    error = system("gcc GA.c -o GA -lm");
    if(error!=0) exit(error);

    char name[150];
    sprintf(name,"parameters/GA.txt");
    FILE* param_results = fopen(name, "w");
    fprintf(param_results, "param1 param2 Fitness\n");
    fclose(param_results);

    for(param1=param1init;param1<param1end;param1=param1+param1step)
        for(param2=param2init; param2<param2end; param2=param2+param2step){
            sprintf(command, "./GA %s %s 100 %d %lf 1", argv[1], argv[2],param1,param2);
            error = error + system(command);
        }

    int N = -1, i;
    param_results = fopen(name,"r");
    for(i=getc(param_results); i!= EOF; i=getc(param_results))
        if (i=='\n')
            N = N + 1;
    fclose(param_results);

    int resparam1[N];
    double resparam2[N];
    double Fitness[N];
    int index;
    double best=__DBL_MAX__;

    
    
    param_results = fopen(name,"r");
    fscanf(param_results,"%*[^\n]\n");
    for(i=0;i<N;i++){
        fscanf(param_results,"%d %lf %lf",&resparam1[i],&resparam2[i], &Fitness[i]);
        if(Fitness[i]<best){
            index=i;
            best=Fitness[i];
        }
    }
    fclose(param_results);
    

    sprintf(name,"parameters/GA-best.txt");
    param_results = fopen(name,"w");
    fprintf(param_results,"%d\n%lf\n",resparam1[index],resparam2[index]);
    fclose(param_results);
    return error;
}