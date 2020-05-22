#include <iostream>
#include <deque>
#include <iomanip>
#include <fstream>
#include <random>
#include <string>
#include <algorithm>
#include <chrono>

void Test(double &t1)
{
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::cout << "Iveskite is naujo: ";
    std::cin >> t1;
}

class Studentas{
public:
    std::string vardas;
    std::string pav;
    double gal;
};



std::string Random(int p)
{
    std::string vardas, pav, eil;
    double gal;
    for (int i=0; i<p; i++)
    {
        srand(time(NULL));
        vardas="Vardas"+std::to_string(rand()%p);
        pav="Pavarde"+std::to_string(rand()%p);;
        eil+=vardas+" "+pav+" "+std::to_string(0+(double)rand()/RAND_MAX*(10))+"\n";
    }
    return eil;
}

void Failai(std::string x, int &y, int p)
{
    std::ofstream fd (x);

    fd << Random(p);

    y--;
    if (y==4)
        Failai("Antras.txt", y, p*10);

    else if (y==3)
        Failai("Trecias.txt", y, p*10);

    else if (y==2)
        Failai("Ketvirtas.txt", y, p*10);

    else if (y==1)
        Failai("Penktas.txt", y, p*10);

}

void Skaitymas(std::string z, int &y, int &p, int &c, int &b, std::deque<Studentas> &Stud)
{
    std::ifstream fd (z);
    p*=10;
    c=b;
    b+=p;
    for (int i=c; i<b; i++)
    {
        Stud.push_back(Studentas());
        fd >> Stud[i].vardas >> Stud[i].pav >> Stud[i].gal;
    }
    y--;

    if (y==4)
        Skaitymas("Antras.txt", y, p, c, b, Stud);

    else if (y==3)
        Skaitymas("Trecias.txt", y, p, c, b, Stud);

    else if (y==2)
        Skaitymas("Ketvirtas.txt", y, p, c, b, Stud);

    else if (y==1)
        Skaitymas("Penktas.txt", y, p, c, b, Stud);
}

bool Rusiavimas(const Studentas &a, const Studentas &b)
{
    return a.gal<b.gal;
}

