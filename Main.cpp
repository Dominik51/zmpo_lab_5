#include<iostream>
#include<string>
#include "CGeneticAlgorithm.h"
using namespace std;

const string GENOTYPE = "genotype: ";
const string SCORE = "score: ";

int main()
{
	CKnapsackProblem<bool> ckp;
	ckp.bSetDCapacity(40);

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

	ckp.bSetItems(5, &vItemsValues, &vItemsSizes);
	CGeneticAlgorithm<bool> cga;

	cga.vSetCKnapsackProblem(&ckp);
	cga.bSetIPopulationSize(10);
	cga.bSetDCrossoverChance(0.3);
	cga.bSetDMutationChance(0.2);
	cga.bSetIIterationsToStop(500);

	cga.bRun();

	vector<bool> best = cga.vGetBestSolution();

	cout << GENOTYPE;
	for (int i = 0; i < best.size(); i++)
	{
		cout << "[" << best.at(i) << "]";
	}
	cout << endl << SCORE << ckp.dGetFintess(best);

	int a;
	cin >> a;
}