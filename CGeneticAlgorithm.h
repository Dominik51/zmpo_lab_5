#pragma once

#include "CKnapsackProblem.h"
#include "CIndividual.h"
#include <vector>
#include <random>
using namespace std;

const int DEFAULT_POPULATION_SIZE = 2;
const double DEFAULT_CROSS_CHANCE = 0.5;
const double DEFAULT_MUTATION_CHANCE = 0.5;
const int DEFAULT_ITERATIONS_TO_STOP = 10;
const double DEFAULT_BEST_GENOTYPE_FITNESS = -1;

template <class T>
class CGeneticAlgorithm
{
public:
	CGeneticAlgorithm();
	bool bRun();
	bool vSetCKnapsackProblem(CKnapsackProblem<T> *c_knapsack_problem);
	bool bSetIPopulationSize(int i_population_size);
	bool bSetDCrossoverChance(double d_crossover_chance);
	bool bSetDMutationChance(double d_mutation_chance);
	bool bSetIIterationsToStop(int i_iterations_to_stop);
	vector<T> vGetBestSolution();

private:
	void vGeneratePopulation();
	int iChooseIndividual(int i_idx1, int i_idx2);
	void vFindBestIndividual();
	vector<CIndividual<T>*> vFindBestTwoIndividuals(vector<CIndividual<T>*> *v_population);
	void vCrossPopulation(vector<CIndividual<T>*> *v_population);
	void vEliteCrossPopulation(vector<CIndividual<T>*> *v_population);
	void vMutatePopulation(vector<CIndividual<T>*> *v_population);
	void vDeletePopulation();
	mt19937 gen;

	CKnapsackProblem<T> *cKnapsackProblem;
	int iPopulationSize;
	double dCrossoverChance;
	double dMutationChance;
	int iIterationsToStop;
	vector<CIndividual<T>*> vPopulation;
	vector<T> vBestGenotype;
	double iBestGenotypeFitness;
};

template <class T>
CGeneticAlgorithm<T>::CGeneticAlgorithm()
{
	random_device rd;
	mt19937 generator(rd());
	gen = generator;

	cKnapsackProblem = nullptr;
	iPopulationSize = DEFAULT_POPULATION_SIZE;
	dCrossoverChance = DEFAULT_CROSS_CHANCE;
	dMutationChance = DEFAULT_MUTATION_CHANCE;
	iIterationsToStop = DEFAULT_ITERATIONS_TO_STOP;
	iBestGenotypeFitness = DEFAULT_BEST_GENOTYPE_FITNESS;
}

template <class T>
bool CGeneticAlgorithm<T>::bRun()
{
	if (cKnapsackProblem != nullptr)
	{
		if (cKnapsackProblem->iGetNumberOfItems() > 0)
		{
			vGeneratePopulation();
			for (int i = 0; i < iIterationsToStop; i++)
			{
				vFindBestIndividual();
				vector<CIndividual<T>*> vNewPopulation;
				vEliteCrossPopulation(&vNewPopulation); // modyfikacja
				vMutatePopulation(&vNewPopulation);
				vDeletePopulation();
				vPopulation = vNewPopulation;
			}
			vFindBestIndividual();
			vDeletePopulation();
			return true;
		}
	}
	return false;
}

