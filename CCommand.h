#ifndef CCommand_H
#define CCommand_H
#include<string>

using namespace std;
const string s_DEFAULT_RUN_COMMENT = "Komenda domyœlna";

class CCommand
{
public:
	virtual void vRunCommand() = 0;
	string sGetName() { return s_description; };
	void vSetDescription(string sDescription) { s_description = sDescription; };
protected:
	string s_description;
};

#endif
