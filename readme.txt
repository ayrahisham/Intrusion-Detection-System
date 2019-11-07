
= 3 pre-requisite files to be in the working directory before executing IDS
1) Events.txt
2) Stats.txt
3) Stats_Live.txt 
	> This file consist of statistics of "Live" data of the same event types indicated in "Events.txt"
	> File name can be changed but must be consistent with user input filename @ Alert_Engine phase


= Command line to compile:
	> g++ IDS.h IDS.cpp Initial_Input.h Initial_Input.cpp Activity_Simulation.h Activity_Simulation.cpp Analysis_Engine.h Analysis_Engine.cpp Alert_Engine.h Alert_Engine.cpp Validation.h Validation.cpp -o IDS


= Command line to execute:
	> ./IDS [event_type filename] [statistics filename] [days_to_monitor]
	> Example:
		> ./IDS Events.txt Stats.txt 5


= Please note that "Training" data will have to be analysed first, before "Live" data can be generated and analysed.

= Please note that the option for generating abnormally report can only be selected if at least one set of "Live" data has been generated and analysed by the system.

= Please note that system generated intermediate files from previous execution will be automatically deleted in the next execution. This excludes the 3 user-created pre-requisite files mentioned above. These content of these files can be manually changed to design the "Training" or "Live" data for next execution.