//425507 Cennet Nıslu
//434399 Kübra Dereli

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype> //isdigit fonksiyonu kütüphanesi
#include <iomanip> // formatli gösterim icin kullaniliyor


using namespace std;

int anaMenu();

class Student {
private:
    string* ad;
    string* ogrNo;
    float* araSinav;
    float* ikinciSinav;
    float* odev;
    float* finalNotu;
    int* devamSayisi;
    int ogrenciSayisi;

public:
    Student(int ogrenciSayisi);
    ~Student();

    void readFromCSV(const string& dosyaAdi);
    float average(int index);
    void print(int mode = -1);
    void print(const string& dosyaAdi, int mode2 = -1);
};

bool isNumber(const string& str) {
    for (char const &c : str) {
        if (std::isdigit(c) == 0 && c != '.'&& c==' ') return false;
    }
    return true;
}

// Constructor
Student::Student(int ogrenciSayisi) : ogrenciSayisi(ogrenciSayisi) {
    ad = new string[ogrenciSayisi];
    ogrNo = new string[ogrenciSayisi];
    araSinav = new float[ogrenciSayisi];
    ikinciSinav = new float[ogrenciSayisi];
    odev = new float[ogrenciSayisi];
    finalNotu = new float[ogrenciSayisi];
    devamSayisi = new int[ogrenciSayisi];
}

// Destructor
Student::~Student() {
    delete[] ad;
    delete[] ogrNo;
    delete[] araSinav;
    delete[] ikinciSinav;
    delete[] odev;
    delete[] finalNotu;
    delete[] devamSayisi;
}

// Dosyadan veri okuma
void Student::readFromCSV(const string& dosyaAdi) {
    ifstream fin(dosyaAdi);
    if (!fin) {
        cerr << "\n\tDosya açilamadi.\n";
        return;
    }

    string line;
    int index = 0;
    getline(fin,line);

    while (getline(fin, line) && index < ogrenciSayisi) {
        stringstream ss(line);
        string word;
        int i = 0;

        while (getline(ss, word, ',') && i < 7) {
            if(word.empty()){
                    switch (i) {
                        case 2: araSinav[index] = 0.0; break;
                        case 3: ikinciSinav[index] = 0.0; break;
                        case 4: odev[index] = 0.0; break;
                        case 5: finalNotu[index] = 0.0; break;
                        case 6: devamSayisi[index] = 0; break;
                    }
            }
            else{
            switch (i) {
                case 0:
                    ad[index] = word;
                    break;
                case 1:
                    ogrNo[index] = word;
                    break;
                case 2:
                    araSinav[index] = isNumber(word) ? stof(word) : 0.0;
                    break;
                case 3:
                    ikinciSinav[index] = isNumber(word) ? stof(word) : 0.0;
                    break;
                case 4:
                    odev[index] = isNumber(word) ? stof(word) : 0.0;
                    break;
                case 5:
                    finalNotu[index] = isNumber(word) ? stof(word) : 0.0;
                    break;
                case 6:
                    devamSayisi[index] = isNumber(word) ? stoi(word) : 0;
                    break;
            }
            }
            i++;
        }

        while (i < 7) {
            switch (i) {
                case 2: araSinav[index] = 0.0; break;
                case 3: ikinciSinav[index] = 0.0; break;
                case 4: odev[index] = 0.0; break;
                case 5: finalNotu[index] = 0.0; break;
                case 6: devamSayisi[index] = 0; break;
            }
            i++;
        }

        index++;
    }

    fin.close();
}

// Ortalama hesaplama
float Student::average(int index) {
    return (araSinav[index] * 0.2) + (ikinciSinav[index] * 0.2) + (odev[index] * 0.2) + (finalNotu[index] * 0.4);
}

