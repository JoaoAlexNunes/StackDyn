#pragma once

#include <string>

class Block {
public:
    int BlockID;
    double Time_Release, Due_Date;
    std::string Ready;

    Block(int bId, double tr, double dd, std::string r);
    ~Block();

    int GetId() const {
        return BlockID;
    }

    double GetTimeRelease() const {
        return Time_Release;
    }

    double GetDueDate() const {
        return Due_Date;
    }

    std::string GetReady() const {
        return Ready;
    }
};

