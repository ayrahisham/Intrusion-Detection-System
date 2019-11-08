
#ifndef ALERT_ENGINE
#define ALERT_ENGINE

#include "IDS.h"
#include "Initial_Input.h"
#include "Activity_Simulation.h"
#include "Analysis_Engine.h"
#include "Validation.h"

class Alert_Engine
{
public:
    Alert_Engine();
    ~Alert_Engine();
    
    void generate_anomaly_report();
    vector <Event_Anomaly_Report> generate_abnormaly_report();
    void write_AnomalyReport(string);
    
private:
    string stat_live_filename;
    vector <Event_Daily_Total> event_total_live_vec;
    vector <Event_Type> event_type_vec;
    vector <Event_Statistic> event_stat_training_vec;
    int days_to_monitor;
    vector <Event_Anomaly_Report> abnormal_report_vec;
    
    
};

#endif

