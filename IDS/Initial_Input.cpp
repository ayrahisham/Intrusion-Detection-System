
#include "Initial_Input.h"

Initial_Input::Initial_Input()
{
    
}

Initial_Input::~Initial_Input()
{
    
}

Initial_Input::Initial_Input(string event_type_filename, string stat_filename, int days)
{
    cout << "\n########## Initial Input ##########\n" << endl;
    this -> event_type_filename = event_type_filename;
    this -> stat_filename = stat_filename;
    this -> days_to_monitor = days;
    
    event_type_vec = read_event_type_file(event_type_filename);
    event_stat_vec = read_stat_file(stat_filename);
    
    char delimiter = ':';
    cout << endl;
    cout << " >>>>>>>>>>>>>> Events and Statistics read in from files" << endl;
    
    cout << "\nFormat [event_name:[C/D]:min:max:weight]\n" << endl;
    
    for (int i = 0; i < event_type_vec.size(); i++)
    {
        cout << event_type_vec[i].event_name
        << delimiter
        << event_type_vec[i].event_val_type
        << delimiter
        << event_type_vec[i].min
        << delimiter;
        if (event_type_vec[i].max > -1)
            cout << event_type_vec[i].max;
        else
            cout << "";
        cout << delimiter
        << event_type_vec[i].weight
        << delimiter
        << endl;
    }
    
    cout << "\nFormat [event_name:mean:std_dev]\n" << endl;
    
    for (int i = 0; i < event_stat_vec.size(); i++)
    {
        cout << event_stat_vec[i].event_name
        << delimiter
        << event_stat_vec[i].mean
        << delimiter
        << event_stat_vec[i].std_dev
        << delimiter
        << endl;
    }
    
    Activity_Simulation(stat_filename, days_to_monitor, 'T');
}


