#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100   // satır uzunluğu için maksimum değer
#define MAX_LINES 100         // dosyadaki maksimum satır sayısı

// yapı tanımlaması: Kisi yapısı, her bir kişinin bilgilerini tutar
typedef struct {
    char isim[50];
    char soyisim[50];
    float satis;
    float fark;
} kisi;

// karşılaştırma fonksiyonu
int compare(const void *a, const void *b) {
    kisi *kisiA = (kisi *)a;
    kisi *kisiB = (kisi *)b;

    // önce isimleri karşılaştır
    int isimCompare = strcmp(kisiA->isim, kisiB->isim);

    // isimler aynıysa soyisimleri karşılaştır
    if (isimCompare == 0) {
        return strcmp(kisiA->soyisim, kisiB->soyisim);
    }
    return isimCompare;  // isimleri karşılaştırma sonucu döndür
}

int main() {
    // "satis.txt" dosyasını okuma modunda aç
    FILE *file = fopen("satis.txt", "r");
    if (!file) {
        printf("dosya acilamadi\n");
        return 1;
    }

    // kisi dizisini tanımla satır sayısını tutmak için sayac değişkenini başlat
    kisi kisiler[MAX_LINES];
    int sayac = 0;
    char line[MAX_LINE_LENGTH];  // satırdaki veriyi tutacak dizi

    // dosyayı oku
    while (fgets(line, sizeof(line), file)) {
        // her satırdaki veriyi soyisim, isim ve satış olarak ayır ve kisiler dizisine kaydet
        sscanf(line, "%s %s %f", kisiler[sayac].soyisim, kisiler[sayac].isim, &kisiler[sayac].satis);
        sayac++;  // işlenen kişi sayısını arttır
    }
    fclose(file);  // dosyayı kapat

    // en büyük satış değerini bul
    float ENB = 0.0;
    for (int i = 0; i < sayac; i++) {
        if (kisiler[i].satis > ENB) {
            ENB = kisiler[i].satis;  // en yüksek satış değeri güncelleniyor
        }
    }

    // performans farkını hesapla
    for (int i = 0; i < sayac; i++) {
        kisiler[i].fark = ENB - kisiler[i].satis;
    }

    // alfabetik şekilde sırala
    qsort(kisiler, sayac, sizeof(kisi), compare);

    // "prfrmns.txt" dosyasını yazma modunda aç
    FILE *outFile = fopen("prfrmns.txt", "w");
    if (!outFile) {
        printf("cikti dosyasi acilamadi\n");
        return 1;
    }

    // performans verilerini prfrmns.txt dosyasına yaz
    for (int i = 0; i < sayac; i++) {
        fprintf(outFile, "%s %s %.2f\n", kisiler[i].isim, kisiler[i].soyisim, kisiler[i].fark);
    }
    fclose(outFile);  // prfrmns.txt dosyasını kapat

    // kullanıcıya işlem tamamlandığını bildir
    printf("performans verileri 'prfrmns.txt' dosyasina yazildi\n");
    return 0;
}