 #include <iostream>
 #include <cmath>
 #include <vector>
 #include <functional>
 #include <stdexcept>
 
 std::function<double(double)> suma11(double prvi,double drugi, double koef) {
  return [prvi,drugi,koef](double y) {
   if(y==prvi) return drugi;
   return koef*drugi/(y-prvi);
  };
 }
 
 std::function<double(double)> suma22(double prvi, double drugi, double koef) {
  return [prvi,drugi,koef](double y) {
   return koef/(y-prvi);
  };
 }
 
 std::function<double(double)>fun(){
  return [](double x) {
   return x*x+sin(x);
  };
 }
 
 std::function<float(float)>BaricentricnaInterpolacija(std::vector<std::pair<double,double>>parovi, int d) {
  if(d<0 || d>parovi.size()) throw std::domain_error("Nedozvoljen red");
  
  for(int i=0; i<parovi.size()-1; i++)
  for(int j=i+1; j<parovi.size(); j++) 
  if(parovi[i].first==parovi[j].first) throw std::domain_error("Neispravni cvorovi");
  
  return [parovi,d](double x) {
   double suma1=0,suma2=0,proizvod=1,wi=0;
   int poc=1,end=1;
   
   for(int i=1; i<=parovi.size(); i++) {
    poc=1;
    end=i;
    wi=0;
    if(i-d>poc) poc=i-d;
    if(parovi.size()-d<end) end=parovi.size()-d;
    
    for(int j=poc; j<=end; j++) {
     proizvod=1;
     for(int k=j; k<=j+d; k++) {
      if(i==k) continue;
      proizvod*=1./(parovi[i-1].first-parovi[k-1].first);
     }
     wi+=pow(-1,j-1)*proizvod;
    }
    if(x==parovi[i-1].first)
    return parovi[i-1].second;
    suma1+=suma11(parovi[i-1].first, parovi[i-1].second,wi)(x);
    suma2+=suma22(parovi[i-1].first, parovi[i-1].second,wi)(x);
   }
   return suma1/suma2;
  };
 }
 
 std::function<double(double)>BaricentricnaInterpolacija(std::function<double(double)>fun,double x_min, double x_max, double dx,int d) {
  if(x_min>x_max || dx<0) throw std::domain_error("Nekorektni parametri");
  
  return [fun, x_min, x_max, dx, d](double x) {
   std::vector<double> tacke;
   for(double i=x_min;i<=x_max; i+=dx)
   tacke.push_back(i);
   
   std::vector<std::pair<double,double>>parovi(tacke.size());
   
   for(int i=0; i<parovi.size(); i++) {
    parovi[i].first=tacke[i];
    parovi[i].second=fun(tacke[i]);
   }
   
   double suma1=0,suma2=0,proizvod=1,wi=0;
   int poc=1,end=1;
   
   for(int i=1; i<=parovi.size(); i++) {
    poc=1;
    end=i;
    wi=0;
    
    if(i-d>poc) poc=i-d;
    if(parovi.size()-d<end) end=parovi.size()-d;
    
    for(int j=poc; j<=end; j++) {
     proizvod=1;
     
     for(int k=j; k<=j+d; k++) {
      if(i==k) continue;
      proizvod*=1./(parovi[i-1].first-parovi[k-1].first);
     }
     wi+=pow(-1,j-1)*proizvod;
    }
    if(x==parovi[i-1].first)
    return parovi[i-1].second;
    
    suma1+=suma11(parovi[i-1].first, parovi[i-1].second, wi)(x);
    suma2+=suma22(parovi[i-1].first, parovi[i-1].second, wi)(x);
   }
   
   return suma1/suma2;
  };
 }
 
 int main() {
  try {
   int opcija=0, broj_cvorova=0;
   double x, y, red, unos=0;
   
   for(;;) {
    std::cout << "Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
    std::cin >> opcija;
    
    if(opcija==1) {
     std::cout << "Unesite broj cvorova: ";
     std::cin >> broj_cvorova;
     std::cout << "Unesite cvorove kao parove x y: ";
     std::vector<std::pair<double,double>>parovi(broj_cvorova);
     
     for(int i=0; i<broj_cvorova; i++) {
      std::cin >> x;
      std::cin >> y;
      parovi[i].first=x;
      parovi[i].second=y;
     }
     std::cout << "Unesite red interpolacije: ";
     std::cin>>red;
     
     while(1) {
      std::cout << "Unesite argument (ili \"kraj\" za kraj): ";
      std::cin >>unos;
      if(std::cin.fail()) {
       return 0;
      }
      
      double rez=BaricentricnaInterpolacija(parovi,red)(unos);
      std::cout << "f("<<unos << ") = " << rez << std::endl;
     }
    }
    
    else if(opcija==2) {
     std::function<double(double)>pom(fun());
     std::cout << "Unesite krajeve intervala i korak: ";
     double korak,poc,end;
     std::cin>>poc;
     std::cin>>end;
     std::cin>>korak;
     std::cout << "Unesite red interpolacije: ";
     std::cin >> red;
     std::cin.clear();
     std::cin.ignore(10000,'\n');
     
     while(1) {
      std::cout << "Unesite argument (ili \"kraj\" za kraj): ";
      std::cin>>unos;
      if(std::cin.fail()) {
       return 0;
      }
      
      double re=BaricentricnaInterpolacija(pom,poc,end,korak,red)(unos);
      std::cout << "f(" << unos << ") = " << pom(unos) << " fapprox(" <<unos <<") = " << re << std::endl;
     }
    }
    
    break;
  }
  
  return 0;
 } catch(std::domain_error e) {
  std::cout << e.what();
 }
 }
