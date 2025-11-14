#pragma once

#include <iostream>

#include "copyable.h"

class Timestamp : public copyable {
public:
    Timestamp();

    explicit Timestamp(int64_t microSecondsSinceEpochArg);

    std::string toString() const;

    static Timestamp now();

private:
    int64_t microSecondsSinceEpoch_;
};