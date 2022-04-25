#pragma once
#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Birey
{
public:
    string kromozom;
    int uygunluk;
    /*Birey(string kromozom);
    Birey caprazla(Birey parent2);
    int uygunluk_hesapla();*/
    string GENLER = "ABCDEFGHIJKLMNOPRS�TUVYZ 1234567890,.-?!";

    // Olu�turulacak hedef dize
    const string HEDEF = "DOGA MUKEMMEL DEGIL MI? TUM RENKLERIN, TUM KOKULARIN, TUM KUMASLARIN, TUM GENISLIKLERIN SAHIBIDIR. VE - SAHIP OLDUGUMUZ HER SEY BU - DUSUNDUGUMUZDEN DAHA FAZLASI";
    //const string HEDEF = "Selama";
    Birey(string kromozom)
    {
        this->kromozom = kromozom;
        uygunluk = uygunluk_hesapla();
    };

    // �iftle�me ger�ekle�tirin ve yeni yavrular �retin
    Birey caprazla(Birey ata2)
    {
        // yavrular i�in kromozom
        string yavru_kromozom = "";

        int len = kromozom.size();
        for (int i = 0;i < len;i++)
        {
            // rastgele olas�l�k
            float p = rastgele_sayi(0, 100) / 100;
            // if ve else if sat�rlar�nda crossing over i�lemi yap�l�yor. Else k�sm�nda ise tabi k���k bir olas�l�k mutasyon ekleniyor.
            // E�er say� 0.45 den k���k ise, ata1 den gen ekle.
            if (p < 0.45)
                yavru_kromozom += kromozom[i];

            // if prob is between 0.45 and 0.90, insert
            // gene from parent 2
            else if (p < 0.90)
                yavru_kromozom += ata2.kromozom[i];

            // aksi takdirde �e�itlili�i korumak i�in rastgele gen (mutasyon) ekleyin
            else
                yavru_kromozom += mutasyonlu_genler();
        }

        // yavrular i�in �retilen kromozomu kullanarak yeni Birey(yavru) olu�turun
        return Birey(yavru_kromozom);
    };


    // Uygunluk puan�n� hesapl�yoruz, bu hedef dizeden farkl� olan karakter say�s�d�r.
    //Yani uygunluk de�eri azald�k�a daha uygun birey olur.
    int uygunluk_hesapla()
    {
        int len = HEDEF.size();
        int uygunluk = 0;
        for (int i = 0;i < len;i++)
        {
            if (kromozom[i] != HEDEF[i])
                uygunluk++;
        }
        return uygunluk;
    };
    /*int rastgele_sayi(int start, int end)
    {
        int range = (end - start) + 1;
        int rastgele_int = start + (rand() % range);
        return rastgele_int;
    }

    // Mutasyon i�in rastgele genler olu�turduk
    char mutasyonlu_genler()
    {
        int len = GENLER.size();
        int r = rastgele_sayi(0, len - 1);
        return GENLER[r];
    }
    // kromozom yani genlerden olu�an dizi olu�turmak
    string baslangic_olustur()
    {
        string metin = HEDEF;
        for (int i = 0;i < metin.size();i++) {
            if (i % 9 == 0)
                metin.erase(i, 1);
            else if (i % 9 == 3)
                metin.insert(i, 1, mutasyonlu_genler());
            else if (i % 9 == 6)
                metin[i] = mutasyonlu_genler();
        }

        return metin;
    }*/
};

