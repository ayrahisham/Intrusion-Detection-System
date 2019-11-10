
#ifndef Alert_Engine_h
#define Alert_Engine_h

#include "IDS.h"
#include "Initial_Input.h"
#include "Activity_Simulation.h"
#include "Analysis_Engine.h"

class Alert_Engine
{
public:
    Alert_Engine(char, int, string);
    ~Alert_Engine();
    
    void generate_anomaly_report();
    vector <Event_Anomaly_Report> generate_abnormaly_report();
    void write_AnomalyReport(string);
    
private:
    string stat_live_filename;
    vector <Day_Total> day_total_vec;
    vector <Event_Type> event_type_vec;
    vector <Event_Statistic> event_stat_vec;
    int days_to_monitor;
    vector <Event_Anomaly_Report> abnormal_report_vec;
    
    
};


#endif /* Alert_Engine_hpp */
