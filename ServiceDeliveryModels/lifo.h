#ifndef LIFO_H
#define LIFO_H
#include "cpu.h"

class LIFO : public CPU{
public:
    LIFO(double lambda, double mu, int count);
    void start();
    vector<task> queue_LIFO;
};

#endif // LIFO_H
