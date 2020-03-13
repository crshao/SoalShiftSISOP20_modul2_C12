#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h> 

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

int main() {
  pid_t child_id,child_id1,child_id3,child_id2,child_id4;
  int status;

  child_id = fork();
  
  if (child_id < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }

  if (child_id == 0) {
    // this is child
    child_id1 = fork();

        if (child_id1 < 0) {         
          exit(EXIT_FAILURE); 
        }

        if (child_id1 == 0) {
          char *argv[] = {"mkdir", "/home/rofita/modul2/indomie", NULL};
          execv("/bin/mkdir", argv);
        } 
        
        else {
          while ((wait(&status)) > 0);
          sleep(5);
          char *argv[] = {"mkdir","/home/rofita/modul2/sedaap", NULL};
          execv("/bin/mkdir", argv);
        }
  } 
  
  else {
    // this is parent
    child_id1 = fork();
    while ((wait(&status)) > 0);

      if (child_id1 < 0) {   
        exit(EXIT_FAILURE); 
      }
      if (child_id1 == 0) {
        while ((wait(&status)) > 0);
        // this is child
        char *argv[] = {"unzip", "jpg.zip", "-d", "/home/rofita/modul2/", NULL};
        execv("/usr/bin/unzip", argv);
      } 
      else {
        while ((wait(&status)) > 0);
        // char *argv[] = {"mv", "/home/rofita/modul2/jpg/`*`/","/home/rofita/modul2/indomie", NULL};
        // execv("/bin/mv", argv);
        DIR *d;
        struct dirent *dir;
        chdir("/home/rofita/modul2/jpg/"); 
        d = opendir(".");
        if (d)
        {
          while ((dir = readdir(d)) != NULL)
          {
            if(strcmp(dir->d_name, "..")==0 || strcmp(dir->d_name, ".")==0)
            continue; 
            
            child_id3 = fork();

              if (child_id3 < 0) {
                exit(EXIT_FAILURE); 
              }

              if (child_id3 == 0) {
                  if (isDirectory(dir->d_name)) {
                    child_id2 = fork();

                    if (child_id2 < 0) {
                      exit(EXIT_FAILURE);
                    }
                    if (child_id2 == 0) {
                      char ppath[300];
                      sprintf(ppath, "/home/rofita/modul2/jpg/%s", dir->d_name);
                      char *argv[] = {"mv", ppath, "/home/rofita/modul2/indomie/", NULL};
                      execv("/bin/mv", argv);
                    }
                    else {
                      while ((wait(&status)) > 0);
                      child_id4 = fork();

                      if (child_id4 < 0) {
                        exit(EXIT_FAILURE); 
                      }
                      if (child_id4 == 0) {
                        char ppath1[300];
                        sprintf(ppath1, "/home/rofita/modul2/indomie/%s/coba1.txt", dir->d_name);
                        char *argv[] = {"touch", ppath1, NULL};
                        execv("/bin/touch", argv);
                      }
                      else {
                        while ((wait(&status)) > 0);
                        sleep(3);
                        char ppath2[300];
                        sprintf(ppath2, "/home/rofita/modul2/indomie/%s/coba2.txt", dir->d_name);
                        char *argv[] = {"touch", ppath2, NULL};
                        execv("/bin/touch", argv);
                      } 
                    }
                  } 
                  else {
                      while ((wait(&status)) > 0);
                      char ppath[300];
                      sprintf(ppath, "/home/rofita/modul2/jpg/%s", dir->d_name);
                      char *argv[] = {"mv", ppath, "/home/rofita/modul2/sedaap/", NULL};
                      execv("/bin/mv", argv);
                    }
              }
              else{
                while ((wait(&status)) > 0);
              }
          }closedir(d);
        }
      }
  }
}