template <class T>
void CGeneticAlgorithm<T>::vCrossPopulation(vector<CIndividual<T>*> *v_population)
{
	while (v_population->size() < iPopulationSize)
	{
		uniform_int_distribution<> disInt(0, iPopulationSize - 1);
		uniform_real_distribution<> disReal(0, 1);

		int idxCIndividual1 = iChooseIndividual(disInt(gen), disInt(gen));
		int idxCIndividual2 = iChooseIndividual(disInt(gen), disInt(gen));

		if (dCrossoverChance <= disReal(gen))
		{
			vector<CIndividual<T>*> newCIndividuals = vPopulation.at(idxCIndividual1)->vCrossover(vPopulation.at(idxCIndividual2));
			v_population->push_back(newCIndividuals.at(0));
			v_population->push_back(newCIndividuals.at(1));
		}
		else
		{
			CIndividual<T> *cNewIndividual1 = new CIndividual<T>;
			CIndividual<T> *cNewIndividual2 = new CIndividual<T>;
			cNewIndividual1->vSetVGenotype(vPopulation.at(idxCIndividual1)->vGetVGenotype());
			cNewIndividual1->vSetCKnapsackProblem(cKnapsackProblem);

			cNewIndividual2->vSetVGenotype(vPopulation.at(idxCIndividual2)->vGetVGenotype());
			cNewIndividual2->vSetCKnapsackProblem(cKnapsackProblem);

			v_population->push_back(cNewIndividual1);
			v_population->push_back(cNewIndividual2);
		}
	}
}
template <class T>
void CGeneticAlgorithm<T>::vEliteCrossPopulation(vector<CIndividual<T>*>* v_population) // modyfikacja
{
	while (v_population->size() < iPopulationSize - 2)
	{
		uniform_int_distribution<> disInt(0, iPopulationSize - 1);
		uniform_real_distribution<> disReal(0, 1);

		int idxCIndividual1 = iChooseIndividual(disInt(gen), disInt(gen));
		int idxCIndividual2 = iChooseIndividual(disInt(gen), disInt(gen));

		if (dCrossoverChance <= disReal(gen))
		{
			vector<CIndividual<T>*> newCIndividuals = vPopulation.at(idxCIndividual1)->vCrossover(vPopulation.at(idxCIndividual2));
			v_population->push_back(newCIndividuals.at(0));
			v_population->push_back(newCIndividuals.at(1));
		}
		else
		{
			CIndividual<T> *cNewIndividual1 = new CIndividual<T>;
			CIndividual<T> *cNewIndividual2 = new CIndividual<T>;
			cNewIndividual1->vSetVGenotype(vPopulation.at(idxCIndividual1)->vGetVGenotype());
			cNewIndividual1->vSetCKnapsackProblem(cKnapsackProblem);

			cNewIndividual2->vSetVGenotype(vPopulation.at(idxCIndividual2)->vGetVGenotype());
			cNewIndividual2->vSetCKnapsackProblem(cKnapsackProblem);

			v_population->push_back(cNewIndividual1);
			v_population->push_back(cNewIndividual2);
		}
	}
	vector<CIndividual<T>*> vBestTwoInd = vFindBestTwoIndividuals(&vPopulation);
	v_population->push_back(vBestTwoInd.at(0));
	v_population->push_back(vBestTwoInd.at(1));
}

template <class T>
void CGeneticAlgorithm<T>::vMutatePopulation(vector<CIndividual<T>*> *v_population)
{
	for (int i = 0; i < iPopulationSize; i++)
	{
		v_population->at(i)->vMutate(dMutationChance);
	}
}

template <class T>
void CGeneticAlgorithm<T>::vDeletePopulation()
{
	while (!vPopulation.empty()) {
		delete vPopulation.back();
		vPopulation.pop_back();
	}
}

template <class T>
int CGeneticAlgorithm<T>::iChooseIndividual(int i_idx1, int i_idx2)
{
	if (vPopulation.at(i_idx1)->dGetFitness() >= vPopulation.at(i_idx2)->dGetFitness())
	{
		return i_idx1;
	}
	else
	{
		return i_idx2;
	}
}

template <class T>
void CGeneticAlgorithm<T>::vFindBestIndividual()
{
	int iBestIndividual = 0;
	int iBestAdaptation = vPopulation.at(0)->dGetFitness();
	for (int i = 1; i < iPopulationSize; i++)
	{
		if (vPopulation.at(i)->dGetFitness() > iBestAdaptation)
		{
			iBestAdaptation = vPopulation.at(i)->dGetFitness();
			iBestIndividual = i;
		}
	}
	if (iBestAdaptation > iBestGenotypeFitness)
	{
		vBestGenotype = vPopulation.at(iBestIndividual)->vGetVGenotype();
		iBestGenotypeFitness = cKnapsackProblem->dGetFintess(vBestGenotype);
	}
}

