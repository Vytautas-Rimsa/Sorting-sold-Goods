#include <iostream>
#include <fstream>

using namespace std;

const int MAXzaidimu=30;
const int MAXpardavimu=30;

struct Zaidimai
{
    string pavadinimas;
    string tipas;
    double kaina;
    double pardavimai;
};

struct Pardavimai
{
    string pavadinimas;
    int kiekis;
};

void duomenu_nuskaitymas(Zaidimai Z[], int &zaidimusk, Pardavimai P[], int &pardavimusk)
{
    ifstream srautas;
    srautas.open("zaidimai.txt");
    int i=0;
    while (!srautas.eof())
    {
        srautas >> Z[i].pavadinimas >> Z[i].tipas >> Z[i].kaina;
        i++;
    }
    zaidimusk = i;
    srautas.close();

    ifstream srautas2;
    srautas2.open("pardavimai.txt");
    i=0;
    while (!srautas2.eof())
    {
        srautas2 >> P[i].pavadinimas >> P[i].kiekis;
        i++;
    }
    pardavimusk = i;
    srautas2.close();
}

void skaiciavimai (Zaidimai Z[], int zaidimusk, Pardavimai P[], int pardavimusk, int &action_kiekis, int &rpg_kiekis, int &shooter_kiekis)
{
    action_kiekis=0;
    rpg_kiekis=0;
    shooter_kiekis=0;
    for (int i=0; i<zaidimusk; i++)
    {
        for (int j=0; j<pardavimusk; j++)
        {
            if(Z[i].pavadinimas == P[j].pavadinimas)
            {
                Z[i].pardavimai = Z[i].kaina * P[j].kiekis;
            }
        }
    }
    for (int i=0; i<zaidimusk; i++)
    {
        if (Z[i].tipas=="Action")
        action_kiekis++;
        if (Z[i].tipas=="RPG")
        rpg_kiekis++;
        if (Z[i].tipas=="Shooter")
        shooter_kiekis++;
    }
}

void duomenu_rikiavimas(Zaidimai Z[], int zaidimusk)
{
    Zaidimai laikinas;
    for (int a=0; a<zaidimusk; a++)
    {
        for (int i=0; i<zaidimusk-1; i++)
        {
            if (Z[i].tipas>Z[i+1].tipas)
            {
                laikinas = Z[i];
                Z[i] = Z[i+1];
                Z[i+1] = laikinas;
            }
        }
    }
}

void ruomenu_rodymas_ekrane(Zaidimai Z[], int zaidimusk, int action_kiekis, int rpg_kiekis, int shooter_kiekis)
{
    for (int i=0; i<zaidimusk; i++)
    {
        cout << Z[i].pavadinimas << " " << Z[i].tipas << " " << Z[i].kaina << " parduota uz " << Z[i].pardavimai << endl;
        cout << "Action tipo zaidimu kiekis yra " << action_kiekis << ", RPG tipo zaidimus yra " << rpg_kiekis << ",o Shooter tipo zaidimu bus " << shooter_kiekis << endl;
    }
}

void duomenu_irasymas(Zaidimai Z[], int zaidimusk)
{
    ofstream srautas;
    srautas.open("rezultatai.txt");
    for (int i=0; i<zaidimusk; i++)
    {
        srautas << Z[i].pavadinimas << " " << Z[i].tipas << " " << Z[i].kaina << " " << Z[i].pardavimai << endl;
    }
    srautas.close();
}

int main()
{
    Zaidimai Z[MAXzaidimu];
    Pardavimai P[MAXpardavimu];
    int zaidimusk;
    int pardavimusk;
    int action_kiekis;
    int rpg_kiekis;
    int shooter_kiekis;
    duomenu_nuskaitymas(Z, zaidimusk, P, pardavimusk);
    skaiciavimai (Z, zaidimusk, P, pardavimusk, action_kiekis, rpg_kiekis, shooter_kiekis);
    duomenu_rikiavimas(Z, zaidimusk);
    ruomenu_rodymas_ekrane(Z, zaidimusk, action_kiekis, rpg_kiekis, shooter_kiekis);
    duomenu_irasymas(Z, zaidimusk);
    return 0;
}
