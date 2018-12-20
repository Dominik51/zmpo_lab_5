#pragma once
#include "CCommand.h"
#include "CGeneticAlgorithm.h"

class CSimulationSettings
{
public:
	CSimulationSettings();
	void vSetPopulationSize(int i_population_size);
	void vSetCrossoverChance(double d_crossover_chance);
	void vSetMutationChance(double d_mutation_chance);
	void vSetTimeForSim(double d_time_for_sim);
	void vSetProblemType(string s_problem_type);
	void vSetKnapsackCapacity(double d_knapsack_capacity);

	int iGetPopulationSize();
	double dGetCrossoverChance();
	double dGetMutationChance();
	double dGetTimerForSim();
	string sGetProblemType();
	double dGetKnapsackCapacity();

private:
	int iPopulationSize;
	double dCrossoverChance;
	double dMutationChance;
	double dTimeForSim;
	string sProblemType;
	double dKnapsackCapacity;
};


class CShowSimulationSettings : public CCommand
{
public:
	CShowSimulationSettings(CSimulationSettings *c_simulation_settings);
	virtual void vRunCommand();

private:
	CSimulationSettings *cSimulationSettings;
};

class CStartSimulation : public CCommand
{
public:
	CStartSimulation(CSimulationSettings *c_simulation_settings);
	virtual void vRunCommand();

private:
	CSimulationSettings * cSimulationSettings;
};

class CSetProblemType : public CCommand
{	
public:
	CSetProblemType(CSimulationSettings *c_simulation_settings);
	virtual void vRunCommand();
private:
	CSimulationSettings * cSimulationSettings;
};

class CSetKnapsackCapacity : public CCommand
{
public:
	CSetKnapsackCapacity(CSimulationSettings *c_simulation_settings);
	virtual void vRunCommand();
private:
	CSimulationSettings * cSimulationSettings;
};

class CSetPopulation : public CCommand
{
public:
	CSetPopulation(CSimulationSettings *c_simulation_settings);
	virtual void vRunCommand();
private:
	CSimulationSettings * cSimulationSettings;
};

class CSetMutationProb : public CCommand
{
public:
	CSetMutationProb(CSimulationSettings *c_simulation_settings);
	virtual void vRunCommand();
private:
	CSimulationSettings * cSimulationSettings;
};

class CSetCrossProb : public CCommand
{
public:
	CSetCrossProb(CSimulationSettings *c_simulation_settings);
	virtual void vRunCommand();
private:
	CSimulationSettings * cSimulationSettings;
};

class CSetTimeForSim : public CCommand
{
public:
	CSetTimeForSim(CSimulationSettings *c_simulation_settings);
	virtual void vRunCommand();
private:
	CSimulationSettings * cSimulationSettings;
};

///////////////////////////////////

CSimulationSettings::CSimulationSettings()
{
	sProblemType = DEFAULT_PROBLEM_TYPE;
	iPopulationSize = DEFAULT_POPULATION_SIZE;
	dCrossoverChance = DEFAULT_CROSS_CHANCE;
	dMutationChance = DEFAULT_MUTATION_CHANCE;
	dTimeForSim = DEFAULT_TIME_FOR_SIMULATION;
	dKnapsackCapacity = DEFAULT_KNAPSACK_CAPACITY;
}

void CSimulationSettings::vSetPopulationSize(int i_population_size)
{
	iPopulationSize = i_population_size;
}

void CSimulationSettings::vSetCrossoverChance(double d_crossover_chance)
{
	dCrossoverChance = d_crossover_chance;
}

void CSimulationSettings::vSetMutationChance(double d_mutation_chance)
{
	dMutationChance = d_mutation_chance;
}

void CSimulationSettings::vSetTimeForSim(double d_time_for_sim)
{
	dTimeForSim = d_time_for_sim;
}

inline void CSimulationSettings::vSetProblemType(string s_problem_type)
{
	sProblemType = s_problem_type;
}

inline void CSimulationSettings::vSetKnapsackCapacity(double d_knapsack_capacity)
{
	dKnapsackCapacity = d_knapsack_capacity;
}

int CSimulationSettings::iGetPopulationSize()
{
	return iPopulationSize;
}

double CSimulationSettings::dGetCrossoverChance()
{
	return dCrossoverChance;
}

double CSimulationSettings::dGetMutationChance()
{
	return dMutationChance;
}

