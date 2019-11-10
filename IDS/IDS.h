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
#include <ctime>
#include <iomanip>
#include <cctype>
#include <iostream>
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
    float mean;
    float std_dev;
};

struct Event_Info
{
    string event_name;
    float total;
    char event_val_type;
};

struct Day_Total
{
    int day;
    vector <Event_Info> all_event_totals;
};

struct Event_Log
{
    string event_name;
    char event_val_type;
    float daily_total_val;
};

struct Event_Anomaly_Report
{
    int day_number;
    int abnormaly_threshold;
    int abnormaly_counter;
    bool status_normal;
};


template <class T>
int search_event_in_vec(string event_name, vector <T> events_vec)
{
    int index = 0;
    
    for (int i = 0; i < events_vec.size(); i++)
    {
        if (event_name.compare(events_vec[i].event_name) == 0)
        {
            index = i;
            break;
        }
    }
    return index;
}

// functions that can be shared across classes
vector <Event_Type> read_event_type_file(string);
vector <Event_Statistic> read_stat_file(string);
vector <Day_Total> read_event_log_file(string);

int search_event(string, vector <Event_Info>);
int search_day(int, vector <Day_Total>);

void delete_output_files(char);


#endif

