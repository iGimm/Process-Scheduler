/*
*
* By->
* Giovanni Israel Mondragón Medina
*/

#include <stdio.h>
#include <stdlib.h>

#define PROCESOS 50

typedef struct process{
	int ID;
	int tiempo_total;
	int pt;
	int rt;
	int burst;
	int prior;
	int temp_burst;
	float tiempo_llegada;
	float tiempo_espera;
	float tiempo_termino;
	float tiempo_inicio;
	
}process;

void Fcfs (struct process[PROCESOS], int);
void nonPsjf (struct process[PROCESOS], int);
void npPrior (struct process[PROCESOS], int);
void pPrior (struct process[PROCESOS], int);
void pSjf (struct process[PROCESOS], int);
void imprimir(struct process[PROCESOS], int);



int main(int ac,char *av[]){
	int contador=0;
	int p1=0;
	int p2=0;
	int p3=0;
	int p4=0;
	process array[PROCESOS];

	while ( scanf("%d %d %d %d", &p1, &p2, &p3, &p4) != EOF ){//
		array[contador].ID             = p1;
		array[contador].tiempo_llegada = p2;
		array[contador].burst          = p3;
		array[contador].prior          = p4;
		contador++;
	}

	Fcfs   (array, contador);  
	npPrior(array, contador);
	nonPsjf(array, contador);
	pPrior (array, contador);
	pSjf   (array, contador);

	return 0;
}

void Fcfs (struct process array[PROCESOS], int num_pid){
	printf("\nFCFS: for %d processes\n",num_pid);
	int i;
	int j;
	
	for (i = 0; i < num_pid; i++){
		if(i==0){ 
			array[i].tiempo_inicio=array[i].tiempo_llegada; 
			array[i].tiempo_espera=array[i].tiempo_inicio-array[i].tiempo_llegada; 
			array[i].tiempo_termino=array[i].tiempo_inicio+array[i].burst; 
		}
		else{ 
			array[i].tiempo_inicio=array[i-1].tiempo_termino;
			array[i].tiempo_espera=array[i].tiempo_inicio-array[i].tiempo_llegada;
			array[i].tiempo_termino=array[i].tiempo_inicio+array[i].burst;
		} 
	}

	imprimir(array, num_pid);
}


void npPrior (struct process array[PROCESOS], int num_pid){
	printf("\nNon-preemptive Priority: for %d processes\n",num_pid);
	int i;
	int j;
	
for(i=0;i<num_pid;i++){
	int min = i;
		
		if(i==0){ 
			array[i].tiempo_inicio=array[i].tiempo_llegada; 
			array[i].tiempo_espera=array[i].tiempo_inicio-array[i].tiempo_llegada; 
			array[i].tiempo_termino=array[i].tiempo_inicio+array[i].burst;
		
		}else{                  
			for (j = i+1; j < num_pid; j++)
			if (array[j].prior < array[min].prior)    
				min = j;                             
			process temp = array[i];                           
			array[i] = array[min];                   
			array[min] = temp;                    
	
			array[i].tiempo_inicio=array[i-1].tiempo_termino;
			array[i].tiempo_espera=array[i].tiempo_inicio-array[i].tiempo_llegada;
			array[i].tiempo_termino=array[i].tiempo_inicio+array[i].burst;
		
		}
	}
	imprimir(array, num_pid);
	
}


void nonPsjf (struct process array[PROCESOS], int num_pid){
	printf("\nNon-preemptive SJF: for %d processes\n",num_pid);

	int i;
	int j;
	
for(i=0;i<num_pid;i++){
	int min = i;
		
		if(i==0){
			array[i].tiempo_inicio=array[i].tiempo_llegada; 
			array[i].tiempo_espera=array[i].tiempo_inicio-array[i].tiempo_llegada; 
			array[i].tiempo_termino=array[i].tiempo_inicio+array[i].burst; 
		}else{                                            
			for (j = i+1; j < num_pid; j++)                
			if (array[j].burst < array[min].burst)    
				min = j;                              
			process temp = array[i];                          
			array[i] = array[min];                  
			array[min] = temp;                      
	
			array[i].tiempo_inicio=array[i-1].tiempo_termino;
			array[i].tiempo_espera=array[i].tiempo_inicio-array[i].tiempo_llegada;
			array[i].tiempo_termino=array[i].tiempo_inicio+array[i].burst;
			
		}
	}
	imprimir(array, num_pid);

}


void pPrior (struct process array[PROCESOS], int num_pid){
	printf("\nPreemptive Priority: for %d processes\n",num_pid);
	
	int i,j,time,min, faltante;
	float sum_wait=0;
	
	faltante = num_pid;
  	for(i=0;i<num_pid;i++){
    	array[i].rt=array[i].burst;
  	}
	array[9].prior=11;
  
  	for(time=0;faltante!=0;time++){
    	min=9;
    	
    	for(i=0;i<num_pid;i++){
      		if(array[i].tiempo_llegada<=time && array[i].prior<array[min].prior && array[i].rt>0){
    			min=i;
      		}
    	}
    	
    	array[min].rt--;
    	if(array[min].rt==0){
      		faltante--;
     		sum_wait += time+1-array[min].tiempo_llegada-array[min].burst;
    	}
  	}

	printf("Avg waiting time = %.2f \n",sum_wait/num_pid);	
}


void pSjf (struct process array[PROCESOS], int num_pid){
	printf("\nPreemptive SJF: for %d processes\n",num_pid);
	
	int i,j,time,min, faltante;
	float sum_wait=0;
	
	faltante = num_pid;
  	for(i=0;i<num_pid;i++){
    	array[i].rt=array[i].burst;
  	}

	array[9].burst=11;
  	for(time=0;faltante!=0;time++){
    	min=9;
    	for(i=0;i<num_pid;i++){
      		if(array[i].tiempo_llegada<=time && array[i].burst<array[min].burst && array[i].rt>0){
    			min=i;
      		}
    	}
    
    	array[min].rt--;
	    if(array[min].rt==0){
	    	faltante--;
	      	sum_wait+=time+1-array[min].tiempo_llegada-array[min].burst;
    	}
  	}
	
	printf("Avg waiting time = %.2f \n\n",sum_wait/num_pid);		

}

void imprimir(struct process array[PROCESOS], int num_pid){
	int i;
	float tiempo_total=0;
	float tw;

	for(i=0; i<num_pid; i++){
		tiempo_total=tiempo_total+array[i].tiempo_espera;
	}
	printf("Avgerage wait time: %.2f \n", tiempo_total/num_pid);
}