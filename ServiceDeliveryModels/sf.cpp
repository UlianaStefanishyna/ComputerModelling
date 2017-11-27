#include "sf.h"

SF::SF(double lambda, double mu, int count){
    this->m_Lambda = lambda;
    this->m_Mu =mu;
    this->m_Count = count;
    this->m_timeReaction.clear();
}

void SF::start(){
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
            }
            else{               //to queue
                task taskToQueue = {T, t_mu};
                queue_SF.push_back(taskToQueue);
            }
        }
        else{
            if(!queue_SF.empty()){
                task minT2 = {0,INT_MAX};
                int i = 0;
                for(task value : queue_SF){
                    if(value.timeDuration <= minT2.timeDuration){
                        minT2.timeDuration = value.timeDuration;
                        i++;
                    }
                }
                queue_SF[i].timeDuration = INT_MAX;
                m_timeReaction.push_back(T-minT2.timeComeIn);
                minT2.timeComeIn = T-minT2.timeComeIn;
                generalTimeOnCPU.push_back(minT2);
                countOfCompletedTask++;
                t2 = T + minT2.timeDuration;
            }
            else{
                t2 = INT_MAX;
                task taskToCPU = {0, t_mu};
                generalTimeOnCPU.push_back(taskToCPU);
                countOfCompletedTask++;
            }
        }
        i++;
    }
    calculateMx_Dx();

}

/*ExecutedTasksTime.clear();
    int index = 0;
    int i = 0;
    double T = 0;
    task taskOnCpu = {0,0};
    double t1 = CommingTime[index];
    while (i < m_Count){
        if((taskOnCpu.timeExecution > t1 || taskOnCpu.timeExecution == 0) && index < m_Count){
            task input;
            T += t1;
            input.timeComing = T;
            input.timeExecution = ExecutionTime[index];
            if(taskOnCpu.timeExecution != 0){
                queue_SF.insert(input);
                taskOnCpu.timeExecution -= t1;
            }
            else
                taskOnCpu = input;
            ++index;
            t1 = CommingTime[index];
        }
        {
            i++;
            T += taskOnCpu.timeExecution;
            t1 -= taskOnCpu.timeExecution;
            if(!queue_SF.empty()){
                taskOnCpu.timeComing = T - taskOnCpu.timeComing;
                ExecutedTasksTime.push_back(taskOnCpu);
                auto temp = min_element(queue_SF.begin(), queue_SF.end());
                taskOnCpu = *temp;
                queue_SF.erase(temp);
            }
            else
            {
                taskOnCpu.timeExecution = 0;
                taskOnCpu.timeComing = T - taskOnCpu.timeComing;
                ExecutedTasksTime.push_back(taskOnCpu);
            }
        }
    }
    calculateMxDx();
}

bool operator<(task const& l, task const& r)
{
    return l.timeExecution < r.timeExecution;
}
*/
