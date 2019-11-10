#include "Analysis_Engine.h"

Analysis_Engine::Analysis_Engine()
{
    
}

Analysis_Engine::~Analysis_Engine()
{
    
}


Analysis_Engine::Analysis_Engine(string event_log_filename, int days_to_monitor, char mode, string stat_filename)
{
    cout << "\n\n########## Analysis Engine ##########\n" << endl;
    
    day_total_vec = read_event_log_file(event_log_filename);
    event_type_vec = read_event_type_file("Events.txt");
    
    this -> days_to_monitor = days_to_monitor;
    this -> mode = mode;
    
    if (this -> mode == 'L')
    {
        write_DayTotal("Daily_Total_Live.txt");
        write_Statistics(stat_filename);
        cout << "\n >>>>>>>>>>>>>> Event Statistics and Daily Totals have been created for Live Data" << endl;
        Alert_Engine alert (mode, days_to_monitor, stat_filename);
    }
    else
    {
        write_DayTotal("Daily_Total_Training.txt");
        write_Statistics("Stat_Training.txt");
        cout << "\n >>>>>>>>>>>>>> Event Statistics and Daily Totals have been created for Training Data" << endl;
        Alert_Engine alert (mode, days_to_monitor, "Stat_Training.txt");
    }
    
    
    
}

void Analysis_Engine :: write_DayTotal(string fileName)
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
    
    for (int i = 0; i < day_total_vec.size(); i++)
    {
        Day_Total total_struct = day_total_vec[i];
        outfile << "Day " << total_struct.day << endl;
        
        int sum_totals = 0;
        
        for (int j = 0; j < total_struct.all_event_totals.size(); j++)
        {
            outfile
            << total_struct.all_event_totals[j].event_name
            << delimiter
            << total_struct.all_event_totals[j].total
            << delimiter
            << endl;
            sum_totals += total_struct.all_event_totals[j].total;
        }
        
        outfile << "Day Total = " << sum_totals << endl;
        outfile << endl;
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
    
    int size = (int)event_type_vec.size();
    outfile << size << endl;
    
    for (int i = 0; i < size; i++)
    {
        string event_name_calculated = event_type_vec[i].event_name;
        
        float mean = 0;
        for (int i = 0; i < days_to_monitor; i++)
        {
            int index_day = search_day(i+1, day_total_vec);
            int index_event = search_event(event_name_calculated, day_total_vec[index_day].all_event_totals);
            mean += day_total_vec[index_day].all_event_totals[index_event].total;
        }
        
        mean /= days_to_monitor;
        
        float variance = 0;
        for (int i = 0; i < days_to_monitor; i++)
        {
            int index_day = search_day(i+1, day_total_vec);
            int index_event = search_event(event_name_calculated, day_total_vec[index_day].all_event_totals);
            
            float total = day_total_vec[index_day].all_event_totals[index_event].total;
        
            float diff = total - mean;
                variance += pow(diff, 2);
        }
        
        variance /= days_to_monitor;
        
        float std_dev = sqrt(variance);
        
        outfile
        << event_name_calculated
        << delimiter
        << mean
        << delimiter
        << std_dev
        << delimiter
        << endl;
    }
    
}
