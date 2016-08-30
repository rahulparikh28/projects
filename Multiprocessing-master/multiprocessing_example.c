//Student A: Rahul Parikh Student B:Arjun Pawar
//Lab 4




#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



typedef struct myStruct{
        double percent[12];
        double average;
	double varience;
	double std_deviation;
	int flagh;
	int flags;
        }myStruct;
void memory_ready();
void memory_ready1();
void hist_done();
void std_done();
int shmid,shmid1,i,j,k,count,h,done_h,done_s;
//char shmid_str[8];
int main (int argc, char *argv[])
{
	i=atoi(argv[1]);


	j=atoi(argv[2]);
	
		
	myStruct temp;
	double *data_gen;
	myStruct *shm;
	double  diff1,diff;


        struct timespec start, end;


	int pid_h,pid_s,lastpid,status;
	
	
	
	if((shmid = shmget(IPC_PRIVATE, sizeof(myStruct), 0666 | IPC_CREAT))==-1){printf("shmget at parent failed\n");}
	if((shmid1 = shmget(IPC_PRIVATE, 1000*i*sizeof(double), 0666 | IPC_CREAT))==-1){printf("shmget at parent failed\n");}
	
	
	pid_h=fork();
	pid_s=fork();                                   //fork call will duplicate parent process
       	 
	if((pid_h<0)&&(pid_s<0))                                   //if return value is minus number means error
	perror("error occured\n");
	
	else if((pid_h!=0)&&(pid_s!=0)){                            //if return value is not zero than its parent
	
	shm =(myStruct *) shmat(shmid, NULL, 0);
	if(shm==(myStruct *)-1){printf("shmat at parent failed\n");}
	
        data_gen=(double *)shmat(shmid1,NULL,0);
	if(data_gen==(double *)-1){printf("shmat at parent failed\n");}
	for(k=0;k<j;k++) {   
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);    
	srand(CLOCK_PROCESS_CPUTIME_ID);
	for(h=0;h<1000*i;h++){
	
	data_gen[h]=rand();
	}
	shm->flagh=0;
	shm->flags=0;
        if(kill(pid_h,SIGUSR1)){printf("kill user 1 failed\n");}   // pass the signal to histogram child
	if(kill(pid_s,SIGUSR2)){printf("kill user 2 failed\n");}   // pass signal to std child
	
	
	while((shm->flagh!=1)&&(shm->flags!=1)){
		sleep(1);
	}
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
        diff=1000000000*(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec);
        diff1=diff/1000000000;
	printf("%.3lfseconds\n",diff1);
        printf("%.3lfnanosec\n",diff);

	printf("average=%.2lf  varience=%.2lf  std_deviation=%.2lf\n",shm->average,shm->varience, shm->std_deviation);
	printf("Distribution: %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf total:%.2lf\n ",shm->percent[0],shm->percent[1],shm->percent[2],shm->percent[3],shm->percent[4],shm->percent[5],shm->percent[6],shm->percent[7],shm->percent[8],shm->percent[9],shm->percent[11]);
	done_h=0;done_s=0;
	
	
	
	}
	}	
	else if(pid_h==0) {               //child process

		
	signal(SIGUSR1,memory_ready);    //wait for the signal
        while(count<j){} 
	exit(0); 
	
	
	}
  
	else if(pid_s==0){              // child process
	
	signal(SIGUSR2,memory_ready1);   //wait for the signal
	while(count<j){}
	exit(0);  
	
	}
	
	while((lastpid=wait(&status))>0){           //wait for the child process to terminate

	printf("After wait() child ID: %d is Terminated.....\n",lastpid);
	printf("child %d exiting...........\n",lastpid);
	}

	if(shmdt(shm)){printf("shmdt at parent failed\n");}
	if(shmdt(data_gen)){printf("shmdt at parent failed\n");}
        if(shmctl(shmid, IPC_RMID, NULL)){printf("shmctl st parent failed\n");}
        if(shmctl(shmid1, IPC_RMID, NULL)){printf("shmctl st parent failed\n");}
	exit(0);
}


void memory_ready( )       //called when signal arrives. this signal handller will be called when SIGUSR1 signal is passed
{
	     
	
        
	double frequency[11],bins[11],binstep=0;
	myStruct *shm1;
        double *data1;
	int d;
        
        shm1 = (myStruct *)shmat(shmid, NULL, 0);
        data1=(double *)shmat(shmid1,NULL,0);
	
	
	

	binstep=RAND_MAX/10;
        for(d=0;d<10;d++){frequency[d]=0;}
        for(d=1;d<=10;d++){
        bins[d]=d*binstep;
        }

        for(d=0;d<1000*i;d++){

        if(data1[d]<=bins[1]){frequency[0]++;}
        else if(data1[d]<=bins[2]){frequency[1]++;}
        else if(data1[d]<=bins[3]){frequency[2]++;}
        else if(data1[d]<=bins[4]){frequency[3]++;}
        else if(data1[d]<=bins[5]){frequency[4]++;}
        else if(data1[d]<=bins[6]){frequency[5]++;}
        else if(data1[d]<=bins[7]){frequency[6]++;}
        else if(data1[d]<=bins[8]){frequency[7]++;}
        else if(data1[d]<=bins[9]){frequency[8]++;}
        else if(data1[d]<=bins[10]){frequency[9]++;}
        }
        for(d=0;d<10;d++){
        shm1->percent[d]=(frequency[d]/(1000*i))*100;
	
        }
	shm1->percent[11]=0;
        for(d=0;d<10;d++){shm1->percent[11]=shm1->percent[11]+shm1->percent[d];}

	shm1->flagh=1;
        
        
        if(shmdt(shm1)){printf("shmdt at histogram failed\n");}
	if(shmdt(data1)){printf("shmdt at histogram failed\n");}
	count++;
	
	
	
}
void memory_ready1( )                    //called when signal arrives this signal handeller will be called when SIGUSR2 signal is passed
{
	
        myStruct *shm2;
	double *data,sum=0,sum1=0,varience=0;
	int d;
        
        
        
        shm2 = (myStruct *)shmat(shmid, NULL, 0);
        data=(double *)shmat(shmid1,NULL,0);
	
        
        
	for(d=0;d<1000*i;d++){
        sum=sum+data[d];
        }

        shm2->average=sum/(1000*i);

        for(d=0;d<1000*i;d++){
        sum1=sum1+((data[d]-shm2->average)*(data[d]-shm2->average));
        }

        shm2->varience=sum1/1000*i;
	
        shm2->std_deviation= sqrt (shm2->varience);
	

	shm2->flags=1;
        if(shmdt(shm2)){printf("shmdt at std_deviation failed\n");}
	if(shmdt(data)){printf("shmdt at histogram failed\n");}
	
	count++;
	

	
}


