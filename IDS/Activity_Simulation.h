

#ifndef Activity_Simulation_hpp
#define Activity_Simulation_hpp

#include "IDS.h"
#include "Initial_Input.h"
#include "Analysis_Engine.h"
#include "Validation.h"

class Activity_Simulation
{
public:
    Activity_Simulation();
    ~Activity_Simulation();
    
    Activity_Simulation(string, int, char);
    
    void generateAndLogEvent(string);
    float calculate_DailyTotals(float, float, char, string);
    void write_LogFile(string, char, float, string, int);
    bool check_EventTypes();
    
    
    
private:
    vector <Event_Statistic> event_stat_vec;
    vector <Event_Type> event_type_vec;
    int days_to_monitor;
    string event_log_filename;
    char mode;
};


#endif 