double CSimulationSettings::dGetTimerForSim()
{
	return dTimeForSim;
}

inline string CSimulationSettings::sGetProblemType()
{
	return sProblemType;
}

inline double CSimulationSettings::dGetKnapsackCapacity()
{
	return dKnapsackCapacity;
}


CShowSimulationSettings::CShowSimulationSettings(CSimulationSettings *c_simulation_settings)
{
	cSimulationSettings = c_simulation_settings;
}

void CShowSimulationSettings::vRunCommand()
{
	cout << "rodzaj problemu: " << cSimulationSettings->sGetProblemType() << endl;
	cout << "rozmiar populacji: " << cSimulationSettings->iGetPopulationSize() << endl;
	cout << "Pojemnosc plecaka: " << cSimulationSettings->dGetKnapsackCapacity() << endl;
	cout << "Prawdopodobienstwo mutacji: " << cSimulationSettings->dGetMutationChance() << endl;
	cout << "Prawdopodobienstwo krzyzowania: " << cSimulationSettings->dGetCrossoverChance() << endl;
	cout << "czas dzialania: " << cSimulationSettings->dGetTimerForSim() << " (sekundy)" <<endl;
}

CStartSimulation::CStartSimulation(CSimulationSettings * c_simulation_settings)
{
	cSimulationSettings = c_simulation_settings;
}

void CStartSimulation::vRunCommand()
{
	vector <double> vItemsValues;
	vItemsValues.push_back(2);
	vItemsValues.push_back(3);
	vItemsValues.push_back(3);
	vItemsValues.push_back(5);
	vItemsValues.push_back(5);

	vector<double>  vItemsSizes;
	vItemsSizes.push_back(2);
	vItemsSizes.push_back(1);
	vItemsSizes.push_back(3);
	vItemsSizes.push_back(4);
	vItemsSizes.push_back(5);

	if(cSimulationSettings->sGetProblemType() == "bool")
	{
		CKnapsackProblem<bool> ckp;
		ckp.bSetDCapacity(cSimulationSettings->dGetKnapsackCapacity());

		ckp.bSetItems(5, &vItemsValues, &vItemsSizes);
		CGeneticAlgorithm<bool> cga;
		cga.vSetCKnapsackProblem(&ckp);
		cga.bSetIPopulationSize(cSimulationSettings->iGetPopulationSize());
		cga.bSetDCrossoverChance(cSimulationSettings->dGetCrossoverChance());
		cga.bSetDMutationChance(cSimulationSettings->dGetMutationChance());
		cga.bSetdTimeForSim(cSimulationSettings->dGetTimerForSim());

		cga.bRun();

		vector<bool> vBestGenotype = cga.vGetBestSolution();
		cout << "Najlepsze rozwiazanie: " << endl;
		for (int i = 0; i < vBestGenotype.size(); i++)
		{
			cout << "[" << vBestGenotype.at(i) << "]";
		}
		cout << endl;
	}
	else if (cSimulationSettings->sGetProblemType() == "int")
	{
		CKnapsackProblem<int> ckp;
		ckp.bSetDCapacity(cSimulationSettings->dGetKnapsackCapacity());

		ckp.bSetItems(5, &vItemsValues, &vItemsSizes);
		CGeneticAlgorithm<int> cga;
		cga.vSetCKnapsackProblem(&ckp);
		cga.bSetIPopulationSize(cSimulationSettings->iGetPopulationSize());
		cga.bSetDCrossoverChance(cSimulationSettings->dGetCrossoverChance());
		cga.bSetDMutationChance(cSimulationSettings->dGetMutationChance());
		cga.bSetdTimeForSim(cSimulationSettings->dGetTimerForSim());

		cga.bRun();

		vector<int> vBestGenotype = cga.vGetBestSolution();
		cout << "Najlepsze rozwiazanie: " << endl;
		for (int i = 0; i < vBestGenotype.size(); i++)
		{
			cout << "[" << vBestGenotype.at(i) << "]";
		}
		cout << endl;
	}
	else if (cSimulationSettings->sGetProblemType() == "double")
	{
		CKnapsackProblem<double> ckp;
		ckp.bSetDCapacity(cSimulationSettings->dGetKnapsackCapacity());

		ckp.bSetItems(5, &vItemsValues, &vItemsSizes);
		CGeneticAlgorithm<double> cga;
		cga.vSetCKnapsackProblem(&ckp);
		cga.bSetIPopulationSize(cSimulationSettings->iGetPopulationSize());
		cga.bSetDCrossoverChance(cSimulationSettings->dGetCrossoverChance());
		cga.bSetDMutationChance(cSimulationSettings->dGetMutationChance());
		cga.bSetdTimeForSim(cSimulationSettings->dGetTimerForSim());

		cga.bRun();

		vector<double> vBestGenotype = cga.vGetBestSolution();
		cout << "Najlepsze rozwiazanie: " << endl;
		for (int i = 0; i < vBestGenotype.size(); i++)
		{
			cout << "[" << vBestGenotype.at(i) << "]";
		}
		cout << endl;
	}

}

