#ifndef CMenu_H
#define CMenu_H
#include "CMenuItem.h"
#include "CCommand.h"
#include "CMenuCommand.h"

using namespace std;

class CMenu : public CMenuItem
{
public:
	CMenu(string sName, string sCommand);
	virtual ~CMenu();

	virtual void vRun();
	virtual string sGetName();
	virtual string sGetCommand();
	void vAddCMenuItem(CMenuItem *cMenuItem);
	CMenuItem *cGetCMenuItem(string sName);
	void vRemoveCMenuItem(string sName);
	vector<CMenuItem*> cGetCMenuItems();
	vector<CCommand*> cGetCMenuCommands();
	void vSetCMenuCommands(vector<CCommand*> cMenuCommands);

	CMenu *cGetRoot();
	virtual void vSetRoot(CMenuItem * root);

private:
	vector<CMenuItem*> c_menu_items;
	vector<CCommand*> c_menu_commands;
	CMenu *c_root;
};

#endif
