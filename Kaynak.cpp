#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;
// Her üretimdeki birey sayýsýný baþlangýçta 100 olarak belirledim.
#define POPULATION_SIZE 1000

// Gen olarak harf rakam ve bazý karakterleri verdim.
string GENLER = "ABCDEFGHIJKLMNOPRSÞTUVYZ 1234567890,.-?!";

// Oluþturulacak hedef dize
const string HEDEF = "DOGA MUKEMMEL DEGIL MI? TUM RENKLERIN, TUM KOKULARIN, TUM KUMASLARIN, TUM GENISLIKLERIN SAHIBIDIR. VE - SAHIP OLDUGUMUZ HER SEY BU - DUSUNDUGUMUZDEN DAHA FAZLASI";
// Verilen aralýkta rasgele sayýlar üretmek için bir fonksiyon
int rastgele_sayi(int ilk, int son)
{
    int range = (son - ilk) + 1;
    int rastgele_int = ilk + (rand() % range);
    return rastgele_int;
}

// Mutasyon için rastgele gen üretim fonksiyonu. Bu fonksiyonu ayrýca ilk metni (bozuk metin) oluþtururken de kullanacaðým.
char mutasyonlu_genler()
{
    int uzunluk = GENLER.size();
    int r = rastgele_sayi(0, uzunluk - 1);
    return GENLER[r];
}

// kromozom yani genlerden oluþan dizi oluþturmak için bir fonksiyon. 3 karakterde bir silme ekleme veya deðiþtirme iþlemi yapar.
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

    return metin; // En sonunda ana metinden ürettiðimiz bozuk metni geri döndürür.
}

// Popülasyonda bireyi temsil eden sýnýf
class Birey
{
public:
    string kromozom; // Genlerden oluþan diziyi temsil eder.
    int uygunluk;
    Birey(string kromozom);
    Birey caprazla(Birey ata2);
    int uygunluk_hesapla();
};

Birey::Birey(string kromozom)// Yapýcý fonksiyon. Bir birey oluþturmak için kromozom gerekir.
{
    this->kromozom = kromozom;
    uygunluk = uygunluk_hesapla();// Bireyin uygunluðunu da ilgili fonksiyona eriþerek burada belirledik.
};

// Ýki bireyi çaprazlayarak yeni bir birey üretme fonksiyonu.1. atadan eriþilir. Parametre olarak 2. atasýný alýr.
Birey Birey::caprazla(Birey ata2)
{
    // yavrular için kromozom
    string yavru_kromozom = "";

    int len = kromozom.size();
    for (int i = 0;i < len;i++)
    {
        // rastgele olasýlýk
        float p = rastgele_sayi(0, 100) / 100;
        // if ve else if satýrlarýnda crossing over iþlemi yapýlýyor. Else kýsmýnda ise (tabi küçük bir olasýlýk) mutasyon ekleniyor.
        // Eðer sayý 0.45 den küçük ise, ata1 den gen ekliyorum
        if (p < 0.45)//45
            yavru_kromozom += kromozom[i];

        // Sayý 0.90 dan küçükse ata2 den gen ekliyorum.
        else if (p < 0.90)//90
            yavru_kromozom += ata2.kromozom[i];

        // Aksi takdirde çeþitliliði korumak için rastgele gen (mutasyon) ekliyorum.
        else
            yavru_kromozom += mutasyonlu_genler();
    }

    // Yavrular için üretilen kromozomu kullanarak yeni bir birey oluþturdum.
    return Birey(yavru_kromozom);
};


// Uygunluk puanýný hesaplýyoruz, bu hedef dizeden farklý olan karakter sayýsýdýr.
//Yani uygunluk deðeri azaldýkça daha uygun birey olur.
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

// < operatörünü overload ettik. Bu operator main içerisinde sort fonksiyonunda kullanýlýyor.
bool operator<(const Birey& birey1, const Birey& birey2)
{
    return birey1.uygunluk < birey2.uygunluk;
}


int main()
{
    srand((unsigned)(time(0)));

    // þuanki üretilmiþ birey sayýsý.
    int birey = 0;

    vector<Birey> populasyon;// Bu vektörü bireyleri tutmak için kullanacaðýz.
    bool bulundu = false;

    // baþlangýç popülasyonu oluþturmak için hedef metinde yönergede istenen deðiþiklikleri(karakter ekleme,silme vb.) yaparak yeni metinler oluþturduk.
    for (int i = 0;i < POPULATION_SIZE;i++)
    {
        string baslangic_metni = baslangic_olustur();
        populasyon.push_back(Birey(baslangic_metni));
    }

    while (!bulundu)
    {
        // popülasyonu artan uygunluk puaný sýrasýna göre sýraladýk. < operatörünü overload ettiðimiz için uygunluk deðerine göre sýralama yapacaktýr.
        sort(populasyon.begin(), populasyon.end());

        // Eðer birey en düþük uygunluk puanýna sahipse ki bu da 0'dýr. O zaman hedefe ulaþtýðýmýzý anlýyoruz ve döngüyü kýrýyoruz.
        if (populasyon[0].uygunluk <= 0)
        {
            bulundu = true;
            break;
        }

        // Aksi takdirde yeni nesil için yeni yavrular üretiyoruz.
        vector<Birey> yeni_nesil;

        // Eleme gerçekleþtiriyoruz, yani en uygun nüfusun %10'u bir sonraki nesle gidiyor.
        int sayi = (10 * POPULATION_SIZE) / 100;
        for (int i = 0;i < sayi;i++)
            yeni_nesil.push_back(populasyon[i]);

        // En uygun popülasyonun %50'sinden, Bireyler yavru üretmek için eþlenecek.
        sayi = (90 * POPULATION_SIZE) / 100;
        for (int i = 0;i < sayi;i++)
        {
            int len = populasyon.size();
            int r = rastgele_sayi(0, 50);
            Birey ata1 = populasyon[r];
            r = rastgele_sayi(0, 50);
            Birey ata2 = populasyon[r];
            Birey yavru = ata1.caprazla(ata2);//2 atadan bir yavru üretmek için çaprazla fonksiyonunu kullanýyoruz.
            yeni_nesil.push_back(yavru);
        }
        populasyon = yeni_nesil;
        //Bireyler uygun olmasa da ne kadar yakýnsadýðýmýzý görmek için ekrana bastýrýyoruz.
        cout << "Metin: " << populasyon[0].kromozom << " ";
        cout << "\nBirey: " << birey << " ";
        cout << "Uygunluk: " << populasyon[0].uygunluk << "\n";

        birey++;
    }
    // Birey bulunduysa döngü kýrýldýðýndan buraya eriþiriz ve uygun birey yani metni ekrana bastýrýrýz.
    cout << "\nMetin: " << populasyon[0].kromozom << " ";
    cout << "\nUygun birey " << birey << ". bireyde bulunmustur. ";
    getchar();

}