#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <stdexcept>
#include <cstring>
#include <iterator>
#include <algorithm>


//Klasicna funkcija sa ORa kojom cu prvobitno izmjeriti duzinu stringa
int BrojSlova(std::string s)
{
    int brojac(0);
    for(int i=0; i<s.size(); i++) {
        if((s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z') || (s[i]>='0' && s[i]<='9') || s[i]==' ') {
            brojac++;
        }
    }

    return brojac;
}

std::vector <std::set<std::string>> Razvrstavanje(std::vector<std::string>v_imena, int k)
{
    int n(v_imena.size());

    if(k<1 || k>n) {
        throw std::logic_error("Razvrstavanje nemoguce");
    }

    //Stavljamo imena u listu
    std::list<std::string> l_imena;
    std::copy(v_imena.begin(), v_imena.end(),std::back_inserter(l_imena));

    //Deklarisemo pomocni vektor
    std::vector<int> v2;
    int br_clan(0);
    
    
    if(n%k==0) {
        br_clan=n/k;
        for(int i=0; i<k; i++) {
            v2.push_back(br_clan);
        }
    } else {
        int mod(n%k);
        br_clan=(n/k);
        
        for(int i=0; i<k; i++) {
            if(i<mod) {
                v2.push_back(br_clan+1);
            } else {
                v2.push_back(br_clan);
            }
        }
    }

    std::vector<std::set<std::string>> PovratniSkupDjece(k);
    
    std::list<std::string>::iterator it(l_imena.begin());
    
    std::string PrvoIme(*it);
    
    PovratniSkupDjece[0].insert(PrvoIme);
    int duzina=BrojSlova(*it);
    
    v2[0]--; //Smanjujemo broj clanova 
    
    std::set<std::string>PomocniSkup;
    std::string PomocniString;
    
    auto it2=it;
    it++;
    it=l_imena.erase(it2);
    
    
    for(int i=0; i<v2.size(); i++) {
        for(int j=0; i<v2[i]; j++) {
            duzina--;
            if(duzina==0) break;
        }
        duzina=BrojSlova(*it);
        PovratniSkupDjece[i].insert(*it);
        it=l_imena.erase(it);
        if(it==l_imena.end()) it=l_imena.begin();
    }


    return PovratniSkupDjece;
}


int main ()
{
    try {
        std::cout << "Unesite broj djece: ";
        int br(0);
        std::cin >> br;
        std::cin.ignore(10000, '\n');
        std::vector<std::string> v;
        std::cout << "Unesite imena djece: ";

        for(int i=0; i<br; i++) {
            std::string s;
            std::getline(std::cin, s);
            v.push_back(s);
        }

        std::cout << std::endl << "Unesite broj timova: ";
        int br_tim(0);
        std::cin >> br_tim;
        std::vector <std::set<std::string>> razvrstavanje;
        razvrstavanje=Razvrstavanje(v, br_tim);
        std::set<std::string>::iterator it;

        for(int i=0; i!=br_tim; i++) {
            std::cout << "Tim: " << i+1 <<" ";
            for(it=razvrstavanje[i].begin(); it!=razvrstavanje[i].end(); it++)
                if(it==--(razvrstavanje[i].end()))
                    std::cout << *it;
                else std::cout << *it << " ";
            std::cout << std::endl;
        }
    } catch(std::logic_error e) {
        std::cout << "Izuzetak: " << e.what() <<std::endl;
    }
    return 0;
}
