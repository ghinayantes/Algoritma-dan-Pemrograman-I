/*
 * adt_time.c
 * Implementasi ADT TIME dalam bahasa C
 * Mata Kuliah: IF1210 Algoritma dan Pemrograman 1
 */

#include <stdio.h>   /* Untuk fungsi input/output: printf, scanf */
#include <stdbool.h> /* Untuk tipe data bool, true, false */

/* =========================================================
 * DEFINISI TIPE DATA (ADT TIME)
 * ========================================================= */

/* Mendefinisikan struct Time dengan tiga komponen integer */
typedef struct {
    int hours;   /* Jam:  0 <= hours   <= 23 */
    int minutes; /* Menit: 0 <= minutes <= 59 */
    int seconds; /* Detik: 0 <= seconds <= 59 */
} Time;

/* =========================================================
 * DEKLARASI PROTOTIPE FUNGSI
 * (Dideklarasikan lebih dulu agar bisa saling memanggil)
 * ========================================================= */

void  CreateTime     (Time *T, int h, int m, int s);
int   GetHours       (Time T);
int   GetMinutes     (Time T);
int   GetSeconds     (Time T);
void  SetHours       (Time *T, int newH);
void  SetMinutes     (Time *T, int newM);
void  SetSeconds     (Time *T, int newS);
bool  IsValidTime    (int h, int m, int s);
void  ReadTime       (Time *T);
void  PrintTime      (Time T);
int   TimeToSeconds  (Time T);
Time  SecondsToTime  (int n);
bool  IsEQTime       (Time T1, Time T2);
bool  IsGTTime       (Time T1, Time T2);
bool  IsLTTime       (Time T1, Time T2);
Time  NextSecond     (Time T);
Time  PrevSecond     (Time T);
int   Difference     (Time start, Time end);

/* =========================================================
 * KONSTRUKTOR
 * ========================================================= */

/*
 * CreateTime: Membentuk/mengisi nilai Time dari komponen h, m, s.
 * Menggunakan pointer agar perubahan T di dalam fungsi
 * terrefleksikan di pemanggil (seperti "output" di notasi algoritmik).
 */
void CreateTime(Time *T, int h, int m, int s) {
    T->hours   = h; /* Mengisi field hours dengan nilai h   */
    T->minutes = m; /* Mengisi field minutes dengan nilai m */
    T->seconds = s; /* Mengisi field seconds dengan nilai s */
}

/* =========================================================
 * SELEKTOR (Getter)
 * ========================================================= */

/* Mengembalikan nilai jam (hours) dari T */
int GetHours(Time T) {
    return T.hours;   /* Mengakses field hours dari struct T */
}

/* Mengembalikan nilai menit (minutes) dari T */
int GetMinutes(Time T) {
    return T.minutes; /* Mengakses field minutes dari struct T */
}

/* Mengembalikan nilai detik (seconds) dari T */
int GetSeconds(Time T) {
    return T.seconds; /* Mengakses field seconds dari struct T */
}

/* =========================================================
 * MODIFIER (Setter)
 * ========================================================= */

/* Mengubah komponen hours dari T menjadi newH */
void SetHours(Time *T, int newH) {
    T->hours = newH;   /* Menulis nilai baru ke field hours via pointer */
}

/* Mengubah komponen minutes dari T menjadi newM */
void SetMinutes(Time *T, int newM) {
    T->minutes = newM; /* Menulis nilai baru ke field minutes via pointer */
}

/* Mengubah komponen seconds dari T menjadi newS */
void SetSeconds(Time *T, int newS) {
    T->seconds = newS; /* Menulis nilai baru ke field seconds via pointer */
}

/* =========================================================
 * VALIDASI
 * ========================================================= */

/*
 * IsValidTime: Mengecek apakah nilai h, m, s membentuk Time yang valid.
 * Dipakai SEBELUM memanggil CreateTime.
 */
bool IsValidTime(int h, int m, int s) {
    /* Mengembalikan true hanya jika ketiga syarat terpenuhi sekaligus */
    return (h >= 0 && h <= 23) &&  /* Jam harus 0-23  */
           (m >= 0 && m <= 59) &&  /* Menit harus 0-59 */
           (s >= 0 && s <= 59);    /* Detik harus 0-59 */
}

/* =========================================================
 * OPERASI BACA / TULIS
 * ========================================================= */

/*
 * ReadTime: Membaca input jam dari pengguna secara berulang
 * sampai nilai yang dimasukkan valid.
 * Menggunakan pointer agar T terisi setelah fungsi selesai.
 */
