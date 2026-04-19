#include "Polynomial.h"

/* --- Konstruktor dan Inisialisasi --- */
/*
   Fungsi: CreatePolynomial
   Deskripsi:
     Menginisialisasi sebuah polinomial P dengan derajat tertentu (menyiapkan wadah kosong).
     Semua koefisien pada polinomial diinisialisasi ke nilai 0 (belum ada energi yang dimasukkan).
   I.S. (Initial State): P belum terdefinisi
   F.S. (Final State): P terdefinisi dengan nilai degree yang diberikan, dan seluruh koefisien bernilai 0.
   Contoh:
     Polynomial P;
     CreatePolynomial(&P, 3);
     // Hasil: P.degree = 3, dan P.coef[0..3] semuanya bernilai 0.
*/
void CreatePolynomial(Polynomial *P, int degree) {
    P->degree = degree;
    for(int i = 0; i <= degree; i++) {
        P->coef[i] = 0;
    }
}

/* --- Input/Output Polinomial --- */
/*
   Fungsi: ReadPolynomial
   Deskripsi:
     Membaca input sandi polinomial dari Grunkle Ford. Proses input dilakukan dengan langkah berikut:
       1. Membaca nilai derajat polinomial (tingkat bahaya dimensi).
          Nilai derajat menentukan berapa banyak suku (pangkat) yang akan dibaca, dari 0 hingga derajat tersebut.
       2. Membaca koefisien (dalam bentuk integer) untuk setiap pangkat dari 0 hingga derajat yang telah ditentukan.
   I.S.: P sembarang.
   F.S.: P terdefinisi sesuai dengan input pengguna.
*/
void ReadPolynomial(Polynomial *P) {
    int d, i;
    scanf("%d", &d);
    CreatePolynomial(P, d);
    for(i = 0; i <= d; i++) {
        scanf("%d", &P->coef[i]);
    }
}

/*
   Fungsi: WritePolynomial
   Deskripsi:
     Menampilkan polinomial ke layar monitor portal dalam format standar, misalnya:
       3x^3 + 2x^2 - x + 5
     Polinomial dicetak dari pangkat tertinggi ke pangkat 0. Koefisien dengan nilai 0 dilewati
     agar tampilan output lebih rapi dan tidak membingungkan Dipper.
   I.S.: P terdefinisi.
   F.S.: Polinomial ditampilkan pada layar.
*/
void WritePolynomial(Polynomial P) {
    int i;
    
    // 1. Geser P.degree ke suku pertama yang bukan nol
    // Ini teknik "membersihkan" derajat tanpa nambah variabel baru
    while (P.degree > 0 && P.coef[P.degree] == 0) {
        P.degree--;
    }

    // 1. MISS: Tambahkan return setelah print degree 0
    // Biar kalau derajat 0, angkanya nggak diprint dua kali oleh loop for di bawahnya.
    if(P.degree == 0) {
        printf("%d", P.coef[0]);
        return; 
    }
    
    else {
        for(i = P.degree; i >= 0; i--) {
        // 2. MISS: Kalau koefisien 0, harus di-skip total!
        // Tanpa ini, polinomial "0x^2 + 5x" bakal berantakan.
        if (P.coef[i] == 0) continue;

        if(i == P.degree) {
            // 3. MISS: Suku pertama (i == P.degree) nggak boleh ada angka 1 atau -1 eksplisit
            // Contoh: Harusnya "x^3", bukan "1x^3"
            if(P.coef[i] == 1) printf("x^%d", i);
            else if(P.coef[i] == -1) printf("-x^%d", i);
            else printf("%dx^%d", P.coef[i], i);
        }
        else if(i == 1) {
            if(P.coef[i] < 0) {
                // 4. MISS: Suku tengah x pangkat 1 koefisien -1
                if(P.coef[i] == -1) printf(" - x");
                else printf(" - %dx", abs(P.coef[i]));
            }
            else if(P.coef[i] > 0) {
                if(P.coef[i] == 1) printf(" + x");
                else printf(" + %dx", P.coef[i]);
            }
        }
        else if(i == 0) {
            if(P.coef[i] < 0) printf(" - %d", abs(P.coef[i]));
            else if(P.coef[i] > 0) printf(" + %d", P.coef[i]);
        }
        else {
            if(P.coef[i] < 0) {
                if(P.coef[i] == -1) printf(" - x^%d", i);
                else printf(" - %dx^%d", abs(P.coef[i]), i);
            } 
            else if(P.coef[i] > 0) {
                if(P.coef[i] == 1) printf(" + x^%d", i);
                else printf(" + %dx^%d", P.coef[i], i);
            }
        }
        }
    }
    
}

