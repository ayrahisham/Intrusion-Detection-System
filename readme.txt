// NUR SUHAIRA BTE BADRUL HISHAM     5841549
// HUNG SIEW KEE                     5986606
// JANICE LIM JIA HWEI               5987040
// Assignment 3 readme.txt
// Email System Event Modeller & Intrusion Detection System


Compilation:
============
1. In CSCI262_A3_5841549_5986606_5987040/IDS:
// to generate IDS executable file
	g++ IDS.h IDS.cpp Initial_Input.h Initial_Input.cpp Activity_Simulation.h Activity_Simulation.cpp Analysis_Engine.h Analysis_Engine.cpp Alert_Engine.h Alert_Engine.cpp Validation.h Validation.cpp -o IDS
	OR simply,
	g++ *.cpp -o IDS


Before Execution:
=================
1. Make sure all the .cpp files are compiled with no error.
2. Make sure 3 pre-requisite files to be in the working directory before executing IDS
	- Events.txt
	- Stats.txt
	- Stats_Live.txt (user input statistics file)
3. In command prompt:
// ./IDS [event_type filename] [statistics filename] [days_to_monitor]
	./IDS Events.txt Stats.txt 5

	
During Execution:
=================
1. Please note that the system generated intermediate files 
from previous execution will be automatically deleted in the next execution. 
This excludes the 3 user-created pre-requisite files mentioned above. 

2. Initial Input phase:
	- Reading of events file [Events.txt]
	- Reading of statistics file [Stats.txt]
	- Displaying contents of both files (with indicated format)

3. Activity Simulation Engine phase:
	- The 2 above files are brought forward to this phase
	- Reading of the 2 above files
	- Validation of event types in both files
	- Creation of new event log file (training) [Event_Log_Training.txt]

4. Analysis Engine phase:
	- The event and new event log files are brought forward to this phase
	- Reading of the 2 above files
	- Generating of 2 new additional files:
		[Daily_Total_Training.txt] and [Stat_Training.txt]

5. Alert Engine phase:
	- The event, statistics and new event log files are 
	brought forward to this phase
	- Display of daily counters (with indicated format)
	- Creation of new anomaly report (Anomaly Report.txt)
	- Display threshold value
	- Display of anomaly check results with status (with indicated format)
	- Program prompts to analyse Live Data (Y/N): 'Y'
	- Program prompts for new stats filename: 'Stats_Live.txt'
	- Program prompts for number of days: '5'
	- Program executes Activity Simulation Engine, Analysis Engine
	and Alert Engine phase once again (updated Anomaly Report.txt created)

After Execution:
=================
6 text files will be generated:
	1. Event_Log_Training.txt
	2. Event_Log_Live.txt
	3. Daily_Total_Training.txt
	4. Stat_Training.txt
	5. Daily_Total_Live.txt
	6. Anomaly Report.txt


Execute Environment
===================
Operating system: Ubuntu/Windows
Using terminal.