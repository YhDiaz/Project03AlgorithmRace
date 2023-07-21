#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

vector<int> inverselyOrdered;
vector<int> ordered;

void GenerateInverselyOrderedSet(int size)
{
	inverselyOrdered.erase(inverselyOrdered.begin(), inverselyOrdered.end());
	
	for(int i = size; i > 0; i--)
	{
		inverselyOrdered.push_back(i);
	}
}

void GenerateOrderedSet(int size)
{
	ordered.erase(ordered.begin(), ordered.end());
	
	for(int i = 0; i < size; i++)
	{
		ordered.push_back(i + 1);
	}
}

void PrintSet(vector<int> set)
{
	cout << '\n';
	for(const auto& i : set)
	{
		cout << i << " ";
	}
}

int Partition(vector<int>& set, int start, int end)
{
	int pivot = set[start];
	int i = start + 1;
	
	for(int j = i; j <= end; j++)
	{
		if(set[j] < pivot)
		{
			int temp = set[i];
			set[i] = set[j];
			set[j] = temp;
			i++;
		}
	}
	
	int temp = set[start];
	set[start] = set[i - 1];
	set[i - 1] = temp;
	
	return i - 1;
}

void QuickSort(vector<int>& set, int start, int end)
{
	if(start < end)
	{
		int pivot = Partition(set, start, end);
		QuickSort(set, start, pivot - 1);
		QuickSort(set, pivot + 1, end);
	}
}

int main()
{
	//Prueba con 100 elementos
	GenerateInverselyOrderedSet(100);
//	PrintSet(inverselyOrdered);
	QuickSort(inverselyOrdered, 0, inverselyOrdered.size() - 1);
//	PrintSet(inverselyOrdered);
	cout << "\n\tPrueba exitosa con 100 datos";
	
	//Cantidad limite de datos
	GenerateInverselyOrderedSet(32503);
//	PrintSet(inverselyOrdered);
	QuickSort(inverselyOrdered, 0, inverselyOrdered.size() - 1);
//	PrintSet(inverselyOrdered);
	cout << "\n\tPrueba exitosa con 32503 datos";
	
	GenerateOrderedSet(32503);
	QuickSort(ordered, 0, ordered.size() - 1);
	cout << "\n\tPrueba exitosa con 32503 datos (set ordenado)";
	
	//Desde 32504 datos en adelante hay un error
	GenerateInverselyOrderedSet(32504);
//	PrintSet(inverselyOrdered);
	QuickSort(inverselyOrdered, 0, inverselyOrdered.size() - 1);
//	PrintSet(inverselyOrdered);
	cout << "\n\tPrueba exitosa con 32504 datos";
	
	GenerateOrderedSet(32504);
	QuickSort(ordered, 0, ordered.size() - 1);
	cout << "\n\tPrueba exitosa con 32504 datos (set ordenado)";
	
	GenerateInverselyOrderedSet(40000);
//	PrintSet(inverselyOrdered);
	QuickSort(inverselyOrdered, 0, inverselyOrdered.size() - 1);
//	PrintSet(inverselyOrdered);
	cout << "\n\tPrueba exitosa con 40000 datos";
	
	GenerateOrderedSet(40000);
	QuickSort(ordered, 0, ordered.size() - 1);
	cout << "\n\tPrueba exitosa con 40000 datos (set ordenado)";
	
	GenerateInverselyOrderedSet(100000);
//	PrintSet(inverselyOrdered);
	QuickSort(inverselyOrdered, 0, inverselyOrdered.size() - 1);
//	PrintSet(inverselyOrdered);
	cout << "\n\tPrueba exitosa con 100000 datos";
	
	GenerateOrderedSet(100000);
	QuickSort(ordered, 0, ordered.size() - 1);
	cout << "\n\tPrueba exitosa con 100000 datos (set ordenado)";
	
	return 0;
}
