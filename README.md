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
