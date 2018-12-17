#pragma once
#include<vector>
using namespace std;

template <class T>
class CKnapsackProblem
{
public:
	CKnapsackProblem();
	bool bSetDCapacity(double d_capacity);
	bool bSetItems(int i_number_of_items, vector<double> *v_items_value, vector<double> *v_items_size);
	double dGetFintess(vector <T> &v_genotype);
	int iGetNumberOfItems();
private:
	double dCapacity;
	int iNumberOfItems;
	vector<double> *vItemsSize;
	vector<double> *vItemsValue;
};

template <class T>
CKnapsackProblem<T>::CKnapsackProblem()
{
}

template <class T>
bool CKnapsackProblem<T>::bSetDCapacity(double d_capacity)
{
	if (d_capacity > 0)
	{
		dCapacity = d_capacity;
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
bool CKnapsackProblem<T>::bSetItems(int i_number_of_items, vector<double>* v_items_value, vector<double>* v_items_size)
{
	if (v_items_size != nullptr && v_items_value != nullptr)
	{
		if (i_number_of_items > 0 && i_number_of_items == v_items_size->size() && i_number_of_items == v_items_value->size())
		{
			iNumberOfItems = i_number_of_items;
			vItemsValue = v_items_value;
			vItemsSize = v_items_size;
			return true;
		}
	}
	return false;
}

template <class T>
double CKnapsackProblem<T>::dGetFintess(vector <T> &v_genotype)
{
	double dValue = 0;
	double dSize = 0;
	for (int i = 0; i < v_genotype.size(); i++)
	{
		if (v_genotype.at(i) != 0)
		{
			dValue += v_genotype.at(i) * vItemsValue->at(i);
			dSize += v_genotype.at(i) * vItemsSize->at(i);
		}
	}
	return dSize <= dCapacity ? dValue : 0;
}

template <class T>
int CKnapsackProblem<T>::iGetNumberOfItems()
{
	return iNumberOfItems;
}
