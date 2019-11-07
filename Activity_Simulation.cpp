
#include "Activity_Simulation.h"


Activity_Simulation::Activity_Simulation()
{
    
}

Activity_Simulation::~Activity_Simulation()
{
    
}

Activity_Simulation::Activity_Simulation(string stat_filename, int days_to_monitor)
{
    cout << "\n\n########## Activity Simulation Engine ##########\n" << endl;
    event_stat_vec = read_stat_file(stat_filename);
    event_type_vec = read_event_type_file("Events.txt");
    
    this -> days_to_monitor = days_to_monitor;
    
    srand((int)time(NULL));
    
    int choice = 0;
    cout << endl;
    cout << "Data to be Simulated:" << endl;
    cout << "   Option 1: Live Data" << endl;
    cout << "   Option 2: Training Data" << endl;
    cout << "Enter Choice: ";
    cin >> choice;
    cout << endl;
    
    cout << "Begin validation of file content ..." << endl;
    Validation v;
    if (choice == 1)
    {
        // if live data option selected
        // check if "training data" has already been generated
        this -> event_log_filename = "Event_Log_Live_Data.txt";
        bool check = v.check_file_created("Event_Log_Training_Data.txt");
        if (check == true)
        {
            // check if event types and # events in both event and stats file match
            bool check_2 = check_EventTypes();
            if (check_2 == true)
            {
                cout << "\n >>>>>>>>>>>>>> Content Validation: Success" << endl;
                generateAndLogEvent(event_log_filename);
                Analysis_Engine analysis(event_log_filename, days_to_monitor, choice);
            }
            
        }
        else
        {
            cout << "Please select option to generate Training Data before generating Event Logs and Statistics for Live Data" << endl;
        }
    }
    else if(choice == 2)
    {
        // if training data option is selected
        this -> event_log_filename = "Event_Log_Training_Data.txt";
        
        // check if event types and # events in both event and stats file match
        bool check = check_EventTypes();
        if (check == true)
        {
            cout << "\n >>>>>>>>>>>>>> Content Validation: Success" << endl;
            generateAndLogEvent(event_log_filename);
            Analysis_Engine analysis(event_log_filename, days_to_monitor, choice);
        }
    }
}

void Activity_Simulation :: generateAndLogEvent(string event_log_filename)
{
    int total_event_type = (int)event_stat_vec.size();
    
    cout << "Writing File: " << event_log_filename << endl;
    
    for (int i = 0; i < total_event_type; i++)
    {
        // extract information each struct in stat vector
        string event_name = event_stat_vec[i].event_name;
        char event_val_type = event_stat_vec[i].event_val_type;
        float mean = event_stat_vec[i].mean;
        float std_dev = event_stat_vec[i].std_dev;
        
        // randomize daily total and write file
        for (int i = 0; i < days_to_monitor; i++)
        {
            // calculate total log for event in one day
            float daily_total_eventLog = calculate_DailyTotals(mean, std_dev, event_val_type, event_name);
            int day_number = i + 1;
            
            // write the logs in text file
            // format for discrete = event:day_number:
            // format for continuous = event:day_number:duration:
            write_LogFile(event_log_filename, event_val_type, daily_total_eventLog, event_name, day_number);
        }
    }
}

float Activity_Simulation :: calculate_DailyTotals(float mean, float std_dev, char type, string event_name)
{
    float range_min = 0;
    float range_max = mean + std_dev;
    
    bool value_exceed_max = true;
    float final_rand = 0.0;
    int random_int = 0.0;
    Validation v;
    
    if (type == 'C' || type == 'c')
    {
        while (value_exceed_max == true)
        {
            float random = ((float) rand()) / (float) RAND_MAX;
            float range = range_max - range_min;
            float r = random * range;
            final_rand = range_min + r;
            
            value_exceed_max = v.check_Event_Max_Value(event_type_vec, event_name, final_rand);
        }
        
        return final_rand; 
    }
    else
    {
        while (value_exceed_max == true)
        {
            int range_min_int = static_cast<int>(range_min);
            int range_max_int = static_cast<int>(range_max);
            random_int = rand() % ((range_max_int - range_min_int) + 1) + range_min_int;
            
            value_exceed_max = v.check_Event_Max_Value(event_type_vec, event_name, random_int);
        }
        
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
    
    // for each day of 1 event type
    if (event_val_type == 'D' || event_val_type == 'd')
    {
        // for discrete events
        for (int k = 0; k < daily_total_eventLog; k++)
        {
            // generate all logs for 1 day of 1 event type
            outfile
            << event_val_type
            << delimiter
            << event_name
            << delimiter
            << day_number
            << delimiter
            << endl;
        }
    }
    else
    {
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
    }
    
    
    outfile.close ();
    
}

bool Activity_Simulation::check_EventTypes()
{
    Validation v;
    bool check_Total_Event = v.check_Total_EventTypes(event_type_vec, event_stat_vec);
    if (check_Total_Event == true)
    {
        bool check_EventTypes = v.validate_events(event_type_vec, event_stat_vec);
        if (check_EventTypes == true)
            return true;
        else
        {
            cout << "\n Please check files and try again." << endl;
            return false;
            
        }
    }
    else
    {
        cout << "\n Please check files and try again." << endl;
        return false;
    }
}



