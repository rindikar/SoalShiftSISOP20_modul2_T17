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
* ```int main(int argc, char *argv[])``` menunjukkan bahwa di dalam fungsi ```main``` terdapat fungsi ```argc``` (_Argument Count)_
yang menunjukkan jumlah argumen yang digunakan. Selain itu, juga terdapat fungsi ```argv``` _(Argument Vector)_ yang menyimpan setiap argumen yang diberikan oleh user dalam bentuk array. Kedua fungsi tersebut dimasukkan ke dalam fungsi ```main``` untuk mengetahui berapa banyak dan apa saja parameter yang akan dikirimkan oleh sistem operasi ke program. <br>
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
	Jadi, untuk membuat __Daemon__, kita perlu melakukan _forking_ (men-_swpan_ proses menjadi __Parent Process__ dan __Child Process__) kemudian membunuh __Parent Process__ yang ada. Dengan matinya __Parent Process__, maka sistem operasi akan mengira bahwa __Parent Process__ telah selesai sehingga kita akan mendapatkan sebuah __Child Process__ yang menandakan bahwa kita mendapatkan proses yang hampir bekerja secara _background_. Fungsi ```umask(0)``` akan mengubah mode file untuk memastikan bahwa file tersebut dapat ditulis dan dibaca dengan benar. 
* Perlu diketahui bahwa __Daemon__ harus bekerja secara independen daripada proses yang lain (termasuk proses yang menjalankannya). Maka, kita harus melakukan langkah kedua dari pembuatan __Daemon__ dengan code berikut : 
	```bash 
	 	sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }
  	```
	Code pada langkah kedua di atas merupakan pemanggilan fungsi ```setsid()``` sehingga proses akan mendapatkan sebuah __session ID__ baru. 
	Langkah ketiga dari pembuatan __Daemon__ adalah mengubah direktori kerja dengan code di bawah ini :
	```bash
		if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }
  	```
	Direktori kerja yang aktif harus ditempatkan ke tempat yang pasti akan selalu ada dengan menggunakan implementasi fungsi ```chdir```. Direktori kerja yang kami pakai disini yakni direktori _root_ `"/"` karena _root_ akan selalu hidup ssat sistem operasi kita berjalan. 
* Dalam program ini, kami memasukkan jumlah argumen sebanyak 5 (lima) argumen.
	```bash
	if(argc != 5){
    printf("Error");
    return 0;
  }
  	```
	Hal tersebut dikarenakan ```./program/``` terhitung menjadi argumen. Apabila jumlah argumen kurang dari 5 (lima) ```if(argc != 5)```, maka program tidak akan berjalan ```printf("Error")```.
* Pada program akan diminta argumen dari __Detik__ ```d```, __Menit__ ```m``` dan __Jam__ ```j```. Oleh karena itu, perlu adanya inisialisasi argumen awal untuk ketiga variabel tersebut dengan ```0``` seperti code di bawah ini :
	```bash
	d = 0;
	m = 0;
	j = 0;
	```
* Kemudian, dilanjutkan dengan proses pengecekan argumen yang tersimpan dalam variabel __Detik__ ```d```.
	```bash
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

	```
	Terdapat fungsi```argv[1]``` yang akan menyimpan argumen __Detik__ ```d``` kemudian dianjutkan dengan pengecekan argumen yang tersimpan dalam variabel __Detik__ ```d```. Pengecekan yang dilakukan adalah pengecekan terhadap apakah argumenyang tersimpan dalam variabel __Detik__ ```d``` merupakan bilangan diantara 0 hingga 59 ```if(atoi(argv[1]) < 0 || atoi(argv[1]) > 59)```, hal ini dikarenakan 1 menit terdiri dari 60 detik. Selain itu, juga dilakukan pengecekan terhadap apakah argumen yang tersimpan dalam variabel __Detik__ ```d``` merupakan karakter _bintang_ ```if(argv[1][0] == '*')```, jika kondisi ini terpenuhi maka argumen ```0``` akan masuk dalam variabel __Detik__ ```d```. Penggunaan ```atoi``` berfungsi untuk mengonversi nilai _string_ menjadi bilangan bertipe _integer_. Jika kondisi-kondisi tersebut tidak terpenuhi, maka argumen yang tersimpan dalam variabel ```argv[1]``` akan dikonversi menjadi nilai bertipe integer yang akan disimpan dalam variabel __Detik__ ```d```.
