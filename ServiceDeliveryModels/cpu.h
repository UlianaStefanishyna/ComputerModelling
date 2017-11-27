#ifndef CPU_H
#define CPU_H
#include <iostream>
#include <vector>
#include <time.h>
#include <limits.h>
#include <math.h>

using namespace std;

struct task{
    double timeComeIn;
    double timeDuration;
};

class CPU{
protected:
    double m_Mx;
    double m_Dx;
    vector<double> m_timeReaction;
    double m_MarkActual;
    double m_Lambda;
    double m_Mu;
    int m_Count;
    task m_CurrTask;
public:
    CPU() : m_Mx(0), m_Dx(0), m_CurrTask{0,0}{}
    double tau;
    vector<task> generalTimeOnCPU;
    int countOfCompletedTask = 0;
    double react;
    void   setMu(double mu);
    void   setLambda(double lambda);
    double getLambda();
    void setGoodTau(double mu);
    double getMu();
    double getMx();
    double getDx();
    void   calculateMx_Dx();
    double timeReaction();
    double calcActual();
    double coefDone();

};

#endif // CPU_H
