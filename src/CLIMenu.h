#ifndef _CLEMENU_H_
#define _CLEMENU_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

//TODO: once primitively working, go back and add exception throwing 

/*TODO: extend for program commands as well as options, possibly
making connections between commandand the available
options for that specific commands */

class CLIMenu {
	/* This class represents the program's command line interface menu, 
	with all the options available to the user. 
	
	TODO: pretty much everything in this class 
	
	*/
private:

	vector<MenuOption> options; // holds all valid options for the menu instance

	// creates the help option which should always be present 
	void addHelp(void);
		
	
public:
	
	CLIMenu(void);

	void addOption(const MenuOption & opt);

};

class MenuOption {
	/* Represents a single option and acts as base class for options 
	which accept arguments. Use this class for options that take no arguments.*/

private:
	char shortName; // single char name of option, e.g. 'h' for help
	string longName; // full name of option, e.g 'help'
	string desc; // description of option as shown when help option is used

	vector<string> alts; // alternatives of string values that option accepts
	
	bool optional; // false if the option is mandatory


public:
	MenuOption(char sn = 0, string ln = "", string dsc = "", bool opt = true) :
		shortName(sn), longName(ln), desc(dsc), optional(opt) {};

	// getters/setters
	bool isOptional() { return optional; };
	string getDesc() { return desc; };
	char getSn() { return shortName; };
	string getLn() { return longName; };

	// returns information string about the command as showed by the help command 
	string getInfoStr();


};

template <class Numeric>
class NumMenuOption : public MenuOption {
	/* Represents a menu option that accepts a numeric argument.
	Has a range of acceptable values.*/

private:
	Numeric val; // value of numeric argument given to option 
	Numeric min, max; // limits of acceptable value range for argument

public: 
	NumMenuOption(char sn = 0, string ln = "", string dsc = "", bool opt = true, 
		Numeric mini = 0, Numeric maxi = std::numeric_limits<Numeric>::max()) : 
		MenuOption(sn, ln, dsc, opt), val(0), min(mini), max(maxi) {};

	// getters/setters
	void setRange(const Numeric &mini, const Numeric &maxi);
	void getRange(Numeric &mini, Numeric &maxi);
	void setVal(const Numeric value) { val = value; };
	Numeric getVal() { return val; };

	// is given value within the set range?
	bool validRange(const Numeric value);

};


class StrMenuOption : public MenuOption {
private:
	string val; // value of string argument given to option
	vector<string> choices; // acceptable string values 

public:
	StrMenuOption(char sn = 0, const string &ln = "", const string &dsc = "", 
		bool opt = true, const vector<string> &cho) :
		MenuOption(sn, ln, dsc, opt), val(""), choices(cho) {};

	// getters/setters
	void setVal(const string& value);
	string getVal() const; // TODO: Add const to all getters
	void addChoice(const string& newChoice);

};


#endif