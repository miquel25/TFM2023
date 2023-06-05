#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *arcv[]){
    char command[50];
    int error=0;
    int itermax = 10000;
    int popsize = 101;
    double gamma = 0.5;
    double result;
    
    error = system("gcc ACO.c -o ACO -lm");
    if(error!=0) exit(error);

    FILE* param_results = fopen("ACO_param_results/ACO_params.txt", "w");
    fprintf(param_results, "popsize gamma Fitness\n");
    fclose(param_results);

    for(popsize=10;popsize<200;popsize=popsize+10)
        for(gamma=0.1; gamma<5; gamma=gamma+0.2){
            sprintf(command, "./ACO %d %d %lf 1",itermax, popsize, gamma);
            error = error + system(command);
        }
    return error;
}