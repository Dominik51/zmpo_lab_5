#include "CMenu.h"

CMenu::CMenu(string sName, string sCommand)
{
	s_name = sName;
	s_command = sCommand;
	s_path = sName;
}

CMenu::~CMenu()
{

}

void CMenu::vRun()
{
	string s_user_command;
	while (s_user_command != BACK_COMMAND)
	{
		cout << LINE << endl;
		cout << s_name << POINTS << endl;
		for (int i = 0; i < c_menu_items.size(); i++)
		{
			cout << (*c_menu_items.at(i)).sGetName() << SPACE << OPENING_ROUND_BRACKET << (*c_menu_items.at(i)).sGetCommand() << CLOSING_ROUND_BRACKET << endl;
		}
		cout << LINE << endl;
		cout << INSERT_COMMAND << endl;
			
		getline(cin, s_user_command);
		if (s_user_command == BACK_COMMAND) return;
		else
		{
			bool b_operation_found = false;
			for (int i = 0; i < c_menu_items.size() && (!b_operation_found); i++)
			{
				if ((*c_menu_items.at(i)).sGetCommand() == s_user_command)
				{
					b_operation_found = true;
					(*c_menu_items.at(i)).vRun();
				}
			}
			if ((!b_operation_found) && s_user_command != BACK_COMMAND)
			{
				cout << COMMAND_NOT_FOUND << endl;
			}
			cin.clear();
		}
	}
}

string CMenu::sGetName()
{
	return s_name;
}

string CMenu::sGetCommand()
{
	return s_command;
}

void CMenu::vAddCMenuItem(CMenuItem *cMenuItem)
{
	bool b_item_exist = false;
	for (int i = 0; i < c_menu_items.size() && b_item_exist == false; i++)
	{
		if (cMenuItem->sGetName() == c_menu_items.at(i)->sGetName() || cMenuItem->sGetCommand() == c_menu_items.at(i)->sGetCommand())
		{
			b_item_exist = true;
			cout << ITEM_ALREADY_EXIST << endl;
		}
	}
	if (!b_item_exist)
	{
		(*cMenuItem).vSetRoot(c_root == nullptr ? this : c_root);
		(*cMenuItem).vSetPath(sGetPath() + ARROW + (*cMenuItem).sGetName());
		c_menu_items.push_back(cMenuItem);
	}
}

CMenuItem *CMenu::cGetCMenuItem(string sName)
{
	for (int i = 0; i < c_menu_items.size(); i++)
	{
		if (sName == c_menu_items.at(i)->sGetName())
		{
			return c_menu_items.at(i);
		}
	}
}

void CMenu::vRemoveCMenuItem(string sCommand)
{
	for (int i = 0; i < c_menu_items.size(); i++)
	{
		if (sCommand == c_menu_items.at(i)->sGetCommand())
		{
			delete c_menu_items.at(i);

			c_menu_items.erase(c_menu_items.begin() + i);
			cout << ITEM_REMOVED << endl;
			return;
		}
	}
	cout << ITEM_NOT_REMOVED << endl;
}

vector<CMenuItem*> CMenu::cGetCMenuItems()
{
	return vector<CMenuItem*>();
}

vector<CCommand*> CMenu::cGetCMenuCommands()
{
	return c_menu_commands;
}

void CMenu::vSetCMenuCommands(vector<CCommand*> cMenuCommands)
{
	c_menu_commands = cMenuCommands;
}

CMenu * CMenu::cGetRoot()
{
	return c_root;
}

void CMenu::vSetRoot(CMenuItem * root)
{
	c_root = static_cast<CMenu*>(root); 
}
