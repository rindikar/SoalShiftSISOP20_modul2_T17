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
 #### Code :https://github.com/rindikar/SoalShiftSISOP20_modul2_T17/blob/master/Revisi_Soal1.c
 #### Penyelesaian :
 ```bash
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>




int main(int argc, char *argv[]) {
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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }


  if(argc != 5){
    printf("Error");
    return 0;
  }



  d = 0;
  m = 0;
  j = 0;
  
//Detik
	if(isalpha(argv[1][0])){
    		printf("Int boi kalo ga *");
  	}else if(atoi(argv[1]) < 0 || atoi(argv[1]) > 59){
    		printf("Detik cuma 0 - 59");
	}else if(argv[1][0] == '*'){
		d = 0;  	
	}else{
    		d = atoi(argv[1]);
  	}
  
//Menit
  	if(isalpha(argv[2][0])){
    		printf("Int boi kalo ga *");
  	}else if(atoi(argv[2]) < 0 || atoi(argv[2]) > 59){
    		printf("Menit cuma 0 - 59");
	}else if(argv[2][0] == '*'){
		m = 0;
  	}else{
    		m = atoi(argv[2]);
  	}
  
//Jam
  	if(isalpha(argv[3][0])){
    		printf("Int boi kalo ga *");
  	}else if(atoi(argv[3]) < 0 || atoi(argv[3]) > 23){
   		printf("Jam 0 - 23");
	}else if(argv[3][0] == '*'){
		j = 0;
  	}else{
    		j = atoi(argv[3]);
  	}



  while(1) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if((j == tm.tm_hour || j == 0) && (m == tm.tm_min || m == 0) && (d == tm.tm_sec || d == 0)){
      if(fork()==0){
        char *argx[] = {"bash",argv[4], NULL};
        execv("/bin/bash", argx);
      }
    }
    sleep(1);
  }
}

```
* ```int main(int argc, char** argv)``` terdiri atas fungsi ```main```, ```argc``` dan ```argv```.<br> Dalam fungsi ```main``` tersebut, terdapat fungsi ```argc``` atau _Argument Count_ menunjukkan jumlah argumen yang digunakan. <br>
Selain itu, juga terdapat fungsi ```argv``` atau _Argument Vector_ yang menyimpan setiap argumen yang diberikan oleh _user_ dalam bentuk array. Kedua fungsi tersebut dimasukkan ke dalam fungsi ```main``` untuk mengetahui beraoa banyak dan aoa saja parameter yang akan dikirimkan oleh sistem operasi ke program. <br>
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
	Jadi, untuk membuat __Daemon__, kita perlu melakukan _forking_ (men-_swpan_ proses menjadi __Parent Process__ dan __Child Process__) kemudian membunuh __Parent Process__ yang ada. Dengan matinya __Parent Process__, maka sistem operasi akan mengira bahwa __Parent Process__ telah selesai sehingga kita akan mendapatkan sebuah __Child Process__ yang menandakan bahwa kita mendapatkan proses yang hampir bekerja secara _background_. Fungsi ```umask(0)``` akan mengubah mode file untuk memastikan bahwa file tersebut dapat ditulis dan dibaca dengan benar. <br>
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
* Pada program akan diminta argumen dari __Detik__ ```d```, __Menit__ ```m``` dan __Jam__ ```j```. Oleh karena itu, perlu adanya inisialisasi argumen awal untuk ketiga variabel tersebut dengan ```0``` seperti code di bawah ini :
	```bash
	d = 0;
	m = 0;
	j = 0;
	```
* Lalu, pada code di bawah ini :
	```bash
	if(d = atoi(argv[1]) != '*' && (atoi(argv[1] > 60 && atoi(argv[1]) < 0);
	```
	Terdapat fungsi```argv[1]``` yang akan menyimpan argument __Detik__ kemudian dianjutkan dengan pengecekan argumen yang tersimpan dalam variabel __Detik__ ```d```. Pengecekan pertama yakni  ```argv[1]) != '*'``` apakah argumen yang tersimpan dalam variabel __Detik__ merupakan karakter ```*``` dan apakah argumen yang tersimpan dalam variabel __Detik__ merupakan bilangan diantara 0 hingga 60 ```(atoi(argv[1] > 60 && atoi(argv[1]) < 0```. Penggunaan ```atoi``` berfungsi untuk mengonversi nilai _string_ menjadi bilangan bertipe _integer_. <br>
