// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "DLL.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

void openWindow() {

    std::string cont;
    do {
        std::string powershellCommand = "powershell.exe -Command \"";

        std::string setting;
        

        cout << "Valdymo skydo komponentes:" << endl;
        cout << "1 - Display" << endl;
        cout << "2 - Security" << endl;
        cout << "3 - Power" << endl;
        cout << "4 - Storage" << endl;
        cout << "5 - Update" << endl;
        cin >> setting;

        if (setting == "1") {
            powershellCommand += "Start-Process ms-settings:display;";
        }
        else if (setting == "2") {
            powershellCommand += "Start-Process ms-settings:windowsdefender;";
        }
        else if (setting == "3") {
            powershellCommand += "Start-Process ms-settings:powersleep;";
        }
        else if (setting == "4") {
            powershellCommand += "Start-Process ms-settings:storagesense;";
        }
        else if (setting == "5") {
            powershellCommand += "Start-Process ms-settings:windowsupdate;";
        }
        else {
            std::cerr << "Klaida" << std::endl;
            return;
        }

        powershellCommand += "\"";

        system(powershellCommand.c_str());

        cout << "Jei norite testi irasykite t." << endl;
        cin >> cont;

    } while (cont == "t");
}

void folderCreate(std::string vardas, std::string pavarde) {

    std::string command = "mkdir " + pavarde; // mkdir Kubilius\Klaidas1\Klaido1Klaidas1
    system(command.c_str());
    string command2;
    string command3;
    
    for (int i = 1; i <= 3; i++) {
        command2 = command + "\\" + vardas + std::to_string(i);
        system(command2.c_str());
        for (int j = 1; j <= 3; j++) {
            command3=command2 + "\\" + vardas + std::to_string(i) + vardas + std::to_string(j);
            system(command3.c_str());
        }
    }
    cout << "Folders created" << endl;
}

void deletion() {

    string foldername = "Kubilius";

    std::string command = "rmdir /s /q  " + foldername;


    int result = system(command.c_str());
    if (result == 0) {
        std::cout << "Directory '" << foldername << "' successfully deleted." << std::endl;
    }
    else {
        std::cerr << "Failed to delete directory '" << foldername << "'." << std::endl;
    }
}

