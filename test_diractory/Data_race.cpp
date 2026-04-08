// C++ Program to illustrate the data race condition
#include <iostream>
#include <thread>
using namespace std;

// Global counter variable
int counter = 0;

// Function to increment the counter
void increment()
{
    for (int i = 0; i < 100000; ++i) {
        ++counter;
    }
}

int main()
{
    // Create two threads that run the increment function
    // concurrently
    thread t1(increment);
    thread t2(increment);

    // Wait for both threads to finish
    t1.join();
    t2.join();

    // Print the final counter value
    cout << "Counter value: " << counter << endl;
    return 0;
}