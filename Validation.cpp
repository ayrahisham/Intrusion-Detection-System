#include "Validation.h"

Validation::Validation()
{
    
}

Validation::~Validation()
{
    
}

bool Validation::validate_events(vector <Event_Type> event_type_vec, vector <Event_Statistic> event_stat_vec)
{
    // check if events and value type are the same in event type and event stat file
    bool match = false;
    bool exit_event_type = false;
    
    cout << "Validation of Event Types in Event and Statistic files" << endl;
    
    int i = 0;
    while (i < event_stat_vec.size() && exit_event_type == false)
    {
        string name_toCompare = event_stat_vec[i].event_name;
        
        int j = 0;
        bool exit_event_stat = false;
        while (j < event_type_vec.size() && exit_event_stat == false)
        {
            string name = event_type_vec[j].event_name;

            if (name.compare(name_toCompare) == 0)
            {
                match = true;
                exit_event_stat = true;
            }
            else
                j++;
        }
        
        if (match == false)
        {
            cout << "Error: Event Not Found" << endl;
            cout << "Not found in either Stats or Events file: "
            <<  name_toCompare
            << endl;
            exit_event_type = true;
        }
        else
            i++;
    }
    return match;
}

bool Validation::check_file_created(string filename)
{
    fstream afile;
    afile.open(filename, ios::in);
    if (!afile)
    {
        cout << "Error: Missing pre-requisite file(s)" << endl;
        return false;
    }
    return true;
}

bool Validation::check_Total_EventTypes(vector <Event_Type> event_type_vec, vector <Event_Statistic> event_stat_vec)
{
    if (event_type_vec.size() != event_stat_vec.size())
    {
        cout << "Error: Total number of event types mismatch in Events and Stats files" << endl;
        return false;
    }
    return true;
}

bool Validation::check_Event_Max_Value(vector <Event_Type> event_type_vec, string event_name, float value)
{
    int i = 0;
    while(i < event_type_vec.size())
    {
        if (event_type_vec[i].event_name.compare(event_name) == 0)
        {
            if (event_type_vec[i].max == 0 || event_type_vec[i].max >= value)
                return false;
        }
        i++;
    }
    return true;
}




