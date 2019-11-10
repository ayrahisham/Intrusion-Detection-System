

#include "Activity_Simulation.h"


Activity_Simulation::Activity_Simulation()
{
    
}

Activity_Simulation::~Activity_Simulation()
{
    
}

Activity_Simulation::Activity_Simulation(string stat_filename, int days_to_monitor, char mode)
{
    delete_output_files(mode); 
    cout << "\n\n########## Activity Simulation Engine ##########\n" << endl;
    this -> days_to_monitor = days_to_monitor;
    this -> mode = mode;
    
    srand((int)time(NULL));
    

    event_type_vec = read_event_type_file("Events.txt");
    event_stat_vec = read_stat_file(stat_filename);
    
    Validation v;
    bool check_events = v.validate_events(event_type_vec, event_stat_vec);
    bool check_total = v.check_Total_EventTypes(event_type_vec, event_stat_vec);
    
    if (check_events == true && check_total == true)
    {
        if (mode == 'T')
        {
            generateAndLogEvent("Event_Log_Training.txt");
            cout << "\n >>>>>>>>>>>>>> Event Logs have been created for Training Data" << endl;
            Analysis_Engine("Event_Log_Training.txt", days_to_monitor, mode, stat_filename);
        }
        else
        {
            generateAndLogEvent("Event_Log_Live.txt");
            cout << "\n >>>>>>>>>>>>>> Event Logs have been created for Live Data" << endl;
            Analysis_Engine("Event_Log_Live.txt", days_to_monitor, mode, stat_filename);
        }
    }
    

}

void Activity_Simulation :: generateAndLogEvent(string event_log_filename)
{
    cout << "Writing File: " << event_log_filename << endl;
    
    for (int i = 0; i < event_stat_vec.size(); i++)
    {
        // extract information each struct in stat vector
        string event_name = event_stat_vec[i].event_name;
        float std_dev = event_stat_vec[i].std_dev;
        
        int event_vec_index = search_event_in_vec(event_name, event_type_vec);
        char event_val_type = event_type_vec[event_vec_index].event_val_type;
        float val_min = 0;
        float val_max = event_type_vec[event_vec_index].max;
        if (val_max == -1)
            val_max = std_dev * 4;
        
        // randomize daily total and write file
        for (int i = 0; i < days_to_monitor; i++)
        {
            // calculate total log for event in one day
            float daily_total_eventLog = calculate_DailyTotals(val_min, val_max, event_val_type, event_name);
            int day_number = i + 1;
            
            // write the logs in text file
            // format for discrete = event:day_number:
            // format for continuous = event:day_number:duration:
            write_LogFile(event_log_filename, event_val_type, daily_total_eventLog, event_name, day_number);
        }
    }
}

float Activity_Simulation :: calculate_DailyTotals(float val_min, float val_max, char val_type, string event_name)
{
 
    float final_rand = 0.0;
    int random_int = 0.0;
    
    if (val_type == 'C' || val_type == 'c')
    {
        float random = ((float) rand()) / (float) RAND_MAX;
        float range = val_max - val_min;
        float r = random * range;
        final_rand = val_min + r;
        
        return final_rand;
    }
    else
    {
        int range_min_int = static_cast<int>(val_min);
        int range_max_int = static_cast<int>(val_max);
        random_int = rand() % ((range_max_int - range_min_int) + 1) + range_min_int;
        
        return random_int;
    }
}

void Activity_Simulation::write_LogFile(string fileName, char event_val_type, float daily_total_eventLog, string event_name, int day_number)
{
    fstream outfile;
    
    outfile.open (fileName, fstream::in | fstream::out | fstream::app);
    char delimiter = ':';
    
    if (!outfile)
    {
        cout << "Writing to file failed" << endl;
        exit (-1);
    }
    outfile
        << event_val_type
        << delimiter
        << event_name
        << delimiter
        << day_number
        << delimiter
        << daily_total_eventLog
        << delimiter
        << endl;
    
    outfile.close ();
    
}