int main()
{
    int k, s, egzas, b;
    double vid, med, k1, s1, egzas1;

    std::cout << "Ar norite kad studentu sarasu failai butu sugeneruoti? Taip - 1 ; Ne - 2 ";
    std::cin >> s1;
        while(std::cin.fail() || s1==0 || s1 !=(int)s1 || (s1!=1 && s1!=2))
            Test(s1);

    if (s1==2)
    {
       std::cout << "Iveskite studentu kieki: ";
        std::cin >> k1;
        while(std::cin.fail() || k1==0 || k1 !=(int)k1)
            Test(k1);

        k=(int)k1;
        std::string V[k], vardas, pavarde;
        double Vid[k]={0}, Med[k]={0};
        int E[k];
        std::vector<int> v = {};
        for (int i=0; i<k; i++)
        {
            std::vector<int> v = {};
            b=0;
            std::cout << "Iveskite studento varda ir pavarde: ";
            std::cin >> vardas >> pavarde;
            V[i] = vardas + " " + pavarde;
            std::cout << "Ar norite kad balai butu atsitiktinai generuojami? Taip - 1 ; Ne - 2 ";
            std::cin >> s1;
            while(std::cin.fail() || s1==0 || s1 !=(int)s1 || (s1!=1 && s1!=2))
                Test(s1);

            s=(int)s1;
            if (s==2)
            {
                std::cout << "Iveskite egzamino rezultata: ";
                std::cin >> egzas1;
                while(std::cin.fail() || egzas1==0 || egzas1 !=(int)egzas1)
                    Test(s1);

                egzas=(int)egzas1;
                E[i]=egzas;
                std::cout << "Iveskite namu darbu rezultatus (jei nebenoresite vesti rezultatu, iveskite skaiciu 11): ";
                go: while (true)
                {
                    std::cin >> s1;
                    while((std::cin.fail() && s1>=0 && s1<10)|| s1==0 || s1 !=(int)s1)
                        Test(s1);

                    s=(int)s1;
                    if (s>=0 && s<=10)
                    {
                        v.push_back(s);
                    }
                    else if (s==11)
                        break;
                }

            }
            else if (s==1)
            {
                for (int j=0; j<(rand()%100); j++)
                    v.push_back((rand()%10));
            }

            std::cout << "Skaiciuoti vidurki(1) ar mediana(2)? ";
            std::cin >> s1;
            while(std::cin.fail() || s1==0 || s1 !=(int)s1)
                Test(s1);

            s=(int)s1;
            if (s==1)
            {
                for (int j=0; j<v.size(); j++)
                {
                    b+=v[j];
                }
                Vid[i]=(double)(b/v.size())*0.4+E[i]*0.6;
            }
            else if (s==2)
            {
                v.push_back(E[i]);
                for (int a=0; a<v.size()-1; a++)
                    for (int b=a+1; b<v.size(); b++)
                        if (v[a]>v[b])
                            std::swap (v[a], v[b]);

                if (v.size()%2!=0)
                    Med[i]=v[v.size()/2];
                else
                    Med[i]=(double)(v[v.size()/2-1]+v[v.size()/2])/2;
            }
        }
        std::cout << "Pavarde   " << "Vardas    " << "Galutinis (Vid.) / Galutinis (Med.)" << std::endl << "--------------------------------------------------------" << std::endl;
        for (int i=0; i<k; i++)
        {
            std::cout << V[i] << "  ";
            if (Vid[i]!=0)
                std::cout << std::fixed << std::setprecision(2) << Vid[i] << std::endl;

            else
                std::cout << "                                      " << std::fixed << std::setprecision(2) << Med[i] << std::endl;
        }
    }
    else
    {
        int y=5, p=1000, b=0, c;
        std::deque<Studentas> Stud;
        std::deque<Studentas> Kiet;
        std::deque<Studentas> Varg;
        std::string StudV, StudK, v0, p0;
        double g0;

        Failai("Pirmas.txt",y,p);

        y=5;
        p=100;
        auto start2 = std::chrono::high_resolution_clock::now();
        Skaitymas("Pirmas.txt", y, p, c, b, Stud);
        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff2 = end2-start2;
        std::cout << "Duomenu nuskaitymas is failu uztruko: "<< diff2.count() << " s\n";

        std::sort(Stud.begin(), Stud.end(), Rusiavimas);

        int kt=0, vr=0;
        auto start3 = std::chrono::high_resolution_clock::now();
        for (int i=0; i<b; i++)
        {
            if (Stud[i].gal>=5.0)
            {
                for (int j=i; j<b; j++,i++)
                {
                    Kiet.push_back(Studentas());
                    Kiet[kt].vardas=Stud[j].vardas;
                    Kiet[kt].pav=Stud[j].pav;
                    std::to_string(Kiet[kt].gal)=std::to_string(Stud[j].gal);
                    kt++;
                    StudK+=Stud[j].vardas+" "+Stud[j].pav+" "+std::to_string(Stud[j].gal)+"\n";
                }

            }
            Varg.push_back(Studentas());
            Varg[vr].vardas=Stud[i].vardas;
            Varg[vr].pav=Stud[i].pav;
            std::to_string(Varg[vr].gal)=std::to_string(Stud[i].gal);
            vr++;
            StudV+=Stud[i].vardas+" "+Stud[i].pav+" "+std::to_string(Stud[i].gal)+"\n";
        }
        auto end3 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff3 = end3-start3;
        std::cout << "Studentu rusiavimas i dvi grupes/kategorijas uztruko: "<< diff3.count() << " s\n";
        std::ofstream a1 ("Kietekiai.txt");
        std::ofstream b1 ("Vargsiukai.txt");
        a1 << StudK;
        b1 << StudV;
    }

    return 0;
}
