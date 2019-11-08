
#include "Analysis_Engine.h"

Analysis_Engine::Analysis_Engine()
{
    
}

Analysis_Engine::~Analysis_Engine()
{
    
}

Analysis_Engine::Analysis_Engine(string event_log_filename, int days_to_monitor, int choice)
{
    cout << "\n\n########## Analysis Engine ##########\n" << endl;
    
    event_daily_total_vec = read_event_log_file(event_log_filename);
    this -> days_to_monitor = days_to_monitor;
    this -> choice = choice;
    
    Validation v;
    
    if (this -> choice == 1)
    {
        write_DailyTotal("Daily_Total_Live.txt");
        write_Statistics("Stats_Live_Computed.txt");
        cout << "\n >>>>>>>>>>>>>> Event Statistics and Logs have been created for Live Data" << endl;
    }
    else if (this -> choice == 2)
    {
        write_DailyTotal("Daily_Total_Training.txt");
        write_Statistics("Stat_Training.txt");
        cout << "\n >>>>>>>>>>>>>> Event Statistics and Logs have been created for Training Data" << endl;
    }
    
    bool continue_program = true;
    while (continue_program)
    {
        Alert_Engine();
        char response;
        cout << "\nWould you like to continue using the system? (Y/N): ";
        cin >> response;
        
        if (response == 'N' || response == 'n')
            exit(-1);
    }
}

void Analysis_Engine :: write_DailyTotal(string fileName)
{
    ofstream outfile;
    
    outfile.open(fileName, fstream::out);
    
    char delimiter = ':';
    
    if(!outfile)
    {
        cout << "Writing to file failed" << endl;
        exit(-1);
    }
    
    cout << "Writing File: " << fileName << endl;
    
    for (int i = 0; i < event_daily_total_vec.size(); i++)
    {
        Event_Daily_Total day_total = event_daily_total_vec[i];
        for (int k = 0; k < days_to_monitor; k++)
        {
            int size = (int)day_total.total_vec.size();
            bool found = false;
            int index = 0;
            
            while(index < size && found == false)
            {
                if (day_total.total_vec[index].first == k+1)
                    found = true;
                else
                    index++;
            }
            
            // generate all logs for 1 day of 1 event type
            outfile
            << day_total.event_val_type
            << delimiter
            << day_total.event_name
            << delimiter
            << k+1
            << delimiter
            << day_total.total_vec[index].second
            << delimiter
            << endl;
        }
    }
    outfile.close();
}


void Analysis_Engine::write_Statistics(string filename)
{
    fstream outfile;
    outfile.open(filename, fstream::out);
    char delimiter = ':';
    
    if (!outfile)
    {
        cout << "Writing to file failed" << endl;
        exit (-1);
    }
    
    cout << "Writing File: " << filename << endl;
    
    int totalNum_event_type = (int)event_daily_total_vec.size();
    outfile << totalNum_event_type << endl;
    
    for (int i = 0; i < totalNum_event_type; i++)
    {
        Event_Daily_Total temp = event_daily_total_vec[i];
        
        string name = temp.event_name;
        
        float mean = 0;
        for (int i = 0; i < days_to_monitor; i++)
        {
            // find value of the day
            int index = 0;
            bool found = find_day_total(temp, i, index);
            
            if (found)
            {
                float day_value = temp.total_vec[index].second;
                mean += day_value;
            }
        }
        
        mean /= days_to_monitor;
        
        float variance = 0;
        for (int i = 0; i < days_to_monitor; i++)
        {
            int index = 0;
            bool found = find_day_total(temp, i, index);
            
            if (found)
            {
                float day_value = temp.total_vec[index].second;
                float diff = day_value - mean;
                variance += pow(diff, 2);
            }
        }
        
        variance /= days_to_monitor;
        
        float std_dev = sqrt(variance);
        
        outfile
        << name
        << delimiter
        << mean
        << delimiter
        << std_dev
        << delimiter
        << endl;
    }
    
}


