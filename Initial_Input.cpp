

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
    
    cout << "Begin validation of file format ... " << endl;
    
    Validation v;
    bool check_file_format_event = v.check_file_created(event_type_filename);
    bool check_file_format_stat = v.check_file_created(stat_filename);
    
    if (check_file_format_event == true && check_file_format_stat == true)
    {
        cout << "\n >>>>>>>>>>>>>> Format Validation: Success" << endl;
        Activity_Simulation(stat_filename, days_to_monitor);
    }
    else
    {
        cout << "\n >>>>>>>>>>>>>> Please check files and try again." << endl;
    }
}


