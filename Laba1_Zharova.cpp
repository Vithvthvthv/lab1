#include <iostream>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

struct Pipe {
    string name;
    float length = -1;
    int diameter = -1;
    bool repair;
};

struct Compress {
    string name;
    int count = -1;
    int count_working = -1;
    string classification;
    bool working;
};

// Function to check if pipe is created
bool isPipeCreated(const Pipe& pipe) {
    return !pipe.name.empty() || pipe.length != -1 || pipe.diameter != -1;
}

// Function to check if station is created
bool isStationCreated(const Compress& compstation) {
    return !compstation.name.empty() || compstation.count != -1 ||
        compstation.count_working != -1 || !compstation.classification.empty();
}

// Function to check if there is any data
bool hasData(const Pipe& pipe, const Compress& compstation) {
    return isPipeCreated(pipe) || isStationCreated(compstation);
}

// 1. Function to read pipe data from console
void readPipeFromConsole(Pipe& pipe) {
    cout << "Enter pipe name: ";
    cin >> pipe.name;

    cout << "Enter pipe length (km): ";
    cin >> pipe.length;
    while (cin.fail() || pipe.length < 0) {
        cout << "Error! Enter a valid positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> pipe.length;
    }

    cout << "Enter pipe diameter (mm): ";
    cin >> pipe.diameter;
    while (cin.fail() || pipe.diameter < 0) {
        cout << "Error! Enter a valid positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> pipe.diameter;
    }

    cout << "Is pipe under repair? (0 - no, 1 - yes): ";
    cin >> pipe.repair;
    while (cin.fail()) {
        cout << "Error! Enter 0 or 1: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> pipe.repair;
    }

    cout << "Pipe '" << pipe.name << "' created successfully!\n";
}

// 2. Function to print pipe data
void printPipe(const Pipe& pipe) {
    cout << "\nPipe parameters:\n";
    cout << "Name: " << (pipe.name.empty() ? "unknown" : pipe.name) << "\n";
    cout << "Length: " << (pipe.length == -1 ? "unknown" : to_string(pipe.length) + " km") << "\n";
    cout << "Diameter: " << (pipe.diameter == -1 ? "unknown" : to_string(pipe.diameter) + " mm") << "\n";
    cout << "Under repair: " << (pipe.repair ? "yes" : "no") << "\n";
}

// 3. Function to edit pipe repair status
void editPipeRepair(Pipe& pipe) {
    if (!isPipeCreated(pipe)) {
        cout << "Error! First create a pipe.\n";
        return;
    }

    cout << "Current repair status for pipe '" << pipe.name << "': "
        << (pipe.repair ? "under repair" : "working") << "\n";
    cout << "Enter new repair status (0 - working, 1 - under repair): ";
    cin >> pipe.repair;

    while (cin.fail()) {
        cout << "Error! Enter 0 or 1: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> pipe.repair;
    }

    cout << "Pipe '" << pipe.name << "' repair status updated: "
        << (pipe.repair ? "under repair" : "working") << "\n";
}

// 4. Function to start workshop (increase working workshops)
void startWorkshop(Compress& compstation) {
    if (!isStationCreated(compstation)) {
        cout << "Error! First create a compressor station.\n";
        return;
    }

    if (compstation.count == -1) {
        cout << "Error! First set the total number of workshops.\n";
        return;
    }

    if (compstation.count == 0) {
        cout << "Error! Total number of workshops is zero. Cannot start workshop.\n";
        return;
    }

    if (compstation.count_working < compstation.count) {
        compstation.count_working++;
        cout << "Workshop started. Now " << compstation.count_working
            << " out of " << compstation.count << " workshops are working.\n";
    }
    else {
        cout << "All workshops are already working!\n";
    }
}

