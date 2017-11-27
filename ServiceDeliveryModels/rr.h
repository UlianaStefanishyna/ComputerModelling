#ifndef RR_H
#define RR_H
#include "cpu.h"
#include <queue>

class RR : public CPU{
public:
    RR(double lambda, double mu, int count);
    void start();
    queue<task> queue_RR;
};

#endif // RR_H