* Kemudian , pada code di bawah ini :
	```bash
	if(m = atoi(argv[2]) != '*' && (atoi(argv[1] > 60 && atoi(argv[2]) < 0);
	```
	Terdapat fungsi```argv[2]``` yang akan menyimpan argument __Menit__ kemudian dianjutkan dengan pengecekan argumen yang tersimpan dalam variabel __Menit__ ```m```. Pengecekan yang dilakukan yakni  ```argv[2]) != '*'``` apakah argumen yang tersimpan dalam variabel __Menit__ merupakan karakter ```*``` dan apakah argumen yang tersimpan dalam variabel __Menit__ merupakan bilangan diantara 0 hingga 60 ```(atoi(argv[2] > 60 && atoi(argv[2]) < 0```. Penggunaan ```atoi``` berfungsi untuk mengonversi nilai _string_ menjadi bilangan bertipe _integer_. <br>
* Dan pengecekan terakhir, dengan code di bawah ini :
	```bash
	if(j = atoi(argv[3]) != '*' && (atoi(argv[1] > 60 && atoi(argv[3]) < 0);
	```
	Terdapat fungsi```argv[3]``` yang akan menyimpan argument __Jam__ kemudian dianjutkan dengan pengecekan argumen yang tersimpan dalam variabel __Jam__ ```j```. Pengecekan yang dilakukan yakni  ```argv[3]) != '*'``` apakah argumen yang tersimpan dalam variabel __Menit__ merupakan karakter ```*``` dan apakah argumen yang tersimpan dalam variabel __Menit__ merupakan bilangan diantara 0 hingga 60 ```(atoi(argv[3] > 60 && atoi(argv[3]) < 0```. Penggunaan ```atoi``` berfungsi untuk mengonversi nilai _string_ menjadi bilangan bertipe _integer_. <br>
* Pada ```while(1)``` akan membuat sebuah looping (loop utama) dikarenakan __Daemon__ akan bekerja dalam jangka waktu tertentu. <br>
* Pada code berikut :
	```bash
	time_t t = time(NULL); 
	struct w tm = *localtime(&t)
	```
	maka ```time_t t = time(NULL);```akan menyimpan waktu saat ini ```time(NULL)``` ke dalam variabel ```t```. <br>
	Sedangkan ```struct w tm = *localtime(&t)``` akan mengonversi nilai dalam variabel ```t``` ke waktu yang dinyatakan sebagai _localtime_. <br>
* Code berikutnya yakni :
	```bash
	if((j == w.tm_j || j == 0) && (m == w.tm_m || m == 0) && (d == w.tm_d || d == 0)) {
      	if (fork()==0)
	execl("/bin/bash", "bash", argv[5], NULL);}
	sleep(1);
	```
	akan melakukan pengecekan ```if((j == w.tm_j || j == 0) && (m == w.tm_m || m == 0) && (d == w.tm_d || d == 0))``` apakah nilai yang tersimpan dalam variabel __Jam__ ```j``` bernilai sama dengan nilai yang tersimpan dalam variabel __Jam__ pada _localtime_ atau nilai yang tersimpan dalam variabel __Jam__ adalah ```0``` dan apakah nilai yang tersimpan dalam variabel __Menit__ ```m``` bernilai sama dengan nilai yang tersimpan dalam variabel __Menit__ pada _localtime_ atau nilai yang tersimpan dalam variabel __Menit__ adalah ```0``` dan juga apakah nilai yang tersimpan dalam variabel __Detik__ ```d``` bernilai sama dengan nilai yang tersimpan dalam variabel __Detik__ pada _localtime_ atau nilai yang tersimpan dalam variabel __Detik__ adalah ```0```. Jika kondisi tersebut terpenuhi, maka program akan melakukan _Fork_ ```if (fork()==0)```. <br>
	_Fork_ tersebut akan menjalankan _bash_ pada script yang dinputkan oleh _user_ yang berada pada direktori ```/bin/bash```
	Proses looping yang dibuat oleh fungsi ```while(1)``` ini akan memberhentikan program sejenak ```sleep(1);``` selama 1 detik sebelum melakukan proses looping kembali.
