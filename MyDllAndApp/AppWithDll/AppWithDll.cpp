// AppWithDll.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "DLL.h"


int main()
{

    Timer t; // 1# Laiko matavimo funkcija
    
    openWindow(); // 2# Funkcija kuri pagal naudotojo poreikį atveria valdymo skydo atitinkamą komponentę

    

    folderCreate("Klaidas", "Kubilius"); // 3# aplankalų kūrimo funkcija

    int student_ID = 2210342;
    double x0 = -(student_ID % 19); //15
    double xn = student_ID % 25; //17
    double deltax = student_ID / 1000000000000.0; //0,000002210342
    std::vector<double> F = { -2, -1, 0 , 1, 2}; // F reikšmės

    //calculate_and_write_points(F, x0, xn, deltax); //4#
    //cout << "Suskaiciuoti taskai" << endl;

    //merge_and_sort_points(); //5#

    string del;
    cout << "Norite sunaikinti aplanka? (Irasykite t)" << endl;
    cin >> del;
    if (del == "t") {
        deletion(); // #6
    }
    

    cout << t.elapsed() << " s" << endl;
    system("pause");
}


