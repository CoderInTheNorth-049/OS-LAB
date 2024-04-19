#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <ctime>
#include <cstdlib>
#define NUM_READERS 2
#define NUM_WRITERS 2

std::mutex mtx;
std::condition_variable cond_reader, cond_writer;
int readers_count = 0;
int writers_count = 0;
int resource = 0;
bool synchronized_flag = true; // To switch between synchronized and unsynchronized cases
// Reader function
void readerFunction(int reader_id)
{
    if (synchronized_flag)
    {
        std::unique_lock<std::mutex> lock(mtx);
        while (writers_count > 0)
        {
            std::cout << "Reader " << reader_id << " is waiting because a writer is writing" << std::endl;
            cond_reader.wait(lock);
        }
        readers_count++;
        lock.unlock();
        // Read the resource
        std::cout << "Reader " << reader_id << " reading shared resource" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        lock.lock();
        readers_count--;
        if (readers_count == 0)
        {
            cond_writer.notify_one();
        }
        lock.unlock();
    }
    else
    { // Without synchronization
        // Read the resource
        std::cout << "Reader " << reader_id << " reads resource: " << resource << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Reader " << reader_id << " completed with reading, CS is free" << std::endl;
}
// Writer function
void writerFunction(int writer_id)
{
    if (synchronized_flag)
    {
        std::unique_lock<std::mutex> lock(mtx);
        writers_count++;
        while (readers_count > 0 || writers_count > 1)
        {
            std::cout << "Writer " << writer_id << " wants to write but not allowed" << std::endl;
            cond_writer.wait(lock);
        }
        lock.unlock();
        // Write to the resource
        resource = writer_id;
        std::cout << "Writer " << writer_id << " writing shared resource" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        lock.lock();
        writers_count--;
        cond_writer.notify_one();
        cond_reader.notify_all(); // Signal all readers
        lock.unlock();
    }
    else
    { // Without synchronization
        // Write to the resource
        resource = writer_id;
        std::cout << "Writer " << writer_id << " writes resource: " << resource << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Writer " << writer_id << " completed with writing, CS is free" << std::endl;
}
int main()
{
    std::thread readers[NUM_READERS];
    std::thread writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
    for (int i = 0; i < NUM_READERS; i++)
    {
        reader_ids[i] = i + 1;
        writer_ids[i] = i + 1;
    }
    std::srand(std::time(nullptr));
    // Reader-Reader (RR) case
    synchronized_flag = true;
    std::cout << "Reader-Reader (RR) case:" << std::endl;
    for (int i = 0; i < NUM_READERS; i++)
    {
        readers[i] = std::thread(readerFunction, reader_ids[i]);
    }
    for (int i = 0; i < NUM_READERS; i++)
    {
        readers[i].join();
    }
    // Reader-Writer (RW) case
    synchronized_flag = true;
    std::cout << "\nReader-Writer (RW) case:" << std::endl;
    readers[0] = std::thread(readerFunction, reader_ids[0]);
    writers[0] = std::thread(writerFunction, writer_ids[0]);
    readers[0].join();
    writers[0].join();
    // Writer-Writer (WW) case
    synchronized_flag = true;
    std::cout << "\nWriter-Writer (WW) case:" << std::endl;
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        writers[i] = std::thread(writerFunction, writer_ids[i]);
    }
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        writers[i].join();
    }
    // Writer-Reader (WR) case
    synchronized_flag = true;
    std::cout << "\nWriter-Reader (WR) case:" << std::endl;
    writers[0] = std::thread(writerFunction, writer_ids[0]);
    readers[0] = std::thread(readerFunction, reader_ids[0]);
    readers[0].join();
    writers[0].join();
    // Reader-Reader (RR) case without synchronization
    synchronized_flag = false;
    std::cout << "\nReader-Reader (RR) case without synchronization:" << std::endl;
    for (int i = 0; i < NUM_READERS; i++)
    {
        readers[i] = std::thread(readerFunction, reader_ids[i]);
    }
    for (int i = 0; i < NUM_READERS; i++)
    {
        readers[i].join();
    }
    // Reader-Writer (RW) case without synchronization
    synchronized_flag = false;
    std::cout << "\nReader-Writer (RW) case without synchronization:" << std::endl;
    readers[0] = std::thread(readerFunction, reader_ids[0]);
    writers[0] = std::thread(writerFunction, writer_ids[0]);
    readers[0].join();
    writers[0].join();
    // Writer-Writer (WW) case without synchronization
    synchronized_flag = false;
    std::cout << "\nWriter-Writer (WW) case without synchronization:" << std::endl;
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        writers[i] = std::thread(writerFunction, writer_ids[i]);
    }
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        writers[i].join();
    }
    // Writer-Reader (WR) case without synchronization
    synchronized_flag = false;
    std::cout << "\nWriter-Reader (WR) case without synchronization:" << std::endl;
    writers[0] = std::thread(writerFunction, writer_ids[0]);
    readers[0] = std::thread(readerFunction, reader_ids[0]);
    readers[0].join();
    writers[0].join();
    return 0;
}