### Soal 3
Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan (multiprocessing).
* #### Soal 3A
  Program buatan jaya harus bisa membuat dua direktori di __“/home/[USER]/modul2/”__. Direktori yang pertama diberi nama __“indomie”__, lalu lima detik kemudian membuat direktori yang kedua bernama __“sedaap”__.
* #### Soal 3B
  Kemudian program tersebut harus meng-ekstrak file __jpg.zip__ di direktori __“/home/[USER]/modul2/”__. Setelah tugas sebelumnya selesai, ternyata tidak hanya itu tugasnya.
* #### Soal 3C
  Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di dalam direktori __“home/[USER]/modul2/jpg/”__) harus dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke __“/home/[USER]/modul2/sedaap/”__ dan semua direktori harus dipindahkan ke __“/home/[USER]/modul2/indomie/”__.
* #### Soal 3D
  Untuk setiap direktori yang dipindahkan ke __“/home/[USER]/modul2/indomie/”__ harus membuat dua file kosong. File yang pertama diberi nama __“coba1.txt”__, lalu 3 detik kemudian membuat file bernama __“coba2.txt”__. (contoh :__“/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”__).
 #### Code : https://github.com/rindikar/SoalShiftSISOP20_modul2_T17/blob/master/soal3.c
 #### Penyelesaian :
 ```bash
 #include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(){
pid_t child_id1, child_id2;

int proses;
child_id1 = fork();

	if (child_id == 0)	{
	sleep(3);
	char *argv[3] = {"mkdir", "sedaap", NULL};
	execv("/bin/mkdir", argv);
	  }
	else {
	child_id2 = fork();
	if (child_id2 == 0)	{
	char *argv[3] = {"unzip", "jpg.zip", NULL};
	execv("/usr/bin/unzip", argv);
	else {
	char *argv[3] = {"mkdir", "indomie", NULL};
	execv("/bin/mkdir", argv);
	while ((wait($proses)) > 0);
	     }
}
}
```
* Di awal tertulis code ```pid_t child_id1, child_id2;``` ini merupakan pendeklarasian variabel __child_id1__ dan __child_id2__. Kedua variabel ini akan menyimpan ID dari __Child Process__.
* Dilanjutkan dengan 
	```bash
	int proses;
	child_id1 = fork();

	if (child_id == 0)	{
	sleep(3);
	char *argv[3] = {"mkdir", "sedaap", NULL};
	execv("/bin/mkdir", argv);
	  }
	```
yang merupakan fungsi untuk membuat __Child Process yang Pertama__. ```child_id1 = fork();``` menunjukkan bahwa PID yang dihasilkan dari proses _fork_ akan disimpan dalam variabel ```child_id1```.<br>
Pada __Child Process yang Pertama__ akan membuat direktori baru dengan nama "sedaap" dengan menggunakan code berikut ```char *argv[3] = {"mkdir", "sedaap", NULL};```. Dalam __Child Process yang Pertama__ ini menggunakan fungsi ```exec``` yang ditunjukkan dari code ```execv("/bin/mkdir", argv);```. <br>
__Parent Process__ akan menunggu proses pembuatan direktori baru tersebut selesai, kemudian program akan diberhentikan sejenak ```sleep(3);``` selama 3 detik sebelum __Parent Process__ membuat __Child Process__ kembali.
* Setelah __Child Process yang Pertama__ telah selesai dilakukan, maka dilanjutkan dengan membuat __Child Process yang Kedua__.
	```bash
	else {
	child_id2 = fork();
	if (child_id2 == 0)	{
	char *argv[3] = {"unzip", "jpg.zip", NULL};
	execv("/usr/bin/unzip", argv);
	``` 
	```child_id2 = fork();``` akan melakukan penyimpanan PID yang dihasilkan dari proses _fork_ ke dalam variabel ```child_id2```.<br>
	Berbeda dengan proses yang dilakukan oleh __Child Process yang Pertama__, pada __Child Process yang Kedua__ dilakukan proses meng-ekstrak file __jpg.zip__. <br> 
	Dalam pembuatan __Child Process yang Kedua__ juga menggunakan fungsi ```exec``` dengan code berikut ```execv("/usr/bin/unzip", argv);```
* Kemudian, hasil dari ekstrakan tersebut nantinya akan dipindahkan ke direktori baru bernama ```"indomie```", maka kita perlu membuat direktori baru tersebut ```char *argv[3] = {"mkdir", "indomie", NULL};```

