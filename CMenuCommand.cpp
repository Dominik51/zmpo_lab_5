#include "CMenuCommand.h"
#include<vector>
CMenuCommand::CMenuCommand(string sName, string sCommand)
{
	s_name = sName;
	s_command = sCommand;
}
CMenuCommand::~CMenuCommand()
{

}

void CMenuCommand::vSetCCommand(CCommand * cCommand)
{
	c_command = cCommand;
}

void CMenuCommand::vRun()
{
	if (c_command != 0)
	{
		c_command->vRunCommand();
	}
	else
	{
		cout << EMPTY_COMMAND << endl;
	}
}

string CMenuCommand::sGetName()
{
	return s_name;
}

string CMenuCommand::sGetCommand()
{
	return s_command;
}

string CMenuCommand::sGetDescription()
{
	if (s_description != EMPTY_STRING) return s_description;
	return c_command != nullptr ? (*c_command).sGetName() : NO_COMMAND;
}
void CMenuCommand::vSetDescription(string sDescription)
{
	s_description = sDescription;
}

