#include <iostream>
#include <utility>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <iterator>


//npr. ako vraca taj pojam i skup pozicija na kojima se on nalazi u datom stringu tipa abc: {0,14,24}
std::map<std::string, std::set<int>> KreirajIndeksPojmova(std::string s)
{
    std::map<std::string, std::set<int>> mapa;

    //Neosjetljivost na mala/velika slova, tretiramo ih isto
    for(int i=0; i<s.size(); i++) {
        if(s[i]>='A' && s[i]<='Z')
            s[i]+=('a'-'A');
    }

   //Standardni prolaz kroz string
    for(int i=0; i<s.size(); i++) {
        //Provjera da li je znak slovo ili cifra
        if((s[i]>='a' && s[i]<='z') || (s[i]>='0' && s[i]<='9')) {
            
            int index(i);
            std::string pomocni;
            //Stavljamo sve znakove koje zadovoljavaju uslov da su slovo ili broj u pomocni string
            while((s[i]>='a' && s[i]<='z') || (s[i]>='0' && s[i]<='9')) {
                pomocni.push_back(s[i]);
                i++;
            }
            
            //Kreiramo mapu
            auto it(mapa.find(pomocni));
            if(it==mapa.end())
                mapa.insert(std::pair<std::string, std::set<int>>(pomocni, {index}));
            else {
                //U drugi dio stavljamo indeks
                (it->second).insert(index);
            }
        }
    }
    return mapa;
}


std::set<int> PretraziIndeksPojmova(std::string s, std::map<std::string, std::set<int>> index_pojmova)
{
    std::set <int> skup;
    //Trazimo string npr 'abc' u mapi
    auto it(index_pojmova.find(s));
    
    //Ukoliko nema bacamo izuzetak
    if(it==index_pojmova.end())
        throw std::logic_error("Pojam nije nadjen");
    else {
        //U suprotnom ako je nadjen taj string u skup stavljamo index_pojmova
        skup=it->second;
    }

    return skup;
}


void IspisiIndeksPojmova(std::map<std::string, std::set<int>> mapa)
{
    
    //Ispisivanje mape kao skup uređenih parova po primjeru iz predavanja
    for(auto it=mapa.begin(); it!=mapa.end(); it++) {
        std::cout << it->first <<": ";
        for(auto x=(it->second).begin(); x!=(it->second).end(); x++) {
            if(x==--(it->second).end())
                std::cout << *x << " ";
            else std::cout << *x << ",";
        }
        std::cout << std::endl;
    }
}


int main ()
{
    try {
        std::string tekst;
        std::cout << "Unesite tekst: ";
        std::getline(std::cin, tekst);
        
        
        auto mapa(KreirajIndeksPojmova(tekst));

        IspisiIndeksPojmova(mapa);
        
        while(true) {
            try {
                std::cout << "Unesite rijec: ";
                std::string rijec;
                std::getline(std::cin, rijec);
                if(rijec==".") break;
                
                auto skup=PretraziIndeksPojmova(rijec,mapa);

                for(auto x : skup)
                    std::cout << x << " ";
                std::cout << std::endl;
            } catch(std::logic_error e) {
                std::cout << "Unesena rijec nije nadjena!" << std::endl;
            }
        }
    } catch(std::logic_error el) {
        std::cout << el.what() << std::endl;
    }
    return 0;
}