void ReadTime(Time *T) {
    int h, m, s;  /* Variabel lokal penampung input sementara */

    /* Loop "iterate...stop" dari notasi algoritmik → do-while di C */
    do {
        printf("Masukkan jam (0-23)   : "); /* Prompt input jam    */
        scanf("%d", &h);                    /* Baca nilai jam      */
        printf("Masukkan menit (0-59) : "); /* Prompt input menit  */
        scanf("%d", &m);                    /* Baca nilai menit    */
        printf("Masukkan detik (0-59) : "); /* Prompt input detik  */
        scanf("%d", &s);                    /* Baca nilai detik    */

        /* Jika input tidak valid, tampilkan pesan error dan ulangi */
        if (!IsValidTime(h, m, s)) {
            printf("Masukan Time tidak tepat. Ulangi.\n\n");
        }
    } while (!IsValidTime(h, m, s)); /* Ulangi selama belum valid */

    CreateTime(T, h, m, s); /* Bentuk Time dari komponen yang sudah valid */
}

/*
 * PrintTime: Mencetak nilai T ke layar dengan format HH:MM:SS
 * T di sini tidak diubah sehingga tidak perlu pointer (cukup pass by value).
 */
void PrintTime(Time T) {
    /* %02d → cetak integer minimal 2 digit, diawali nol jika perlu */
    printf("%02d:%02d:%02d",
           GetHours(T),   /* Ambil jam    */
           GetMinutes(T), /* Ambil menit  */
           GetSeconds(T)  /* Ambil detik  */
    );
}

/* =========================================================
 * OPERASI KONVERSI
 * ========================================================= */

/*
 * TimeToSeconds: Mengkonversi Time T ke total jumlah detik.
 * Rumus: detik_total = 3600*jam + 60*menit + detik
 * Nilai maksimum: 3600*23 + 60*59 + 59 = 86399
 */
int TimeToSeconds(Time T) {
    return 3600 * GetHours(T)   /* Jam dikonversi ke detik   */
         +   60 * GetMinutes(T) /* Menit dikonversi ke detik */
         +        GetSeconds(T); /* Detik sudah dalam satuan detik */
}

/*
 * SecondsToTime: Mengkonversi total detik n ke Time.
 * Prekondisi: 0 <= n <= 86399
 * Algoritma:
 *   jam    = n div 3600
 *   menit  = (n mod 3600) div 60
 *   detik  = n mod 60
 */
Time SecondsToTime(int n) {
    Time T;                           /* Variabel lokal untuk hasil */
    CreateTime(&T,
        n / 3600,                     /* Jam:   bagi bulat dengan 3600      */
        (n % 3600) / 60,              /* Menit: sisa bagi 3600, lalu div 60 */
        n % 60                        /* Detik: sisa bagi 60                */
    );
    return T;                         /* Kembalikan Time hasil konversi */
}

/* =========================================================
 * OPERASI RELASIONAL
 * ========================================================= */

/* IsEQTime: Mengembalikan true jika T1 == T2 (semua komponen sama) */
bool IsEQTime(Time T1, Time T2) {
    return (GetHours(T1)   == GetHours(T2))   && /* Jam sama?    */
           (GetMinutes(T1) == GetMinutes(T2)) && /* Menit sama?  */
           (GetSeconds(T1) == GetSeconds(T2));   /* Detik sama?  */
}

/*
 * IsGTTime: Mengembalikan true jika T1 > T2.
 * Membandingkan dari komponen terbesar (jam) ke terkecil (detik).
 */
bool IsGTTime(Time T1, Time T2) {
    if (GetHours(T1) > GetHours(T2)) return true;  /* Jam T1 lebih besar → T1 pasti lebih besar */
    if (GetHours(T1) < GetHours(T2)) return false; /* Jam T1 lebih kecil → T1 pasti lebih kecil */
    /* Jam sama, bandingkan menit */
    if (GetMinutes(T1) > GetMinutes(T2)) return true;
    if (GetMinutes(T1) < GetMinutes(T2)) return false;
    /* Jam & menit sama, bandingkan detik */
    return GetSeconds(T1) > GetSeconds(T2);
}

/*
 * IsLTTime: Mengembalikan true jika T1 < T2.
 * Logika sama dengan IsGTTime tetapi arah perbandingan terbalik.
 */
bool IsLTTime(Time T1, Time T2) {
    if (GetHours(T1) > GetHours(T2)) return false; /* Jam T1 lebih besar → T1 tidak lebih kecil */
    if (GetHours(T1) < GetHours(T2)) return true;  /* Jam T1 lebih kecil → T1 pasti lebih kecil */
    if (GetMinutes(T1) > GetMinutes(T2)) return false;
    if (GetMinutes(T1) < GetMinutes(T2)) return true;
    return GetSeconds(T1) < GetSeconds(T2);
}

/* =========================================================
 * OPERASI ARITMATIKA
 * ========================================================= */

