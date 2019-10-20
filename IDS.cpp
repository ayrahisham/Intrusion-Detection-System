// NUR SUHAIRA BTE BADRUL HISHAM 5841549
// HUNG SIEW KEE		 5986606
// JANICE LIM JIA HWEI		 5987040
// Assignment 3
// Email System Event Modeller & Intrusion Detection System
// A3_IDS.cpp
#include "Stats.h"
#include "Events.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <iomanip>
using namespace std;

int getFilesize (fstream&, string);
void infileToVector (fstream&, string, Stats s []);
void generateEvents (Stats [], Events [], int);
float randomFloat (float, float);
int randomInt (int, int);
void outfileToFile (Events [], ofstream&, int, string);
void generateLog (vector <char*>, vector <char> vType,
	vector <float> vMin, vector <float> vMax, vector <int>, 		
	ofstream&, int, int, string);
void analyzeEngine (fstream&, Stats [], int, int, string);
float getMean (float, int);
void getSD (fstream&, Stats[], int, int, string);

int main (int argc, char *argv[])
{
	// You only need command line options at the setup phase
	string eventfile = argv [1];
	string statfile = argv [2];
	string strdays = argv [3];
	int days = stoi (strdays);
	char filename [LENGTH];

	cout << "\033[H\033[2J";
	cout << "Email System Event Modeller & Intrusion Detection System" << endl;
	cout << "========================================================\n" << endl;
	fstream afile;
	ofstream outfile;

	cout << "Initial Input" << endl;
	cout << "-------------\n" << endl;
	int size = getFilesize (afile, statfile);
	cout << "\tThere are " << size << " events in " << statfile << "\n" << endl;

	Stats s [size];
	infileToVector (afile, statfile, s);

	Events e [size];
	generateEvents (s, e, size);	
	outfileToFile (e, outfile, size, eventfile);

	cout << "////////////////////////////////////////////////////////\n" << endl;

	// Once the intial setup has taken place, 
	// and you have read in the base files, 
	// the activity engine should start generating and logging events.
	// Your program should give some indication as to what is happening, without being verbose.
	cout << "Activity Simulation Engine and the Logs" << endl;
	cout << "---------------------------------------\n" << endl;

	// // You should log for the number of Days specified at the initial running of IDS.
	cout << "Number of Days to log: " << days << endl; 

	vector <char*> vEventname;
	vector <char> vType;
	vector <float> vMin;
	vector <float> vMax;
	vector <int> vWeight;

	cout << "Fetching events for:" << endl;
	for (int i = 0; i < days; i++)
	{
		// You are attempting to produce statistics approximately consistent with the statistics specified in the file Stats.txt. 
		cout << " Day: " << i+1 << endl;
		generateEvents (s, e, size);
		
		for (int j = 0; j < size; j++)
		{
			vEventname.push_back (e[j].getEventName ());
			vType.push_back (e[j].getType ());
			vMin.push_back (e[j].getMin ());
			vMax.push_back (e[j].getMax ());
			vWeight.push_back (e[j].getWeight ());	
		}	
	}

	cout << endl;

	// You can, if you like, store the events in distinct files for each day, or in a single log file. 
	// This collection of events forms the baseline data for the system.
	generateLog (vEventname, vType, vMin, vMax, vWeight, outfile, days, size, "log.txt");
	cout << "Event generation completed...\n" << endl;

	cout << "////////////////////////////////////////////////////////\n" << endl;

	cout << "Analysis Engine" << endl;
	cout << "---------------\n" << endl;
	
	// Your program should indicate it has completed event generation and is going to begin analyis. 
	cout << "Begin analysis..." << endl;

	// You can now measure that baseline data for the events 
	// and determine the statistics associated with the baseline.
	Stats live [size];	
	analyzeEngine (afile, live, days, size, "log.txt");

	// Report what is happening as you consider appropriate.
	// Even if you are unable to produce data consistent with a given distribution 
	// you can still have the analysis engine reading and reporting on the log file.
	cout << "Baseline vs Statistics Data for " << days << " days:" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "\tEvent: " << live[i].getEventName () << endl;
		cout << "\t\tBase Mean: " << fixed << showpoint << setprecision (2) 
		     << live[i].getMean () << " | Stat Mean: " << s[i].getMean () << endl;
		cout << "\t\tBase Std. Dev: " << fixed << showpoint << setprecision (2) 
		     << live[i].getStddev () << " | Stat Std. Dev: " << s[i].getStddev () << endl;
	}

	cout << endl;
	cout << "////////////////////////////////////////////////////////\n" << endl;

	cout << "Alert Engine" << endl;
	cout << "------------\n" << endl;

	// The alert engine is used to check consistency between live data and the base line statistics. 
	// Once this phase is reached you should prompt the user for a file, containing new statistics, and a number of days.
	// The new statistics file has the same format as Stats.txt from earlier 
	// but will generally have different parameters for the events. 
	cout << "Enter a statistics filename: ";
	cin.getline (filename, LENGTH);

	cout << "Enter a number of days: ";
	cin >> days;

	// You should run your activity engine and produce data for the number of days specified. 
	// Use the analysis engine to produce daily totals, those are used in alert detection.
	size = getFilesize (afile, statfile);
	cout << "\tThere are " << size << " events in " << filename << "\n" << endl;

	Stats sX [size];
	infileToVector (afile, filename, sX);

	cout << "Number of Days to log: " << days << endl; 

	vEventname.clear ();
	vType.clear ();
	vMin.clear ();
	vMax.clear ();
	vWeight.clear ();	
	cout << "Fetching events for:" << endl;
	for (int i = 0; i < days; i++)
	{
		cout << " Day: " << i+1 << endl;
		generateEvents (sX, e, size);
		
		for (int j = 0; j < size; j++)
		{
			vEventname.push_back (e[j].getEventName ());
			vType.push_back (e[j].getType ());
			vMin.push_back (e[j].getMin ());
			vMax.push_back (e[j].getMax ());
			vWeight.push_back (e[j].getWeight ());	
		}	
	}

	cout << endl;

	generateLog (vEventname, vType, vMin, vMax, vWeight, outfile, days, size, "alertLog.txt");

	cout << "Event generation completed...\n" << endl;

	// For each day generated you need to report on whether the there is an intrusion 
	// detected by comparing an anomaly counter with a threshold. 
	// You calcualte the anomaly counter by adding up the weighted number of standard deviations 
	// each specific tested event value is from the mean for that event, where
	// the standard deviation and mean are those you have generated from the base data and reported, 
	// and the weight is taken from the original Events.txt file.
	// For example, if the mean number of logins per day is 4 and the standard deviation is 1.5; 
	// then if we get 1 login in a day we are 2 standard deviations from the mean. 
	// Referrring back to the weight of the login event we see it was 2 
	// so the login event contributes 4 to our overall anomaly counter.
	// The threshold for detecting an intrusion is 2*(Sums of weights) where the weights are taken from
	// Events.txt. If the anomaly counter is greater or equal to the threshold you should report this as an
	// anomaly.
	// You should output the threshold, and give the anomaly counter for each day as well as stating each
	// day as okay or flagged as having an alert detected.
	// Once the alert engine part has finished you should return to the start of this phase, so another set of
	// statistics and number of days can be considered. An option to quit should be provided.
}

