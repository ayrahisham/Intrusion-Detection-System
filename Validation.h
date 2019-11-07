
#ifndef VALIDATION
#define VALIDATION

#include "IDS.h"
#include "Initial_Input.h"
#include "Activity_Simulation.h"
#include "Analysis_Engine.h"
#include "Alert_Engine.h"

class Validation
{
public:
    Validation();
    ~Validation();
    
    // check if event types matched in both Events and Stats file from user
    bool validate_events(vector <Event_Type>, vector <Event_Statistic>);
    
    // check if pre-requisite files are already created
    bool check_file_created(string);
    
    // check if total event types matched in both Events and Ststs file from user
    bool check_Total_EventTypes(vector <Event_Type>, vector <Event_Statistic>);
    
    // check if random daily total value exceeds max indicated in Events.txt
    bool check_Event_Max_Value(vector <Event_Type>, string, float);
    
    
private:
    
};

#endif

