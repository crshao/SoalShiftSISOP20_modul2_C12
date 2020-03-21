# SoalShiftSISOP20_modul2_C12
Soal Shift Sistem Operasi 2020
#
- Rofita Siti Musdalifah / 05111840000034
- Calvin Wijaya / 0511184000086
#
1. [Soal1](#soal1)
2. [Soal2](#soal2)
3. [Soal3](#soal3)
#

## Soal1
Membuat program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut<br>
a. Program menerima 4 argumen berupa:
    * Detik: 0-59 atau * (any value)
    * Menit: 0-59 atau * (any value)
    * Jam: 0-23 atau * (any value)
    * Path file .sh<br>
b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai.<br>
c. Program hanya menerima 1 config cron.<br>
d. Program berjalan di background (daemon).<br>
e. tidak menggunakan system().<br>
#

### Jawaban Soal1
```
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
	else
	{
		argument[i] = atoi(argv[i]);
	}
}

printf("%d %d %d\n", argument[1], argument[2], argument[3]);

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
	
	if(
	   (tm1->tm_sec == argument[1] || argument[1] == -1)
	   &&
	   (tm1->tm_min == argument[2] || argument[2] == -1)
	   &&
	   (tm1->tm_hour == argument[3] || argument[3] == -1)
	   )
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
	if(strlen(argument) == 1)
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
```

Pada kode diatas, terdapat fungsi check1, check2, check3, yang mana fungsi check1 merupakan fungsi untuk memeriksa apakah argumen yang dimasukkan berupa angka yang valid. Fungsi check2 memeriksa apakah argumen yang dimasukkan merupakan * yang bertanda akan dijalankan pada setiap detik/menit/jam. Fungsi check3 merupakan fungsi yang memeriksa apakah format waktu yang dimasukkan valid. Setelah argumen di periksa, program memulai dengan membuat variabel bertipe data time_t dan struct tm, yang mana variabel bertipe data struct tm menunjuk ke alamatnya time_t untuk mendapatkan waktu saat ini, setelah membuat 2 variabel tersebut, program akan memeriksa argumen yang dimasukkan, dan jika waktu yang dimasukkan menemui ketepatan dengan argumen yang dimasukkan, script yang ada akan dijalankan dengan command bash.


#
## Soal2
Diminta membuat program c dengan ketentuan berikut<br>
a. Program yang berada di suatu folder khusus, dapat membuat direktori baru setiap 30 detik, dengan nama timestamp ```[YYYY-mm-dd_HH:ii:ss]```.<br>
b. Tiap-tiap folder yang dibuat tadi, diisi dengan 20 gambar yang didownload dari *https://picsum.photos/* setiap 5 detik. Tiap gambar yang berbentuk persegi dengan ukuran ```(t % 1000) + 100``` piksel, di mana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp juga ```[YYYY-mm-dd_HH:ii:ss]```.<br>
c. Kemudian tiap folder yang sudah berisi 20 gambar akan dizip dan folder akan didelete, yang tersisa hanya file zipnya.<br>
d. Program tersebut dapat men-generate sebuah program *killer* yang siap di-execute untuk menterminasi semua operasi program tersebut. Setelah dirun, program itu akan mendelete dirinya sendiri.<br>
e. Program utama dapat dijalankan dalam 2 mode, yaitu **MODE_A** dan **MODE_B**. Di mana di MODE_A, jika program killer dijalankan, semua kegiatan operasi akan langsung terhenti, sedangkan untuk MODE_B, apabila masih ada proses download di masing-masing folder sampai 20 gambar dan sudah ter-zip, maka akan tetap berjalan sampai selesai.<br>
#

### Jawaban Soal2

#
## Soal3
Diminta membuat sebuah program yang dapat mengerjakan tugas yang berbeda tapi harus dikerjakan secara bersamaan atau biasa disebut multiprocessing, dengan ketentuan berikut<br>
a. Membuat 2 direktori di **"/home/user/modul2/"**, yang bernama **"indomie"** dan **"sedaap"** (selang 5 detik).<br>
b. Mengekstrak file **jpg.zip** di direktori **"/home/user/modul2/"**.<br>
c. Memisahkan semua file hasil ekstrak ke dalam direktori **sedaap**, dan semua direktori ke dalam direktori **indomie**.<br>
d. Membuat semua direktori kosong dalam direktori **indomie** menjadi memiliki 2 file kosong masing-masing bernama **coba1.txt** dan setelah 3 detik **coba2.txt**.<br>
#

### Jawaban Soal3

Pertama, program melakukan fork dua kali untuk membuat kedua subfolder **sedaap** dan **indomie**. Proses pada parent akan menunggu kedua child process selesai sebelum melanjutkan. Lalu, program melakukan fork lagi untuk melakukan `unzip` file `jpg.zip`.

```c
....
  child_id = fork();
  
  if (child_id < 0) {
    exit(EXIT_FAILURE); 
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
 ...
```

Setelah `unzip` selesai, parent akan melakukan looping untuk setiap objek pada direktori, menggunakan kode berikut
```c
        DIR *d;
        struct dirent *dir;
        chdir("/home/rofita/modul2/jpg/"); 
        d = opendir(".");
        if (d)
        {
          while ((dir = readdir(d)) != NULL)
          { 
        .....
        }closedir(d);
        
```
`struct dirent` memiliki isi berupa nama objeknya, dan tipenya.

Dengan melewati objek `.` dan `..`, setiap loop akan membuat child process lagi untuk memproses setiap objek.

Untuk melakukan pengecekan apakah directory atau bukan menggunakan fungsi berikut
```c
int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}
```

Apabila objek adalah file, child process tersebut melakukan operasi `mv` menggunakan `exec` untuk memindah ke subfolder `sedaap`.

Apabila objek adalah folder, maka pertama child process melakukan fork untuk menjalankan `mv` dengan `exec`, memindahkan folder ke subfolder `indomie`. Lalu, child proces melakukan fork lagi untuk membuat file `coba1.txt`. Child process menunggu tiga detik kemudian berakhir dengan membuat file `coba2.txt`.

```c
            ......

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
             .......
```



