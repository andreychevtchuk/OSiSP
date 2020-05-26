#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int main(){
	int i, fd;
	char string[255];
	char sem_name1[]="mytex";
	char sem_name2[]="empty";
	char sem_name3[]="full";
	while (1){
	sem_t *s1 = sem_open(sem_name1, O_CREAT, 0666);
	sem_t *s2 = sem_open(sem_name2, O_CREAT, 0666);
	sem_t *s3 = sem_open(sem_name3, O_CREAT, 0666);
	sem_wait(s3);
	sem_wait(s1);
	if((fd=open("BUF", O_RDONLY)) < 0){
		printf("Can\'t open file BUF\n");
		return(-1);
	}
	if (read(fd, string, 255)<= 0){
		printf("Can\'t read.\n");
		return(-1);
	}
	printf("Prog2 получила информацию из файла BUF.\n");
	if(close(fd) < 0){
		printf("Can\'t close file BUF\n");
	}
	for(i=0; i<strlen(string); i++){
		if (string[i]!='\n') printf("%c", string[i]);
	}
	printf("-%d\n", getpid());
	sleep(5);
	sem_post(s1);
	sem_post(s2);	
	sem_close(s1);
	sem_close(s2);
	sem_close(s3);
	}
	return 0;
}
