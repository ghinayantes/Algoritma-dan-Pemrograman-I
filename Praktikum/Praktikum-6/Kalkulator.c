#include <stdio.h>
#include "Kalkulator.h"

void BuatKalkulator (Kalkulator *K) {
    int i;
    for(i = 0; i < MAX_OPERATOR; i++) {
        K->Operan[i] = 0;
        K->Operator[i] = '\0';
    }
    K->Operan[MAX_OPERAND-1] = 0;  // elemen terakhir
    K->NEffOperan = 0;
    K->NEffOperator = 0;
    K->Ans = 0;
}
/* Membuat kalkulator kosong
 I.S. K sembarang
 F.S. Terbentuk kalkulator K kosong */

boolean CekError (Kalkulator K) {
    int i;
    if (K.NEffOperan == 0 && K.NEffOperator == 0) return false;
    if (K.NEffOperator >= K.NEffOperan) return true;
    // cek bagi 0
    for (i = 0; i < K.NEffOperator; i++) {
        if (K.Operator[i] == '/' && K.Operan[i+1] == 0) return true;
    }
    return false;
}
/* Mengembalikan nilai true jika kalkulator akan mengeluarkan error dan false jika tidak ada error */

void ResetKalkulator (Kalkulator *K) {
    int i;
    for(i = 0; i < MAX_OPERATOR; i++) {
        K->Operan[i] = 0;
        K->Operator[i] = '\0';
    }
    K->Operan[MAX_OPERAND-1] = 0;
    K->NEffOperan = 0;
    K->NEffOperator = 0;
    K->Ans = 0;
}
/* Menghapus keseluruhan data pada kalkulator K */

void InputOperasi (Kalkulator *K, int oprn[], int n_oprn, char oprtor[], int n_oprtor) {
    int i;
    ResetKalkulator(K);
    for(i = 0; i < n_oprn; i++) {
        K->Operan[i] = oprn[i];
    }
    for(i = 0; i < n_oprtor; i++) {
        K->Operator[i] = oprtor[i];
    }
    K->NEffOperan = n_oprn;
    K->NEffOperator = n_oprtor;
}
/* Menerima sekumpulan array operan dan operator sekaligus beserta panjangnya, 
   lalu menyimpannya ke dalam kalkulator K
   Pastikan untuk mengosongkan kalkulator K dulu sebelum memasukkan input baru */

void TambahOperator (Kalkulator *K, char oprtor) {
    K->Operator[K->NEffOperator] = oprtor;
    K->NEffOperator++;
}
/* Menambahkan operator di akhir list */

void HapusOperator(Kalkulator *K) {
    if(K->NEffOperator == 0) return;
    K->Operator[K->NEffOperator-1] = '\0';
    K->NEffOperator--;
}
/* Menghapus operator di akhir list */

void UbahOperator (Kalkulator *K, int idx, char oprtor) {
    K->Operator[idx] = oprtor;
}
/* Mengubah operator pada posisi idx */

void TambahOperan (Kalkulator *K, int oprn) {
    K->Operan[K->NEffOperan] = oprn;
    K->NEffOperan++;
}
/* Menambahkan operan di akhir list */

void HapusOperan(Kalkulator *K) {
    if(K->NEffOperan == 0) return;
    K->Operan[K->NEffOperan-1] = 0;
    K->NEffOperan--;
}
/* Menghapus operan di akhir list */

void UbahOperan (Kalkulator *K, int idx, int oprn) {
    K->Operan[idx] = oprn;
}
/* Mengubah operan pada posisi idx */

boolean JalankanKalkulasi (Kalkulator *K) {
    if(CekError(*K) || K->NEffOperan == 0) return false;

    int hasil = K->Operan[0];
    int i;
    for(i = 0; i < K->NEffOperator; i++) {
        if(K->Operator[i] == '+') {
            hasil += K->Operan[i+1];
        } else if(K->Operator[i] == '-') {
            hasil -= K->Operan[i+1];
        } else if(K->Operator[i] == '*') {
            hasil *= K->Operan[i+1];
        } else if(K->Operator[i] == '/') {
            // Perbaikan: Jika bagi 0, langsung gagal
            if (K->Operan[i+1] == 0) return false; 
            hasil /= K->Operan[i+1];
        }
    }
    K->Ans = hasil;
    return true;
}
/* Jika kalkulasi valid dan berhasil: 
   - Hasil kalkulasi disimpan ke Ans dan fungsi akan mengembalikan true.
   Jika kalkulasi tidak valid dan gagal: 
   - Hasil kalkulasi tidak disimpan ke Ans dan fungsi akan mengembalikan false 
   Note: Abaikan presedensi operator, cukup ikuti urutan pada list */

void CetakHasil(Kalkulator K) {
     if (K.NEffOperan == 0 && K.NEffOperator == 0) {
        printf("KALKULATOR MASIH KOSONG\n");
        return;
    }
 
    int i;
 
    // Kasus khusus: tidak ada operan sama sekali, hanya ada operator
    if (K.NEffOperan == 0) {
        for(i = 0; i < K.NEffOperator; i++) printf("%c", K.Operator[i]);
        printf("\n");
        printf("Hasil Kalkulasi: ERROR\n");
        return;
    }
 
    // Cetak operan dan operator secara bergantian
    for(i = 0; i < K.NEffOperan; i++) {
        printf("%d", K.Operan[i]);
        if(i < K.NEffOperator) printf("%c", K.Operator[i]);
    }
    printf("\n");
 
    if (CekError(K)) {
        printf("Hasil Kalkulasi: ERROR\n");
    } else {
        JalankanKalkulasi(&K);
        printf("Hasil Kalkulasi: %d\n", K.Ans);
    }
}
/* Mencetak operan dan operasi yang terlibat serta menampilkan hasil kalkulasi
Contoh 1:
4+2*5-7
Hasil Kalkulasi: 7

Contoh 2:
4+2*5-
Hasil Kalkulasi: ERROR

Contoh 3 (Kalkulator Kosong):
KALKULATOR MASIH KOSONG
Jangan lupa akhiri dengan newline ('\n') */