#pragma once

#include <iostream>
#include <string>
#include <chrono>



class Block {
public:
    int BlockID;
    double Time_Release, Due_Date;
    std::string Ready;
    double secondsUntilDue;

    Block(int bId, double tr, double dd, std::string r);
    ~Block();

    void SetSecondsUntilDue(double s) {
        secondsUntilDue = s;
    }

    int GetId() const {
        return BlockID;
    }

    double GetTimeRelease() const {
        return Time_Release;
    }

    double GetDueDate() const {  
        return Due_Date;
    }

    double GetSecondsLeftToDueDate() const {
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now.time_since_epoch();
        double releaseTim = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count(); // Time in seconds

        return Due_Date - releaseTim;
    }

    std::string GetReady() const {
        return Ready;
    }
};