CSetProblemType::CSetProblemType(CSimulationSettings * c_simulation_settings)
{
	cSimulationSettings = c_simulation_settings;
}

void CSetProblemType::vRunCommand()
{
	cout << "Podaj typ symulacji: (1- bool, 2- int, 3- double)" << endl;
	int iType;
	cin >> iType;
	while (cin.fail() || iType < 1 || iType > 3)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Podaj liczbe calkowita z zakresu [1; 3]" << endl;
		cin >> iType;
	}
	if (iType == 1)
	{
		cSimulationSettings->vSetProblemType("bool");
	}
	else if (iType == 2)
	{
		cSimulationSettings->vSetProblemType("int");
	}
	else if (iType == 3)
	{
		cSimulationSettings->vSetProblemType("double");
	}
}

CSetKnapsackCapacity::CSetKnapsackCapacity(CSimulationSettings * c_simulation_settings)
{
	cSimulationSettings = c_simulation_settings;
}

void CSetKnapsackCapacity::vRunCommand()
{
	cout << "Podaj pojemnosc plecaka:" << endl;
	double dCapacity;
	cin >> dCapacity;
	while (cin.fail() || dCapacity <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Podaj liczbe wieksza od 0" << endl;
		cin >> dCapacity;
	}
	cSimulationSettings->vSetKnapsackCapacity(dCapacity);
}

CSetPopulation::CSetPopulation(CSimulationSettings * c_simulation_settings)
{
	cSimulationSettings = c_simulation_settings;
}

void CSetPopulation::vRunCommand()
{
	cout << "Podaj rozmiar populacji:" << endl;
	int iPopSize;
	cin >> iPopSize;
	while (cin.fail() || iPopSize <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Podaj liczbe wieksza od 0" << endl;
		cin >> iPopSize;
	}
	cSimulationSettings->vSetPopulationSize(iPopSize);
}

CSetMutationProb::CSetMutationProb(CSimulationSettings * c_simulation_settings)
{
	cSimulationSettings = c_simulation_settings;
}

void CSetMutationProb::vRunCommand()
{
	cout << "Podaj prawdopodobienstwo mutacji:" << endl;
	double dMutationProbability;
	cin >> dMutationProbability;
	while (cin.fail() || dMutationProbability < 0 || dMutationProbability > 1)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Podaj liczbe z zakresu [0;1]" << endl;
		cin >> dMutationProbability;
	}
	cSimulationSettings->vSetMutationChance(dMutationProbability);
}

CSetCrossProb::CSetCrossProb(CSimulationSettings * c_simulation_settings)
{
	cSimulationSettings = c_simulation_settings;
}

void CSetCrossProb::vRunCommand()
{
	cout << "Podaj prawdopodobienstwo krzyzowania:" << endl;
	double dCrossProbability;
	cin >> dCrossProbability;
	while (cin.fail() || dCrossProbability < 0 || dCrossProbability > 1)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Podaj liczbe z zakresu [0;1]" << endl;
		cin >> dCrossProbability;
	}
	cSimulationSettings->vSetCrossoverChance(dCrossProbability);
}

CSetTimeForSim::CSetTimeForSim(CSimulationSettings * c_simulation_settings)
{
	cSimulationSettings = c_simulation_settings;
}

void CSetTimeForSim::vRunCommand()
{
	cout << "Podaj dlugosc symulacji w sekundach:" << endl;
	double dSimTime;
	cin >> dSimTime;
	while (cin.fail() || dSimTime <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Podaj liczbe wieksza od 0" << endl;
		cin >> dSimTime;
	}
	cSimulationSettings->vSetKnapsackCapacity(dSimTime);
}