#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;
// Her �retimdeki birey say�s�n� ba�lang��ta 100 olarak belirledim.
#define POPULATION_SIZE 1000

// Gen olarak harf rakam ve baz� karakterleri verdim.
string GENLER = "ABCDEFGHIJKLMNOPRS�TUVYZ 1234567890,.-?!";

// Olu�turulacak hedef dize
const string HEDEF = "DOGA MUKEMMEL DEGIL MI? TUM RENKLERIN, TUM KOKULARIN, TUM KUMASLARIN, TUM GENISLIKLERIN SAHIBIDIR. VE - SAHIP OLDUGUMUZ HER SEY BU - DUSUNDUGUMUZDEN DAHA FAZLASI";
// Verilen aral�kta rasgele say�lar �retmek i�in bir fonksiyon
int rastgele_sayi(int ilk, int son)
{
    int range = (son - ilk) + 1;
    int rastgele_int = ilk + (rand() % range);
    return rastgele_int;
}

// Mutasyon i�in rastgele gen �retim fonksiyonu. Bu fonksiyonu ayr�ca ilk metni (bozuk metin) olu�tururken de kullanaca��m.
char mutasyonlu_genler()
{
    int uzunluk = GENLER.size();
    int r = rastgele_sayi(0, uzunluk - 1);
    return GENLER[r];
}

// kromozom yani genlerden olu�an dizi olu�turmak i�in bir fonksiyon. 3 karakterde bir silme ekleme veya de�i�tirme i�lemi yapar.
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

    return metin; // En sonunda ana metinden �retti�imiz bozuk metni geri d�nd�r�r.
}

// Pop�lasyonda bireyi temsil eden s�n�f
class Birey
{
public:
    string kromozom; // Genlerden olu�an diziyi temsil eder.
    int uygunluk;
    Birey(string kromozom);
    Birey caprazla(Birey ata2);
    int uygunluk_hesapla();
};

Birey::Birey(string kromozom)// Yap�c� fonksiyon. Bir birey olu�turmak i�in kromozom gerekir.
{
    this->kromozom = kromozom;
    uygunluk = uygunluk_hesapla();// Bireyin uygunlu�unu da ilgili fonksiyona eri�erek burada belirledik.
};

// �ki bireyi �aprazlayarak yeni bir birey �retme fonksiyonu.1. atadan eri�ilir. Parametre olarak 2. atas�n� al�r.
Birey Birey::caprazla(Birey ata2)
{
    // yavrular i�in kromozom
    string yavru_kromozom = "";

    int len = kromozom.size();
    for (int i = 0;i < len;i++)
    {
        // rastgele olas�l�k
        float p = rastgele_sayi(0, 100) / 100;
        // if ve else if sat�rlar�nda crossing over i�lemi yap�l�yor. Else k�sm�nda ise (tabi k���k bir olas�l�k) mutasyon ekleniyor.
        // E�er say� 0.45 den k���k ise, ata1 den gen ekliyorum
        if (p < 0.45)//45
            yavru_kromozom += kromozom[i];

        // Say� 0.90 dan k���kse ata2 den gen ekliyorum.
        else if (p < 0.90)//90
            yavru_kromozom += ata2.kromozom[i];

        // Aksi takdirde �e�itlili�i korumak i�in rastgele gen (mutasyon) ekliyorum.
        else
            yavru_kromozom += mutasyonlu_genler();
    }

    // Yavrular i�in �retilen kromozomu kullanarak yeni bir birey olu�turdum.
    return Birey(yavru_kromozom);
};


// Uygunluk puan�n� hesapl�yoruz, bu hedef dizeden farkl� olan karakter say�s�d�r.
//Yani uygunluk de�eri azald�k�a daha uygun birey olur.
int Birey::uygunluk_hesapla()
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

// < operat�r�n� overload ettik. Bu operator main i�erisinde sort fonksiyonunda kullan�l�yor.
bool operator<(const Birey& birey1, const Birey& birey2)
{
    return birey1.uygunluk < birey2.uygunluk;
}


int main()
{
    srand((unsigned)(time(0)));

    // �uanki �retilmi� birey say�s�.
    int birey = 0;

    vector<Birey> populasyon;// Bu vekt�r� bireyleri tutmak i�in kullanaca��z.
    bool bulundu = false;

    // ba�lang�� pop�lasyonu olu�turmak i�in hedef metinde y�nergede istenen de�i�iklikleri(karakter ekleme,silme vb.) yaparak yeni metinler olu�turduk.
    for (int i = 0;i < POPULATION_SIZE;i++)
    {
        string baslangic_metni = baslangic_olustur();
        populasyon.push_back(Birey(baslangic_metni));
    }

    while (!bulundu)
    {
        // pop�lasyonu artan uygunluk puan� s�ras�na g�re s�ralad�k. < operat�r�n� overload etti�imiz i�in uygunluk de�erine g�re s�ralama yapacakt�r.
        sort(populasyon.begin(), populasyon.end());

        // E�er birey en d���k uygunluk puan�na sahipse ki bu da 0'd�r. O zaman hedefe ula�t���m�z� anl�yoruz ve d�ng�y� k�r�yoruz.
        if (populasyon[0].uygunluk <= 0)
        {
            bulundu = true;
            break;
        }

        // Aksi takdirde yeni nesil i�in yeni yavrular �retiyoruz.
        vector<Birey> yeni_nesil;

        // Eleme ger�ekle�tiriyoruz, yani en uygun n�fusun %10'u bir sonraki nesle gidiyor.
        int sayi = (10 * POPULATION_SIZE) / 100;
        for (int i = 0;i < sayi;i++)
            yeni_nesil.push_back(populasyon[i]);

        // En uygun pop�lasyonun %50'sinden, Bireyler yavru �retmek i�in e�lenecek.
        sayi = (90 * POPULATION_SIZE) / 100;
        for (int i = 0;i < sayi;i++)
        {
            int len = populasyon.size();
            int r = rastgele_sayi(0, 50);
            Birey ata1 = populasyon[r];
            r = rastgele_sayi(0, 50);
            Birey ata2 = populasyon[r];
            Birey yavru = ata1.caprazla(ata2);//2 atadan bir yavru �retmek i�in �aprazla fonksiyonunu kullan�yoruz.
            yeni_nesil.push_back(yavru);
        }
        populasyon = yeni_nesil;
        //Bireyler uygun olmasa da ne kadar yak�nsad���m�z� g�rmek i�in ekrana bast�r�yoruz.
        cout << "Metin: " << populasyon[0].kromozom << " ";
        cout << "\nBirey: " << birey << " ";
        cout << "Uygunluk: " << populasyon[0].uygunluk << "\n";

        birey++;
    }
    // Birey bulunduysa d�ng� k�r�ld���ndan buraya eri�iriz ve uygun birey yani metni ekrana bast�r�r�z.
    cout << "\nMetin: " << populasyon[0].kromozom << " ";
    cout << "\nUygun birey " << birey << ". bireyde bulunmustur. ";
    getchar();

}