/* --- Operasi Aritmatika Polinomial --- */
/*
   Fungsi: AddPolynomial
   Deskripsi:
     Menjumlahkan dua buah sandi polinomial P1 dan P2 (Interferensi Energi). 
     Proses penjumlahan dilakukan dengan menjumlahkan koefisien pada pangkat yang sama. 
     Jika salah satu polinomial memiliki derajat yang lebih rendah, koefisien yang tidak ada dianggap sebagai 0.
   I.S.: P1 dan P2 terdefinisi.
   F.S.: Mengembalikan polinomial hasil penjumlahan P1 + P2, dengan derajat disesuaikan berdasarkan
         koefisien tertinggi yang bukan nol.
*/
Polynomial AddPolynomial(Polynomial P1, Polynomial P2) {
    Polynomial R;
    int i;
    // Cari derajat tertinggi antara P1 dan P2
    int maxDeg = (P1.degree > P2.degree) ? P1.degree : P2.degree;

    CreatePolynomial(&R, maxDeg);

    for(i = 0; i <= maxDeg; i++) {
        int c1 = (i <= P1.degree) ? P1.coef[i] : 0;
        int c2 = (i <= P2.degree) ? P2.coef[i] : 0;
        R.coef[i] = c1 + c2;
    }

    return R;
}

/*
   Fungsi: MultiplyPolynomial
   Deskripsi:
     Mengalikan dua buah polinomial P1 dan P2 (Reaksi Berantai). Setiap koefisien pada P1 dikalikan 
     dengan setiap koefisien pada P2, dan hasil perkalian ditempatkan pada pangkat yang merupakan 
     penjumlahan indeks kedua koefisien yang dikalikan.
   I.S.: P1 dan P2 terdefinisi.
   F.S.: Mengembalikan polinomial hasil perkalian P1 * P2.
*/
Polynomial MultiplyPolynomial(Polynomial P1, Polynomial P2) {
    Polynomial R;
    int i, j;

    CreatePolynomial(&R, P1.degree + P2.degree);
    for(i = 0; i <= P1.degree; i++)
        for(j = 0; j <= P2.degree; j++)
            R.coef[i+j] += P1.coef[i] * P2.coef[j];

    return R;
}

/*
   Fungsi: EvaluatePolynomial
   Deskripsi:
     Mengevaluasi nilai polinomial P untuk suatu nilai x tertentu (Uji Coba Stabilitas Portal).
     Karena koefisien bertipe integer dan x juga merupakan integer,
     maka hasil evaluasi juga berupa integer.
   I.S.: P terdefinisi dan x merupakan bilangan integer.
   F.S.: Mengembalikan nilai hasil evaluasi P(x) dalam bentuk integer.
*/
// fungsi bantuan
int pangkat(int a, int b) {
    if(b == 0) return 1;
    return a * pangkat(a, b-1);
}

int EvaluatePolynomial(Polynomial P, int x) {
    int i, result = 0;

    for(i = P.degree; i >= 0; i--) {
        result += P.coef[i] * pangkat(x, i);
    }

    return result;
}

/*
   Fungsi: DerivativePolynomial
   Deskripsi:
     Menghitung turunan pertama dari polinomial P (Penyusutan Energi Seiring Waktu). 
     Jika polinomial didefinisikan sebagai
       P(x) = a_n*x^n + ... + a_1*x + a_0,
     maka turunan P'(x) adalah:
       P'(x) = n*a_n*x^(n-1) + (n-1)*a_(n-1)*x^(n-2) + ... + 1*a_1.
     Apabila P merupakan polinomial konstan (degree 0), maka turunan yang dihasilkan adalah 0.
   I.S.: P terdefinisi.
   F.S.: Mengembalikan polinomial yang merupakan turunan pertama dari P.
*/
Polynomial DerivativePolynomial(Polynomial P) {
    Polynomial R;
    int i;

    if(P.degree == 0) {
        CreatePolynomial(&R, 0); // Turunan konstanta adalah 0
        return R;
    }

    CreatePolynomial(&R, P.degree - 1);
    for(i = 1; i <= P.degree; i++) {
        // Rumus turunan: a * n * x^(n-1)
        R.coef[i-1] = P.coef[i] * i;
    }

    return R;
}

