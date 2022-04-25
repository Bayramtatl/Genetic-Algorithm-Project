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
    string GENLER = "ABCDEFGHIJKLMNOPRSÞTUVYZ 1234567890,.-?!";

    // Oluþturulacak hedef dize
    const string HEDEF = "DOGA MUKEMMEL DEGIL MI? TUM RENKLERIN, TUM KOKULARIN, TUM KUMASLARIN, TUM GENISLIKLERIN SAHIBIDIR. VE - SAHIP OLDUGUMUZ HER SEY BU - DUSUNDUGUMUZDEN DAHA FAZLASI";
    //const string HEDEF = "Selama";
    Birey(string kromozom)
    {
        this->kromozom = kromozom;
        uygunluk = uygunluk_hesapla();
    };

    // Çiftleþme gerçekleþtirin ve yeni yavrular üretin
    Birey caprazla(Birey ata2)
    {
        // yavrular için kromozom
        string yavru_kromozom = "";

        int len = kromozom.size();
        for (int i = 0;i < len;i++)
        {
            // rastgele olasýlýk
            float p = rastgele_sayi(0, 100) / 100;
            // if ve else if satýrlarýnda crossing over iþlemi yapýlýyor. Else kýsmýnda ise tabi küçük bir olasýlýk mutasyon ekleniyor.
            // Eðer sayý 0.45 den küçük ise, ata1 den gen ekle.
            if (p < 0.45)
                yavru_kromozom += kromozom[i];

            // if prob is between 0.45 and 0.90, insert
            // gene from parent 2
            else if (p < 0.90)
                yavru_kromozom += ata2.kromozom[i];

            // aksi takdirde çeþitliliði korumak için rastgele gen (mutasyon) ekleyin
            else
                yavru_kromozom += mutasyonlu_genler();
        }

        // yavrular için üretilen kromozomu kullanarak yeni Birey(yavru) oluþturun
        return Birey(yavru_kromozom);
    };


    // Uygunluk puanýný hesaplýyoruz, bu hedef dizeden farklý olan karakter sayýsýdýr.
    //Yani uygunluk deðeri azaldýkça daha uygun birey olur.
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

    // Mutasyon için rastgele genler oluþturduk
    char mutasyonlu_genler()
    {
        int len = GENLER.size();
        int r = rastgele_sayi(0, len - 1);
        return GENLER[r];
    }
    // kromozom yani genlerden oluþan dizi oluþturmak
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

