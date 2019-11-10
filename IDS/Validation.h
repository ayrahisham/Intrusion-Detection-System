
#ifndef VALIDATION
#define VALIDATION

#include "IDS.h"
#include "Initial_Input.h"
#include "Activity_Simulation.h"
#include "Analysis_Engine.h"
#include "Alert_Engine.h"
#include <cctype>

class Validation
{
public:
    Validation();
    ~Validation();
    
    // check if event types matched in both Events and Stats file from user
    bool validate_events(vector <Event_Type>, vector <Event_Statistic>);
    
    // check if total event types matched in both Events and Ststs file from user
    bool check_Total_EventTypes(vector <Event_Type>, vector <Event_Statistic>);
    
    // check if arguments entered from command line is correct
    bool check_initial_arguments(string a, string b);
    
    
private:
    
};

#endif



