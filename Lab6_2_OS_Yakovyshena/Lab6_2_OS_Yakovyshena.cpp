#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int sharedVariable = 0;

// Function executed by each thread using a critical section
void incrementWithMutex(int iterations)
{
    for (int i = 0; i < iterations; i++)
    {
        std::lock_guard<std::mutex> lock(mtx);
        sharedVariable++;
    }
}

// Function executed by each thread without using a critical section
void incrementWithoutMutex(int iterations)
{
    for (int i = 0; i < iterations; i++)
    {
        sharedVariable++;
    }
}

int main()
{
    int iterations = 10000000; // 10^7

    // Threads using a critical section
    std::thread thread1(incrementWithMutex, iterations);
    std::thread thread2(incrementWithMutex, iterations);

    thread1.join();
    thread2.join();

    std::cout << "Value of the shared variable with a critical section: " << sharedVariable << std::endl;

    // Reset the value
    sharedVariable = 0;

    // Threads without using a critical section
    std::thread thread3(incrementWithoutMutex, iterations);
    std::thread thread4(incrementWithoutMutex, iterations);

    thread3.join();
    thread4.join();

    std::cout << "Value of the shared variable without a critical section: " << sharedVariable << std::endl;

    return 0;
}

//На місці sharedVariable у консолі мають вивестися значення спільної комірки пам'яті після виконання потоків.
//
//У випадку з використанням критичного сегменту, ви повинні побачити значення, рівне 2 * iterations, оскільки два потоки
//виконують інкремент iterations разів кожен.
//
//У випадку без використання критичного сегменту, результат може бути непередбачуваним.Можливі варіанти : 
//значення менше 2 * iterations, значення рівне 2 * iterations або значення більше 2 * iterations.Це залежить від того, 
//як потоки конкурують один з одним та взаємодіють зі спільною коміркою пам'яті.
