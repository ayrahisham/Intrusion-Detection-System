// NUR SUHAIRA BTE BADRUL HISHAM 5841549
// HUNG SIEW KEE		 5986606
// JANICE LIM JIA HWEI		 5987040
// Assignment 3
// Email System Event Modeller & Intrusion Detection System
// Stats.h
#include <iostream>
#include <string.h>
using namespace std;

const int LENGTH = 50;

class Stats
{
	public:
		// constructor
		Stats ();

		// desctructor
		~Stats ();

		Stats (char*, float, float);
		
		char* getEventName ();
		float getMean ();
		float getStddev ();
		float getSum ();
		float getVariance ();

		void setEventName (string);
		void setMean (float);
		void setStddev (float);
		void setSum (float);
		void setVariance (float);

	private:
		char eventName [LENGTH];
		float mean;
		float stddev;
		float sum;
		float variance;
	
};
