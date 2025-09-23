#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Pipe {
    string name;
    float length = 0; // 0 когда мы ничего не вводили
    int diameter = 0;
    bool repair;
};

struct CompressorStation {
    string name;
    int count = 0;
    int count_working = 0;
    string classification;
    bool working;
};

void Menu(Pipe& pipe, CompressorStation& CS) {
    while (true)
    {
        cout << "\nSelect type:\n 1. Pipe \n 2. Compressor Station\n 3. Show all\n 4. Exit\n";
        int type;
        cin >> type;
        if (cin.fail()) {
            cout << "Error!" << endl;
            cout << "Enter a valid number (1-4)" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (type == 4) {
            cout << "Exiting program." << endl;
            break;
        }

        switch (type)
        {
        case 1:
            cout << "Select option:\n 1. Add pipe \n 2. Pipe length\n 3. Pipe diameter\n 4. Repair\n";
            int option;
            cin >> option;
            if (cin.fail()) {
                cout << "Error!" << endl;
                cout << "Enter a valid number (1-4)" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            switch (option)
            {
            case 1:
                cout << "Enter pipe name: ";
                cin >> pipe.name;
                break;
            case 2:
                cout << "Enter pipe length (km): ";
                cin >> pipe.length;
                if (cin.fail() || pipe.length < 0) {
                    cout << "Error!" << endl;
                    cout << "Enter a valid positive number" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    pipe.length = 0;
                }
                break;
            case 3:
                cout << "Enter pipe diameter (mm): ";
                cin >> pipe.diameter;
                if (cin.fail() || pipe.diameter < 0) {
                    cout << "Error!" << endl;
                    cout << "Enter a valid positive number" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    pipe.diameter = 0;
                }
                break;
            case 4:
                cout << "Is the pipe under repair? (0 - no, 1 - yes): ";
                cin >> pipe.repair;
                if (cin.fail()) {
                    cout << "Error!" << endl;
                    cout << "Enter 0 or 1" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }
            break;
        case 2:
            cout << "Select option:\n 1. Add CS \n 2. Number of workshops \n 3. Number of working workshops\n 4. Classification\n 5. Repair\n";
            int option2;
            cin >> option2;
            if (cin.fail()) {
                cout << "Error!" << endl;
                cout << "Enter a valid number (1-5)" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            switch (option2)
            {
            case 1:
                cout << "Enter CS name: ";
                cin >> CS.name;
                break;
            case 2:
                cout << "Enter number of workshops: ";
                cin >> CS.count;
                if (cin.fail() || CS.count < 0) {
                    cout << "Error!" << endl;
                    cout << "Enter a valid positive number" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    CS.count = 0;
                }
                break;
            case 3:
                cout << "Enter number of working workshops: ";
                cin >> CS.count_working;
                if (cin.fail() || CS.count_working < 0) {
                    cout << "Error!" << endl;
                    cout << "Enter a valid positive number" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    CS.count_working = 0;
                }
                break;
            case 4:
                cout << "Enter classification: ";
                cin >> CS.classification;
                break;
            case 5:
                cout << "Is CS under repair? (0 - no, 1 - yes): ";
                cin >> CS.working;
                if (cin.fail()) {
                    cout << "Error!" << endl;
                    cout << "Enter 0 or 1" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }
            break;
        case 3:
            cout << "\nPipe parameters: \n" << "Name: " << (pipe.name.empty() ? "unknown" : pipe.name)
                << "\nLength: " << (pipe.length == 0 ? "unknown" : to_string(pipe.length) + " km")
                << "\nDiameter: " << (pipe.diameter == 0 ? "unknown" : to_string(pipe.diameter) + " mm")
                << "\nUnder repair: " << (pipe.repair ? "yes" : "no");

            cout << "\n\nCS parameters: \n" << "Name: " << (CS.name.empty() ? "unknown" : CS.name)
                << "\nNumber of workshops: " << (CS.count == 0 ? "unknown" : to_string(CS.count))
                << "\nNumber of working workshops: " << (CS.count_working == 0 ? "unknown" : to_string(CS.count_working))
                << "\nClassification: " << (CS.classification.empty() ? "unknown" : CS.classification)
                << "\nUnder repair: " << (CS.working ? "yes" : "no");
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            break;
        }
    }
}

int main()
{
    Pipe pipe;
    CompressorStation CS;
    Menu(pipe, CS);

    return 0;
}