// Listeyi ekrana yazdirma
void Student::print(int mode) {
    if(mode>1 || mode< -1 ){
        cout<<"\n\tGecersiz parametre girildi!"<<endl;
    }
    else{
    cout << left << setw(10) << "\nAd"
         << setw(10) << "Ogr. No"
         << setw(10) << "Ara Sinav"
         << setw(10) << "2. Sinav"
         << setw(10) << "Odev"
         << setw(10) << "Final"
         << setw(10) << "Devam"
         << setw(10) << "Ortalama"
         << endl;
    cout << "--------------------------------------------------------------------------------\n";

    for (int i = 0; i < ogrenciSayisi; i++) {
        float ort = average(i);
        if ((mode == 0 && ort < 50) || (mode == 1 && ort >= 50) || mode == -1) {
            cout << left << setw(10) << ad[i]
                 << setw(10) << ogrNo[i]
                 << setw(10) << araSinav[i]
                 << setw(10) << ikinciSinav[i]
                 << setw(10) << odev[i]
                 << setw(10) << finalNotu[i]
                 << setw(10) << devamSayisi[i]
                 << setw(10) << fixed << setprecision(2) << ort
                 << endl;
        }
    }
    }
}

// Sonuçlari dosyaya yazdirma
void Student::print(const string& dosyaAdi, int mode2) {
    if(mode2>1 || mode2< -1 ){
        cout<<"\n\tGecersiz parametre girildi! Dosya olusturulamadigindan veriler dosyaya yazilmadi."<<endl;
    }
    else{
    ofstream fout(dosyaAdi);
    fout << left << setw(10) << "Ad"
         << setw(10) << "Ogr. No"
         << setw(10) << "Ara Sinav"
         << setw(10) << "2. Sinav"
         << setw(10) << "Odev"
         << setw(10) << "Final"
         << setw(10) << "Devam"
         << setw(10) << "Ortalama"
         << endl;
    fout << "-----------------------------------------------------------------------------------\n";

    for (int i = 0; i < ogrenciSayisi; i++) {
        float ort = average(i);
        if ((mode2 == 0 && ort < 50) || (mode2 == 1 && ort >= 50) || mode2 == -1) {
            fout << left << setw(10) << ad[i]
                 << setw(10) << ogrNo[i]
                 << setw(10) << araSinav[i]
                 << setw(10) << ikinciSinav[i]
                 << setw(10) << odev[i]
                 << setw(10) << finalNotu[i]
                 << setw(10) << devamSayisi[i]
                 << setw(10) << fixed << setprecision(2) << ort
                 << endl;
        }
    }
    fout.close();
    cout<<"\n\tSonuclar yazildi."<<endl;
    }
}

int main() {
    int ogrenciSayisi = 125;
    Student ogrenciler(ogrenciSayisi);

    ogrenciler.readFromCSV("girdi.csv");

    int secim = anaMenu();
    while (secim != 0) {
        switch (secim) {
        case 1: ogrenciler.print(); break;
        case 2: ogrenciler.print(1); break;
        case 3: ogrenciler.print(0); break;
        case 4: ogrenciler.print("tumsinif.txt"); break;
        case 5: ogrenciler.print("gecen.txt",1); break;
        case 6: ogrenciler.print("kalan.txt",0); break;
        default: cout << "\n\tHatali Secim" << endl; break;
        }
        secim = anaMenu();
    }

    return 0;
}
int anaMenu() {
    int secim;
    cout << " \n\n\t\t1- Tum ogrencileri ekrana yazdir" << endl;
    cout << " \t\t2- Gecen ogrencileri ekrana yazdir" << endl;
    cout << " \t\t3- Kalan ogrencileri ekrana yazdir" << endl;
    cout << " \t\t4- Tum ogrencileri tumsinif dosyasina yazdir" << endl;
    cout << " \t\t5- Gecen ogrencileri gecen dosyasina yazdir" << endl;
    cout << " \t\t6- Kalan ogrencileri kalan dosyasina yazdir\n\n" << endl;
    cout << " \t\t0- CIKIS\n" << endl;
    cout << " \t\tSeciminizi giriniz: ";
    cin >> secim;
    return secim;
}
