#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int main(){
	long int ttime; // Переменная для сохранения текущего времени
	int i, j, ValuePID, fd, sizeRead;
	char *Value;
	char string[255];
	char sem_name1[]="mytex";
	char sem_name2[]="empty";
	char sem_name3[]="full";
	for(j=0; j<10; j++){
	sem_t *s1 = sem_open(sem_name1, O_CREAT, 0666, 1);
	sem_t *s2 = sem_open(sem_name2, O_CREAT, 0666, 1);
	sem_t *s3 = sem_open(sem_name3, O_CREAT, 0666, 0);
	sem_wait(s2);
	sem_wait(s1);
	(void)umask(0);
	if((fd=open("BUF", O_WRONLY | O_CREAT, 0666)) < 0){
		printf("Can\'t open file BUF\n");
		return(-1);
	}
	ValuePID=getpid();
	/*Подготовка номера PID к выводу*/
	int razryad=1;
	i=ValuePID;
	while ((i = i/10) != 0){ 
	razryad++;
	}
	Value = (char*) malloc(razryad+1);
	for (i=razryad-1; i>=0; i--){
		Value[i]=(ValuePID % 10)+'0';
		ValuePID = ValuePID/10;
	}
	Value[razryad]='-';
	if (write(fd, Value, strlen(Value))<= 0){
		printf("Can\'t write.\n");
		return(-1);
	}
	ttime = time (NULL);// Считываем текущее время
	// С помощью функции ctime преобразуем считанное время в локальное, а затем в строку
	if (write(fd, ctime (&ttime), strlen(ctime (&ttime)))<= 0){
		printf("Can\'t write.\n");
		return(-1);
	}
	printf("Prog1 отправила информацию в файл BUF.\n");
	if(close(fd) < 0){
		printf("Can\'t close file BUF\n");
	}
	sem_post(s1);
	sem_post(s3);
	sem_close(s1);
	sem_close(s2);
	sem_close(s3);
	}
	return 0;
}