* Kemudian, dilanjutkan dengan proses pengecekan argumen yang tersimpan dalam variabel __Menit__ ```m```. :
	```bash
	 if(atoi(argv[2]) < 0 || atoi(argv[2]) > 59)
	```
	Terdapat fungsi```argv[2]``` yang akan menyimpan argumen __Menit__ ```m``` kemudian dianjutkan dengan pengecekan argumen yang tersimpan dalam variabel __Menit__ ```m```. Pengecekan yang dilakukan adalah pengecekan terhadap apakah argumenyang tersimpan dalam variabel __Menit__ ```m``` merupakan bilangan diantara 0 hingga 59 ```if(atoi(argv[2]) < 0 || atoi(argv[2]) > 59)```, hal ini dikarenakan 1 jam terdiri dari 60 menit. Selain itu, juga dilakukan pengecekan terhadap apakah argumen yang tersimpan dalam variabel __Menit__ ```m``` merupakan karakter _bintang_ ```if(argv[2][0] == '*')```, jika kondisi ini terpenuhi maka argumen ```0``` akan masuk dalam variabel __Menit__ ```m```. Penggunaan ```atoi``` berfungsi untuk mengonversi nilai _string_ menjadi bilangan bertipe _integer_. Jika kondisi-kondisi tersebut tidak terpenuhi, maka argumen yang tersimpan dalam variabel ```argv[2]``` akan dikonversi menjadi nilai bertipe integer yang akan disimpan dalam variabel __Menit__ ```m```.
* Pengecekan terakhir yakni proses pengecekan argumen yang tersimpan dalam variabel __Jam__ ```j```
	```bash
	if(atoi(argv[3]) < 0 || atoi(argv[3]) > 23)
	```
	Terdapat fungsi```argv[3]``` yang akan menyimpan argumen __Jam__ ```j``` kemudian dianjutkan dengan pengecekan argumen yang tersimpan dalam variabel __Jam__ ```j```. Pengecekan yang dilakukan adalah pengecekan terhadap apakah argumenyang tersimpan dalam variabel __Jam__ ```j``` merupakan bilangan diantara 0 hingga 59 ```if(atoi(argv[3]) < 0 || atoi(argv[3]) > 23)```, hal ini dikarenakan jam dimulai dari 0 (12 malam) hingga 23 (11 malam). Selain itu, juga dilakukan pengecekan terhadap apakah argumen yang tersimpan dalam variabel __Jam__ ```j``` merupakan karakter _bintang_ ```if(argv[3][0] == '*')```, jika kondisi ini terpenuhi maka argumen ```0``` akan masuk dalam variabel __Jam__ ```j```. Penggunaan ```atoi``` berfungsi untuk mengonversi nilai _string_ menjadi bilangan bertipe _integer_. Jika kondisi-kondisi tersebut tidak terpenuhi, maka argumen yang tersimpan dalam variabel ```argv[3]``` akan dikonversi menjadi nilai bertipe integer yang akan disimpan dalam variabel __Jam__ ```j```.
* Proses dilanjutkan dengan code di bawah ini :
	```bash
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
	```
	Dari code di atas, maka pada ```while(1)``` akan membuat sebuah _loopimg_ (loop utama) dikarenakan __Daemon__ akan bekerja dalam jangka waktu tertentu. <br>
	Daalam proses _looping_ akan terjadi penyimpanan waktu saat ini. Hal ini di-code-kan dengan
	```bash
	time_t t = time(NULL);
    	struct tm tm = *localtime(&t);
	```
	```time_t t = time(NULL)``` akan menyimpan waktu saat ini ```time(NULL)``` ke dalam variabel ```t```. Sedangkan ```struct tm tm = *localtime(&t)``` akan mengonversi nilai dalam variabel ```t``` ke waktu yang dinyatakan sebagai _localtime_.
* Lalu, pada code berikut ini akan melakukan pengecekan apakah nilai yang tersimpan dalam variabel __Jam__ ```j``` bernilai sama dengan nilai yang tersimpan dalam variabel __Jam__ pada _localtime_ atau nilai yang tersimpan dalam variabel __Jam__ adalah ```0``` dan  apakah nilai yang tersimpan dalam variabel __Menit__ ```m``` bernilai sama dengan nilai yang tersimpan dalam variabel __Menit__ pada _localtime_ atau nilai yang tersimpan dalam variabel __Menit__ adalah ```0``` dan juga  apakah nilai yang tersimpan dalam variabel __Detik__ ```d``` bernilai sama dengan nilai yang tersimpan dalam variabel __Detik__ pada _localtime_ atau nilai yang tersimpan dalam variabel __Detik__ adalah ```0```
	```bash
	if((j == tm.tm_hour || j == 0) && (m == tm.tm_min || m == 0) && (d == tm.tm_sec || d == 0)){
	```
	Jika kondisi tersebut terpenuhi, maka program akan melakukan _Fork_ ```if(fork()==0)```. _Fork_ tersebut akan menjalankan _bash_ pada script yang dinputkan oleh _user_ yang berada pada direktori ```/bin/bash```. Proses looping yang dibuat oleh fungsi ```while(1)``` ini akan memberhentikan program sejenak ```sleep(1);``` selama 1 detik sebelum melakukan proses looping kembali.
* Untuk menjalankan _crontab_ tersebut, kita perlu membuat sebuah _script bash_ yang kami beri nama __test.sh__ yang berisikan fungsi untuk mengambil waktu saat ini agar dapat ditampilkan dalam suatu file __s1.txt__
	```bash
	#!/bin/bash
	date >> s1.txt
	```
