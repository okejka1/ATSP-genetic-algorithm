//
// Created by User on 13.10.2023.
//

#include "Timer.h"

using namespace std::chrono;

void Timer::start() {
    beginning = high_resolution_clock::now();
}

void Timer::stop() {
    end = high_resolution_clock::now();
}

long Timer::nano() {
    return duration_cast<nanoseconds>(end - beginning).count();
}

long Timer::micro(){
    return duration_cast<microseconds>(end - beginning).count();
}

long long int Timer::mili() {
    return duration_cast<milliseconds>(end - beginning).count();
}