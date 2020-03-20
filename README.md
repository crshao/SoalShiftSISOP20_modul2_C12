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

#
## Soal2
Diminta membuat program c dengan ketentuan berikut
a. Program yang berada di suatu folder khusus, dapat membuat direktori baru setiap 30 detik, dengan nama timestamp ```[YYYY-mm-dd_HH:ii:ss]```.<br>
b. Tiap-tiap folder yang dibuat tadi, diisi dengan 20 gambar yang didownload dari *https://picsum.photos/* setiap 5 detik. Tiap gambar yang berbentuk persegi dengan ukuran ```(t % 1000) + 100``` piksel, di mana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp juga ```[YYYY-mm-dd_HH:ii:ss]```.<br>
c. Kemudian tiap folder yang sudah berisi 20 gambar akan dizip dan folder akan didelete, yang tersisa hanya file zipnya.<br>
d. Program tersebut dapat men-generate sebuah program *killer* yang siap di-execute untuk menterminasi semua operasi program tersebut. Setelah dirun, program itu akan mendelete dirinya sendiri.<br>
e. Program utama dapat dijalankan dalam 2 mode, yaitu **MODE_A** dan **MODE_B**. Di mana di MODE_A, jika program killer dijalankan, semua kegiatan operasi akan langsung terhenti, sedangkan untuk MODE_B, apabila masih ada proses download di masing-masing folder sampai 20 gambar dan sudah ter-zip, maka akan tetap berjalan sampai selesai.<br>
#

### Jawaban Soal2

#
## Soal3
Diminta membuat sebuah program yang dapat mengerjakan tugas yang berbeda tapi harus dikerjakan secara bersamaan atau biasa disebut multiprocessing, dengan ketentuan berikut
a. Membuat 2 direktori di **"/home/user/modul2/"**, yang bernama **"indomie"** dan **"sedaap"** (selang 5 detik).<br>
b. Mengekstrak file **jpg.zip** di direktori **"/home/user/modul2/"**.<br>
c. Memisahkan semua file hasil ekstrak ke dalam direktori **sedaap**, dan semua direktori ke dalam direktori **indomie**.<br>
d. Membuat semua direktori kosong dalam direktori **indomie** menjadi memiliki 2 file kosong masing-masing bernama **coba1.txt** dan setelah 3 detik **coba2.txt**.<br>
#

### Jawaban Soal3

