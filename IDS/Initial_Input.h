

#ifndef Initial_Input_h
#define Initial_Input_h

#include "IDS.h"
#include "Activity_Simulation.h"

class Initial_Input
{
public:
    // constructors
    Initial_Input();
    
    Initial_Input(string, string, int);
    
    // deconstructors
    ~Initial_Input();
    
    //methods
    bool validate_events();
    
private:
    //class attributes
    string event_type_filename;
    int days_to_monitor;
    string stat_filename;
    vector <Event_Type> event_type_vec;
    vector <Event_Statistic> event_stat_vec;
};


#endif
