/* 
   CS288 HW10
*/
#include <stdio.h>
//#include </usr/src/kernels/4.4.7-300.fc23.x86_64+debug/include/linux/mpi.h>
#include <mpi.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define NELMS 1000000
#define MASTER 0
#define MAXPROCS 16

int dot_product();
void init_lst();
void print_lst();

int main(int argc, char **argv) {
  int i,n,vector_x[NELMS],vector_y[NELMS],lst_prods[MAXPROCS];
  int prod,tmp_prod,sidx,eidx,size;
  int pid,nprocs, rank;
  double stime,etime;
  MPI_Status status;
  MPI_Comm world;

  n = atoi(argv[1]);
  if (n > NELMS) { printf("n=%d > N=%d\n",n,NELMS); exit(1); }
  
  MPI_Init(&argc, &argv);
  world = MPI_COMM_WORLD;
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);

  stime = MPI_Wtime();
  // ...
  size=n/nprocs;
  sidx=size*pid;
  eidx=sidx+size;
  //printf("PID:%d, sind:%d, eind:%d, # of workers:%d, size:%d\n",pid,sidx,eidx,nprocs,size);
    
  if(pid==MASTER){
  	init_lst(vector_x,n);
  	init_lst(vector_y,n);
  }
  
  //MPI_Scatter(vector_x,size,MPI_INT,vector_x+sidx,size,MPI_INT,MASTER,world);
  //MPI_Scatter(vector_y,size,MPI_INT,vector_y+sidx,size,MPI_INT,MASTER,world);
  MPI_Scatter(vector_x,size,MPI_INT,vector_x,size,MPI_INT,MASTER,world);
  MPI_Scatter(vector_y,size,MPI_INT,vector_y,size,MPI_INT,MASTER,world);
  //print_lst(0,n,vector_x);print_lst(0,n,vector_y);
  
  //prod=dot_product(vector_x,vector_y,sidx,eidx);
  prod=dot_product(vector_x,vector_y,0,size);
  //printf("PID:%d, temp_prod:%d\n",pid,prod);
  
  MPI_Gather(&prod,1,MPI_INT,lst_prods,1,MPI_INT,MASTER,world);prod=0;
  if(pid==MASTER){
  	for(i=0;i<nprocs;i++){
  		prod+=lst_prods[i];
  	}
  }
  /*  
  init_lst(vector_x,n);
  init_lst(vector_y,n);
  
  prod=dot_product(vector_x,vector_y,sidx,eidx);
  //printf("PID:%d, temp_prod:%d\n",pid,prod);
  if(pid==MASTER){
  	for(i=1;i<nprocs;i++){
  		MPI_Recv(&tmp_prod,1,MPI_INT,i,21,world,&status);
  		prod+=tmp_prod;
  		//printf("\t%d: prod:%d, temp_prod:%d, status:%d\n",pid,prod,tmp_prod,status);
  	}
  }
  else{
  	MPI_Send(&prod,1,MPI_INT,MASTER,21,world);
  	//printf("\t%d: prod:%d\n",pid,prod);
  }
  */
  
  etime = MPI_Wtime();

  if (pid == MASTER) {
    printf("========================================\n");
    printf("pid=%d: final prod=%u\n",pid,prod);
    printf("pid=%d: elapsed=%f\n",pid,etime-stime);
    printf("========================================\n");
  }
  MPI_Finalize();
}

int dot_product(int *x,int *y,int s,int e){
  int i,prod=0;
  // ...
  for(i=s;i<e;i++){
  	prod+=x[i]*y[i];
  }
  return prod;
}

void init_lst(int *l,int n){
  int i;
  for (i=0; i<n; i++) *l++ = i;
}
void print_lst(int s,int e, int *l){
  int i;
  for (i=s; i<e; i++) {
    printf("%x ",l[i]);
  }
  printf("\n");
}

// end of file
