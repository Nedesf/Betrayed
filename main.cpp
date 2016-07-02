//Pozdrawiam Barusa i adriana17
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

void pomoc(int jakapomoc); string ekwipunek(int *przedmiot, int glod, int zmeczenie, int krew, int *wyposazenie, float &waga); int walka(int zdrowie, int &zmeczenie, int smierc, int *przedmiot, int pozycjaX, int pozycjaY, int *wyposazenie, string rodzajp);
string biom();  char interfejs(int &dzien, int &poraroku, int pozycjaX, int pozycjaY, int pole[100][100], int &glod, int &zdrowie, int &smierc, char ruch, double temperatura, int &godzina, int &minuta, int &zmeczenie);
void wyswietlanie(int mapa[100][100], int pozycjaX, int pozycjaY, int pole[100][100], int rozpaloneognisko, int &bandytaX, int &bandytaY, int wytrzymaloscs[100][100], int wyswietlenieo);
void sztucznaint(int zyjacybandyta, int pozycjaX, int pozycjaY, int &bandytaX, int &bandytaY, int wytrzymaloscs[100][100], int mapa[100][100]);
void wierszpolecen(int *przedmiot, int &glod, int &zmeczenie, int &krew, int *wyposazenie, float &waga, string &wybor3, string &poprzedniw,
                   int &zdrowie, int pole[100][100], int pozycjaX, int pozycjaY, int &dzienrozpalenia, int dzien, int &rozpaloneognisko,
                   int &ogniskoX, int &ogniskoY, int mapa[100][100], int wytrzymaloscs[100][100]);


