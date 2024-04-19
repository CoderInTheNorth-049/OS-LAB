#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;

int shared = 1;

void reader(int id) {
    cout << "Reader " << id << " reads the value as " << shared << endl;
}

void writer(int id) {
    shared = id;
    cout << "Writer " << id << " updates the value of shared variable to "
         << shared << endl;
}

int main() {
    int numReaders, numWriters;
    cout << "Enter the number of readers: ";
    cin >> numReaders;
    cout << "Enter the number of writers: ";
    cin >> numWriters;

    vector<thread> readerThreads;
    for (int i = 1; i <= numReaders; ++i) {
        readerThreads.push_back(thread(reader, i));
    }

    vector<thread> writerThreads;
    for (int i = 1; i <= numWriters; ++i) {
        writerThreads.push_back(thread(writer, i));
    }

    for (auto &t : readerThreads) {
        t.join();
    }
    for (auto &t : writerThreads) {
        t.join();
    }

    cout << "Final value of shared is " << shared << endl; 
    return 0;
}
