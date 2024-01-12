#include <iostream>
#include "controller.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;


int main(int argc, char* argv[]) {
    Controller c;
    bool testing = false;
    bool loading = false;
    string savefile = "";
    if (argc > 1) {
        for (int i = 0; i < argc; i++) {
            string argument = argv[i];
            if (argument == "-testing") {
                testing = true;
                cout << "You are in testing mode!" << endl;
            }
            if (argument == "-load") {
                if (i < argc - 1) {
                    i++;
                    savefile = argv[i];
                    fstream fs;
                    fs.open(savefile);
                    if (fs.is_open()) {
                        cout << "File opened successfully!" << endl;
                        fs.close();
                        loading = true;
                    } else {
                        cerr << "Error opening file" << endl;
                        return 0;
                    }
                } else {
                    cerr << "No file name specified! Please enter a file name" << endl;
                    return 0;
                }
            }
        }
    }
    try {
        srand(time(NULL));
        c.launch(testing, loading, savefile);
    } catch(invalidFile&) {
        cerr << "Invalid file format!" << endl;
    } catch(...) {
        cerr << "Goodbye!" << endl;
    }
}