// 5. Function to stop workshop (decrease working workshops)
void stopWorkshop(Compress& compstation) {
    if (!isStationCreated(compstation)) {
        cout << "Error! First create a compressor station.\n";
        return;
    }

    if (compstation.count_working == 0) {
        cout << "No workshops are working! Cannot stop workshop.\n";
        return;
    }

    if (compstation.count_working > 0) {
        compstation.count_working--;
        cout << "Workshop stopped. Now " << compstation.count_working
            << " out of " << compstation.count << " workshops are working.\n";
    }
}

// Function to add compressor station
void addCompressorStation(Compress& compstation) {
    cout << "Enter compressor station name: ";
    cin >> compstation.name;

    cout << "Enter number of workshops: ";
    cin >> compstation.count;
    while (cin.fail() || compstation.count < 0) {
        cout << "Error! Enter a valid positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> compstation.count;
    }

    cout << "Enter number of working workshops: ";
    cin >> compstation.count_working;
    while (cin.fail() || compstation.count_working < 0 || compstation.count_working > compstation.count) {
        cout << "Error! Enter a valid number (0-" << compstation.count << "): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> compstation.count_working;
    }

    cout << "Enter classification: ";
    cin >> compstation.classification;

    cout << "Is compressor station under repair? (0 - no, 1 - yes): ";
    cin >> compstation.working;
    while (cin.fail()) {
        cout << "Error! Enter 0 or 1: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> compstation.working;
    }

    cout << "Compressor station '" << compstation.name << "' created successfully!\n";
}

// Function to show all objects
void showAllObjects(const Pipe& pipe, const Compress& compstation) {
    if (!hasData(pipe, compstation)) {
        cout << "No data available. Please add pipes or compressor stations first.\n";
    }
    else {
        printPipe(pipe);

        cout << "\nCompressor station parameters:\n";
        cout << "Name: " << (compstation.name.empty() ? "unknown" : compstation.name) << "\n";
        cout << "Number of workshops: " << (compstation.count == -1 ? "unknown" : to_string(compstation.count)) << "\n";
        cout << "Number of working workshops: " << (compstation.count_working == -1 ? "unknown" : to_string(compstation.count_working)) << "\n";
        cout << "Classification: " << (compstation.classification.empty() ? "unknown" : compstation.classification) << "\n";
        cout << "Under repair: " << (compstation.working ? "yes" : "no") << "\n";
    }
}

// Function to edit compressor station workshops
void editCompressorStationWorkshops(Compress& compstation) {
    if (!isStationCreated(compstation)) {
        cout << "Error! First create a compressor station.\n";
        return;
    }

    cout << "Current workshops: " << compstation.count_working << " working out of " << compstation.count << "\n";
    cout << "Select action:\n 1. Start workshop\n 2. Stop workshop\n";
    int action;
    cin >> action;
    if (action == 1) {
        startWorkshop(compstation);
    }
    else if (action == 2) {
        stopWorkshop(compstation);
    }
    else {
        cout << "Invalid choice.\n";
    }
}

// 7. Function to load data from file
void loadFromFile(Pipe& pipe, Compress& compstation) {
    ifstream file("mydata.txt");
    if (!file.is_open()) {
        cout << "Error: cannot open file 'mydata.txt'. File may not exist.\n";
        return;
    }

    string line;
    string currentSection;

    // Reset current data
    pipe = Pipe();
    compstation = Compress();

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line == "Pipe parameters:") {
            currentSection = "pipe";
        }
        else if (line == "Compressor station parameters:") {
            currentSection = "station";
        }
        else if (line.find("Name: ") != string::npos) {
            string name = line.substr(6);
            if (name != "unknown") {
                if (currentSection == "pipe") pipe.name = name;
                else compstation.name = name;
            }
        }
        else if (line.find("Length: ") != string::npos) {
            string lengthStr = line.substr(8);
            if (lengthStr != "unknown") {
                pipe.length = stof(lengthStr.substr(0, lengthStr.find(" km")));
            }
        }
        else if (line.find("Diameter: ") != string::npos) {
            string diameterStr = line.substr(10);
            if (diameterStr != "unknown") {
                pipe.diameter = stoi(diameterStr.substr(0, diameterStr.find(" mm")));
            }
        }
        else if (line.find("Under repair: ") != string::npos) {
            string status = line.substr(14);
            if (currentSection == "pipe") {
                pipe.repair = (status == "yes");
            }
            else {
                compstation.working = (status == "yes");
            }
        }
        else if (line.find("Number of workshops: ") != string::npos) {
            string countStr = line.substr(21);
            if (countStr != "unknown") {
                compstation.count = stoi(countStr);
            }
        }
        else if (line.find("Number of working workshops: ") != string::npos) {
            string countStr = line.substr(29);
            if (countStr != "unknown") {
                compstation.count_working = stoi(countStr);
            }
        }
        else if (line.find("Classification: ") != string::npos) {
            string classification = line.substr(16);
            if (classification != "unknown") {
                compstation.classification = classification;
            }
        }
    }

    file.close();
    cout << "Data successfully loaded from file 'mydata.txt'\n";
}

