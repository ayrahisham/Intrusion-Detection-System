


#ifndef Analysis_Engine_hpp
#define Analysis_Engine_hpp

#include "Initial_Input.h"
#include "Activity_Simulation.h"
#include "Alert_Engine.h"

class Analysis_Engine
{
public:
    Analysis_Engine();
    ~Analysis_Engine();
    
    Analysis_Engine(string, int, char, string);
    
    void write_DayTotal(string);
    void write_Statistics(string);
    
private:
    vector <Day_Total> day_total_vec;
    vector <Event_Type> event_type_vec;
    int days_to_monitor;
    char mode;
};



#endif
