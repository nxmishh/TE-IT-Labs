#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

void bubblesort(int a[], int n){
	int temp;
	for (int i=0; i<n-1; i++){
		for(int j=0; j<n-i-1; j++){
			if ( a[j] > a[j+1]){
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}

int main (){
	int n,pid, ppid;
	printf("Enter the size of array : ");
	scanf("%d",&n);
	printf("Enter the array : ");
	int p_a[n],c_a[n];
	for(int i = 0; i<n ; i++){
		scanf("%d",&p_a[i]);
		c_a[i] = p_a[i];
	}
	int choice;
	printf("Enter the choice : \n");
	printf("1. fork and wait \n");
	printf("2. orphan \n");
	printf("3. zombie \n");
	scanf("%d",&choice);
	if (choice == 1){
		pid_t child_pid = fork();
		if (child_pid == -1){
			perror("Fork Failed");
			exit(1);
		}
		else if(child_pid == 0) {
			printf("\n");
			printf("This is child process ...\n");
			pid = getpid();
			ppid = getppid();
			printf("child process pid %d\n", pid );
			printf("parent process %d\n", ppid);
			printf("Child process id sorting the array child array ...\n");
			bubblesort(c_a,n);
			printf("Child process sorting completed ...\n");
			printf("Sorted array : ");
			for (int i = 0;i<n; i++){
				printf("%d",c_a[i]);
			}
			printf("\n");
		}
		else{
			printf("\n");
			printf("This is parent process ...\n");
			printf("parent process %d\n", ppid);
			printf("Parent process id sorting the array Parent array ...\n");
			bubblesort(p_a,n);
			printf("Parent process sorting completed ...\n");
			printf("Sorted array : ");
			for (int i = 0;i<n; i++){
				printf("%d",p_a[i]);
			}
			printf("Parent process waiting for the child to complete its execution \n");
			wait(NULL);
			printf("\n");
			printf("This is parent process ...");
			printf("Parent process waited for the child \n");
			printf("\n");
		}
	}
	else if(choice == 2){
		//orphan
		pid_t child_pid = fork();
		if (child_pid == -1){
			perror("Fork Failed");
			exit(1);
		}
		else if(child_pid == 0) {
			printf("\n");
			printf("This is child process ...");
			pid = getpid();
			ppid = getppid();
			printf("child process pid %d\n", pid );
			printf("parent process %d\n", ppid);
			printf("Child process id sorting the array child array ...\n");
			bubblesort(c_a,n);
			printf("Child process sorting completed ...\n");
			printf("Sorted array : ");
			for (int i = 0;i<n; i++){
				printf("%d",c_a[i]);
			}
			printf("Child process is going to sleep \n");
			sleep(1);
			printf("\n");
			printf("This is child process ...");
			system("ps -elf | grep a.out");		
			printf("\n");
		}
		else{
			printf("\n");
			printf("This is parent process ...");
			printf("parent process %d\n", ppid);
			printf("Parent process id sorting the array Parent array ...\n");
			bubblesort(p_a,n);
			printf("Parent process sorting completed ...\n");
			printf("Sorted array : ");
			for (int i = 0;i<n; i++){
				printf("%d",p_a[i]);
			}
			printf("Parent process is terminating without waiting for the child to complete its execution \n");
			printf("Parent process has terminated \n");
			printf("\n");
		}
	}

	else{
		// zombie
		pid_t child_pid = fork();
		if (child_pid == -1){
			perror("Fork Failed");
			exit(1);
		}
		else if(child_pid == 0) {
			printf("\n");
			printf("This is child process ...");
			pid = getpid();
			ppid = getppid();
			printf("child process pid %d\n", pid );
			printf("parent process %d\n", ppid);
			printf("Child process id sorting the array child array ...\n");
			bubblesort(c_a,n);
			printf("Child process sorting completed ...\n");
			printf("Sorted array : ");
			for (int i = 0;i<n; i++){
				printf("%d",c_a[i]);
			}
			printf("Child process is terminating to become a zombie \n");
			printf("Child process has terminated \n");
			printf("\n");
		}
		else{
			printf("\n");
			printf("This is parent process ...");
			printf("parent process %d\n", ppid);
			printf("Parent process id sorting the array Parent array ...\n");
			bubblesort(p_a,n);
			printf("Parent process sorting completed ...\n");
			printf("Sorted array : ");
			for (int i = 0;i<n; i++){
				printf("%d",p_a[i]);
			}
			printf("Parent process is going to sleep \n");
			sleep(1);
			printf("\n");
			printf("This is parent process ...");
			system("ps -elf | grep a.out");		
			printf("\n");
		}

	}
	return 0;
}
