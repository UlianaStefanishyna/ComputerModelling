#include "lifo.h"

LIFO::LIFO(double lambda, double mu, int count){
    this->m_Lambda = lambda;
    this->m_Mu =mu;
    this->m_Count = count;
    this->m_timeReaction.clear();
}

void LIFO::start(){
    int i = 0;
    double T = 0; //current time in system
    double t1 = 0;
    double t2 = INT_MAX;
    double t_mu = 0, t_lambda = 0;
    while(i < m_Count){
        if(t1 < t2){
            T = t1;
            t_lambda = (-1/m_Lambda)*log(((double) rand() / (RAND_MAX))); //time to come
            t1 += t_lambda;
            t_mu = (-1/m_Mu)*log(((double) rand() / (RAND_MAX))); //time to complete

            if(t2 == INT_MAX){  //if CPU is free  [first entry]
                t2 = T + t_mu;
                task taskToCPU = {0, t_mu};
                generalTimeOnCPU.push_back(taskToCPU);
                countOfCompletedTask++;
                m_timeReaction.push_back(0);
            }
            else{               //to queue
                task taskToQueue = {T,t_mu};
                queue_LIFO.push_back(taskToQueue);
            }
        }
        else{
            if(!queue_LIFO.empty()){
                task taskToCPUFromQueue = queue_LIFO.back();
                queue_LIFO.pop_back();
                taskToCPUFromQueue.timeComeIn = T - taskToCPUFromQueue.timeComeIn;
                generalTimeOnCPU.push_back(taskToCPUFromQueue);
                countOfCompletedTask++;
                m_timeReaction.push_back(taskToCPUFromQueue.timeComeIn);
                t2 = T + taskToCPUFromQueue.timeDuration;
            }
            else{
                t2 = INT_MAX;
                task taskToCPU = {0, t_mu};
                generalTimeOnCPU.push_back(taskToCPU);
                countOfCompletedTask++;
                m_timeReaction.push_back(0);
            }
        }
        i++;
    }
    calculateMx_Dx();
}
