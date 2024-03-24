#include <fstream>
#include <iostream>

#include "std.hpp"

using namespace std;

namespace test {
    void _std_input_output() {

        cout << "____ Input / Output ____" << endl;

        const string file_path = "io_test.txt";
        const string c_make_cache = "CMakeCache.txt";

        // writing to file
        fstream f;
        f.open(file_path, ios::out | ios::trunc);
        for (int i = 0; i < 100; i++) {
            f << "Loriem ipsum dolor sit amet" << endl;
        }
        f.close();

        // reading from file
        fstream f2;
        f2.open(file_path, ios::in);

        string l;
        int counter = 0;

        while (getline(f2, l)) {
            counter++;
        }
        f2.close();

        cout << "Read " << counter << " lines from file" << endl;

        // checking steram state
        fstream f3;
        f3.open(file_path);

        if (f3.bad()) {
            cout << "f2.bad()" << endl;
        }
        if (f3.fail()) {
            cout << "f2.fail()" << endl;
        }
        if (f3.eof()) {
            cout << "f2.eof()" << endl;
        }
        if (f3.good()) {
            cout << "f2.good()" << endl;
        }
        f3.close();

        // readfile to memory
        fstream f4;
        f4.open(c_make_cache, ios::in);
        if (f4.is_open()) {
            f4.seekg(0, ios::end);                // find eof
            streampos size = f4.tellg();          // retrieve eof pos
            cout << "f4.size -> " << size << endl;//
            f4.seekg(0, ios::beg);                // move to start
            char* buff = new char[size];          // allocate buffer
            f4.read(buff, size);                  // read into buffer all file
            delete[] buff;                        // release buffer
        }
        f4.close();
    }
}// namespace test