int getFilesize (fstream& afile, string filename)
{
	afile.open (filename, ios::in);
	if (!afile)
	{
		cout << filename << "opened for reading failed" << endl;
		exit (-1);
	}
	
	cout << "Reading the number of events in file..." << endl;
	int i = 0;
	afile >> i;
	
	afile.close ();

	return i;
}

void infileToVector (fstream& afile, string filename, Stats s [])
{
	afile.open (filename, ios::in);
	if (!afile)
	{
		cout << filename << " opened for reading failed" << endl;
		exit (-1);
	}

	cout << "Begin reading events in file..." << endl;
	int size = 0;
	afile >> size;

	int i = 0;
	char delimiter = ':';
	char event [LENGTH];
	float value = 0.0;
	char* token;

	afile.clear ();
	afile.ignore (LENGTH, '\n');
	while (afile.getline (event, delimiter))
	{		
		// Each subsequent line is of the form:
		// Event name:mean:standard deviation:
		char* token = strtok (event, ":");		
		s[i].setEventName (token);
		token = strtok (NULL, ":");
		value = atof (token);		
		s[i].setMean (value);
		token = strtok (NULL, ":");
		value = atof (token);
		s[i].setStddev (value);
		afile.clear ();
		++i;
	}

	afile.close ();
	cout << "\tCompleted reading events successfully\n" << endl;
}

void generateEvents (Stats s [], Events e [], int size)
{
	for (int i = 0; i < size; i++)
	{
		e[i].setEventName (s[i].getEventName ());
		e[i].setType ('C');
		e[i].setMin (0);
		float statMean = s[i].getMean ();
		float statStddev = s[i].getStddev ();
		float min = statMean - statStddev;
		float max = statMean + statStddev;
		e[i].setMax (randomFloat (min, max));	
		e[i].setWeight (randomInt (1, 10));
	}
}

float randomFloat (float min, float max)
{
	srand (time (NULL));
	return ((float) rand() / RAND_MAX) * (max-min) + min;
}

int randomInt (int min, int max)
{
	srand (time (NULL));
	return ((rand () % max) + min);
}

void outfileToFile (Events e [], ofstream& outfile, int size, string filename)
{
	outfile.open (filename);
	char delimiter = ':';

	if (!outfile)
	{
		cout << "Writing to file failed" << endl;
		exit (-1);
	}

	cout << "Begin writing events to file..." << endl;
	outfile << size << endl;

	for (int i = 0; i < size; i++)
	{
		outfile << e[i].getEventName ()
			<< delimiter
			<< e[i].getType ()
			<< delimiter
			<< e[i].getMin ()
			<< delimiter
			<< e[i].getMax ()
			<< delimiter
			<< endl;
	}

	outfile.close ();
	cout << "\tCompleted writing events successfully\n" << endl;
}

