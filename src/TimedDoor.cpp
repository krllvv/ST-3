// Copyright 2024 Kirillov Maxim
#include <stdexcept>
#include <chrono> // NOLINT [build/c++11]
#include <thread> // NOLINT [build/c++11]
#include "../include/TimedDoor.h"

DoorTimerAdapter::DoorTimerAdapter(TimedDoor &door) : door(door) {}

void DoorTimerAdapter::Timeout() {
    if (door.isDoorOpened()) {
        throw std::runtime_error("Door is opened for too long");
    }
}

TimedDoor::TimedDoor(int timeout) : isOpened(false), iTimeout(timeout) {
    adapter = new DoorTimerAdapter(*this);
}

bool TimedDoor::isDoorOpened() {
    return isOpened;
}

void TimedDoor::unlock() {
    if (isDoorOpened()) {
        throw std::logic_error("Door is already opened");
    }
    isOpened = true;
}

void TimedDoor::lock() {
    if (!isDoorOpened()) {
        throw std::logic_error("Door is already closed");
    }
    isOpened = false;
}

int TimedDoor::getTimeOut() const {
    return iTimeout;
}

void TimedDoor::throwState() {
    adapter->Timeout();
}

void Timer::sleep(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void Timer::tregister(int t, TimerClient * c) {
    client = c;
    sleep(t);
    client->Timeout();
}
