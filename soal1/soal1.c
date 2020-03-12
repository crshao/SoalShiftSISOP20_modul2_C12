#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int cfileexists(const char * filename);
int check1(char argument[]);
int check2(char argument[]);
void check3(int detik, int menit, int jam);

int main(int argc, char **argv) {

if(argc != 5)
{
	printf("Jumlah argumen salah!\n");
	exit(EXIT_FAILURE);
}

int argument[4];
int i, curr_detik, curr_menit, curr_jam;

for(i = 1; i < 4; i++)
{
	if(check1(argv[i]) == 0)
	{
		if(check2(argv[i]) == 0)
		{
			printf("Argumen harus merupakan angka atau '*'\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			argument[i] = -1;
		}
	}

	argument[i] = atoi(argv[i]);
}

//CEK KELEBIHAN ATAU TIDAK
check3(argument[1], argument[2], argument[3]);

pid_t pid, sid;
 
pid = fork();
 
if (pid < 0) {
  exit(EXIT_FAILURE);
}
 
if (pid > 0) {
  exit(EXIT_SUCCESS);
}

umask(0);
 
sid = setsid();
 
if (sid < 0) {
  exit(EXIT_FAILURE);
}
 
//if ((chdir("/home/hao/modul2-2020/latihan-soal3")) < 0) {
//  exit(EXIT_FAILURE);
//}
 
close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);
 
 
while(1) {
	time_t current_time = time(NULL);
	struct tm *tm1 = localtime(&current_time);
	
	curr_detik = tm1->tm_sec;
	curr_menit = tm1->tm_min;
	curr_jam = tm1->tm_hour;
	
	if((curr_detik == argument[1] || argument[1] == -1) &&
	   (curr_menit == argument[2] || argument[2] == -1) &&
	   (curr_jam == argument[3] || argument[3] == -1))
	{
//		printf("TEST");
		pid_t child_id;
		child_id = fork();

		int status;

		if(child_id == 0)
		{
			char *argexec[] = {"bash", argv[4], NULL};
			execv("/bin/bash", argexec);
		}
//		else
//		{
//			while ((wait(&status)) > 0);
//		}
	}
  sleep(1);
}
}

int cfileexists(const char * filename){
  /* try to open file to read */
  FILE *file;
  if (file = fopen(filename, "r")){
      fclose(file);
      return 1;
  }
  return 0;
}

int check1(char argument[])
{
	int i;
	for(i = 0; i < strlen(argument); i++)
	{
		if(argument[i] > '9' || argument[i] < '0')
			return 0;
	}

	return 1;
}

int check2(char argument[])
{
		printf("DEBUG\n");
		if(argument[0] == '*')
			return 1;
	
	return 0;
}

void check3(int detik, int menit, int jam)
{
	if(detik > 59 || menit > 59 || jam > 23)
	{
		printf("Format waktu yang dimasukkan salah\n");
		exit(EXIT_FAILURE);
	}
}
