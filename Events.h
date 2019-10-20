// NUR SUHAIRA BTE BADRUL HISHAM 5841549
// HUNG SIEW KEE		 5986606
// JANICE LIM JIA HWEI		 5987040
// Assignment 3
// Email System Event Modeller & Intrusion Detection System
// Events.h
#include <iostream>
#include <string.h>
using namespace std;

const int MAX = 50;

class Events
{
	public:
		// constructor
		Events ();

		// desctructor
		~Events ();

		Events (char*, char, float, float, int);
		
		char* getEventName ();
		char getType ();
		float getMin ();
		float getMax ();
		int getWeight ();

		void setEventName (string);
		void setType (char);
		void setMin (float);
		void setMax (float);
		void setWeight (int);

	private:
		char eventName [MAX];
		char type;
		float min;
		float max;
		int weight;
	
};
