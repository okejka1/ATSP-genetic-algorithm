//
// Created by User on 13.10.2023.
//

#ifndef INC_1_TIMER_H
#define INC_1_TIMER_H
#include "chrono"

using namespace std::chrono;

class Timer {
public:
    void start();
    void stop();
    long nano();
    long micro();
    long long mili();

private:
    high_resolution_clock::time_point beginning;
    high_resolution_clock::time_point end;
};


#endif //INC_1_TIMER_H
