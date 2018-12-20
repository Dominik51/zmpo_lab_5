#include<iostream>
#include<string>
#include "CMenu.h"
#include "CGeneticAlgorithm.h"
#include "CGeneticAlgorithmCommands.h"

using namespace std;

const string GENOTYPE = "genotype: ";
const string SCORE = "score: ";

int main()
{

	CMenu cMenu("Algorytm genetyczny", "ag");
	CMenu cOptions("Ustawienia", "ust");
	CMenuCommand cSimulationStartCommand("Rozpocznij symulace", "start");
	CMenuCommand cShowSettingsCommand("Wyswietl ustawienia", "wys");
	CMenuCommand cSetMutationProbCommand("Ustaw prawdopodobienstwo mutacji", "mut");
	CMenuCommand cSetCrossoverProbCommand("Ustaw prawdopodobienstwo krzyzowania", "krz");
	CMenuCommand cSetPopulationSizeCommand("Ustaw rozmiar populacji", "pop");
	CMenuCommand cSetSimulationTypeCommand("Ustaw typ symulacji", "typ");
	CMenuCommand cSetKnapsackCapacityCommand("Ustaw pojemnosc plecaka:", "poj");
	CMenuCommand cSetTimeForSimCommand("Ustaw dlugosc symulacji w sekundach:", "czas");

	CSimulationSettings cSimulationSettings;
	CShowSimulationSettings cShowSimulationSettings(&cSimulationSettings);
	CStartSimulation cStartSimulation(&cSimulationSettings);
	CSetProblemType cSetProblemType(&cSimulationSettings);
	CSetKnapsackCapacity cSetKnapsackCapacity(&cSimulationSettings);
	CSetPopulation cSetPopulation(&cSimulationSettings);
	CSetCrossProb cSetCrossProb(&cSimulationSettings);
	CSetMutationProb cSetMutationProb(&cSimulationSettings);
	CSetTimeForSim cSetTimeForSim(&cSimulationSettings);

	cShowSettingsCommand.vSetCCommand(&cShowSimulationSettings);
	cSimulationStartCommand.vSetCCommand(&cStartSimulation);
	cSetSimulationTypeCommand.vSetCCommand(&cSetProblemType);
	cSetKnapsackCapacityCommand.vSetCCommand(&cSetKnapsackCapacity);
	cSetPopulationSizeCommand.vSetCCommand(&cSetPopulation);
	cSetCrossoverProbCommand.vSetCCommand(&cSetCrossProb);
	cSetMutationProbCommand.vSetCCommand(&cSetMutationProb);
	cSetTimeForSimCommand.vSetCCommand(&cSetTimeForSim);

	cOptions.vAddCMenuItem(&cShowSettingsCommand);
	cOptions.vAddCMenuItem(&cSetMutationProbCommand);
	cOptions.vAddCMenuItem(&cSetCrossoverProbCommand);
	cOptions.vAddCMenuItem(&cSetPopulationSizeCommand);
	cOptions.vAddCMenuItem(&cSetSimulationTypeCommand);
	cOptions.vAddCMenuItem(&cSetKnapsackCapacityCommand);
	cOptions.vAddCMenuItem(&cSetTimeForSimCommand);

	cMenu.vAddCMenuItem(&cSimulationStartCommand);
	cMenu.vAddCMenuItem(&cOptions);
	
	cMenu.vRun();

	/*cga.vSetCKnapsackProblem(&ckp);
	cga.bSetIPopulationSize(10);
	cga.bSetDCrossoverChance(0.3);
	cga.bSetDMutationChance(0.2);
	cga.bSetIIterationsToStop(500);
	cga.bSetdTimeForSim(5);

	cga.bRun();*/


	int a;
	cin >> a;
}