void generateLog (vector <char*> vEventname, vector <char> vType,
vector <float> vMin, vector <float> vMax, vector <int> vWeight, ofstream& outfile, int days, int size, string filename)
{
	outfile.open (filename);
	char delimiter = ':';

	if (!outfile)
	{
		cout << "Writing to log failed" << endl;
		exit (-1);
	}

	cout << "Begin writing events to log..." << endl;
	int day = 1;
	int start = 1;
	for (int x = 0; x < vEventname.size (); x++)
	{
		if (x % size == 0)
		{		
			cout << "\t->Log Day " << day << endl;
			outfile << day << delimiter << endl;
			++day;
		}	
	
		outfile << vEventname[x]
			<< delimiter
			<< vType[x]
			<< delimiter
			<< vMin[x]
			<< delimiter
			<< vMax[x]
			<< delimiter
			<< vWeight[x]
			<< delimiter
			<< endl;
		
	}

	outfile.close ();
	cout << "\tCompleted writing log successfully\n" << endl;
}

void analyzeEngine (fstream& afile, Stats live [], int days, int size, string filename)
{
	afile.open (filename, ios::in);
	if (!afile)
	{
		cout << filename << " opened for reading failed" << endl;
		exit (-1);
	}

	for (int i = 0; i < size; i++)
	{
		live[i].setEventName ("");
	}

	cout << "Determine mean and standard deviation of events of " << days << " days..." << endl;
	char delimiter = ':';
	char event [LENGTH];
	float valueF = 0.0;
	int valueInt = 0;
	char* token;	
	int day;
	int eventId = 0;
	char* eventname;
	// remove day 1 log title
	afile.getline (event, delimiter);
	afile.clear ();
	float sum = 0.0;

	// Produce totals for each event for each day, store that in a data file, 
	// and determine the mean and standard deviation associated with that event across that data. 
	for (int i = 0; i < days; i++)
	{
		cout << "\tFetching statistics for Day: " << i+1 << endl;
		
		while (afile.getline (event, delimiter))
		{	
			char* token = strtok (event, ":");
			if (isdigit (*token))
			{
				break;
			}
		
			eventname = token;
			if (eventId < size)
			{
				live[eventId].setEventName (token); // name
				++eventId;
			}

			token = strtok (NULL, ":"); // type
			token = strtok (NULL, ":"); // min
			//valueF = atof (token);	
			token = strtok (NULL, ":"); // max
			valueF = atof (token);
			
			for (int j = 0; j < size; j++)
			{
				if (strcmp (live[j].getEventName (), eventname) == 0)
				{
					sum = live[j].getSum (); // get the current sum first
					sum += valueF;		// increment the sum			
					live[j].setSum (sum);
				}
			}

			token = strtok (NULL, ":"); // weight
			//valueInt = atoi (token);
			afile.clear ();	
		}
	}
	
	afile.close ();

	for (int i = 0; i < size; i++)
	{
		live[i].setMean (getMean (live[i].getSum (), days));
	}

	getSD (afile, live, days, size, filename);
	
	cout << "\tCompleted statistics computation successfully\n" << endl;
}

float getMean (float sum, int days)
{
	return (sum / days);

}

void getSD (fstream& afile, Stats live [], int days, int size, string filename)
{
	afile.open (filename, ios::in);
	if (!afile)
	{
		cout << filename << " opened for reading failed" << endl;
		exit (-1);
	}

	char delimiter = ':';
	char event [LENGTH];
	float valueF = 0.0;
	int valueInt = 0;
	char* token;	
	int day;
	int eventId = 0;
	char* eventname;
	// remove day 1 log title
	afile.getline (event, delimiter);
	afile.clear ();
	float variance = 0.0;

	for (int i = 0; i < days; i++)
	{	
		while (afile.getline (event, delimiter))
		{	
			char* token = strtok (event, ":"); // name
			if (isdigit (*token))
			{
				break;
			}
			eventname = token; 

			token = strtok (NULL, ":"); // type
			token = strtok (NULL, ":"); // min
			token = strtok (NULL, ":"); // max
			valueF = atof (token);

			for (int j = 0; j < size; j++)
			{
				if (strcmp (live[j].getEventName (), eventname) == 0)
				{
					variance = pow (live[j].getMean()-valueF, 2); // get the current variance first 
					variance += live[j].getVariance (); // increment the variance
					live[j].setVariance (variance);
				}
			}

			token = strtok (NULL, ":"); // weight
			afile.clear ();	
		}
	}

	afile.close ();	
	
	for (int i = 0; i < size; i++)
	{	
		live [i].setVariance (live[i].getVariance () / days);
		live [i].setStddev (sqrt (live[i].getVariance ()));
	}
}

