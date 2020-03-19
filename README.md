# SoalShiftSISOP20_modul2_T17
Nama Anggota Kelompok T17 :
  1. Faza Murtadho [05311840000034]
  2. Rindi Kartika Sari [05311840000013]

## Soal Shift Modul 2 dan Penyelesaian Soal Shift Modul 2
### Soal 1
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut: <br>
* #### Ketentuan 1A
  A. Program menerima 4 argumen berupa : <br> 
    * #### Ketentuan A (i, ii, iii dan iv)
      i. Detik: 0-59 atau * (any value) <br>
      ii. Menit: 0-59 atau * (any value) <br>
      iii. Jam: 0-23 atau * (any value) <br>
      iv. Path file .sh <br>
* #### Ketentuan 1B
  B. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai 
* #### Ketentuan 1C
  C. Program hanya menerima 1 config cron
* #### Ketentuan 1D
  D. Program berjalan di background (daemon)
* #### Ketentuan 1E
  E. Tidak boleh menggunakan fungsi system() <br>
  
Contoh ```./program \* 34 7 /home/somi/test.sh ``` <br>
Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap
detik pada jam 07:34.
 #### Code : https://github.com/rindikar/SoalShiftSISOP20_modul2_T17/blob/master/soal1.c
 #### Penyelesaian :
 ```bash
 #include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <stdio.h>
#include <syslog.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
	pid_t pid, sid;
	int d,m,j;

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
  if ((chdir("/home/xd/Desktop/Modul2/shift")) < 0) {
   exit(EXIT_FAILURE);
  }


  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);


	if(argc != 5){
		printf("error");
		return 0;
	}

	d = 0;
	m = 0;
	j = 0;
	
    if(d = atoi(argv[1]) != '*' && (atoi(argv[1] > 60 && atoi(argv[1]) < 0);
    if(m = atoi(argv[2]) != '*' && (atoi(argv[1] > 60 && atoi(argv[2]) < 0);
    if(j = atoi(argv[3]) != '*' && (atoi(argv[1] > 60 && atoi(argv[3]) < 0);

while(1){
 time_t t = time(NULL);
 struct w tm = *localtime(&t)
 if((j == w.tm_j || j == 0) && (m == w.tm_m || m == 0) && (d == w.tm_d || d == 0)) {
      if (fork()==0)
      execl("/bin/bash", "bash", argv[5], NULL);}
      sleep(1);
    }
}
```
* ```int main(int argc, char** argv)``` terdiri atas fungsi ```main```, ```argc``` dan ```argv```.<br> Dalam fungsi ```main``` tersebut, terdapat fungsi ```argc``` atau _Argument Count_ menunjukkan jumlah argumen yang digunakan. <br>
Selain itu, juga terdapat fungsi ```argv``` atau _Argument Vector_ yang menyimpan setiap argumen yang diberikan oleh _user_ dalam bentuk array. Kedua fungsi tersebut dimaasukkan ke dalam fungsi ```main``` untuk mengetahui beraoa banyak dan aoa saja parameter yang akan dikirimkan oleh sistem operasi ke program. <br>
* Dikarenakan program ini akan bekerja secara _background_, maka kita harus membuat __Daemon__. <br>
Untuk membuat __Daemon__, langkah pertama yang harus dilakukan terdapat pada code berikut :
	```bash
		pid_t pid, sid;
		int d,m,j;

		pid = fork();

  	if (pid < 0) {
    		exit(EXIT_FAILURE);
  	}

  	if (pid > 0) {
    		exit(EXIT_SUCCESS);
	}

  umask(0);
	``` 
	Jadi, untuk membuat __Daemon__, kita perlu melakukan _forking_ (men-_swpan_ proses menjadi __Parent Process__ dan __Child Process__) kemudian membunuh __Parent Process__ yang ada. Dengan matinya __Parent Process__, maka sistem operasi akan mengira bahwa __Parent Process__ telah selesai sehingga kita akan mendapatkan sebuah __Child Process__ yang menandakan bahwa kita mendapatkan proses yang hampir bekerja secara _background_. <br>
	Perlu diketahui bahwa __Daemon__ harus bekerja secara independen daripada proses yang lain (termasuk proses yang menjalankannya). Maka, kita harus melakukan langkah kedua dari pembuatan __Daemon__ dengan code berikut : 
	```bash 
	 	sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }
  	```
	Code pada langkah kedua di atas merupakan pemanggilan fungsi ```setsid()``` sehingga proses akan mendapatkan sebuah __session ID__ baru. 
	Langkah ketiga dari pembuatan __Daemon__ adalah mengubah direktori kerja dengan code di bawah ini :
	```bash
		if ((chdir("/home/xd/Desktop/Modul2/shift")) < 0) {
   exit(EXIT_FAILURE);
  }
  	```
	Direktori kerja yang aktif harus ditempatkan ke tempat yang pasti akan selalu ada dengan menggunakan implementasi fungsi ```chdir```. <br>
	Untuk mencegah terjadinya intervensi dari _user_ dan untuk tujuan pengamanan, maka kita perlu melakukan langkah keempat dari pembuatan __Daemon__ yaitu melakukan penutupan terhadap tiga jenis descriptor standard I/O yaitu ```STDIN``` (standar input), ```STDOUT``` (standar output) dan ```STDERR``` (standar error). Penutupan file descriptor standard I/O ini menggunakan implementasi dari fungsi ```close``` dengan penulisan code di bawah ini :
	```bash
	close(STDIN_FILENO);
  	close(STDOUT_FILENO);
  	close(STDERR_FILENO);
  	```
* Dalam program ini, kami memasukkan jumlah argumen sebanyak 5 (lima), hal ini dikarenakan ```./program/``` terhitung menjadi argumen. Apabila jumlah argumen tersebut kurang dari 5 (lima) ```if(argc != 5)```, maka program tidak akan berjalan ```printf("error");``` sehingga terciptalah code di bawah ini :
	```bash 
	if(argc != 5){
		printf("error");
		return 0;
	}
	```
* Pada program akan diminta _value_ dari __Detik__ ```d```, __Menit__ ```m``` dan __Jam__ ```j```. Oleh karena itu, perlu adanya inisialisasi _value_ awal untuk ketiga variabel tersebut dengan ```0``` seperti code di bawah ini :
	```bash
	d = 0;
	m = 0;
	j = 0;
	```
* Lalu, pada code di bawah ini :
	```bash
	if(d = atoi(argv[1]) != '*' && (atoi(argv[1] > 60 && atoi(argv[1]) < 0);
	if(m = atoi(argv[2]) != '*' && (atoi(argv[1] > 60 && atoi(argv[2]) < 0);
    	if(j = atoi(argv[3]) != '*' && (atoi(argv[1] > 60 && atoi(argv[3]) < 0);
	```
