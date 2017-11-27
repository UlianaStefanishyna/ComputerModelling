#ifndef SF_H
#define SF_H
#include "cpu.h"

class SF : public CPU{
public:
    SF(double lambda, double mu, int count);
    void start();
    vector<task> queue_SF;
};

#endif // SF_H
