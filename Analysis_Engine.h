
#ifndef ANALYSIS_ENGINE
#define ANALYSIS_ENGINE

#include "IDS.h"
#include "Initial_Input.h"
#include "Activity_Simulation.h"
#include "Alert_Engine.h"

class Analysis_Engine
{
public:
    Analysis_Engine();
    ~Analysis_Engine();
    
    Analysis_Engine(string, int, int);
    
    void write_DailyTotal(string);
    void write_Statistics(string);
    
private:
    vector <Event_Daily_Total> event_daily_total_vec;
    int days_to_monitor;
    int choice;
};

#endif
