#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//============================================================================================
class Contact{
private:
	string ver; //wersja pliku
	string name; //nazwa kontaktu
	string fullName; //pelna nazwa kontaktu
	string cNum; //numer komorkowy kontaktu
	string wNum; //numer sluzbowy kontaktu

public:
	Contact(){
		ver="2.1";
	};
	
	void setVer(string x)  { ver=x; }					//Publiczne funkcje ustawiajace wartosci zmiennych
	
	void setName(string x)  { name=x; }
	
	void setFullName(string x)  { fullName=x; }
	
	void setCNum(string x)  { cNum=x; }
	
	void setWNum(string x)  { wNum=x; }
	
	string getVer()  { return ver; }					//Publiczne funkcje zwracajace wartosci zmiennych
	
	string getName()  { return name; }
	
	string getFullName()  { return fullName; }
	
	string getCNum()  { return cNum; }
	
	string getWNum()  { return wNum; }
};
//============================================================================================
string PL(const char * text)
{
    string result;
    for(; * text; text++ )
    switch( * text ){
	    case 'π': result += static_cast < char >( 0xa5 ); break;
	    case 'Ê': result += static_cast < char >( 0x86 ); break;
	    case 'Í': result += static_cast < char >( 0xa9 ); break;
	    case '≥': result += static_cast < char >( 0x88 ); break;
	    case 'Ò': result += static_cast < char >( 0xe4 ); break;
	    case 'Û': result += static_cast < char >( 0xa2 ); break;
	    case 'ú': result += static_cast < char >( 0x98 ); break;
	    case 'ø': result += static_cast < char >( 0xbe ); break;
	    case 'ü': result += static_cast < char >( 0xab ); break;
	    case '•': result += static_cast < char >( 0xa4 ); break;
	    case '∆': result += static_cast < char >( 0x8f ); break;
	    case ' ': result += static_cast < char >( 0xa8 ); break;
	    case '£': result += static_cast < char >( 0x9d ); break;
	    case '—': result += static_cast < char >( 0xe3 ); break;
	    case '”': result += static_cast < char >( 0xe0 ); break;
	    case 'å': result += static_cast < char >( 0x97 ); break;
	    case 'Ø': result += static_cast < char >( 0xbd ); break;
	    case 'è': result += static_cast < char >( 0x8d ); break;
        default: result += * text; break;
    }
    return result;
}
//============================================================================================
int countContacts(){
	int nrl=0; //Numer linii, ktora jest atualnie czytana z pliku
	int nb=0; //Ilosc tagow zaczynajacych kontakt w pliku
	int ne=0; //Ilosc tagow konczoncych kontakt w pliku
	int last=0; //Zmienna oznaczajaca jaki tag wlasnie program odczytal, umozliwiajaca upenienie sie ze w pliku wystepuja naprzemiennie tagi zaczynajace i konczace; 0-tag konczacy; 1-tag zaczynajacy
	string line; //Zmienna przechowujaca ostatnia pobrana linie z pliku
	fstream file; //Zmienna odczytujaca plik
	
	file.open("kontakty.vcf",ios::in);
	
	if(!file.good()){
		cout<<PL("B≥πd podczas odczytu pliku: Nie znaleziono pliku!");
		return -1;
	}
	
	while(!file.eof()){
		getline(file,line);
		nrl++;
		if(line=="BEGIN:VCARD"){
			if(last==0){
				last=1;
				nb++;
			}
			else{
				cout<<PL("B≥πd podczas odczytu pliku: KolejnoúÊ tagÛw zamykajπcych i otwierajπcych nie zgadza sie (Dwa tagi otwierajπce z rzedu, linia:")<<nrl<<")!";
				return -1;
			}
		}
		else if(line=="END:VCARD"){
			if(last==1){
				last=0;
				ne++;
			}
			else{
				cout<<PL("B≥πd podczas odczytu pliku: KolejnoúÊ tagÛw zamykajπcych i otwierajπcych nie zgadza sie (Dwa tagi zamykajπce z rzedu, linia:")<<nrl<<")!";
				return -1;
			}
		}
	}
	
	
	
	file.close();
	if(nb==ne) return nb;
	else{
		cout<<PL("B≥πd podczas odczytu pliku: IloúÊ tagÛw zaczynajacych i koÒczπcych kontakty nie jest sobie rÛwna!");
		return -1;
	}
}
//============================================================================================
char mainMenu(){
	char choice=' ';
	
	SetConsoleTextAttribute(hConsole,3); cout<<"\t>";
	SetConsoleTextAttribute(hConsole,11); cout<<PL("Edytor kontaktÛw VCF");
	SetConsoleTextAttribute(hConsole,3); cout<<"<\n\n";
	SetConsoleTextAttribute(hConsole,15); cout<<"(";
	SetConsoleTextAttribute(hConsole,6); cout<<"1";
	SetConsoleTextAttribute(hConsole,15); cout<<") ";
	SetConsoleTextAttribute(hConsole,14);cout<<PL("Wyúwietl kontakty z pliku\n");
	SetConsoleTextAttribute(hConsole,15); cout<<"(";
	SetConsoleTextAttribute(hConsole,6); cout<<"2";
	SetConsoleTextAttribute(hConsole,15); cout<<") ";
	SetConsoleTextAttribute(hConsole,14);cout<<PL("Edycja kontaktÛw\n");
	SetConsoleTextAttribute(hConsole,15); cout<<"(";
	SetConsoleTextAttribute(hConsole,6); cout<<"3";
	SetConsoleTextAttribute(hConsole,15); cout<<") ";
	SetConsoleTextAttribute(hConsole,14);cout<<"Zapisz plik\n";
	SetConsoleTextAttribute(hConsole,15); cout<<"(";
	SetConsoleTextAttribute(hConsole,6); cout<<"4";
	SetConsoleTextAttribute(hConsole,15); cout<<")";
	SetConsoleTextAttribute(hConsole,14);cout<<" Zapisz do kopii pliku\n";
	SetConsoleTextAttribute(hConsole,15); cout<<"(";
	SetConsoleTextAttribute(hConsole,6); cout<<"5";
	SetConsoleTextAttribute(hConsole,15); cout<<")";
	SetConsoleTextAttribute(hConsole,14);cout<<PL(" Wyjúcie\n\n");
	
	while(true){
		choice = getch();
		if(choice=='1'||choice=='2'||choice=='3'||choice=='4'||choice=='5') break;
	}
	
	system("cls");
	
	return choice;
	
}
//============================================================================================
int main() {
	const int N = countContacts();
	if(N>0){
		Contact con[N];
		
		string line; //Zmienna przechowujaca ostatnia pobrana linie z pliku
		fstream file; //Zmienna odczytujaca plik
		int cnr=0; //zmienna przechowujaca numer porzadkowy aktualnie czytanego kontaktu
		
		file.open("kontakty.vcf",ios::in);
		while(!file.eof()){
			getline(file,line);
			if(line.substr(0,8)=="VERSION:") con[cnr].setVer(line.substr(8,line.length()-2));
			else if(line.substr(0,2)=="N:") con[cnr].setName(line.substr(2,line.length()-4));
			else if(line.substr(0,3)=="FN:") con[cnr].setFullName(line.substr(3,line.length()-2));
			else if(line.substr(0,9)=="TEL;CELL:") con[cnr].setCNum(line.substr(9,line.length()-2));
			else if(line.substr(0,9)=="TEL;WORK:") con[cnr].setWNum(line.substr(9,line.length()-2));
			else if(line=="END:VCARD") cnr++;
		}
		file.close();
		
		bool tr=true;
		
		while(tr){
			char ch=mainMenu();
			switch(ch){
				case '1':
					int maxLName=15,maxLNum=6;
					for(int i=0;i<N;i++){
					 	string name=con[i].getFullName(), cNum=con[i].getCNum(), wNum=con[i].getWNum();
					 	if(name.length()>maxLName) maxLName=name.length();
					 	if(cNum.length()+wNum.length()+7>maxLName) maxLNum=cNum.length()+wNum.length()+7;
					}
					 
					for(int i=-1;i<N;i++){
						if(i==-1){
							cout<<PL("ImiÍ i nazwisko");
					 		for(int j=0;j<maxLName-15;j++) cout<<" ";
					 		cout<<PL("|Numery");
					 		cout<<"\n";
					 		//---------------------------------------
					 		for(int j=0;j<maxLName;j++) cout<<"-";
					 		cout<<"+";
					 		for(int j=0;j<maxLNum;j++) cout<<"-";
					 		cout<<"\n";
					 		//---------------------------------------
						}
						else{
							string name=con[i].getFullName(), cNum=con[i].getCNum(), wNum=con[i].getWNum();
				 			//-----------------------------------
				 			SetConsoleTextAttribute(hConsole,14);
				 			cout<<name;
				 			SetConsoleTextAttribute(hConsole,15);
				 			for(int k=name.length();k<maxLName;k++) cout<<" ";
				 			cout<<"|";
				 			//-----------------------------------
				 			cout<<"(K)";
				 			SetConsoleTextAttribute(hConsole,6);
				 			cout<<cNum;
				 			SetConsoleTextAttribute(hConsole,15);
				 			cout<<" (W)";
				 			SetConsoleTextAttribute(hConsole,6);
				 			cout<<wNum;
				 			SetConsoleTextAttribute(hConsole,15);
				 			//-----------------------------------
				 			cout<<"\n";
						}
					}
					
					getch();
					system("cls");
					 
				break;
				/*case '2':
					
				break;
				case '3':
					
				break;
				case '4':
					
				break;
				case '5':
					tr=false;*/
			}
		}
		
	}
}

/*
	for(int i=0; i<n; i++){
			cout<<"Kontakt nr: "<<i+1<<"; | "<<con[i].getVer()<<" | "<<con[i].getName()<<" | "<<con[i].getFullName()<<" | "<<con[i].getCNum()<<" | "<<con[i].getWNum()<<"\n";
		}
*/

//============================================================================================
/*
Pliki takie zawierajπ dane w postaci jak poniøej:
BEGIN:VCARD
VERSION:2.1
N:Wisla;Taxi;;;
FN:Taxi Wisla
TEL;CELL:888 237 217
TEL;WORK:666 222 390
END:VCARD

1) wyúwietlenie listy numerÛw telefonÛw - w postaci tabeli o dwÛch kolumnach: abonent (pole FN lub sklejenie sk≥adowych pola N) oraz jego numery (wszystkie znalezione pola TEL), posortowanej wed≥ug nazwiska i imienia
2) wprowadzenie zmian do dowolnej pozycji
3) zapisanie zmienionego pliku VCF na dysk (w postaci dajπcej siÍ poprawnie zaimportowaÊ w telefonie)
*/
