#include "rr.h"

RR::RR(double lambda, double mu, int count){
    this->m_Lambda = lambda;
    this->m_Mu =mu;
    this->m_Count = count;
    this->m_timeReaction.clear();
}

/*void RR::start(){
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
                if(t_mu <= tau){
                    task taskToCPU = {0, t_mu};
                    generalTimeOnCPU.push_back(taskToCPU);
                    countOfCompletedTask++;
                    m_timeReaction.push_back(0);
                    //T += t_mu;
                    t2 = T + t_mu;
                }
                else{
                    t_mu = t_mu - tau;
                    task taskToQueue = {T, t_mu};
                    queue_RR.push(taskToQueue);
                    //T += tau;
                }
            }
            else{               //to queue
                task taskToQueue = {T,t_mu};
                queue_RR.push(taskToQueue);
            }
        }
        else{
            if(!queue_RR.empty()){
                task taskToCPUFromQueue = queue_RR.front();
                queue_RR.pop();
                if(taskToCPUFromQueue.timeDuration <= tau){
                    taskToCPUFromQueue.timeComeIn = T - taskToCPUFromQueue.timeComeIn;
                    generalTimeOnCPU.push_back(taskToCPUFromQueue);
                    countOfCompletedTask++;
                    m_timeReaction.push_back(taskToCPUFromQueue.timeComeIn);
                    t2 = T + taskToCPUFromQueue.timeDuration;
                }
                else{
                    taskToCPUFromQueue.timeDuration = taskToCPUFromQueue.timeDuration - tau;
                    queue_RR.push(taskToCPUFromQueue);
                   // T += tau;
                }
            }
            else{
                t2 = INT_MAX;
                if(t_mu <= tau){
                    task taskToCPU = {T, t_mu};
                    generalTimeOnCPU.push_back(taskToCPU);
                    countOfCompletedTask++;
                    m_timeReaction.push_back(0);
                }
                else{
                    t_mu = t_mu - tau;
                    task taskToQueue = {T, t_mu};
                    queue_RR.push(taskToQueue);
                }
            }
        }
        i++;
    }
    calculateMx_Dx();
}*/

void RR::start(){
    double t1 = 0, T = 0;
    double t2 = INT_MAX;
    int i = 0;
    while(i < m_Count){
        if(t1 < t2){
            T = t1;
            t2 = (-1/m_Mu)*log(((double) rand() / (RAND_MAX)));
            task taskToCPU = {t1,t2};
            if(t2 <= tau){
                taskToCPU.timeComeIn = 0;
                generalTimeOnCPU.push_back(taskToCPU);
                m_timeReaction.push_back(0);
                t2 += T;
            }
            else{
                t2 -= tau;
                taskToCPU.timeDuration = t2;
                T += tau;
                queue_RR.push(taskToCPU);
            }
            t1 += (-1/m_Lambda)*log(((double) rand() / (RAND_MAX)));
        }
        else{
            if(!queue_RR.empty()){
                task fromQueue = queue_RR.front();
                queue_RR.pop();
                if(fromQueue.timeDuration <= tau){
                    fromQueue.timeComeIn = T - fromQueue.timeComeIn;
                    generalTimeOnCPU.push_back(fromQueue);
                    m_timeReaction.push_back(fromQueue.timeComeIn);
                    T += fromQueue.timeDuration;
                }
                else{
                    fromQueue.timeDuration = fromQueue.timeDuration - tau;
                    queue_RR.push(fromQueue);
                }
            }
            else{
                t2 = INT_MAX;
            }
        }
        i++;
    }
    calculateMx_Dx();
}