int main()
{
    //PlaySound(TEXT("test.wav"), NULL, SND_ASYNC); TODO: muzyka do menu
    bool *pominiecie= new bool;
    *pominiecie=false;
    string credits="Nedesf przedstawia gre survivalowa pod tytulem";
    Sleep(2000); //intro
    for (int a=0; a<=46;a++) {cout<<credits[a]; Sleep(100); if (a==17) {Sleep(1000);} if (a==34){Sleep(1000);} if (kbhit()){*pominiecie=true; break;}}
    if (*pominiecie==false)
    {
    Sleep(2000);
    cout<<endl<<endl<<endl<<"PRZETRWANIEC";
    Sleep(2000);
    }
    delete pominiecie;
    system("cls");
    while (true)
    {
   HANDLE uchwyt = GetStdHandle( STD_OUTPUT_HANDLE );
    int mapa[100][100], pozycjaX=50, pozycjaY=50, pole[100][100], glod=0, zmeczenie=0, zdrowie=100, wybor2, dzien=1, poraroku=2, smierc=0, wytrzymaloscs[100][100]={0};
    int dzienrozpalenia=999999, ogniskoX, ogniskoY, rozpaloneognisko=0, przedmiot[14]={0}, wyposazenie[6]={0};
    int zyjacybandyta=0, bandytaX=40, bandytaY=40, temperatura=15, odczuwalna, godzina=9, minuta=0, wyswietlenieo=0, krew=5000;
    bool autozbieranie=false, rana[2]={false};
    float temperaturaciala=36.6, waga=0;
    int tworzeniewody;
    vector <int> wodax, woday;
    przedmiot[1]=50;
    string linia, wybor3, poprzedniw="nic", wyboro;
    char ruch='w', *wybor=new char;
    fstream plik;
    srand(time(NULL));
    SetConsoleTextAttribute(uchwyt, 15);
    system("cls");///menu
    cout<<"================================================="<<endl<<endl<<
          "                 PRZETRWANIEC                    "<<endl<<endl<<
          "================================================="<<endl<<
          "1 - Zacznij gre"<<endl;
          *wybor = getch();
          if (*wybor=='1')
          {
              delete wybor;
              for (int x=0; x<100; x++)
              {
                  for (int y=0; y<100; y++)
                  {
                      mapa [x][y] = 1;        
                  }
              }
              for (int x=1; x<99; x++)
              {
                  for (int y=1; y<100; y++)
                  {
                      mapa [x][y] = 0;
                      pole [x][y] = rand()%14+1;  //tablica pole odpowiada za generowanie sie przedmiotow typu patyk itp.
                      if (pole[x][y]==14){
                        wodax.push_back(x);         ///podaj koordynaty generatorowi wody
                        woday.push_back(y);
                      }
                  }
              }
              for (unsigned int i=0; i<wodax.size()-1; i++){    ///GENERATOR WODY
                                      int *x=new int;
                                      int *y=new int;
                                      short *ilewody=new short(0);  ///zmienna odpowiadajaca za chronienie, zeby nie wygenerowac za duzo wody
                                      *x=wodax[i];
                                      *y=woday[i];
                                      tworzeniewody=rand()%4;
                                      if (tworzeniewody<3){pole[*x][*y]=1; continue;}
                                      mapa[*x][*y]=4;
                                      pole[*x][*y]=1;
                        if (mapa[*x][*y]==4){ ///jezeli stworzyles wode,
                        tworzeniewody=rand()%2; ///wylosuj czy tworzyc wode dalej, czy nie (50%)
                            if (tworzeniewody==1){ ///jezeli tak,
                                do{
                                *ilewody++;
                                tworzeniewody=rand()%4; ///wylosuj jeden z 4 kierunkow
                                switch (tworzeniewody){
                                cout<<"X= "<<*x<<endl<<"Y= "<<*y<<endl;
                                case 0: mapa[*x+1][*y]=4; pole[*x+1][*y]=1; *x+=1; break;
                                case 1: mapa[*x][*y+1]=4; pole[*x][*y+1]=1; *y+=1; break;     ///i wygeneruj 1 blok wody
                                case 2: mapa[*x-1][*y]=4; pole[*x-1][*y]=1; *x-=1; break;     ///w tym kierunku
                                case 3: mapa[*x][*y-1]=4; pole[*x][*y-1]=1; *y-=1; break;
                                }
                                tworzeniewody=rand()%8;
                                }while((tworzeniewody<7)||(*ilewody<10));           ///szansa na to, ze woda bedzie generowala sie dalej
                            }
                            else{ ///jezeli nie to wykasuj caly zbiornik wodny, bo jest za maly
                                mapa[*x][*y]=0;
                            }
                      }
                      delete x;
                      delete y;
                      delete ilewody;
              }
              pole[50][50]=0;
              mapa[50][50]=0; mapa[51][50]=0; mapa[52][50]=0; mapa[53][50]=0;     //ochrona przed zablokowaniem gracza na spawnie
              while (ruch!='q')
              {
                  sztucznaint(zyjacybandyta, pozycjaX, pozycjaY, bandytaX, bandytaY, wytrzymaloscs, mapa);
                  if ((dzien==3)&&(zyjacybandyta==0)){zyjacybandyta=1; mapa[40][40]=20; bandytaX=40; bandytaY=40;}
                  if (minuta>59){minuta-=60; godzina++;}            ///czas
                  if (godzina>23){godzina-=24; dzien++;}
                  temperatura+=rand()%6;
                  temperatura-=rand()%6;
                  if (poraroku==1){
                    temperatura-=rand()%2;
                        if (temperatura<=-5){
                            temperatura+=rand()%4+5;                ///TEMPERATURA
                        }
                  }
                  else if (poraroku==3){
                    temperatura+=rand()%2;
                        if (temperatura<=0){
                            temperatura+=rand()%4+5;
                        }
                  }
                  odczuwalna=temperatura;
                  if (wyposazenie[0]==1){
                    odczuwalna+=2;
                  }
                  if (wyposazenie[1]==1){
                    odczuwalna+=5;
                  }
                  if (wyposazenie[4]==1){
                    odczuwalna+=5;
                  }
                  if (wyposazenie[5]==1){
                    odczuwalna+=2;
                  }

                                wyswietlenieo=0;
                                if (poraroku==1){wyswietlenieo+=2;}
                                else if ((poraroku==2)||(poraroku==4)) {wyswietlenieo+=4;}
                                else {wyswietlenieo+=5;}                                      ///zasieg widzenia postaci
                                if ((godzina>=9)&&(godzina<=15)) {wyswietlenieo+=5;}
                                else if ((godzina>15)&&(godzina<20)){wyswietlenieo+=3;}
                                else if ((godzina>20)&&(godzina<24)) {wyswietlenieo+=1;}
                  wyswietlanie(mapa, pozycjaX, pozycjaY, pole, rozpaloneognisko, bandytaX, bandytaY, wytrzymaloscs, wyswietlenieo);
                  if (dzien>dzienrozpalenia) {rozpaloneognisko=0; pole[ogniskoX][ogniskoY]=1;}
                                            if ((pole[pozycjaX][pozycjaY]>7)&&(pole[pozycjaX][pozycjaY]<10)) ///podnoszenie przedmiotów
                          {
                              if (ruch!='x'){cout<<"Patyk"<<endl;}
                              if ((ruch=='x')||(autozbieranie==true)){
                              pole[pozycjaX][pozycjaY]=1;
                              przedmiot[1]++;
                              waga+=0.1;
                              }
                          }
                          else if (pole[pozycjaX][pozycjaY]==10)
                          {
                              if (ruch!='x'){cout<<"Kamyk"<<endl;}
                              if ((ruch=='x')||(autozbieranie==true)){
                              pole[pozycjaX][pozycjaY]=1;
                              przedmiot[2]++;
                              waga+=0.3;
                              }
                          }
                          else if (pole[pozycjaX][pozycjaY]==11)
                          {
                              zdrowie=walka(zdrowie, zmeczenie, smierc, przedmiot, pozycjaX, pozycjaY, wyposazenie, "Jelen");
                              pole[pozycjaX][pozycjaY]=1;
                          }
                          else if (pole[pozycjaX][pozycjaY]==12)
                          {
                              if (ruch!='x'){cout<<"Krzak borowek"<<endl;}
                              if ((ruch=='x')||(autozbieranie==true)){
                              pole[pozycjaX][pozycjaY]=1;
                              przedmiot[4]++;
                              waga+=0.5;
                              }
                          }
                          else if (pole[pozycjaX][pozycjaY]==13){
                            if (ruch!='x'){cout<<"Drzewo"<<endl;}
                            if (wyposazenie[2]==2){
                                if ((zmeczenie<=20)&&(ruch=='x')){
                                    cout<<"Sciales drzewo."<<endl;
                                    pole[pozycjaX][pozycjaY]=20;
                                    zmeczenie+=80;
                                }
                                else if (ruch=='x') {cout<<"Jestes zbyt zmeczony aby sciac to drzewo."<<endl;}
                            }
                          }
                          else if (pole[pozycjaX][pozycjaY]==20){

                                if (wyposazenie[2]==2){
                                if (ruch!='x'){cout<<"Powalone drzewo"<<endl;}
                                if ((zmeczenie<=50)&&(ruch=='x')){
                                int *losdrz=new int;
                                *losdrz=rand()%3+6;
                                przedmiot[13]+=*losdrz;
                                zmeczenie+=50;
                                pole[pozycjaX][pozycjaY]=1;
                                waga+=1**losdrz;
                                delete losdrz;
                                                          }else if (ruch=='x'){cout<<"Jestes zbyt zmeczony aby pocwiartowac to drzewo.\n";}
                                                      }
                                                                }
                          ruch=interfejs(dzien, poraroku, pozycjaX, pozycjaY, pole, glod, zdrowie, smierc, ruch, temperatura, godzina, minuta, zmeczenie);
                        switch (ruch)
                        {
                        case 'w': ///poruszanie siê
                            {
                                if (zmeczenie<95)
                                {
                                if ((mapa[pozycjaX-1] [pozycjaY]==0)||(mapa[pozycjaX-1][pozycjaY]==20))
                                {
                                    pozycjaX--;
                                    glod+=2;
                                    zmeczenie+=3;
                                    if (wyposazenie[5]==1){
                                        zmeczenie--;
                                    }
                                    minuta+=10;
                                }
                                }
                                break;
                            }
                        case 'a':
                            {
                                if (zmeczenie<95)
                                {
                                if ((mapa[pozycjaX] [pozycjaY-1]==0)||(mapa[pozycjaX][pozycjaY-1]==20))
                                {
                                    pozycjaY--;
                                    glod+=2;
                                    zmeczenie+=3;
                                    if (wyposazenie[5]==1){
                                        zmeczenie--;
                                    }
                                    minuta+=10;
                                }
                                }
                                break;
                            }
                        case 's':
                            {
                                if (zmeczenie<95)
                                {
                                if ((mapa[pozycjaX+1] [pozycjaY]==0)||(mapa[pozycjaX+1][pozycjaY]==20))
                                {
                                    pozycjaX++;
                                    glod+=2;
                                    zmeczenie+=3;
                                    if (wyposazenie[5]==1){
                                        zmeczenie--;
                                    }
                                    minuta+=10;
                                }
                                }
                            }
                            break;
                        case 'd':
                            {
                                if (zmeczenie<95)
                                {
                                if ((mapa[pozycjaX] [pozycjaY+1]==0)||(mapa[pozycjaX][pozycjaY+1]==20))
                                {
                                    pozycjaY++;
                                    glod+=2;
                                    zmeczenie+=3;
                                    if (wyposazenie[5]==1){
                                        zmeczenie--;
                                    }
                                    minuta+=10;
                                }
                                }
                                break;
                            }
                        case 'e': ///eq
                            {
                                wierszpolecen(przedmiot, glod, zmeczenie, krew, wyposazenie, waga, wybor3, poprzedniw, zdrowie, pole, pozycjaX, pozycjaY, dzienrozpalenia, dzien, rozpaloneognisko, ogniskoX, ogniskoY, mapa, wytrzymaloscs);
                                break;
                            }
                        case 'z': ///zapis gry      TODO: ulepszenie zapisu gry (narazie zapisuje tylko czesc rzeczy)
                            {
                                cout<<endl<<"Na pewno chcesz zapisac?? "<<endl<<
                                "1 - tak"<<endl<<
                                "2 - nie"<<endl;
                                cin>>wybor2;
                                if (wybor2==1)
                                {
                            plik.open("zapis.txt", ios::out);
                            for (int x=1; x<100; x++)
                            {
                                for (int y=1; y<100; y++)
                            {
                              plik<<pole[x][y]<<endl;
                            }
                            }
                                for (int l=0; l<12; l++){
                                    plik<<przedmiot[l]<<endl;
                                }
                                for (int l=0; l<6; l++){
                                    plik<<wyposazenie[l]<<endl;
                                }
                            plik<<glod<<endl;
                            plik<<zmeczenie<<endl;
                            plik<<zdrowie<<endl;
                            plik<<pozycjaX<<endl;
                            plik<<pozycjaY<<endl;
                            plik.close();
                                }
                                break;
                            }
                        case 'r': ///wczytanie gry
                            {
                            plik.open("zapis.txt", ios::in);
                            if (plik.good()==false)
                            {
                                cout<<"\aNie znalazlem zapisu!";
                                getch();
                                break;
                            }
                            for (int x=1; x<100; x++)
                            {
                                for (int y=1; y<100; y++)
                            {
                                getline (plik, linia);
                                pole[x][y]=atoi(linia.c_str());
                            }
                            }
                            for (int l=0; l<12; l++){
                            getline(plik, linia);
                            przedmiot[l]=atoi(linia.c_str());
                            }
                            for (int l=0; l<6; l++){
                                getline(plik, linia);
                                wyposazenie[l]=atoi(linia.c_str());
                            }
                            plik.close();
                            break;
                            }
                        case 't': ///sen
                            {
                                if ((((mapa[pozycjaX+1][pozycjaY]<20)||(mapa[pozycjaX-1][pozycjaY]<20)||(mapa[pozycjaX][pozycjaY+1]<20)||(mapa[pozycjaX][pozycjaY-1]<20)))){
                                system("cls");
                                cout<<"Spisz..."<<endl;
                                if (rozpaloneognisko==1) {cout<<"W nocy Twoje ognisko zgaslo."; pole[ogniskoX][ogniskoY]=1; rozpaloneognisko=0;}
                                Sleep(1500);
                                zmeczenie=0;
                                godzina+=8;
                                glod+=20;
                                temperatura=rand()%21;
                                }
                                else{
                                    cout<<"\aNie mozesz spac, kiedy w poblizu znajduje sie wrog!"<<endl;
                                    getch();
                                }
                                break;
                            }
                        case 'x': ///interakcja z przedmiotami
                            {
                                if ((pole[pozycjaX][pozycjaY]==21)&&(rozpaloneognisko==1)){
                                system("cls");
                                cout<<"Co chcesz zrobic?"<<endl<<"Napisz ''pomoc ognisko'' jesli nie wiesz co wpisac"<<endl;
                                getline (cin, wyboro);
                                if (wyboro=="ugotuj mieso")
                                {
                                    if (przedmiot[3]>0){
                                    cout<<"Gotuje..."<<endl;
                                    przedmiot[3]--;
                                    przedmiot[6]++;
                                    Sleep(1000);
                                    }
                                    else{
                                        cout<<"Nie posiadasz nieugotowanego miesa."<<endl;
                                        getch();
                                    }
                                }
                                else if (wyboro=="pomoc ognisko")
                                {
                                    pomoc(2);
                                }
                                system("cls");
                            }
                            break;
                            }
                        case 'm':{
                                int *potwierdzenie= new int;
                                cout<<"\nCzy na pewno chcesz usunac te sciane?"<<endl<<"1 - tak"<<endl<<"0 - nie"<<endl;
                                cin>>*potwierdzenie;
                                if (*potwierdzenie==1){
                                if (mapa[pozycjaX+1][pozycjaY]==2){
                                    mapa[pozycjaX+1][pozycjaY]=0;
                                    przedmiot[1]+=3;
                                }
                                else if (mapa[pozycjaX-1][pozycjaY]==2){
                                    mapa[pozycjaX-1][pozycjaY]=0;
                                    przedmiot[1]+=3;
                                }
                                else if (mapa[pozycjaX][pozycjaY+1]==2){
                                    mapa[pozycjaX][pozycjaY+1]=0;
                                    przedmiot[1]+=3;
                                }
                                else if (mapa[pozycjaX][pozycjaY-1]==2){
                                    mapa[pozycjaX][pozycjaY-1]=0;
                                    przedmiot[1]+=3;
                                }
                                }
                                delete potwierdzenie;
                                break;
                            }
                        case '=':{
                            if(autozbieranie==false){autozbieranie=true;}
                            else{autozbieranie=false;}
                            break;
                        }
                        case 'p': {pomoc(0); break;} ///pomoc
                    }
                    if (smierc==1){
                        ruch='q';
                    }
                            if ((pozycjaX==bandytaX)&&(pozycjaY==bandytaY)){
                            zdrowie=walka(zdrowie, zmeczenie, smierc, przedmiot, pozycjaX, pozycjaY, wyposazenie, "Bandyta");
                            mapa[pozycjaX][pozycjaY]=0;
                            zyjacybandyta=0;
                            Sleep(1000);
                           }
          }
          }
    }
    return 0;
}
void pomoc (int jakapomoc) //pomoce
{
    switch (jakapomoc)
    {
        case 0:           cout<<endl<<"Pomoc:"<<endl<<
                          "WASD - poruszanie sie"<<endl<<
                          "E - ekwipunek"<<endl<<
                          "T - spij"<<endl<<
                          "Q - wyjscie"<<endl<<
                          "Z - zapis"<<endl<<
                          "R - wczytaj"<<endl; getch(); break;
        case 1:system("cls");cout<<"zjedz borowki"<<endl<<
                            "zjedz mieso - zjedz nieugotowane mieso"<<endl<<
                            "rozpal ognisko"<<endl<<
                            "zjedz ugotowane mieso"<<endl<<
                            "stworz podstawowy noz (4 kamienia 2 drewna)"<<endl<<
                            "wybuduj drewniana sciane (5 drewna)"<<endl<<
                            "nic - nie rob nic"<<endl;
                            getch(); system("cls"); break;

        case 2:             cout<<"ugotuj mieso"<<endl;
                            Sleep(1000); break;
    }
}
string ekwipunek(int *przedmiot, int glod, int zmeczenie, int krew, int *wyposazenie, float &waga){ ///ekwipunek
                                waga=0;
                                string wybor3;
                                system("cls");
                                cout<<"Ekwipunek: "<<endl;
                                if (przedmiot[1]>=1)
                                {
                                    cout<<"Patyki x"<<przedmiot[1]<<endl;
                                    waga+=przedmiot[1]*0.1;
                                }
                                if (przedmiot[2]>=1)
                                {
                                    cout<<"Kamien x"<<przedmiot[2]<<endl;
                                    waga+=przedmiot[2]*0.3;
                                }
                                if (przedmiot[3]>=1)
                                {
                                    cout<<"Nieugotowane mieso x"<<przedmiot[3]<<endl;
                                    waga+=przedmiot[3]*0.7;
                                }
                                if (przedmiot[4]>=1)
                                {
                                    cout<<"Borowki x"<<przedmiot[4]<<endl;
                                    waga+=przedmiot[4]*0.5;
                                }
                                if (przedmiot[5]>=1)
                                {
                                    cout<<"Skora x"<<przedmiot[5]<<endl;
                                    waga+=przedmiot[5]*0.8;
                                }
                                if (przedmiot[6]>=1)
                                {
                                    cout<<"Ugotowane mieso x"<<przedmiot[6]<<endl;
                                    waga+=przedmiot[6]*0.8;
                                }
                                if (przedmiot[7]>=1)
                                {
                                    cout<<"Podstawowy noz x"<<przedmiot[7]<<endl;
                                    waga+=przedmiot[7]*0.7;
                                }
                                if (przedmiot[8]>=1){
                                    cout<<"Skorzana czapka x"<<przedmiot[8]<<endl;
                                    waga+=przedmiot[8]*0.6;
                                }
                                if (przedmiot[9]>=1){
                                    cout<<"Skorzana koszulka x"<<przedmiot[9]<<endl;
                                    waga+=przedmiot[9]*0.8;
                                }
                                if (przedmiot[10]>=1){
                                    cout<<"Skorzane spodnie x"<<przedmiot[10]<<endl;
                                    waga+=przedmiot[10]*0.8;
                                }
                                if (przedmiot[11]>=1){
                                    cout<<"Skorzane buty x"<<przedmiot[11]<<endl;
                                    waga+=przedmiot[11]*0.6;
                                }
                                if (przedmiot[12]>=1){
                                    cout<<"Podstawowa siekiera x"<<przedmiot[12]<<endl;
                                    waga+=przedmiot[12]*1.3;
                                }
                                if (przedmiot[13]>=1){
                                    cout<<"Drewno x"<<przedmiot[13]<<endl;
                                    waga+=przedmiot[13];
                                }
                                if (waga==0)
                                {
                                    cout<<"Nie masz nic przy sobie."<<endl;
                                }
                                cout<<endl<<endl<<"Potrzeby:  "<<endl<<
                                "Glod - ";
                                if (glod<=20) {cout<<"Czuje sie najedzony."<<endl;}
                          else  if (glod<=40) {cout<<"Zjadlbym cos."<<endl;}
                          else  if (glod<=60) {cout<<"Lepiej poszukam czegos do zjedzenia."<<endl;}
                          else  if (glod<=80) {cout<<"Koniecznie musze cos zjesc."<<endl;}
                          else  if (glod<=100) {cout<<"Jedzenie.. oddam wszystko za borowke."<<endl;}
                          cout<<"Zmeczenie - "<<zmeczenie<<"/100"<<endl<<
                                "Krew - "<<krew<<"/5000"<<endl<<endl;
                                cout<<"Wyposazenie:"<<endl;
                             cout<<"Glowa - ";
                             if (wyposazenie[0]==1){
                                cout<<"skorzana czapka"<<endl;
                                waga+=0.6;
                             }
                             else{
                                cout<<"nic"<<endl;
                             }
                             cout<<"Tulow - ";
                             if (wyposazenie[1]==1){
                                cout<<"skorzana koszulka"<<endl;
                                waga+=0.8;
                             }
                             else{cout<<"nic"<<endl;}
                             cout<<"Prawa reka - ";
                             if (wyposazenie[2]==1){
                                cout<<"podstawowy noz"<<endl;
                                waga+=0.7;
                             }
                             else if (wyposazenie[2]==2){
                                cout<<"podstawowa siekiera"<<endl;
                                waga+=1.3;
                             }
                             else{
                                cout<<"nic"<<endl;
                             }
                             cout<<"Lewa reka - nic"<<endl;
                             cout<<"Nogi - ";
                             if (wyposazenie[4]==1){
                                cout<<"skorzane spodnie"<<endl;
                                waga+=0.8;
                             }
                             else{
                                cout<<"nic"<<endl;
                             }
                             cout<<"Buty - ";
                             if (wyposazenie[5]==1){
                                cout<<"skorzane buty"<<endl;
                                waga+=0.6;
                             }
                             else{
                                cout<<"nic"<<endl;
                             }
                             cout<<"Waga: "<<waga<<endl;
                                    cout<<"Co chcesz zrobic?"<<endl<<"Jezeli nie wiesz co wpisac, napisz ''pomoc''"<<endl;
                                    getline (cin, wybor3);
                                    transform (wybor3.begin(), wybor3.end(), wybor3.begin(), ::tolower);
                                    return wybor3;
}
string biom(){

return "lol";
}
int walka(int zdrowie, int &zmeczenie, int smierc, int *przedmiot, int pozycjaX, int pozycjaY, int *wyposazenie, string rodzajp){ ///system walki
                                        system("cls");
                                        HANDLE uchwyt = GetStdHandle( STD_OUTPUT_HANDLE );
                                        int obrazenia, zdrowiep=100, obrazeniap;
                                        cout<<"Rozpoczales walke z "<<rodzajp<<endl;
                                        while ((zdrowie>0)&&(zdrowiep>0))
                                        {
                                        cout<<rodzajp;
                                        if (zdrowiep>=80) { SetConsoleTextAttribute(uchwyt, 10); cout<<"(zdrowy)"; SetConsoleTextAttribute(uchwyt, 15);}
                                        else if (zdrowiep>=60) {SetConsoleTextAttribute(uchwyt, 14); cout<<"(ranny)";SetConsoleTextAttribute(uchwyt, 15);}
                                        else if (zdrowiep>=40) {SetConsoleTextAttribute(uchwyt, 6); cout<<"(ciezko ranny)";SetConsoleTextAttribute(uchwyt, 15);}
                                        else if (zdrowiep>=20) {SetConsoleTextAttribute(uchwyt, 12); cout<<"(zmasakrowany)";SetConsoleTextAttribute(uchwyt, 15);}
                                        else {SetConsoleTextAttribute(uchwyt, 4); cout<<"(w agonii)";SetConsoleTextAttribute(uchwyt, 15);}
                                        cout<<endl;
                                        obrazenia=rand()%21;
                                        if (obrazenia>=17) {cout<<"Ty: Mocne uderzenie!"<<endl;}
                                        else if (obrazenia>=7) {cout<<"Ty: Cios."<<endl;}
                                        else if (obrazenia>=3)  {cout<<"Ty: Slabe uderzenie."<<endl;}
                                        else {cout<<"Ty: Pudlo."<<endl;}
                                        if (wyposazenie[2]==1) {obrazenia+=5;}
                                        zdrowiep-=obrazenia;
                                        Sleep(1000);
                                        obrazeniap=rand()%11;
                                        if (obrazeniap>=7) {cout<<rodzajp<<": Mocne uderzenie!"<<endl;}
                                        else if (obrazeniap>=5) {cout<<rodzajp<<": Cios."<<endl;}
                                        else if (obrazeniap>=3)  {cout<<rodzajp<<": Slabe uderzenie."<<endl;}
                                        else {cout<<rodzajp<<": Pudlo."<<endl;}
                                        if (rodzajp=="Bandyta"){obrazeniap+=15;}
                                        zdrowie-=obrazeniap;
                                        Sleep(1000);
                                        system("cls");
                                        }
                                        if (zdrowiep<=0)
                                        {
                                            cout<<endl<<"Wygrales walke!"<<endl<<"Nacisnij enter."<<endl<<endl;
                                            if (rodzajp=="Jelen"){
                                            przedmiot[3]+=rand()%3+1;
                                            przedmiot[5]+=rand()%3+1;
                                            }
                                            zmeczenie+=10;
                                        }
                                        if (zdrowie<=0)
                                        {
                                            cout<<"Zginales.";
                                            smierc=1;
                                        }
                                        return zdrowie;
}
char interfejs(int &dzien, int &poraroku, int pozycjaX, int pozycjaY, int pole[100][100], int &glod, int &zdrowie, int &smierc, char ruch, double temperatura, int &godzina, int &minuta, int &zmeczenie){
                HANDLE uchwyt=GetStdHandle(STD_OUTPUT_HANDLE);
                  if (glod>100) {glod=100;}
                  if (glod<0) {glod=0;}
                  if (zmeczenie>=95){
                  SetConsoleTextAttribute(uchwyt, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                  cout<<"Przemeczony"<<endl;
                  SetConsoleTextAttribute(uchwyt, 15);
                  }
                  if (glod==100){
                    SetConsoleTextAttribute(uchwyt, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    cout<<"\aGlod"<<endl;
                    SetConsoleTextAttribute(uchwyt, 15);
                  if ((((ruch=='w')||(ruch=='a')||(ruch=='s')||(ruch=='d')))){zdrowie-=5;}
                  }
                  if (zdrowie<=0){
                    cout<<endl<<"Smierc."<<endl;
                    smierc=1;
                    getch();
                  }
                    cout<<"P - pomoc"<<endl;
                    cout<<temperatura<<"C"<<endl;
                    cout<<"Dzien - "<<dzien<<"      Pora roku: ";
                          if (dzien==20) {poraroku++; dzien=0;}
                          if (poraroku==5) {poraroku=1;}
                          if (poraroku==2) {cout<<"Wiosna";}            ///interfejs
                          else if (poraroku==3) {cout<<"Lato";}
                          else if (poraroku==4) {cout<<"Jesien";}
                          else {cout<<"Zima";}
                          cout<<endl<<godzina<<":"<<minuta;
                          if (minuta==0){cout<<"0";}
                          if (pole[pozycjaX][pozycjaY]==21) {cout<<endl<<"X - interakcja"<<endl;}
                          cout<<endl<<pozycjaX<<"     "<<pozycjaY<<endl;
                        return ruch=getch();
}
void wyswietlanie(int mapa[100][100], int pozycjaX, int pozycjaY, int pole[100][100], int rozpaloneognisko, int &bandytaX, int &bandytaY, int wytrzymaloscs[100][100], int wyswietlenieo){
    HANDLE uchwyt=GetStdHandle(STD_OUTPUT_HANDLE);
    int wyswietlenieod=wyswietlenieo;
    fstream fileerr;
    bool *konieclinii = new bool;
    system("cls");
                  for (int x=pozycjaX-wyswietlenieod; x<pozycjaX+wyswietlenieo; x++)
                  {              ///wyswietlanie mapy
                      for (int y=pozycjaY-wyswietlenieod; y<pozycjaY+wyswietlenieo; y++)
                      {
                          if ((((x>=0)&&(x<=100)&&(y>=0)&&(y<=100)))){
                                *konieclinii=true;
                        switch (mapa[x][y])
                          {
                          case 0:
                            {
                                if ((pozycjaX==x)&&(pozycjaY==y))
                                {
                                    cout<<"0";
                                }
                                else
                                {
                                    if (pole[x][y]<=7)
                                    {
                                        cout<<" ";
                                    }
                                    else if (pole[x][y]<=9)
                                    {
                                        SetConsoleTextAttribute(uchwyt, 4);
                                        cout<<"P";
                                        SetConsoleTextAttribute(uchwyt, 15);

                                    }
                                    else if (pole[x][y]==10)
                                    {
                                        SetConsoleTextAttribute(uchwyt, 8);
                                        cout<<"K";
                                        SetConsoleTextAttribute(uchwyt, 15);
                                    }
                                    else if (pole[x][y]==11)
                                    {
                                        cout<<"J";
                                    }
                                    else if (pole [x][y]==12)
                                    {
                                        SetConsoleTextAttribute(uchwyt, 9);
                                        cout<<"B";
                                        SetConsoleTextAttribute(uchwyt, 15);
                                    }
                                    else if (pole[x][y]==13){
                                        SetConsoleTextAttribute(uchwyt, FOREGROUND_RED);
                                        cout<<"D";
                                        SetConsoleTextAttribute(uchwyt, 15);
                                    }
                                    else if (pole[x][y]==20){
                                        SetConsoleTextAttribute(uchwyt, 7);
                                        cout<<"D";
                                        SetConsoleTextAttribute(uchwyt, 15);
                                    }
                                    else if ((pole[x][y]==21)&&(rozpaloneognisko==1))
                                    {
                                    SetConsoleTextAttribute(uchwyt, 12);
                                    cout<<"O";
                                    SetConsoleTextAttribute(uchwyt, 15);
                                    }
                                }
                                break;
                            }
                          case 1:
                            {
                               cout<<"X";
                               break;
                            }
                            case 2:{
                                if (wytrzymaloscs[x][y]>99){
                                SetConsoleTextAttribute(uchwyt, BACKGROUND_RED);
                                }
                                else if (wytrzymaloscs[x][y]<1){
                                    mapa[x][y]=0;
                                }
                                else{
                                    SetConsoleTextAttribute(uchwyt, BACKGROUND_RED | FOREGROUND_RED | BACKGROUND_INTENSITY);
                                }
                                cout<<" ";
                                SetConsoleTextAttribute(uchwyt, 15);
                                break;
                            }
                            case 3:{
                                if (wytrzymaloscs[x][y]==60){
                                    SetConsoleTextAttribute(uchwyt, FOREGROUND_RED);
                                }
                                else if (wytrzymaloscs[x][y]==0){
                                    mapa[x][y]=0;
                                }
                                else{
                                    SetConsoleTextAttribute(uchwyt, FOREGROUND_RED | FOREGROUND_INTENSITY);
                                }
                                if ((mapa[x][y+1]==2)||(mapa[x][y-1]==2)){cout<<"-";}
                                else{cout<<"|";}
                                SetConsoleTextAttribute(uchwyt, 15);
                                break;
                            }
                            case 4:{
                                SetConsoleTextAttribute(uchwyt, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                cout<<" ";
                                SetConsoleTextAttribute(uchwyt, 15);
                                break;
                            }
                            case 20:{
                                if ((x==bandytaX)&&(y==bandytaY)){
                                SetConsoleTextAttribute(uchwyt, FOREGROUND_RED | FOREGROUND_INTENSITY);
                            cout<<"B";
                                SetConsoleTextAttribute(uchwyt, 15);
                                }
                                else{
                                    SetConsoleTextAttribute(uchwyt, FOREGROUND_RED | FOREGROUND_INTENSITY);
                                    cout<<"E";
                                    SetConsoleTextAttribute(uchwyt, 15);
                                    fileerr.open("errors.txt", ios::app);
                                    fileerr<<"Found an error[2] - more than 1 bandit ("<<x<<","<<y<<")"<<endl;
                                    fileerr.close();
                                }
                                break;
                            }
                            default:{
                            SetConsoleTextAttribute(uchwyt, FOREGROUND_RED | FOREGROUND_INTENSITY);
                            cerr<<"E";
                            fileerr.open("errors.txt", ios::app);
                            fileerr<<"Found an error [1] - unexpected tile ("<<x<<", "<<y<<")"<<endl;
                            fileerr.close();
                            SetConsoleTextAttribute(uchwyt, 15);
                            break;
                            }
                          }
                          }
                          else{
                            *konieclinii=false;
                          }
                          if (y>100){*konieclinii=true;}
                      }
                      if (*konieclinii==true){
                      cout<<endl;
                      }
                  }
                  delete konieclinii;
}
void sztucznaint(int zyjacybandyta, int pozycjaX, int pozycjaY, int &bandytaX, int &bandytaY, int wytrzymaloscs[100][100], int mapa[100][100]){
                                if (zyjacybandyta==1){
                                int loso=rand()%2+1;  ///SZTUCZNA INTELIGENCJA PRZECIWNIKÓW
                                bool *ataksciany = new bool;
                                *ataksciany=true;
                                if (pozycjaX-bandytaX==0){
                                    loso=2;
                                }
                                if (pozycjaY-bandytaY==0){
                                    loso=1;
                                }
                            if (loso==1){
                            if (pozycjaX-bandytaX>0){
                                if ((mapa[bandytaX+1][bandytaY]==0)||(mapa[bandytaX+1][bandytaY]==1)){
                                mapa[bandytaX][bandytaY]=0;
                                mapa[bandytaX+1][bandytaY]=20;
                                bandytaX++;
                                *ataksciany=false;
                                }
                                else if ((mapa[bandytaX+1][bandytaY]==2)&&(*ataksciany==true)){
                                    wytrzymaloscs[bandytaX+1][bandytaY]-=10;
                                }
                            }
                            if (pozycjaX-bandytaX<0){
                                if ((mapa[bandytaX-1][bandytaY]==0)||(mapa[bandytaX-1][bandytaY]==1)){
                                mapa[bandytaX][bandytaY]=0;
                                mapa[bandytaX-1][bandytaY]=20;
                                bandytaX--;
                                *ataksciany=false;
                                }
                                else if ((mapa[bandytaX-1][bandytaY]==2)&&(*ataksciany==true)){
                                    wytrzymaloscs[bandytaX-1][bandytaY]-=10;
                                }
                            }
                            }
                            else{
                            if (pozycjaY-bandytaY>0){
                                if ((mapa[bandytaX][bandytaY+1]==0)||(mapa[bandytaX][bandytaY+1]==1)){
                                mapa[bandytaX][bandytaY]=0;
                                mapa[bandytaX][bandytaY+1]=20;
                                bandytaY++;
                                *ataksciany=false;
                                }
                                else if ((mapa[bandytaX][bandytaY+1]==2)&&(*ataksciany==true)){
                                    wytrzymaloscs[bandytaX][bandytaY+1]-=10;
                                }
                            }
                            if (pozycjaY-bandytaY<0){
                                if ((mapa[bandytaX][bandytaY-1]==0)||(mapa[bandytaX][bandytaY-1]==1)){
                                mapa[bandytaX][bandytaY]=0;
                                mapa[bandytaX][bandytaY-1]=20;
                                bandytaY--;
                                *ataksciany=false;
                                }
                                else if ((mapa[bandytaX][bandytaY-1]==2)&&(*ataksciany==true)){
                                    wytrzymaloscs[bandytaX][bandytaY-1]-=10;
                                }
                            }
                            }

                            delete ataksciany;
                                }
}
void wierszpolecen(int *przedmiot, int &glod, int &zmeczenie, int &krew, int *wyposazenie, float &waga, string &wybor3, string &poprzedniw,
                   int &zdrowie, int pole[100][100], int pozycjaX, int pozycjaY, int &dzienrozpalenia, int dzien, int &rozpaloneognisko,
                   int &ogniskoX, int &ogniskoY, int mapa[100][100], int wytrzymaloscs[100][100])
                                {
                                bool *petla= new bool;
                                int knc=1;
                                if (wybor3.length()>0){ poprzedniw=wybor3; }
                                wybor3=ekwipunek(przedmiot, glod, zmeczenie, krew, wyposazenie, waga);
                                string *blok=new string;
                                *blok=wybor3.substr(0,7);
                                do{
                            *petla=false;

                            if (*blok=="zdejmij"){

                                    if (wybor3=="zdejmij glowa"){

                                        if (wyposazenie[0]==1){
                                            wyposazenie[0]=0;
                                            przedmiot[8]++;
                                        }
                                    }
                                    else if (wybor3=="zdejmij tulow"){

                                            if (wyposazenie[1]==1){
                                                wyposazenie[1]=0;
                                                przedmiot[9]++;
                                            }
                                    }
                                    else if (wybor3=="zdejmij prawa"){

                                            if (wyposazenie[2]==1){
                                                wyposazenie[2]=0;
                                                przedmiot[7]++;
                                            }
                                            else if (wyposazenie[2]==2){
                                                wyposazenie[2]=0;
                                                przedmiot[12]++;
                                            }
                                    }
                                    else if (wybor3=="zdejmij lewa"){

                                            if (wyposazenie[3]==1){

                                            }
                                    }
                                    else if (wybor3=="zdejmij nogi"){

                                            if (wyposazenie[4]==1){
                                                wyposazenie[4]=0;
                                                przedmiot[10]++;
                                            }
                                    }
                                    else if (wybor3=="zdejmij stopy"){

                                            if (wyposazenie[5]==1){
                                                wyposazenie[5]=0;
                                                przedmiot[11]++;
                                            }
                                    }
                            }

                                    if (wybor3=="zjedz borowki")
                                    {
                                        if (przedmiot[4]>0)
                                        {
                                        cout<<"Zjadles borowki."<<endl;
                                        przedmiot[4]--;
                                        glod-=5;
                                        }
                                        else {cout<<"Nie posiadasz borowek."<<endl;}
                                    }
                                    else if (wybor3=="zjedz mieso")
                                    {
                                        if (przedmiot[3]>0)
                                        {
                                        cout<<"Zjadles nieugotowane mieso."<<endl;
                                        przedmiot[3]--;
                                        glod-=15;
                                        zdrowie-=10;
                                        }
                                        else {cout<<"Nie posiadasz nieugotowanego miesa."<<endl;}
                                    }
                                    else if (wybor3=="rozpal ognisko")
                                    {
                                        if ((przedmiot[1]>4)&&(przedmiot[2]>2)){
                                        cout<<"Rozpalam..."<<endl;
                                        przedmiot[1]-=5;
                                        przedmiot[2]-=3;
                                        pole [pozycjaX][pozycjaY]=21;
                                        dzienrozpalenia=dzien;
                                        rozpaloneognisko=1;
                                        ogniskoX=pozycjaX; ogniskoY=pozycjaY;
                                        }
                                        else{
                                            cout<<"Nie posiadasz wystarczajacej ilosci materialow."<<endl;
                                        }
                                        cout<<"Nacisnij enter."<<endl;
                                        getch();
                                    }
                                    else if (wybor3=="zjedz ugotowane mieso")
                                    {
                                        if (przedmiot[6]>0)
                                        {
                                        cout<<"Zjadles ugotowane mieso"<<endl;
                                        przedmiot[6]--;
                                        glod-=37;
                                        }
                                        else {cout<<"Nie posiadasz ugotowanego miesa."<<endl;}
                                    }
                                    else if (wybor3=="stworz podstawowy noz")
                                    {
                                        if ((przedmiot[1]>=2)&&(przedmiot[2]>=4))
                                        {
                                        cout<<"Tworze..."<<endl;
                                        przedmiot[1]-=2;
                                        przedmiot[2]-=4;
                                        przedmiot[7]++;
                                        }
                                        else {cout<<"Nie posiadasz wystarczajaco materialow"<<endl;}
                                    }
                                    else if (wybor3=="wybuduj drewniana sciane"){
                                        if (przedmiot[1]>=5){
                                        if (mapa[pozycjaX][pozycjaY]==0){
                                        mapa[pozycjaX][pozycjaY]=2;
                                        przedmiot[1]-=5;
                                        wytrzymaloscs[pozycjaX][pozycjaY]=100;
                                        }
                                        else{
                                            cout<<"Na tym polu postawiles juz sciane."<<endl;
                                            Sleep(1500);
                                        }
                                        }
                                        else{
                                            cout<<"Nie posiadasz wystarczajacej ilosci materialow."<<endl;
                                            Sleep(1500);
                                        }
                                    }
                                    else if (wybor3=="wybuduj drewniane drzwi"){
                                        if (przedmiot[1]>=3){
                                        if (mapa[pozycjaX][pozycjaY]==0){
                                            przedmiot[1]-=3;
                                            mapa[pozycjaX][pozycjaY]=3;
                                            wytrzymaloscs[pozycjaX][pozycjaY]=60;
                                        }
                                        else{
                                            cout<<"Na tym polu postawiles juz sciane!"<<endl;
                                            Sleep(1500);
                                        }
                                        }
                                        else{
                                            cout<<"Nie posiadasz wystarczajacej ilosci materialow."<<endl;
                                            Sleep(1500);
                                        }
                                    }
                                    else if (wybor3=="stworz skorzana czapke"){
                                        if (przedmiot[5]>0){
                                        przedmiot[8]++;
                                        przedmiot[5]--;
                                        }
                                        else{
                                            cout<<"Nie masz wystarczajacej ilosci materialow."<<endl;
                                        }
                                    }
                                    else if (wybor3=="stworz skorzana koszulke"){
                                        if (przedmiot[5]>2){
                                            przedmiot[9]++;
                                            przedmiot[5]-=3;
                                        }
                                        else{
                                            cout<<"Nie posiadasz wystarczajacej ilosci materialow"<<endl;
                                        }
                                    }
                                    else if (wybor3=="zaloz skorzana koszulke"){
                                        if (przedmiot[9]>0){
                                            wyposazenie[1]=1;
                                            przedmiot[9]--;
                                        }
                                        else{
                                            cout<<"Nie posiadasz skorzanej koszulki"<<endl;
                                        }
                                    }
                                    else if (wybor3=="zaloz skorzana czapke"){
                                        if (przedmiot[8]>0){
                                        wyposazenie[0]=1;
                                        przedmiot[8]--;
                                        }
                                        else{
                                            cout<<"Nie posiadasz skorzanej czapki."<<endl;
                                        }
                                    }
                                    else if (wybor3=="zaloz podstawowy noz"){
                                        if(przedmiot[7]>0){
                                        wyposazenie[2]=1;
                                        przedmiot[7]--;
                                        }
                                        else{
                                            cout<<"Nie posiadasz tego noza."<<endl;
                                        }
                                    }
                                    else if (wybor3=="stworz podstawowa siekiere"){

                                            if ((przedmiot[1]>=3)&&(przedmiot[2]>=2)){
                                                przedmiot[1]-=3;
                                                przedmiot[2]-=2;
                                                przedmiot[12]++;
                                            }
                                            else{cout<<"Nie posiadasz wystarczajacej ilosci materialow."<<endl;}
                                    }
                                    else if (wybor3=="zaloz podstawowa siekiere"){
                                        if (przedmiot[12]>0){
                                            wyposazenie[2]=2;
                                            przedmiot[12]--;
                                        }
                                        else {cout<<"Nie posiadasz tej siekiery."<<endl;}
                                    }
                                    else if (wybor3=="stworz skorzane spodnie"){
                                        if (przedmiot[5]>=3){
                                            przedmiot[5]-=3;
                                            przedmiot[10]++;
                                        }
                                        else{
                                            cout<<"Nie posiadasz tyle skory."<<endl;
                                        }
                                    }
                                    else if (wybor3=="zaloz skorzane spodnie"){
                                        if (przedmiot[10]>0){
                                            wyposazenie[4]=1;
                                            przedmiot[10]--;
                                        }
                                        else{
                                            cout<<"Nie posiadasz tych spodni"<<endl;
                                        }
                                    }
                                    else if (wybor3=="stworz skorzane buty"){
                                        if (przedmiot[5]>=2){
                                            przedmiot[5]-=2;
                                            przedmiot[11]++;
                                        }
                                        else{
                                            cout<<"Nie posiadasz tyle skory."<<endl;
                                        }
                                    }
                                    else if (wybor3=="zaloz skorzane buty"){
                                        if (przedmiot[11]>=1){
                                            przedmiot[11]--;
                                            wyposazenie[5]=1;
                                        }
                                        else{
                                            cout<<"Nie posiadasz tych butow."<<endl;
                                        }
                                    }
                                    else if (wybor3=="pomoc")
                                    {
                                    pomoc(1);
                                    }
                                    else if (wybor3=="p"){
                                        wybor3=poprzedniw;
                                        *petla=true;
                                    }
                                    knc++;
                                }while((*petla==true)&&(knc<3));
                                delete blok;
}
