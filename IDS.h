// NUR SUHAIRA BTE BADRUL HISHAM     5841549
// HUNG SIEW KEE                     5986606
// JANICE LIM JIA HWEI               5987040

// Assignment 3
// Email System Event Modeller & Intrusion Detection System

#ifndef IDS_main
#define IDS_main

// C++ libaries
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
#include <math.h>
#include <string.h>
using namespace std;

struct Event_Type
{
    string event_name;
    char event_val_type;
    float min;
    float max;
    int weight;
};

struct Event_Statistic
{
    string event_name;
    char event_val_type;
    float mean;
    float std_dev;
};

struct Event_Daily_Total
{
    string event_name;
    char event_val_type;
    vector <pair<int,float>> total_vec;
};

struct Event_Log
{
    string event_name;
    char event_val_type;
    float daily_total_val;
};

struct Event_Abnormaly_Report
{
    string event_name;
    int day_number;
    int abnormaly_threshold;
    int abnormaly_counter;
    bool status_normal;
};

// functions that can be shared across classes
vector <Event_Type> read_event_type_file(string);
vector <Event_Statistic> read_stat_file(string);
vector <Event_Daily_Total> read_event_log_file(string);
bool find_day_total_struct(int&, vector <Event_Daily_Total>, string);
bool find_day_total(Event_Daily_Total, int, int&);
vector <Event_Daily_Total> read_event_daily_total_file(string, int);
void delete_output_files();


#endif
