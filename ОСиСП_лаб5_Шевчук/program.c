#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
	int fd1, fd2, i, j, k, Nstr=0, razryad, NN;
	size_t sizeRead;
	char* Nn;
	char key='n';
	char string[255], A[12]="AaEeIiOoUuYy", B[]="Строка №";
	/*Создание файлов для записи строк в третьем задании:*/
	(void)umask(0);
	if((fd1=open("Chetn", O_WRONLY | O_CREAT, 0666)) < 0){
		printf("Can\'t open file Chetn\n");
		return(-1);
	}
	if((fd2=open("Nechetn", O_WRONLY | O_CREAT, 0666)) < 0){
		printf("Can\'t open file Nechetn\n");
		return(-1);
	}
	/*Считывание данных из стандартного потока ввода:*/
	sizeRead = read(0, string, 255);
	if(sizeRead <= 0){
		printf("Can\'t read.\n");
		return(-1);
	}
	/*Поиск строк, начинающихся на гласные:*/
	j=strlen(string);
	for (i=0; i<j; i++){
		Nstr++;//количество строк (а также номер текущей строки)
		for(k=0; k<12; k++){
			if (string[i]==A[k]){
				key='y';
			}
		}
		/*Если строка начинается не с гласной:*/
		if (key=='n'){
			while(i<j && string[i]!='\n'){
				i++;
			}
		}
		/*Если строка начинается с гласной:*/
		if (key=='y'){
			/*Подготовка номера строки к выводу*/
			razryad=1;
			NN=Nstr;
			while ((NN = NN/10) != 0){ 
			razryad++;
			}
			Nn = (char*) malloc(razryad+1);
			NN=Nstr;
			for (k=razryad-1; k>=0; k--){
			Nn[k]=(NN % 10)+'0';
			NN = NN/10;
			}
			Nn[razryad]='\0';
			/*Вывод в поток для вывода ошибок порядкового номера строки:*/
			write(2, B, strlen(B)+1);
			write(2, Nn, strlen(Nn)+1);
			write(2, ": ", 2);
			/*Вывод самой строки:*/
			while(i<j && string[i]!='\n'){
				/*В файл с чётными номерами:*/
				if (Nstr % 2==0){
					write(fd1, &string[i], 1);
					/*Переход на новую строку:*/
					if (i+1<j && string[i+1]=='\n'){
						write(fd1, &string[i+1], 1);
					}
				}
				/*В файл с нечётными номерами:*/
				else {
					write(fd2, &string[i], 1);
					/*Переход на новую строку:*/
					if (i+1<j && string[i+1]=='\n'){
						write(fd2, &string[i+1], 1);
					}
				}
				/*В стандартный поток вывода:*/
				write(1, &string[i], 1);
				/*Переход на новую строку:*/
				if (i+1<j && string[i+1]=='\n'){
					write(1, &string[i+1], 1);
				}
				i++;
			}
			key='n';
		}		
	}
	if(close(fd1) < 0){
		printf("Can\'t close file Chetn\n");
	}
	if(close(fd2) < 0){
		printf("Can\'t close file Nechetn\n");
	}
	return 0;
} 
