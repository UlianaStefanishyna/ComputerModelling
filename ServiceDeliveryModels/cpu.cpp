#include "cpu.h"

void   CPU::setMu(double mu){
    m_Mu = mu;
}
void   CPU::setLambda(double lambda){
    m_Lambda = lambda;
}
double CPU::getLambda(){
    return m_Lambda;
}
double CPU::getMx(){
    return m_Mx;
}
void CPU::setGoodTau(double mu){
    tau = 1/mu;
}

double CPU::getMu(){
    return m_Mu;
}
double CPU::getDx(){
    return m_Dx;
}
void   CPU::calculateMx_Dx(){
    double sum = 0;
    double time = 0;
    double reaction = 0;
    for(task value : generalTimeOnCPU){
        sum += value.timeDuration + value.timeComeIn;
        reaction += value.timeComeIn;
    }
    m_Mx = sum / (generalTimeOnCPU.size());
    reaction = reaction / (generalTimeOnCPU.size());
    react = reaction;
    sum = 0;
    for(task value : generalTimeOnCPU){
        time = (value.timeComeIn+value.timeDuration) - m_Mx;
        sum += time * time;
    }
    m_Dx = sum / (generalTimeOnCPU.size());
}
double CPU::timeReaction(){
    double sum = 0;
    for(double value : m_timeReaction)
        sum += value;
    return (sum/m_timeReaction.size());
}
double CPU::calcActual(){
    return 0;
}
double CPU::coefDone(){
    return ((double)generalTimeOnCPU.size()/(double)m_Count);
}
