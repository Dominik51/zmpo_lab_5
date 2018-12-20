#ifndef CMenuCommand_H
#define CMenuCommand_H
#include "CMenuItem.h"
#include "CCommand.h"
using namespace std;

class CMenuCommand : public CMenuItem
{
public:
	CMenuCommand(string sName, string sCommand);
	virtual ~CMenuCommand();

	virtual void vRun();
	virtual string sGetName();
	virtual string sGetCommand();
	virtual string sGetDescription();
	void vSetDescription(string sDescription);
	void vSetCCommand(CCommand *cCommand);
	virtual void vSetRoot(CMenuItem * root) {};
private:
	CCommand *c_command = nullptr;
	string s_description = EMPTY_STRING;
};

#endif;
