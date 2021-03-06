#pragma once

#include <vector>
#include <random>
#include "CKnapsackProblem.h"
#include <iostream>
using namespace std;

const int MAX_ITEMS_INT = 5;
const double MAX_ITEMS_DOUBLE = 5;

template <class T>
class CIndividual
{
public:
	CIndividual();
	double dGetFitness();
	//vector<CIndividual<T>*> vCrossover(CIndividual<T> *c_individual);
	vector<T> vGetVGenotype();
	void vSetVGenotype(vector <T> v_genotype);
	void vSetCKnapsackProblem(CKnapsackProblem<T> *c_knapsack_problem);
	void vSetDMutationChance(double d_mutation_chance);

	void operator++(int);
	CIndividual<T>* operator+(CIndividual<T> *secondParent);

private:
	void vMutate();
	mt19937 gen;
	double dMutationChance;

	CKnapsackProblem<T> *cKnapsackProblem;
	vector <T> vGenotype;
};

template <class T>
CIndividual<T>::CIndividual()
{
	random_device rd;
	mt19937 generator(rd());
	gen = generator;

	dMutationChance = 0.05;
	cKnapsackProblem = nullptr;
}

template <class T>
double CIndividual<T>::dGetFitness()
{
	return cKnapsackProblem != nullptr ? cKnapsackProblem->dGetFintess(vGenotype) : 0;
}

template<class T>
void CIndividual<T>::operator++(int) {
	vMutate();
}

template<class T>
CIndividual<T>* CIndividual<T>::operator+(CIndividual<T> * c_individual)
{
	uniform_int_distribution<> disInt(1, vGenotype.size() - 1);
	int iCrossPoint = disInt(gen);

	vector <T> vGenotype1;

	for (int i = 0; i < iCrossPoint; i++)
	{
		vGenotype1.push_back(vGenotype.at(i));
	}

	for (int i = iCrossPoint; i < vGenotype.size(); i++)
	{
		vGenotype1.push_back(c_individual->vGetVGenotype().at(i));
	}

	CIndividual<T>  *cNewIndividual1 = new CIndividual<T>;
	cNewIndividual1->vSetVGenotype(vGenotype1);
	cNewIndividual1->vSetCKnapsackProblem(cKnapsackProblem);
	cNewIndividual1->vSetDMutationChance(dMutationChance);

	return cNewIndividual1;
}

template <class T>
void CIndividual<T>::vMutate()
{
	uniform_real_distribution<> disInt(0, 1);

	for (int i = 0; i < vGenotype.size(); i++)
	{
		if (dMutationChance >= disInt(gen))
		{
			vGenotype.at(i) = (vGenotype.at(i) + 1) % 2;
		}
	}
}
template <>
void CIndividual<int>::vMutate()
{
	uniform_real_distribution<> disReal(0, 1);
	uniform_int_distribution<> disInt(0, MAX_ITEMS_INT);

	for (int i = 0; i < vGenotype.size(); i++)
	{
		if (dMutationChance >= disReal(gen))
		{
			vGenotype.at(i) = disInt(gen);
		}
	}
}

template <>
void CIndividual<double>::vMutate()
{
	uniform_real_distribution<> disReal(0, 1);
	uniform_real_distribution<> disReal2(0, MAX_ITEMS_DOUBLE);
	
	for (int i = 0; i < vGenotype.size(); i++)
	{
		if (dMutationChance >= disReal(gen))
		{
			vGenotype.at(i) = disReal2(gen);
		}
	}
}
/*
template <class T>
vector<CIndividual<T>*> CIndividual<T>::vCrossover(CIndividual<T> *c_individual)
{
	uniform_int_distribution<> disInt(1, vGenotype.size() - 1);
	int iCrossPoint = disInt(gen);

	vector <T> vGenotype1;
	vector <T> vGenotype2;

	for (int i = 0; i < iCrossPoint; i++)
	{
		vGenotype1.push_back(vGenotype.at(i));
		vGenotype2.push_back(c_individual->vGetVGenotype().at(i));
	}

	for (int i = iCrossPoint; i < vGenotype.size(); i++)
	{
		vGenotype1.push_back(c_individual->vGetVGenotype().at(i));
		vGenotype2.push_back(vGenotype.at(i));
	}

	CIndividual<T>  *cNewIndividual1 = new CIndividual<T>;
	CIndividual<T> *cNewIndividual2 = new CIndividual<T>;
	cNewIndividual1->vSetVGenotype(vGenotype1);
	cNewIndividual1->vSetCKnapsackProblem(cKnapsackProblem);

	cNewIndividual2->vSetVGenotype(vGenotype2);
	cNewIndividual2->vSetCKnapsackProblem(cKnapsackProblem);
	vector<CIndividual*> vNewCIndividuals;
	vNewCIndividuals.push_back(cNewIndividual1);
	vNewCIndividuals.push_back(cNewIndividual2);
	return vNewCIndividuals;
}*/

template <class T>
void CIndividual<T>::vSetVGenotype(vector <T> v_genotype)
{
	vGenotype = v_genotype;
}

template <class T>
void CIndividual<T>::vSetCKnapsackProblem(CKnapsackProblem<T> * c_knapsack_problem)
{
	cKnapsackProblem = c_knapsack_problem;
}

template<class T>
inline void CIndividual<T>::vSetDMutationChance(double d_mutation_chance)
{
	dMutationChance = d_mutation_chance;
}

template <class T>
vector<T> CIndividual<T>::vGetVGenotype()
{
	return vGenotype;
}
