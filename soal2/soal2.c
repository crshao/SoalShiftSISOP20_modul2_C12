#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <wait.h>
#include <time.h>
#include <string.h>

int main() {
  pid_t pid, child_id1, sid, child_id2;        // Variabel untuk menyimpan PID
  time_t t ; 
  int status;

  //format waktu
  struct tm *tmp ; 
  char MY_TIME[50];

  //epoch unix
  struct timespec ts;

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    // Tulis program kalian di sini
    time( &t ); 
    tmp = localtime( &t );
    strftime(MY_TIME, sizeof(MY_TIME), "%Y-%m-%d_%X", tmp); 
    
    child_id1 = fork();

        if (child_id1 < 0) {         
          exit(EXIT_FAILURE); 
        }
        if (child_id1 == 0) {
            while ((wait(&status)) > 0);
            chdir("/home/rofita/foldermodul2/praktikum2/soal2");
            char *argv[] = {"mkdir", MY_TIME, NULL};
            execv("/bin/mkdir", argv);
            
        } else {
            while ((wait(&status)) > 0);
            char downl[300];
            char path[300];
            sprintf(path, "/home/rofita/foldermodul2/praktikum2/soal2/%s", MY_TIME);
            chdir(path);
            for(int i=0;i<10;i++){
              child_id2 = fork();
              if (child_id2 < 0) {         
                exit(EXIT_FAILURE); 
              }
              if (child_id2 == 0) {

                //epoch
                timespec_get(&ts, TIME_UTC); //call use ts.tv_nsec
                sprintf(downl, "https://picsum.photos/%ld", (ts.tv_nsec%1000)+100);
                // $ wget -O nama_tersimpan.zip https://example.co.id/source.zip
                //time format nama
                time( &t ); 
                tmp = localtime( &t );
                strftime(MY_TIME, sizeof(MY_TIME), "%Y-%m-%d_%X", tmp); 
                char *argv[] = {"wget","-O", MY_TIME, downl, NULL};
                execv("/usr/bin/wget", argv);  

              }
              else {

                //epoch
                timespec_get(&ts, TIME_UTC); //call use ts.tv_nsec
                sprintf(downl, "https://picsum.photos/%ld", (ts.tv_nsec%1000)+100);
                // $ wget -O nama_tersimpan.zip https://example.co.id/source.zip
                //time format nama
                time( &t ); 
                tmp = localtime( &t );
                strftime(MY_TIME, sizeof(MY_TIME), "%Y-%m-%d_%X", tmp); 
                char *argv[] = {"wget","-O", MY_TIME, downl, NULL};
                execv("/usr/bin/wget", argv);  

              }
            } 
        }
    sleep(5);
  }
}