#### Output :
![01-fixrevisi](https://user-images.githubusercontent.com/49342639/77215591-6932ac00-6b47-11ea-84f5-b8ba78d5d23a.png)

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
 #### Code : https://github.com/rindikar/SoalShiftSISOP20_modul2_T17/blob/master/Revisi_Soal3.c
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
* Di awal, dibuat sebuah fungsi ```struct stat ( ) yang akan mendapatkan informasi dari sebuah file atau direktori.
	```bash
	int Status(const char *path) { 
	struct stat pathDir; 
	stat(path, &pathDir); 
	return S_ISDIR(pathDir.st_mode); }
	```
	```stat(path, &pathDir)``` akan melakukan _stat_ dengan argumen path dari sebuah file atau direktori. ```S_ISDIR``` akan melakukan pengecekan apakah file tersebut berupa direktori atau bukan direktori.
* Kemudian, proses melakukan perubahan direktori menuju ke direktori ```("/home/xd/Desktop/Modul2/shift/")``` menggunakan code berikut 
	```bash
	if (pidB > 0 && pidC > 0){  
  while ((wait(&status)) > 0); 
  DIR *open;  
  struct dirent *directory; 
  chdir("/home/xd/Desktop/Modul2/shift/");  
  open = opendir(".");
  	```
* Setelah itu, apabila kedua direktori sudah tersedia maka program akan dilanjutkan tetapi jika kedua direktori belum tersedia maka program akan memindahkan folder ke dalam folder indomie.
	```bash
	if (open){  
     	  while ((directory = readdir(open)) != NULL){
	    if(strcmp(directory->d_name, ".") == 0 || strcmp(directory->d_name, "..") == 0)
	      continue;  
	      if(Status(directory->d_name)){
		if(fork() == 0){  
		  char file[700];
		  sprintf(file,"/home/xd/Desktop/Modul2/shift/%s",directory->d_name);
		  char* move[] = {"mv", file,"/home/xd/Desktop/Modul2/shift/indomie/", NULL};
		        execv("/bin/mv", move);
          		} 
	```
* Setelah program memindahkan folder ke dalam folder indomie, maka program akan membuat file __coba1.txt__ ke setiap folder. Lalu, program akan diberhentikan sejenak selama 3 detik dan dilanjutkan dengan membuat file __coba2.txt__
	```bash 
	else{
            	  while ((wait(&status)) > 0); 
            	  if(fork() == 0)
			{
            	  	if(fork() == 0)
			{
            	    	  char cobadulu[700];
            	    	  FILE *file;
		          sprintf(cobadulu,"/home/xd/Desktop/Modul2/shift/indomie/%s/coba1.txt",directory->d_name);
		       	  file = fopen(cobadulu, "w");
		          fclose(file);
		        }
	```
* Proses terakhir adalah file yang masih tersisa akan mengalami pemindahan secara langsung ke folder sedaap yang berisi file berupa text dan gambar. 
	```bash
	else
			{
		           while ((wait(&status)) > 0);
		           sleep(3);
		           char cobalagi[700];
		           FILE *file;
		           sprintf(cobalagi,"/home/xd/Desktop/Modul2/shift/indomie/%s/coba2.txt",directory->d_name);
		           file = fopen(cobalagi, "w");
		           fclose(file);
		           exit(0);
		        } 
	```
* Dalam program ini dibutuhkan beberapa folder yang harus dibuat. Code berikut merupakan code untuk membuat folder __indomie__ :
	```bash
	 char *masakindomie[] = {"mkdir", "-p","/home/xd/Desktop/Modul2/shift/indomie", NULL};
     	 execv("/bin/mkdir", masakindomie); 
	 ```
* Selain itu, diperlukan juga untuk membuat folder __sedaap__ dengan code di bawah ini :
	```bash
	char *masaksedaap[] = {"mkdir", "-p","/home/xd/Desktop/Modul2/shift/sedaap", NULL}; 
      	execv("/bin/mkdir", masaksedaap); 
	```
* Sedangkan, untuk meng-_unzip_ file __jpg.zip__ menggunakan code di bawah ini :
	```bash
	char* ekstrak[] = {"unzip", "-oq","/home/xd/Desktop/Modul2/shift/jpg.zip", NULL};
    	execv("/usr/bin/unzip", ekstrak);
	```
### Output :
![03-fixrevisi 01](https://user-images.githubusercontent.com/49342639/77226079-235a0000-6ba8-11ea-886f-a1e6bd3e294a.jpg)
![03-fixrevisi 02](https://user-images.githubusercontent.com/49342639/77226112-5c927000-6ba8-11ea-8318-28858fb084d9.jpg)

### Kendala :
1. SISOP MANTAPPU membuat otak sangat bekerja karena soal setinggi gunung (kemungkinan lebih tinggi dari gunung).

	
	