template <class T>
vector<CIndividual<T>*> CGeneticAlgorithm<T>::vFindBestTwoIndividuals(vector<CIndividual<T>*>* v_population)
{
	vector<CIndividual<T>*> vBestTwoInd;
	CIndividual<T>* firstIndividual = nullptr;
	CIndividual<T>* secondIndividual = nullptr;
	if (v_population->at(0)->dGetFitness() > v_population->at(1)->dGetFitness())
	{
		firstIndividual = v_population->at(0);
		secondIndividual = v_population->at(1);
	}
	else
	{
		firstIndividual = v_population->at(1);
		secondIndividual = v_population->at(0);
	}
	for (int i = 2; i < iPopulationSize; i++)
	{
		if (vPopulation.at(i)->dGetFitness() > secondIndividual->dGetFitness())
		{
			if (vPopulation.at(i)->dGetFitness() > firstIndividual->dGetFitness())
			{
				secondIndividual = firstIndividual;
				firstIndividual = vPopulation.at(i);
			}
			else
			{
				secondIndividual = vPopulation.at(i);
			}
		}
	}
	CIndividual<T>* newFirstIndividual = new CIndividual<T>();
	CIndividual<T>* newSecondIndividual = new CIndividual<T>();
	newFirstIndividual->vSetVGenotype(firstIndividual->vGetVGenotype());
	newFirstIndividual->vSetCKnapsackProblem(cKnapsackProblem);

	newSecondIndividual->vSetVGenotype(secondIndividual->vGetVGenotype());
	newSecondIndividual->vSetCKnapsackProblem(cKnapsackProblem);

	vBestTwoInd.push_back(newFirstIndividual);
	vBestTwoInd.push_back(newSecondIndividual);
	return vBestTwoInd;
}

template <class T>
bool CGeneticAlgorithm<T>::vSetCKnapsackProblem(CKnapsackProblem<T> *c_knapsack_problem)
{
	if (c_knapsack_problem != nullptr)
	{
		cKnapsackProblem = c_knapsack_problem;
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
bool CGeneticAlgorithm<T>::bSetIPopulationSize(int i_population_size)
{
	if (i_population_size > 1)
	{
		iPopulationSize = i_population_size;
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
bool CGeneticAlgorithm<T>::bSetDCrossoverChance(double d_crossover_chance)
{
	if (d_crossover_chance >= 0 && d_crossover_chance <= 1)
	{
		dCrossoverChance = d_crossover_chance;
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
bool CGeneticAlgorithm<T>::bSetDMutationChance(double d_mutation_chance)
{
	if (d_mutation_chance >= 0 && d_mutation_chance <= 1)
	{
		dMutationChance = d_mutation_chance;
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
bool CGeneticAlgorithm<T>::bSetIIterationsToStop(int i_iterations_to_stop)
{
	if (i_iterations_to_stop > 0)
	{
		iIterationsToStop = i_iterations_to_stop;
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
vector<T> CGeneticAlgorithm<T>::vGetBestSolution()
{
	return vBestGenotype;
}

template <class T>
void CGeneticAlgorithm<T>::vGeneratePopulation()
{
	uniform_int_distribution<> disInt(0, 1);
	for (int i = 0; i < iPopulationSize; i++)
	{
		CIndividual<T> *cIndividual = new CIndividual<T>;
		vector<T> cIndividualGenotype;
		for (int j = 0; j < cKnapsackProblem->iGetNumberOfItems(); j++)
		{
			cIndividualGenotype.push_back(disInt(gen));
		}
		cIndividual->vSetVGenotype(cIndividualGenotype);
		cIndividual->vSetCKnapsackProblem(cKnapsackProblem);
		vPopulation.push_back(cIndividual);
	}
}

template <>
void CGeneticAlgorithm<int>::vGeneratePopulation()
{
	uniform_int_distribution<> disInt(0, MAX_ITEMS_INT);
	for (int i = 0; i < iPopulationSize; i++)
	{
		CIndividual<int> *cIndividual = new CIndividual<int>;
		vector<int> cIndividualGenotype;
		for (int j = 0; j < cKnapsackProblem->iGetNumberOfItems(); j++)
		{
			int a = disInt(gen);
			cIndividualGenotype.push_back(a);
		}
		cIndividual->vSetVGenotype(cIndividualGenotype);
		cIndividual->vSetCKnapsackProblem(cKnapsackProblem);
		vPopulation.push_back(cIndividual);
	}
}


template <>
void CGeneticAlgorithm<double>::vGeneratePopulation()
{
	uniform_int_distribution<> disReal(0, MAX_ITEMS_DOUBLE);
	for (int i = 0; i < iPopulationSize; i++)
	{
		CIndividual<double> *cIndividual = new CIndividual<double>;
		vector<double> cIndividualGenotype;
		for (int j = 0; j < cKnapsackProblem->iGetNumberOfItems(); j++)
		{
			double a = disReal(gen);
			cIndividualGenotype.push_back(a);
		}
		cIndividual->vSetVGenotype(cIndividualGenotype);
		cIndividual->vSetCKnapsackProblem(cKnapsackProblem);
		vPopulation.push_back(cIndividual);
	}
}
