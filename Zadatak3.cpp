#include <iostream>
#include <stdexcept>
#include <new>
#include <iomanip>
#include <vector>

template <typename TipElemenata>
struct Matrica {
    int br_redova, br_kolona;
    TipElemenata **elementi=nullptr;
};

template<typename TipElemenata>
void UnistiMatricu(Matrica <TipElemenata> mat)
{
    if(!mat.elementi) return;
    for(int i=0; i<mat.br_redova; i++) delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi=nullptr;
}


template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona)
{
    Matrica <TipElemenata> mat;
    mat.br_redova=br_redova;
    mat.br_kolona=br_kolona;
    mat.elementi=new TipElemenata *[br_redova];

    for(int i=0; i<br_redova; i++) mat.elementi[i]=nullptr;

    try {
        for(int i=0; i<br_redova; i++) {
            mat.elementi[i]=new TipElemenata[br_kolona];
        }
    } catch(...) {
        UnistiMatricu(mat);
        throw;
    }

    return mat;
}

template <typename TipElemenata>
void UnesiMatricu(char ime_matrice, Matrica<TipElemenata> &mat)
{
    for(int i=0; i<mat.br_redova; i++) 
        for(int j=0; j<mat.br_kolona; j++) {
            std::cout << ime_matrice << "(" << i+1 << "," << j+1 << ") = ";
            std::cin >> mat.elementi[i][j];
        }
}


template <typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa, int preciznost=6,bool treba_brisati=false)
{
    for(int i=0; i<mat.br_redova; i++) {
        for(int j=0; j<mat.br_kolona; j++) {
            std::cout << std::setw(sirina_ispisa) << std::setprecision(preciznost) << mat.elementi[i][j];
        }
        std::cout << std::endl;
    }

    if(treba_brisati==true)
        UnistiMatricu(mat);
}



template <typename TipElemenata>
void ZbirMatrica(Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2)
{
    if(m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona)
        throw std::domain_error("Matrice nemaju jednake dimenzije!");
    for(int i=0; i<m1.br_redova; i++)
        for(int j=0; j<m1.br_kolona; j++)
            m1.elementi[i][j]=m1.elementi[i][j]+m2.elementi[i][j];
}


template <typename TipElemenata>
Matrica <TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1, const Matrica <TipElemenata> &m2)
{

    if(m1.br_kolona!=m2.br_redova)
        throw std::domain_error("Matrice nisu saglasne za mnozenje");

    auto m3(StvoriMatricu<TipElemenata>(m1.br_redova, m2.br_kolona));

    for(int i=0; i<m1.br_redova; i++) {
        for(int j=0; j<m1.br_redova; j++) {
            m3.elementi[i][j]=0;
        }
    }

    for(int i=0; i<m1.br_redova; i++)
        for(int j=0; j<m2.br_kolona; j++) {
            int tmp=0;
            for(int k=0; k<m1.br_kolona; k++) {
                tmp+=(m1.elementi[i][k]*m2.elementi[k][j]);
            }
            m3.elementi[i][j]=tmp;
        }

    return m3;

}

template <typename TipElemenata>
Matrica <TipElemenata> KopijaMatrice(const Matrica<TipElemenata> &a)
{
    Matrica<TipElemenata> b;
    b=StvoriMatricu <TipElemenata>(a.br_redova,a.br_kolona);

    for(int i=0; i<a.br_redova; i++) {
        for(int j=0; j<a.br_kolona; j++) {
            b.elementi[i][j]=a.elementi[i][j];
        }
    }
    
    return b;
}

template <typename TipElemenata>
Matrica <TipElemenata> ProizvodSkalara(const Matrica <TipElemenata> &a, double skalar) {
    Matrica <TipElemenata> b;
    b=StvoriMatricu<TipElemenata>(a.br_redova,a.br_kolona);
    for(int i=0; i<a.br_redova; i++) {
        for(int j=0; j<a.br_kolona; j++) {
            b.elementi[i][j]=a.elementi[i][j]*skalar;
        }
    }
    
    return b;
}

template <typename TipElemenata>
void ProizvodSkalaraa(Matrica<TipElemenata> &a, double skalar) {
    for(int i=0; i<a.br_redova; i++) {
        for(int j=0; j<a.br_kolona; j++) {
            a.elementi[i][j]=a.elementi[i][j]*skalar;
        }
    }
}

template <typename TipElemenata>
Matrica <TipElemenata> MatricniPolinom(const Matrica <TipElemenata> &m1, std::vector<double> koeficijenti) {
    if(m1.br_kolona!=m1.br_redova) {
        UnistiMatricu(m1);
        throw std::domain_error("Matrica mora biti kvadratna!");
    }
    
    auto m3(StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona));
    auto pomoc=m3;
    
    for(int i=0; i<m1.br_redova; i++) {
        for(int j=0; j<m1.br_kolona; j++) {
            m3.elementi[i][j]=0;
            
        }
    }
    
    if(koeficijenti.size()==0) {
        return m3;
    }
    
    
    auto JedMat(StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona));
    
    
    for(int i=0; i<m1.br_redova; i++) {
        for(int j=0; j<m1.br_redova; j++) {
            if(i==j)
            JedMat.elementi[i][j]=1;
            else 
            JedMat.elementi[i][j]=0;
        }
    }
    
    auto mat(KopijaMatrice(m1));
    
    try {
        for(int i=0; i<koeficijenti.size(); i++) {
            if(i==0) {
                ProizvodSkalaraa(JedMat,koeficijenti[i]);
            } else if(i==1) {
                m3=ProizvodSkalara(m1,koeficijenti[i]);
            } else if(i>1) {
                auto tmp=mat;
                mat=ProduktMatrica(mat,m1);
                auto pom=ProizvodSkalara(mat,koeficijenti[i]);
                ZbirMatrica<TipElemenata>(m3,pom);
                UnistiMatricu(tmp);
                UnistiMatricu(pom);
            }
        }
        
        UnistiMatricu(mat);
        ZbirMatrica<TipElemenata>(m3,JedMat);
        UnistiMatricu(JedMat);
        UnistiMatricu(pomoc);
        return m3;
    } catch(...) {
        UnistiMatricu(mat);
        UnistiMatricu(m3);
        UnistiMatricu(JedMat);
        throw;
    }
}



int main ()
{
    Matrica<int>a,b;
    int n(0);
    std::cout << "Unesite dimenziju kvadratne matrice: ";
    std::cin >> n;
    
    try {
        a=StvoriMatricu<int>(n,n);
        std::cout << "Unesite elemente matrice A: " << std::endl;
        UnesiMatricu('A',a);
        std::cout << "Unesite red polinoma: ";
        int red_polinoma;
        std::cin>> red_polinoma;
        std::cout << "Unesite koeficijente polinoma: ";
        std::vector <double> koeficijenti;
        double k; 
        
        for(int i=0; i<=red_polinoma; i++) {
            std::cin >> k;
            koeficijenti.push_back(k);
        }
        
        b=MatricniPolinom(a, koeficijenti);
        IspisiMatricu(b,10);
    } catch(std::bad_alloc) {
        UnistiMatricu(a);
        UnistiMatricu(b);
        std::cout << "Nema dovoljno memorije\n";
    }
    UnistiMatricu(a);
    UnistiMatricu(b);
    return 0;
}