// Function to save data to a file
void saveToFile(const Pipe& pipe, const Compress& compstation) {
    ofstream file("mydata.txt");
    if (!file.is_open()) {
        cout << "Error: cannot create file in current directory. Trying desktop...\n";
        file.open("C:\\Users\\NDR_WDI\\Desktop\\results_data.txt");
    }

    if (file.is_open()) {
        if (!hasData(pipe, compstation)) {
            file << "No data has been added yet.\n";
            cout << "File created, but no data has been added yet.\n";
        }
        else {
            file << "Pipe parameters:\n";
            file << "Name: " << (pipe.name.empty() ? "unknown" : pipe.name) << "\n";
            file << "Length: " << (pipe.length == -1 ? "unknown" : to_string(pipe.length) + " km") << "\n";
            file << "Diameter: " << (pipe.diameter == -1 ? "unknown" : to_string(pipe.diameter) + " mm") << "\n";
            file << "Under repair: " << (pipe.repair ? "yes" : "no") << "\n";

            file << "\nCompressor station parameters:\n";
            file << "Name: " << (compstation.name.empty() ? "unknown" : compstation.name) << "\n";
            file << "Number of workshops: " << (compstation.count == -1 ? "unknown" : to_string(compstation.count)) << "\n";
            file << "Number of working workshops: " << (compstation.count_working == -1 ? "unknown" : to_string(compstation.count_working)) << "\n";
            file << "Classification: " << (compstation.classification.empty() ? "unknown" : compstation.classification) << "\n";
            file << "Under repair: " << (compstation.working ? "yes" : "no") << "\n";

            cout << "Data successfully saved to file 'mydata.txt'\n";
        }
        file.close();
    }
    else {
        cout << "Error: unable to open file for writing.\n";
    }
}

void Menu(Pipe& pipe, Compress& compstation) {
    while (true)
    {
        cout << "\nSelect option:\n 1. Add pipe \n 2. Add compressor station\n 3. Show all objects\n 4. Edit pipe repair status\n 5. Edit compressor station workshops\n 6. Save to file\n 7. Load from file\n 0. Exit\n";
        int type;
        cin >> type;
        if (cin.fail()) {
            cout << "Error!" << endl;
            cout << "Enter a valid number (0-7)" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (type == 0) {
            cout << "Exiting the program." << endl;
            break;
        }

        switch (type)
        {
        case 1:
            readPipeFromConsole(pipe);
            break;
        case 2:
            addCompressorStation(compstation);
            break;
        case 3:
            showAllObjects(pipe, compstation);
            break;
        case 4:
            editPipeRepair(pipe);
            break;
        case 5:
            editCompressorStationWorkshops(compstation);
            break;
        case 6:
            saveToFile(pipe, compstation);
            break;
        case 7:
            loadFromFile(pipe, compstation);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}

int main()
{
    Pipe pipe;
    Compress compstation;
    Menu(pipe, compstation);

    return 0;
}