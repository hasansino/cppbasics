#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Not neough arguments" << endl;
        return 1;
    }

    auto file = argv[1];
    auto len = stoi(argv[2]);

    std::ofstream fout(file, ios_base::out | ios_base::trunc);

    if (!fout.is_open()) {
        cout << "Error opening file: " << file << endl;
        return 1;
    }

    fout << "int sqrtTableLen = " << len << ";" << endl;
    fout << "double sqrtTable[] = {" << endl;
    for (int i = 0; i <= len; i++) {
        fout << sqrt(static_cast<double>(i)) << "," << endl;
    }
    fout << "};" << endl;
    fout.close();

    return EXIT_SUCCESS;
}
