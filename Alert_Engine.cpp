
#include "Alert_Engine.h"

Alert_Engine::~Alert_Engine()
{
    
}

Alert_Engine::Alert_Engine()
{
    cout << "\n########## Alert Engine ##########\n" << endl;
    
    int response;
    cout << "Select the following options: "
    << "\n 1) Generate Live Data with new Statistics file"
    << "\n 2) Generate Anomaly Report with latest Live Data" << endl;
    cout << "Enter Option: ";
    cin >> response;
    cout << endl;
    
    Validation v;
    
    if (response == 1)
    {
        bool validate = v.check_file_created("Stat_Training.txt");
        if (validate == true)
        {
            cout << "Enter new statistics file name: ";
            cin >> this -> stat_live_filename;
            
            cout << "Enter number of days to be monitored: ";
            cin >> this -> days_to_monitor;
            
            Activity_Simulation AS (this -> stat_live_filename, days_to_monitor);
        }
        else
        {
            cout << "Please select option to generate training data before simulation and analysis of Live Data" << endl;
        }
    }
    else if (response == 2)
    {
        bool validate_training_file = v.check_file_created("Daily_Total_Training.txt");
        
        if (validate_training_file == true)
        {
            bool validate_live_file = v.check_file_created("Daily_Total_Live.txt");
            if (validate_live_file == true)
            {
                event_type_vec = read_event_type_file("Events.txt");
                event_stat_training_vec = read_stat_file("Stat_Training.txt");
                
                cout << endl;
                cout << "Enter number of days to be monitored: ";
                cin >> this -> days_to_monitor;
                
                event_total_live_vec = read_event_daily_total_file("Daily_Total_Live.txt", days_to_monitor);
                this -> abnormal_report_vec = generate_abnormaly_report();
                write_AnomalyReport("Anomaly Report.txt");
                
                cout << "\n >>>>>>>>>>>>>> Report has been created successfully." << endl;
                cout << " >>>>>>>>>>>>>> Please review file: \"Abnormaly Report.txt\" in the working directory." << endl;
            }
            else
            {
                cout << "Please select option to generate Live Data before generating Anomaly Report" << endl;
            }
        }
        else
        {
            cout << "Please select option to generate Training Data before simulation and analysis of Live Data" << endl;
        }
    }
}

vector <Event_Anomaly_Report> Alert_Engine::generate_abnormaly_report()
{
    // format
    // [C/D]:event_name:day#:threshold:counter:[okay/alert_detected]
    vector <Event_Anomaly_Report> abnormaly_report_vec;
    
    int total_event_type = (int)event_type_vec.size();
    
    int abnormaly_threshold =0;
    
    for (int k = 0; k < total_event_type; k++)
        abnormaly_threshold += event_type_vec[k].weight;
    
    for (int i = 0; i < total_event_type; i++)
    {
        Event_Statistic stat_training_struct = event_stat_training_vec[i];
        
        for (int j = 0; j < days_to_monitor; j++)
        {
            Event_Anomaly_Report report;
            
            string name = stat_training_struct.event_name;
            report.event_name = name;
            report.day_number = j+1;
            report.abnormaly_threshold = abnormaly_threshold;
            
            // find event_daily_total struct
            int index = 0;
            bool find_struct = find_day_total_struct(index, event_total_live_vec, name);
            
            float day_total = 0;
            if (find_struct == true)
            {
                // find specific day number from event_daily_total struct
                // extract value
                int index_2 = 0;
                Event_Daily_Total daily_total_struct = event_total_live_vec[index];
                bool find_day = find_day_total(daily_total_struct, j+1, index_2);
                if (find_day == true)
                    day_total = daily_total_struct.total_vec[index_2].second;
            }
            report.abnormaly_counter = day_total;
            report.abnormaly_counter -= stat_training_struct.mean;
            report.abnormaly_counter /= stat_training_struct.std_dev;
            
            if (report.abnormaly_counter >= report.abnormaly_threshold)
                report.status_normal = false;
            else
                report.status_normal = true;
            
            abnormaly_report_vec.push_back(report);
        }
    }
    return abnormaly_report_vec;
    
}


void Alert_Engine::write_AnomalyReport(string filename)
{
    ofstream outfile;
    
    outfile.open(filename, fstream::out);
    
    char delimiter = ':';
    
    if(!outfile)
    {
        cout << "Writing to file failed" << endl;
        exit(-1);
    }
    
    cout << "Writing File: " << filename << endl;
    
    for (int i = 0; i < abnormal_report_vec.size(); i++)
    {
        string message = "";
        if (abnormal_report_vec[i].status_normal == true)
            message = "OKAY";
        else
            message = "ALERT";
        
        outfile
        << abnormal_report_vec[i].event_name
        << delimiter
        << abnormal_report_vec[i].day_number
        << delimiter
        << abnormal_report_vec[i].abnormaly_threshold
        << delimiter
        << abnormal_report_vec[i].abnormaly_counter
        << delimiter
        << message
        << endl;
        
    }
    outfile.close();
}


