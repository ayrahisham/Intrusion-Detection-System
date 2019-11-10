// NUR SUHAIRA BTE BADRUL HISHAM     5841549
// HUNG SIEW KEE                     5986606
// JANICE LIM JIA HWEI               5987040

// Assignment 3
// Email System Event Modeller & Intrusion Detection System

#include "IDS.h"
#include "Initial_Input.h"

int main(int argc, const char * argv[])
{
    string event_type_filename = argv[1];
    string stat_filename = argv[2];
    string days_str = argv[3];
    int days;
    
    try
    {
        days = stoi (days_str);
    }
    catch(exception e)
    {
        cout << "Invalid days enter at the third argument. Please try again." << endl;
        exit(-1);
    }
    
    Validation v;
    bool check = v.check_initial_arguments(event_type_filename, stat_filename);
    if (check)
        Initial_Input(event_type_filename, stat_filename, days);

}

vector <Event_Type> read_event_type_file(string filename)
{
    fstream afile;
    afile.open(filename, ios::in);
    if (!afile)
    {
        cout << "Invalid filename. Failed to open for reading."<< endl;
        exit (-1);
    }
    
    cout << "Reading file: " << filename << endl;
    int size = 0;
    afile >> size;
    
    afile.clear ();
    afile.ignore(10, '\n');
    
    char* token;
    string line_str;
    vector <Event_Type> event_type_vec;
    
    while (getline(afile, line_str))
    {
        Event_Type event_type;
        
        char* line = &line_str[0];
        
        token = strtok (line, ":");
        string s(token);
        event_type.event_name = s;
        
        token = strtok (NULL, ":");
        event_type.event_val_type = *token;
        
        token = strtok (NULL, ":");
        event_type.min = atof (token);
        
        // might be max value or weight
        char* max_str = strtok (NULL, ":");
        char* weight_str = strtok (NULL, ":");
        
        if (weight_str == NULL)
        {
            event_type.weight = atof(max_str);
            event_type.max = -1;
        }
        else
        {
            event_type.max = atof(max_str);
            event_type.weight = atof(weight_str);
        }
        
        event_type_vec.push_back(event_type);
        
        afile.clear ();
    }
    
    afile.close();
    return event_type_vec;
}

vector <Event_Statistic> read_stat_file(string filename)
{
    fstream afile;
    afile.open(filename, ios::in);
    if (!afile)
    {
        cout << filename << " failed to open for reading" << endl;
        exit (-1);
    }
    
    cout << "Reading file: " << filename << endl;
    int size = 0;
    afile >> size;
    
    afile.clear ();
    afile.ignore(10, '\n');
    
    vector <Event_Statistic> event_stat_vec;
    char* token;
    string line_str;
    while (getline(afile, line_str))
    {
        Event_Statistic event_stat;
        
        char* line = &line_str[0];
        
        token = strtok (line, ":");
        string s(token);
        event_stat.event_name = s;
        
        token = strtok (NULL, ":");
        event_stat.mean = atof (token);
        
        char *stand_dev_str = strtok (NULL, ":");
        event_stat.std_dev = atof (stand_dev_str);
        
        event_stat_vec.push_back(event_stat);
        
        afile.clear ();
    }
    
    afile.close ();
    return event_stat_vec;
}


vector <Day_Total> read_event_log_file(string filename)
{
    vector <Day_Total> day_total_vec;
    
    fstream afile;
    afile.open(filename, ios::in);
    if(!afile)
    {
        cout << filename << " fail to open for reading" << endl;
        exit(-1);
    }
    
    cout << "Reading file: " << filename << endl;
    
    char* token;
    string line_str;
    
    while(getline(afile, line_str))
    {
        Day_Total total_struct;
        Event_Info info_struct;
        
        char *line = &line_str[0];
        
        token = strtok(line, ":");
        info_struct.event_val_type = *token;
        
        token = strtok(NULL, ":");
        string event_name_read(token);
        info_struct.event_name = event_name_read;
        
        token = strtok(NULL, ":");
        int day_number_read = atof(token);
        
        token = strtok(NULL, ":");
        info_struct.total = atof(token);
        
        if (day_total_vec.size() == 0)
        {
            total_struct.day = day_number_read;
            total_struct.all_event_totals.push_back(info_struct);
            day_total_vec.push_back(total_struct);
        }
        else
        {
            int index = search_day(day_number_read, day_total_vec);
            
            if (index == -1)
            {
                total_struct.day = day_number_read;
                total_struct.all_event_totals.push_back(info_struct);
                day_total_vec.push_back(total_struct);
            }
            else
                day_total_vec[index].all_event_totals.push_back(info_struct);
        }
    }
    
    return day_total_vec;

}

int search_event(string event_name, vector <Event_Info> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].event_name.compare(event_name) == 0)
            return i;
    }
    
    return -1;
}

int search_day(int day, vector <Day_Total> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].day == day)
            return i;
    }
    
    return -1;
}


void delete_output_files(char mode)
{
    if (mode == 'T')
    {
        remove ("Event_Log_Training.txt");
        remove ("Daily_Total_Training.txt");
        remove ("Stats_Training.txt");
        remove ("Anomaly_Report.txt");
    }
    else
    {
        remove ("Event_Log_Live.txt");
        remove ("Daily_Total_Live.txt");
        remove ("Stats_Computed.txt");
        remove ("Anomaly_Report.txt");
    }
    
}


