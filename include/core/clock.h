#ifndef TRACER_CLOCK_H
#define TRACER_CLOCK_H

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Clock {
   public:
    Clock(int cols, int steps, float tempo) : m_cols(cols), m_tempo(120.0f), m_steps(16), m_currentStep(0), running(true) {
        changeTempo(m_tempo);
    }

    ~Clock() {
        stop();
    }

    int start() {
        running = true;
        clockThread = std::thread(&Clock::clockLoop, this);

        for (int i = 0; i < m_cols; ++i) {
            workerThreads.emplace_back(&Clock::workerLoop, this, i);
        }

        return 0;
    }

    void changeTempo(float tempo) {
        m_tempo = tempo;
        m_tempoMs = 60000.0f / m_tempo;
    }

    int stop() {
        running = false;
        cv.notify_all();

        if (clockThread.joinable()) {
            clockThread.join();
        }

        for (auto& t : workerThreads) {
            if (t.joinable()) {
                t.join();
            }
        }

        workerThreads.clear();
        return 0;
    }

    void performStep() {
        // You would put your step performing code here
        std::cout << "Performing step: " << m_currentStep << std::endl;
    }

   private:
    void clockLoop() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(m_tempoMs)));

            {
                std::lock_guard<std::mutex> lock(mutex);
                ++m_currentStep;
                if (m_currentStep >= m_steps) {
                    m_currentStep = 0;
                }
            }

            cv.notify_all();
            performStep();
        }
    }

    void workerLoop(int colIndex) {
        while (running) {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock);

            if (!running) break;

            // Now this worker thread knows that a step has occurred, and it can do something with it
            std::cout << "Worker thread for column " << colIndex << " handling step " << m_currentStep << "\n";
        }
    }

    bool running;
    int m_cols;  // I assumed this variable is a class member, representing the number of columns
    int m_steps;
    float m_tempo;
    int m_currentStep = 0;
    float m_tempoMs;
    std::thread clockThread;
    std::vector<std::thread> workerThreads;
    std::mutex mutex;
    std::condition_variable cv;
};

// int main() {
//     Clock clockSystem(4);  // Assuming '4' as an arbitrary number of columns
//     clockSystem.start();
//     std::this_thread::sleep_for(std::chrono::seconds(10));
//     return 0;
// }

#endif  // !TRACER_CLOCK_H