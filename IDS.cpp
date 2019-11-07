
#include "IDS.h"
#include "Initial_Input.h"


int main (int argc, char *argv[])
{
    string event_type_filename = "Events.txt";
    string stat_filename = "Stats.txt";
    string days_str = "10";
    int days = stoi (days_str);
    
    delete_output_files();
    Initial_Input(event_type_filename, stat_filename, days);
    
}

vector <Event_Type> read_event_type_file(string filename)
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
            event_type.max = 0;
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
        event_stat.event_val_type = *token;
        
        token = strtok (NULL, ":");
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

vector <Event_Daily_Total> read_event_log_file(string filename)
{
    vector <Event_Daily_Total> event_total_vec;
    
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
        Event_Daily_Total day_total_struct;
        
        char *line = &line_str[0];
        
        token = strtok(line, ":");
        day_total_struct.event_val_type = *token;
        
        token = strtok(NULL, ":");
        string event_name_read(token);
        day_total_struct.event_name = event_name_read;
        
        token = strtok(NULL, ":");
        int day_number_read = atof(token);
        
        bool found_day_total_struct = false;
        // if vector is not empty
        
        if (event_total_vec.size()!= 0)
        {
            // find struct
            int index = 0;
            found_day_total_struct = false;
            while (found_day_total_struct == false && index < event_total_vec.size())
            {
                // find the struct
                if (event_name_read.compare(event_total_vec[index].event_name) == 0)
                    found_day_total_struct = true;
                else
                    index++;
            }
            
            if (found_day_total_struct == true)
            {
                // find the day within the struct
                int index_2 = 0;
                bool found_day_total = false;
                
                while(found_day_total == false && index_2 < event_total_vec[index].total_vec.size())
                {
                    //if day found
                    if (day_number_read == event_total_vec[index].total_vec[index_2].first)
                    {
                        found_day_total = true;
                        // update value
                        event_total_vec[index].total_vec[index_2].second += 1;
                    }
                    else
                        index_2++;
                }
                
                if (found_day_total == false)
                {
                    // if day not found
                    if (event_total_vec[index].event_val_type == 'D' || event_total_vec[index].event_val_type == 'd')
                    {
                        // update dsicrete event daily count to 1
                        pair <int, float> temp;
                        temp.first = day_number_read;
                        temp.second = 1;
                        event_total_vec[index].total_vec.push_back(temp);
                    }
                    else
                    {
                        // update for events with continous value
                        token = strtok(NULL, ":");
                        float total = atof(token);
                        
                        pair <int, float> temp;
                        temp.first = day_number_read;
                        temp.second = total;
                        event_total_vec[index].total_vec.push_back(temp);
                    }
                }
            }
        }
        
        if (event_total_vec.size() == 0 || found_day_total_struct == false)
        {
            // if struct not found or vector is empty
            if (day_total_struct.event_val_type == 'D' || day_total_struct.event_val_type == 'd')
            {
                // update dsicrete event daily count to 1
                pair <int, float> temp;
                temp.first = day_number_read;
                temp.second = 1;
                day_total_struct.total_vec.push_back(temp);
            }
            else
            {
                // update for events with continous value
                token = strtok(NULL, ":");
                float total = atof(token);
                
                pair <int, float> temp;
                temp.first = day_number_read;
                temp.second = total;
                day_total_struct.total_vec.push_back(temp);
            }
            
            event_total_vec.push_back(day_total_struct);
            
        }
    }
    
    return event_total_vec;
    
}

bool find_day_total_struct(int& index, vector <Event_Daily_Total> event_total_vec, string event_name)
{
    bool find = false;
    index = 0;
    while (find == false && index < event_total_vec.size())
    {
        // find the struct
        if (event_name == event_total_vec[index].event_name)
            find = true;
        else
            index++;
    }
    
    return find;
}

bool find_day_total(Event_Daily_Total event_day_total, int day, int& index)
{
    index = 0;
    bool find = false;
    
    while(find == false && index < event_day_total.total_vec.size())
    {
        //if day found
        if (day == event_day_total.total_vec[index].first)
            find = true;
        else
            index++;
    }
    return find;
}

vector <Event_Daily_Total> read_event_daily_total_file(string filename, int days)
{
    vector <Event_Daily_Total> event_total_vec;
    
    fstream afile;
    afile.open(filename, ios::in);
    if(!afile)
    {
        cout << filename << " fail to open for reading" << endl;
        exit(-1);
    }
    
    cout << "\nReading file: " << filename << endl;
    
    char* token;
    string line_str;
    int count = 0;
    
    vector <pair<int, float>> totals;
    
    while(getline(afile, line_str))
    {
        char *line = &line_str[0];
        
        token = strtok(line, ":");
        char event_val_type_read = *token;
        
        token = strtok(NULL, ":");
        string event_name_read(token);
        
        token = strtok(NULL, ":");
        int day_number_read = atof(token);
        
        token = strtok(NULL, ":");
        float value_read = atof(token);
        
        pair <int, float> temp (day_number_read, value_read);
        
        totals.push_back(temp);
        
        count ++;
        
        if (count % days == 0)
        {
            Event_Daily_Total day_total_struct;
            day_total_struct.event_name = event_name_read;
            day_total_struct.event_val_type = event_val_type_read;
            day_total_struct.total_vec = totals;
            totals.clear();
            event_total_vec.push_back(day_total_struct);
        }
        
    }
    
    return event_total_vec;
    
}

void delete_output_files()
{
    remove("Event_Log_Training_Data.txt");
    remove("Stat_Training.txt");
    remove("Daily_Total_Training.txt");
    
    remove("Event_Log_Live_Data.txt");
    remove("Daily_Total_Live.txt");
    remove("Stats_Live_Computed.txt");
    
    remove("Abnormaly Report.txt");
}


