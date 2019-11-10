
#include "Alert_Engine.h"
Alert_Engine::~Alert_Engine()
{
    
}

Alert_Engine::Alert_Engine(char mode, int days_to_monitor, string stat_filename)
{
    char response;
    
    do
    {
        cout << "\n########## Alert Engine ##########\n" << endl;
        
        this -> days_to_monitor = days_to_monitor;
        event_type_vec = read_event_type_file("Events.txt");
        
        
        if (mode == 'T')
        {
            day_total_vec = read_event_log_file("Event_Log_Training.txt");
            event_stat_vec = read_stat_file(stat_filename);
        }
        else
        {
            day_total_vec = read_event_log_file("Event_Log_Live.txt");
            event_stat_vec = read_stat_file(stat_filename);
        }
        
        this -> abnormal_report_vec = generate_abnormaly_report();
        write_AnomalyReport("Anomaly Report.txt");
        
        cout << "\n >>>>>>>>>>>>>> Report has been created successfully." << endl;
        cout << " >>>>>>>>>>>>>> Please review file: \"Anomaly Report.txt\" in the working directory." << endl;
        
        cout << "\n Would you like to analyse \"Live\" data? (Y / N): ";
        cin >> response;
        
        if (response == 'Y' || response == 'y')
        {
            string stat_filename;
            int days;
            
            cout << "Enter new statistic file name: ";
            cin >> stat_filename;
            
            cout << "Enter number of days: ";
            cin >> days;
            
            Activity_Simulation(stat_filename, days, 'L');
        }
        else
        {
            cout << "\n >>>>>>>>>>>>>>Program terminates" << endl;
            exit(0);
        }
        
    }while(response == 'Y' || response == 'y');
    
    
}

vector <Event_Anomaly_Report> Alert_Engine::generate_abnormaly_report()
{
    // format
    // [C/D]:event_name:day#:threshold:counter:[okay/alert_detected]
    vector <Event_Anomaly_Report> abnormaly_report_vec;
    
    int total_event_type = (int)event_type_vec.size();
    
    int abnormaly_threshold = 0;
    
    for (int k = 0; k < total_event_type; k++)
        abnormaly_threshold += event_type_vec[k].weight;
    
    cout << "\n\n=====================" << endl;
    cout << "Daily Counters" << endl;
    cout << "=====================" << endl;
    cout << "\nFormat [event_name:counter:]" << endl;
    
    for (int i = 0; i < days_to_monitor; i++)
    {
        Event_Anomaly_Report report;
        report.abnormaly_counter = 0;
        report.day_number = i+1;
        report.abnormaly_threshold = abnormaly_threshold;
        
        cout << endl;
        cout << "Day " << i+1 << endl;
        
        for (int j = 0; j < event_stat_vec.size(); j++)
        {
            Event_Statistic stat_struct = event_stat_vec[j];
            
            string name = stat_struct.event_name;
            
            // search for weight of this event
            int index_event_type = search_event_in_vec(name, event_type_vec);
            int weight = event_type_vec[index_event_type].weight;
            
            // find total of the event of a particular day
            int index_day = search_day(i+1, day_total_vec);
            int index_event = search_event(name, day_total_vec[index_day].all_event_totals);
            float total = day_total_vec[index_day].all_event_totals[index_event].total;
            
            float counter = (abs(stat_struct.mean - total))/stat_struct.std_dev;
            counter *= weight;
            
            cout << setprecision(2);
            cout << name << ":" << counter << ":" << endl;
            report.abnormaly_counter += counter;
        }
        
        if (report.abnormaly_counter >= report.abnormaly_threshold)
            report.status_normal = false;
        else
            report.status_normal = true;
        
        abnormaly_report_vec.push_back(report);
    }
    
    return abnormaly_report_vec;
    
}

void Alert_Engine::write_AnomalyReport(string filename)
{
    ofstream outfile;
    
    outfile.open(filename, fstream::out);
    
    if(!outfile)
    {
        cout << "Writing to file failed" << endl;
        exit(-1);
    }
 
    cout << "\n\n=====================" << endl;
    cout << "Anomaly Check Result" << endl;
    cout << "=====================" << endl;
    
    cout << "\nWriting File: " << filename << endl;
    
    cout << "\nFormat [day_number:counter:check_status]" << endl;
    
    for (int i = 0; i < abnormal_report_vec.size(); i++)
    {
        string message = "";
        if (abnormal_report_vec[i].status_normal == true)
            message = "OKAY";
        else
            message = "ALERT";
        
        if (i == 0)
            cout << "\nThreshold : " << abnormal_report_vec[i].abnormaly_threshold << "\n" << endl;
        
        cout << setprecision(2);
        cout << "Day " << abnormal_report_vec[i].day_number << ":"
        << abnormal_report_vec[i].abnormaly_counter << ":"
        << message << endl;
        
        outfile << "Day " << abnormal_report_vec[i].day_number << endl;
        outfile << "Counter: " << abnormal_report_vec[i].abnormaly_counter << endl;
        outfile << "Check Status: " << message << "\n" << endl;
  
    }
    outfile.close();
}