/*
 * NextSecond: Mengembalikan Time 1 detik setelah T.
 * Menangani kasus overflow (detik=59, menit=59, jam=23)
 * dengan wrap-around ke 00:00:00 (hari berikutnya).
 */
Time NextSecond(Time T) {
    Time T1; /* Variabel lokal untuk menyimpan hasil */

    if (GetSeconds(T) == 59) {          /* Jika detik sudah 59... */
        if (GetMinutes(T) == 59) {      /* ...dan menit sudah 59... */
            if (GetHours(T) == 23) {    /* ...dan jam sudah 23 → wrap ke 00:00:00 */
                CreateTime(&T1, 0, 0, 0);
            } else {                    /* Jam belum 23 → naikkan jam, reset menit & detik */
                CreateTime(&T1, GetHours(T) + 1, 0, 0);
            }
        } else {                        /* Menit belum 59 → naikkan menit, reset detik */
            CreateTime(&T1, GetHours(T), GetMinutes(T) + 1, 0);
        }
    } else {                            /* Detik belum 59 → naikkan detik saja */
        CreateTime(&T1, GetHours(T), GetMinutes(T), GetSeconds(T) + 1);
    }
    return T1; /* Kembalikan Time hasil */
}

/*
 * PrevSecond: Mengembalikan Time 1 detik sebelum T.
 * Menangani kasus underflow (detik=0, menit=0, jam=0)
 * dengan wrap-around ke 23:59:59 (hari sebelumnya).
 */
Time PrevSecond(Time T) {
    Time T1;

    if (GetSeconds(T) == 0) {          /* Jika detik sudah 0... */
        if (GetMinutes(T) == 0) {      /* ...dan menit sudah 0... */
            if (GetHours(T) == 0) {    /* ...dan jam sudah 0 → wrap ke 23:59:59 */
                CreateTime(&T1, 23, 59, 59);
            } else {                   /* Jam > 0 → kurangi jam, set menit & detik ke 59 */
                CreateTime(&T1, GetHours(T) - 1, 59, 59);
            }
        } else {                       /* Menit > 0 → kurangi menit, set detik ke 59 */
            CreateTime(&T1, GetHours(T), GetMinutes(T) - 1, 59);
        }
    } else {                           /* Detik > 0 → kurangi detik saja */
        CreateTime(&T1, GetHours(T), GetMinutes(T), GetSeconds(T) - 1);
    }
    return T1;
}

/*
 * Difference: Menghitung selisih dua Time dalam satuan detik.
 * Hasilnya negatif jika start > end.
 * Menggunakan TimeToSeconds untuk menyederhanakan perhitungan.
 */
int Difference(Time start, Time end) {
    int startSec = TimeToSeconds(start); /* Konversi start ke total detik */
    int endSec   = TimeToSeconds(end);   /* Konversi end   ke total detik */
    return endSec - startSec;            /* Selisih: positif jika end > start */
}

/* =========================================================
 * PROGRAM UTAMA (DRIVER ADT TIME)
 * ========================================================= */

int main() {
    Time T1, T2; /* Deklarasi dua variabel bertipe Time */

    printf("=== Program ADT Time ===\n\n");

    /* Membaca Time pertama dari pengguna */
    printf("-- Masukkan Time 1 --\n");
    ReadTime(&T1); /* Kirim alamat T1 (&T1) agar dapat diisi oleh ReadTime */

    /* Membaca Time kedua dari pengguna */
    printf("\n-- Masukkan Time 2 --\n");
    ReadTime(&T2);

    /* Menampilkan hasil */
    printf("\nTime 1 = "); PrintTime(T1); printf("\n");
    printf("Time 2 = "); PrintTime(T2); printf("\n");

    /* Menampilkan selisih kedua Time dalam detik */
    printf("Selisih Time 1 dan Time 2 = %d detik\n", Difference(T1, T2));

    /* ---- Demo fitur lainnya ---- */
    printf("\n--- Demo Operasi Lain ---\n");

    /* Relasional */
    printf("T1 == T2 ? %s\n", IsEQTime(T1, T2) ? "Ya" : "Tidak");
    printf("T1 >  T2 ? %s\n", IsGTTime(T1, T2) ? "Ya" : "Tidak");
    printf("T1 <  T2 ? %s\n", IsLTTime(T1, T2) ? "Ya" : "Tidak");

    /* Konversi */
    printf("\nT1 dalam detik : %d\n", TimeToSeconds(T1));
    printf("86399 detik    : "); PrintTime(SecondsToTime(86399)); printf("\n");

    /* NextSecond & PrevSecond dari T1 */
    printf("\nNextSecond(T1) = "); PrintTime(NextSecond(T1)); printf("\n");
    printf("PrevSecond(T1) = "); PrintTime(PrevSecond(T1)); printf("\n");

    return 0; /* Program selesai dengan status sukses */
}