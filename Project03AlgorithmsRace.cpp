#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <random>
#include <chrono>
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

int race01Range = 0; //Rango carrera 1
int race02Range = 0; //Rango carrera 2
int race03Range = 0; //Rango carrera 3
int numAlgorithms = 7; //Cantidad de algoritmos
unordered_map<string, int> algorithms; //Map: Nombre algoritmo (Key) --- Numero asociado (Value)
int order = 0; //1: Ascendente; 2: Descendente
int races = 3; //Numero de carreras
int modes = 4; //Numero de modos

vector<int> ordered; //Set de datos ordenado
vector<int> inverselyOrdered; //Set de datos inversamente ordenado

void TestFunction();

void GenerateRanges(int, int, int); //Generacion de rangos
bool ReadRangesFile(); //Lectura del archivo de rangos
void StartMessage(); //Eleccion de ordenamiento de datos
void InitializeAlgorithmsMap(); //Inicializacion del mapa de algoritmos
int GetMaxRange(); //Obtencion del rango mayor
void GenerateCommonDataSet(); //Sets de datos comunes
vector<int> GetTruncatedCommonDataSet(int, bool); //Truncamiento de sets de datos comunes
vector<int> GenerateUniqueRandomDataSet(int); //Generacion del set de datos aleatorios unicos
vector<int> GenerateDuplicateRandomDataSet(int); //Generacion del set de datos aleatorios duplicados
vector<int> GenerateRandomDataSet(); //Sets de datos aleatorios
void SelectionSort_Ascending(vector<int>&); //Algoritmo 01: Selection Sort (Orden ascendente)
void SelectionSort_Descending(vector<int>&); //Algoritmo 01: Selection Sort (Orden descendente)
void BubbleSort_Ascending(vector<int>&); //Algoritmo 02: Bubble Sort (Orden ascendente)
void BubbleSort_Descending(vector<int>&); //Algoritmo 02: Bubble Sort (Orden descendente)
void InsertionSort_Ascending(vector<int>&); //Algoritmo 03: Insertion Sort (Orden ascendente)
void InsertionSort_Descending(vector<int>&); //Algoritmo 03: Insertion Sort (Orden descendente)
int ShellSort_KnuthGap(int); //Secuencia de Knuth para el algoritmo 04
void ShellSort_Ascending(vector<int>&); //Algoritmo 04: Shell Sort (Orden ascendente)
void ShellSort_Descending(vector<int>&); //Algoritmo 04: Shell Sort (Orden descendente)
void MergeSort_MergeAscending(vector<int>&, int, int, int); //Fusion ascendente para el algoritmo 05
void MergeSort_MergeDescending(vector<int>&, int, int, int); //Fusion descendente para el algoritmo 05
void MergeSort_Ascending(vector<int>&, int, int); //Algoritmo 05: Merge Sort (Orden ascendente)
void MergeSort_Descending(vector<int>&, int, int); //Algoritmo 05: Merge Sort (Orden descendente)
int QuickSort_PartitionAscending(vector<int>&, int, int); //Particion para el orden ascendente del algoritmo 06
int QuickSort_PartitionDescending(vector<int>&, int, int); //Particion para el orden descendente del algoritmo 06
void QuickSort_Ascending(vector<int>&, int, int); //Algoritmo 06: Quick Sort (Orden ascendente)
void QuickSort_Descending(vector<int>&, int, int); //Algoritmo 06: Quick Sort (Orden descendente)
void MaxHeapify(vector<int>&, int, int); //Arbol con valor maximo para el orden ascendente del algoritmo 07
void MinHeapify(vector<int>&, int, int); //Arbol con valor minimo para el orden descendente del algoritmo 07
void HeapSort_Ascending(vector<int>&); //Algoritmo 07: Heap Sort (Orden ascendente)
void HeapSort_Descending(vector<int>&); //Algoritmo 07: Heap Sort (Orden descendente)
auto ExecutionTime_Ascending(int, vector<int>&); //Tiempo de ejecucion (Orden ascendente)
auto ExecutionTime_Descending(int, vector<int>&); //Tiempo de ejecucion (Orden descendente)
auto ExecutionTime(int, vector<int>&); //Tiempo de ejecucion del algoritmo
void RunAlgorithms(int, vector<int>, unordered_map<int, double>*); //Ejecucion de los algoritmos
void PrintRaceInfo(int, int); //Informacion de las carreras
void UpdateWinner(int, string*, double*, string, double); //Actualizacion del algoritmo ganador
string GetAlgorithmNameByIndex(int); //Obtener el nombre de un algoritmo
vector<string> GetAllWinners(double, unordered_map<int, double>); //Obtener los algoritmos ganadores
void ShowWinners(vector<string>, double); //Mostrar los ganadores
void PrintResults(unordered_map<int, double>); //Resultados de las carreras
vector<int> GetSetByMode(int, int); //Obtener el set que se utilizara
void Competition(int, int); //Competicion en cada carrera y modo
void Races(); //Carreras

int main(int argc, char* argv[])
{
	if(ReadRangesFile())
	{
		StartMessage();
		InitializeAlgorithmsMap();
		GenerateCommonDataSet();
		Races();
	}
	
	return 0;
}

//Generacion de rangos: Se generan los rangos de datos que tendra cada carrera
void GenerateRanges(int race, int minRange, int maxRange)
{
	//FORMULA PARA OBTENCION DE UN VALOR DENTRO DEL RANGO
	//RANGO: min --- max
	//FORMULA: rand() % (max - min) + min
	
	if(race == 1)
	{
		race01Range = rand() % (maxRange - minRange) + minRange;
	}
	else if(race == 2)
	{
		race02Range = rand() % (maxRange - minRange) + minRange;
	}
	else
	{
		race03Range = rand() % (maxRange - minRange) + minRange;
	}
}

//Lectura del archivo que contiene los rangos de cada carrera
bool ReadRangesFile()
{
	srand(time(NULL));
	string filename = "Ranges.txt";
	ifstream file(filename);
	
	if(file.is_open())
	{
		string line;
		getline(file, line); //Omitir la primera linea correspondiente a los encabezados
		int race = 0;
		
		while(getline(file, line))
		{
			race++;
			stringstream ss(line);
			string minRange, maxRange;
			
			getline(ss, minRange, ',');
			getline(ss, maxRange, ',');
			GenerateRanges(race, stoi(minRange), stoi(maxRange));
		}
		
		file.close();
		return true;
	}
	else
	{
		cout << "\n\tError al intentar abrir el archivo: " << filename << endl;
		return false; //El archivo no se leyo correctamente
	}
}

//Mensaje de inicio: El usuario decide si desea que el orden de los sets de datos sea ascendente o descendente
void StartMessage()
{
	do
	{
		cout << "Carreras de algoritmos\n1. Ascendente.\n2. Descendente\nOpcion elegida: ";
		cin >> order;
		
		if(order != 1 && order != 2)
		{
			cout << "\n\t* Error *\n" << endl;
		}
	}
	while(order != 1 && order != 2);
	
	cout << "\n\tRangos:\n\t- Carrera 1: " << race01Range << "\n\t- Carrera 2: " << race02Range << "\n\t- Carrera 3: " << race03Range << endl;
}

//Inicializacion de los valores del mapa de algoritmos
void InitializeAlgorithmsMap()
{
	algorithms["Selection Sort"] = 1;
	algorithms["Bubble Sort"] = 2;
	algorithms["Insertion Sort"] = 3;
	algorithms["Shell Sort"] = 4;
	algorithms["Quick Sort"] = 5;
	algorithms["Merge Sort"] = 6;
	algorithms["Heap Sort"] = 7;
}

//Obtencion del rango mayor para usarlo como dimension maxima de los sets de datos comunes
int GetMaxRange()
{
	if(race01Range > race02Range)
	{
		if(race01Range > race03Range)
		{
			return race01Range;
		}
		else
		{
			return race03Range;
		}
	}
	else if(race02Range > race03Range)
	{
		return race02Range;
	}
	else
	{
		return race03Range;
	}
}

//Generacion de sets de datos comunes: Set de datos comunes para todas las carreras
void GenerateCommonDataSet()
{
	cout << "\n\tGenerando sets de datos comunes (ordenado e inversamente ordenado)...";
	
	int max = GetMaxRange();
	
	if(order == 1) //Generacion de los sets si el orden elegido es ascendente
	{
		for(int i = 0; i < max; i++)
		{
			ordered.push_back(i + 1);
			inverselyOrdered.push_back(max - i);
		}
	}
	else //Generacion de los sets si el orden elegido es descendente
	{
		for(int i = 0; i < max; i++)
		{
			ordered.push_back(max - i);
			inverselyOrdered.push_back(i + 1);
		}
	}
	
	cout << "\n\tSets de datos comunes generados";
}

//Obtencion de los sets de datos comunes (ordenado e inversamente ordenado) truncados para las carreras 2 y 3
vector<int> GetTruncatedCommonDataSet(int race, bool orderedSet)
{
	vector<int> orderedAux, inverselyOrderedAux;
	
	if(order == 1)
	{
		if(orderedSet)
		{
			if(race == 2)
			{
				orderedAux.assign(ordered.begin(), ordered.begin() + race02Range);
			}
			else
			{
				orderedAux.assign(ordered.begin(), ordered.begin() + race03Range);
			}
			
			return orderedAux;
		}
		else
		{
			if(race == 2)
			{
				inverselyOrderedAux.assign(inverselyOrdered.end() - race02Range, inverselyOrdered.end());
			}
			else
			{
				inverselyOrderedAux.assign(inverselyOrdered.end() - race03Range, inverselyOrdered.end());
			}
			
			return inverselyOrderedAux;
		}
	}
	else
	{
		if(orderedSet)
		{
			if(race == 2)
			{
				orderedAux.assign(ordered.end() - race02Range, ordered.end());
			}
			else
			{
				orderedAux.assign(ordered.end() - race03Range, ordered.end());
			}
			
			return orderedAux;
		}
		else
		{
			if(race == 2)
			{
				inverselyOrderedAux.assign(inverselyOrdered.begin(), inverselyOrdered.begin() + race02Range);
			}
			else
			{
				inverselyOrderedAux.assign(inverselyOrdered.begin(), inverselyOrdered.begin() + race03Range);
			}
			
			return inverselyOrderedAux;
		}
	}
}

//Generacion del set de datos aleatorios unicos
vector<int> GenerateUniqueRandomDataSet(int range)
{
	srand(time(NULL));
	vector<int> backup;

	for(int i = 0; i < range; i++)
	{
		backup.push_back(i + 1);
	}
	
	vector<int> uniqueRandom;
	
	for(int i = 0; i < range; i++)
	{
		int num = rand() % (range - i) + 1;
		uniqueRandom.push_back(backup[num - 1]);
		backup.erase(backup.begin() + num - 1);
	}
	
	return uniqueRandom;
}

//Generacion del set de datos aleatorios duplicados
vector<int> GenerateDuplicateRandomDataSet(int range)
{
	srand(time(NULL));
	vector<int> duplicateRandom;
	
	for(int i = 0; i < range; i++)
	{
		int num = rand() % range + 1;
		duplicateRandom.push_back(num);
	}
	
	return duplicateRandom;
}

//Generacion de set de datos aleatorios
vector<int> GenerateRandomDataSet(bool unique, int range)
{
	if(unique)
	{
		return GenerateUniqueRandomDataSet(range);
	}
	else
	{
		return GenerateDuplicateRandomDataSet(range);
	}	
}

//Algoritmo 01: Selection Sort (Orden ascendente)
void SelectionSort_Ascending(vector<int>& set)
{
	for(int i = 0; i < set.size(); i++)
	{
		for(int j = i; j < set.size(); j++)
		{
			if(set[j] < set[i])
			{
				int temp = set[i];
				set[i] = set[j];
				set[j] = temp;
			}
		}
	}
}

//Algoritmo 01: Selection Sort (Orden descendente)
void SelectionSort_Descending(vector<int>& set)
{
	for(int i = 0; i < set.size(); i++)
	{
		for(int j = i; j < set.size(); j++)
		{
			if(set[j] > set[i])
			{
				int temp = set[i];
				set[i] = set[j];
				set[j] = temp;
			}
		}
	}
}

//Algoritmo 02: Bubble Sort (Orden ascendente)
void BubbleSort_Ascending(vector<int>& set)
{
	for(int i = 1; i < set.size(); i++)
	{
		for(int j = 0; j < set.size() - i; j++)
		{
			if(set[j] > set[j + 1])
			{
				int temp = set[j];
				set[j] = set[j + 1];
				set[j + 1] = temp;
			}
		}
	}
}

//Algoritmo 02: Bubble Sort (Orden descendente)
void BubbleSort_Descending(vector<int>& set)
{
	for(int i = 1; i < set.size(); i++)
	{
		for(int j = 0; j < set.size() - i; j++)
		{
			if(set[j] < set[j + 1])
			{
				int temp = set[j];
				set[j] = set[j + 1];
				set[j + 1] = temp;
			}
		}
	}
}

//Algoritmo 03: Insertion Sort (Orden ascendente)
void InsertionSort_Ascending(vector<int>& set)
{
	for(int i = 0; i < set.size(); i++)
	{
		int j = i;
		
		while(j > 0 && set[j - 1] > set[j])
		{
			int temp = set[j];
			set[j] = set[j - 1];
			set[j - 1] = temp;
			j--;
		}
	}	
}

//Algoritmo 03: Insertion Sort (Orden descendente)
void InsertionSort_Descending(vector<int>& set)
{
	for(int i = 0; i < set.size(); i++)
	{
		int j = i;
		
		while(j > 0 && set[j - 1] < set[j])
		{
			int temp = set[j];
			set[j] = set[j - 1];
			set[j - 1] = temp;
			j--;
		}
	}	
}

//Secuencia de Knuth (Algoritmo 04: Shell Sort)
int ShellSort_KnuthGap(int size)
{
	int gap = 0;
	
	while((3 * gap) + 1 < size)
	{
		gap = (3 * gap) + 1;
	}
	
	return gap;
}

//Algoritmo 04: Shell Sort (Orden ascendente)
void ShellSort_Ascending(vector<int>& set)
{
	int size = set.size();
	int gap = ShellSort_KnuthGap(size);
	
	while(gap > 0)
	{
		for(int i = gap; i < size; i++)
		{
			int temp = set[i];
			int j = i;
			
			while(j >= gap && set[j - gap] > temp)
			{
				set[j] = set[j - gap];
				j -= gap;
			}
			
			set[j] = temp;
		}
		
		gap = ShellSort_KnuthGap(gap);
	}
}

//Algoritmo 04: Shell Sort (Orden descendente)
void ShellSort_Descending(vector<int>& set)
{
	int size = set.size();
	int gap = ShellSort_KnuthGap(size);
	
	while(gap > 0)
	{
		for(int i = gap; i < size; i++)
		{
			int temp = set[i];
			int j = i;
			
			while(j >= gap && set[j - gap] < temp)
			{
				set[j] = set[j - gap];
				j -= gap;
			}
			
			set[j] = temp;
		}
		
		gap = ShellSort_KnuthGap(gap);
	}
}

//Mezcla en orden ascendente de las divisiones (Algoritmo 05: Merge Sort)
void MergeSort_MergeAscending(vector<int>& set, int start, int middle, int end)
{
	int i = 0, j = 0, k = 0;
	int leftHalf = middle - start + 1;
	int rightHalf = end - middle;
	
	vector<int> leftElements(leftHalf);
	vector<int> rightElements(rightHalf);
	
	for(i = 0; i < leftHalf; i++)
	{
		leftElements[i] = set[start + i];
	}
	
	for(i = 0; i < rightHalf; i++)
	{
		rightElements[i] = set[middle + i + 1];
	}
	
	i = 0;
	k = start;
	
	while(i < leftHalf && j < rightHalf)
	{
		if(leftElements[i] < rightElements[j])
		{
			set[k] = leftElements[i];
			i++;
		}
		else
		{
			set[k] = rightElements[j];
			j++;
		}
		
		k++;
	}
	
	while(j < rightHalf)
	{
		set[k] = rightElements[j];
		k++;
		j++;
	}
	
	while(i < leftHalf)
	{
		set[k] = leftElements[i];
		k++;
		i++;
	}
}

//Mezcla en orden descendente de las divisiones (Algoritmo 05: Merge Sort)
void MergeSort_MergeDescending(vector<int>& set, int start, int middle, int end)
{
	int i = 0, j = 0, k = 0;
	int leftHalf = middle - start + 1;
	int rightHalf = end - middle;
	
	vector<int> leftElements(leftHalf);
	vector<int> rightElements(rightHalf);
	
	for(i = 0; i < leftHalf; i++)
	{
		leftElements[i] = set[start + i];
	}
	
	for(i = 0; i < rightHalf; i++)
	{
		rightElements[i] = set[middle + i + 1];
	}
	
	i = 0;
	k = start;
	
	while(i < leftHalf && j < rightHalf)
	{
		if(leftElements[i] > rightElements[j])
		{
			set[k] = leftElements[i];
			i++;
		}
		else
		{
			set[k] = rightElements[j];
			j++;
		}
		
		k++;
	}
	
	while(j < rightHalf)
	{
		set[k] = rightElements[j];
		k++;
		j++;
	}
	
	while(i < leftHalf)
	{
		set[k] = leftElements[i];
		k++;
		i++;
	}
}

//Algoritmo 05: Merge Sort (Orden ascendente)
void MergeSort_Ascending(vector<int>& set, int start, int end)
{
	if(start < end)
	{
		int middle = start + (end - start) / 2;
		MergeSort_Ascending(set, start, middle);
		MergeSort_Ascending(set, middle + 1, end);
		MergeSort_MergeAscending(set, start, middle, end);
	}
}

//Algoritmo 05: Merge Sort (Orden descendente)
void MergeSort_Descending(vector<int>& set, int start, int end)
{
	if(start < end)
	{
		int middle = start + (end - start) / 2;
		MergeSort_Descending(set, start, middle);
		MergeSort_Descending(set, middle + 1, end);		
		MergeSort_MergeDescending(set, start, middle, end);
	}
}

//Particion y ordenamiento ascendente (Algoritmo 06: Quick Sort)
int QuickSort_PartitionAscending(vector<int>& set, int start, int end)
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

//Particion y ordenamiento descendente (Algoritmo 06: Quick Sort)
int QuickSort_PartitionDescending(vector<int>& set, int start, int end)
{
	int pivot = set[start];
	int i = start + 1;
	
	for(int j = i; j <= end; j++)
	{
		if(set[j] > pivot)
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

//Algoritmo 06: Quick Sort (Orden ascendente)
void QuickSort_Ascending(vector<int>& set, int start, int end)
{
	if(start < end)
	{
		int pivot = QuickSort_PartitionAscending(set, start, end);
		QuickSort_Ascending(set, start, pivot - 1);
		QuickSort_Ascending(set, pivot + 1, end);
	}
}

//Algoritmo 06: Quick Sort (Orden descendente)
void QuickSort_Descending(vector<int>& set, int start, int end)
{
	if(start < end)
	{
		int pivot = QuickSort_PartitionDescending(set, start, end);
		QuickSort_Descending(set, start, pivot - 1);
		QuickSort_Descending(set, pivot + 1, end);
	}
}

//Arbol con valor maximo (Algoritmo 07: Heap Sort)
void MaxHeapify(vector<int>& set, int size, int current)
{
	int largest = current;
	int left = 2 * current + 1;
	int right = 2 * current + 2;
	
	if(left < size && set[left] > set[largest])
	{
		largest = left;
	}
	
	if(right < size && set[right] > set[largest])
	{
		largest = right;
	}
	
	if(largest != current)
	{
		int temp = set[current];
		set[current] = set[largest];
		set[largest] = temp;
		
		MaxHeapify(set, size, largest);
	}
}

//Arbol con valor minimo (Algoritmo 07: Heap Sort)
void MinHeapify(vector<int>& set, int size, int current)
{
	int smallest = current;
	int left = 2 * current + 1;
	int right = 2 * current + 2;
	
	if(left < size && set[left] < set[smallest])
	{
		smallest = left;
	}
	
	if(right < size && set[right] < set[smallest])
	{
		smallest = right;
	}
	
	if(smallest != current)
	{
		int temp = set[current];
		set[current] = set[smallest];
		set[smallest] = temp;
		
		MinHeapify(set, size, smallest);
	}
}

//Algoritmo 07: Heap Sort (Orden ascendente)
void HeapSort_Ascending(vector<int>& set)
{
	int size = set.size();
	
	for(int i = size / 2 - 1; i >= 0; i--)
	{
		MaxHeapify(set, size, i);
	}
	
	for(int i = size - 1; i > 0; i--)
	{
		int temp = set[0];
		set[0] = set[i];
		set[i] = temp;
		MaxHeapify(set, i, 0);
	}
}

//Algoritmo 07: Heap Sort (Orden descendente)
void HeapSort_Descending(vector<int>& set)
{
	int size = set.size();
	
	for(int i = size / 2 - 1; i >= 0; i--)
	{
		MinHeapify(set, size, i);
	}
	
	for(int i = size - 1; i > 0; i--)
	{
		int temp = set[0];
		set[0] = set[i];
		set[i] = temp;
		MinHeapify(set, i, 0);
	}
}

//Tiempo de ejecucion (Orden ascendente)
auto ExecutionTime_Ascending(int algorithm, vector<int>& set)
{
	switch(algorithm)
	{
		case 1: //Selection Sort
		{
			auto start = high_resolution_clock::now();
			SelectionSort_Ascending(set);
			auto end = high_resolution_clock::now();			
			return duration_cast<duration<double>>(end - start);
		}			
		
		case 2: //Bubble Sort
		{
			auto start = high_resolution_clock::now();
			BubbleSort_Ascending(set);
			auto end = high_resolution_clock::now();
			return duration_cast<duration<double>>(end - start);
		}
		
		case 3: //Insertion Sort
		{
			auto start = high_resolution_clock::now();
			InsertionSort_Ascending(set);
			auto end = high_resolution_clock::now();			
			return duration_cast<duration<double>>(end - start);
		}
		
		case 4: //Shell Sort
		{
			auto start = high_resolution_clock::now();
			ShellSort_Ascending(set);
			auto end = high_resolution_clock::now();			
			return duration_cast<duration<double>>(end - start);
		}
		
		case 5: //Merge Sort
		{
			auto start = high_resolution_clock::now();
			MergeSort_Ascending(set, 0, set.size() - 1);
			auto end = high_resolution_clock::now();			
			return duration_cast<duration<double>>(end - start);
		}
		
		case 6: //Quick Sort
		{
			auto start = high_resolution_clock::now();
			QuickSort_Ascending(set, 0, set.size() - 1);
			auto end = high_resolution_clock::now();			
			return duration_cast<duration<double>>(end - start);
		}
		
		case 7: //Heap Sort
		{
			auto start = high_resolution_clock::now();
			HeapSort_Ascending(set);
			auto end = high_resolution_clock::now();			
			return duration_cast<duration<double>>(end - start);
		}
	}
}

//Tiempo de ejecucion (Orden descendente)
auto ExecutionTime_Descending(int algorithm, vector<int>& set)
{
	switch(algorithm)
	{
		case 1: //Selection Sort
		{
			auto start = high_resolution_clock::now();
			SelectionSort_Descending(set);
			auto end = high_resolution_clock::now();
			return duration_cast<duration<double>>(end - start);
		}			
		
		case 2: //Bubble Sort
		{
			auto start = high_resolution_clock::now();
			BubbleSort_Descending(set);
			auto end = high_resolution_clock::now();
			return duration_cast<duration<double>>(end - start);
		}
		
		case 3: //Insertion Sort
		{
			auto start = high_resolution_clock::now();
			InsertionSort_Descending(set);
			auto end = high_resolution_clock::now();
			return duration_cast<duration<double>>(end - start);
		}
		
		case 4: //Shell Sort
		{
			auto start = high_resolution_clock::now();
			ShellSort_Descending(set);
			auto end = high_resolution_clock::now();
			return duration_cast<duration<double>>(end - start);
		}
		
		case 5: //Merge Sort
		{
			auto start = high_resolution_clock::now();
			MergeSort_Descending(set, 0, set.size() - 1);
			auto end = high_resolution_clock::now();			
			return duration_cast<duration<double>>(end - start);
		}
		
		case 6: //Quick Sort
		{
			auto start = high_resolution_clock::now();
			QuickSort_Descending(set, 0, set.size() - 1);
			auto end = high_resolution_clock::now();			
			return duration_cast<duration<double>>(end - start);
		}
		
		case 7: //Heap Sort
		{
			auto start = high_resolution_clock::now();
			HeapSort_Descending(set);
			auto end = high_resolution_clock::now();			
			return duration_cast<duration<double>>(end - start);
		}
	}
}

//Tiempo de ejecucion: Calcula el tiempo que se demora el algoritmo en ordenar el arreglo
auto ExecutionTime(int algorithm, vector<int>& set)
{
	if(order == 1)
	{
		return ExecutionTime_Ascending(algorithm, set);
	}
	else
	{
		return ExecutionTime_Descending(algorithm, set);
	}	
}

//Ejecucion de los algoritmos
void RunAlgorithms(int mode, vector<int> set, unordered_map<int, double>* results)
{
	for(int i = 0; i < numAlgorithms; i++)
	{
		if(mode == 1) //En el modo 1 no se requiere una copia del set
		{
			auto time_taken = ExecutionTime(i + 1, set);
			(*results)[i + 1] = time_taken.count(); //Agregar al map
		}
		else
		{
			vector<int> setCopy;
			setCopy.assign(set.begin(), set.end());
			auto time_taken = ExecutionTime(i + 1, set);
			(*results)[i + 1] = time_taken.count(); //Agregar al map
		}		
	}
}

//Imprimir informacion de una carrera y modo especificos
void PrintRaceInfo(int race, int mode)
{
	if(race == 1) //Carreras
	{
		cout << "\nCarrera por el tablero: ";
	}
	else if(race == 2)
	{
		cout << "\nCarrera por los caminos entre aldeas: ";
	}
	else if(race == 3)
	{
		cout << "\nCarrera por el renderizado de objetos: ";
	}
	
	if(mode == 1) //Modos
	{
		cout << "Modo ordenado" << endl;
	}
	else if(mode == 2)
	{
		cout << "Modo inversamente ordenado" << endl;
	}
	else if(mode == 3)
	{
		cout << "Modo aleatorios unicos" << endl;
	}
	else if(mode == 4)
	{
		cout << "Modo aleatorios duplicados" << endl;
	}
}

//Actualizacion de los datos del algoritmo ganador
void UpdateWinner(int currentIndex, string* winnerName, double* winnerTime, string algorithmName, double time)
{
	if(currentIndex == 0) //El algoritmo ubicado en la primera posicion comienza siendo el ganador
	{
		*winnerName = algorithmName;
		*winnerTime = time;
	}
	else if(*winnerTime > time)
	{
		*winnerName = algorithmName;
		*winnerTime = time;
	}
}

//Obtener el nombre de un algoritmo en el map de algoritmos a traves del indice
string GetAlgorithmNameByIndex(int index)
{
	for(const auto& pairAlg : algorithms)
	{
		if(index == pairAlg.second)
		{
			return pairAlg.first;
		}
	}
	
	return "NotFound";
}

//Obtener todos los algoritmos ganadores (en caso de que haya mas de uno que logro el mismo tiempo)
vector<string> GetAllWinners(double winnerTime, unordered_map<int, double> results)
{
	vector<string> winners;
	
	for(int i = 0; i < numAlgorithms; i++)
	{
		if(results[i + 1] == winnerTime) //El algoritmo actual tiene el mismo tiempo que el ganador
		{
			winners.push_back(GetAlgorithmNameByIndex(i + 1)); //Se agrega el nombre del algoritmo al vector de algoritmos ganadores
		}
	}
	
	return winners;
}

//Mostrar los algoritmos ganadores y el tiempo de ejecucion
void ShowWinners(vector<string> winners, double time)
{
	if(winners.size() == 1)
	{
		cout << "El ganador es: " << winners[0] << " un tiempo de " << time << " segundos" << endl;
	}
	else
	{
		cout << "Los ganadores son: ";
		
		for(int i = 0; i < winners.size(); i++)
		{
			if(i == winners.size() - 1) //Ultimo elemento
			{
				cout << winners[i];
			}
			else if(i == winners.size() - 2) //Penultimo elemento
			{
				cout << winners[i] << " y ";
			}
			else
			{
				cout << winners[i] << ", ";
			}
		}
		
		cout << ", un tiempo de " << time << " segundos" << endl;
	}
}

//Imprimir los resultados obtenidos en las carreras
void PrintResults(unordered_map<int, double> results)
{
	double winnerTime = 0;
	string winnerName;
	
	for(int i = 0; i < numAlgorithms; i++) //Se recorre el map y se muestran los datos
	{
		string algorithmName = GetAlgorithmNameByIndex(i + 1);
		double time = results[i + 1];
		
		cout << i + 1 << ". " << algorithmName << ", " << time << endl;
		UpdateWinner(i, &winnerName, &winnerTime, algorithmName, time);
	}
	
	ShowWinners(GetAllWinners(winnerTime, results), winnerTime);
}

//Obtener el set de datos que se va a trabajar dependiendo del modo
vector<int> GetSetByMode(int race, int mode)
{
	if(mode == 1) //Modo 01: Set de datos ordenados
	{
		return (race == 1 ? ordered : GetTruncatedCommonDataSet(race, true));
	}
	else if(mode == 2) //Modo 02: Set de datos inversamente ordenado
	{
		return (race == 1 ? inverselyOrdered : GetTruncatedCommonDataSet(race, false));
	}
	else if(mode == 3) //Modo 03: Set de datos aleatorios unicos
	{
		return (race == 1 ? GenerateRandomDataSet(true, race01Range) :
				race == 2 ? GenerateRandomDataSet(true, race02Range) :
							GenerateRandomDataSet(true, race03Range));
	}
	else //Modo 04: Set de datos aleatorios duplicados
	{
		return (race == 1 ? GenerateRandomDataSet(false, race01Range) :
				race == 2 ? GenerateRandomDataSet(false, race02Range) :
							GenerateRandomDataSet(false, race03Range));
	}
}

//Competicion de los algoritmos en cada carrera y modo correspondiente
void Competition(int race, int mode)
{
	vector<int> set = GetSetByMode(race, mode);	
	unordered_map<int, double> results; //Map: Numero de algoritmo (Key) --- Tiempo de ejecucion (Value)
	RunAlgorithms(mode, set, &results);
	PrintRaceInfo(race, mode);
	PrintResults(results);
}

//Carreras de algoritmos
void Races()
{
	//Carrera 01: Carrera por el tablero
	//Carrera 02: Carrera por la determinacion de caminos
	//Carrera 03: Carrera por el renderizado
	
	for(int i = 0; i < races; i++)
	{
		for(int j = 0; j < modes; j++)
		{
			Competition(i + 1, j + 1);
		}
	}
}

void Print(vector<int> set)
{
	for(const auto& val : set)
	{
		cout << val << endl;
	}
}

//Zona de pruebas
void TestFunction()
{
	srand(time(NULL));
	vector<int> random;
	
	StartMessage();
//	GenerateRanges();
	InitializeAlgorithmsMap();
	GenerateCommonDataSet();
	
	/*
	for(int i = 0; i < 20000; i++)
	{
		int num = rand() % 20 + 1;
		ordered.push_back(num);
	}*/
	
	for(int i = 0; i < 20; i++)
	{
		int num = rand() % 20 + 1;
		random.push_back(num);
	}
	
	//cout << "\n\tOriginal random set:" << endl;
	//Print(inverselyOrdered);
	Print(random);
	
	cout << "\n\nAlgoritmo...\n\n";
	//SelectionSort_Ascending(random);
	//SelectionSort_Descending(random);
	//BubbleSort_Ascending(random);
	//BubbleSort_Descending(random);
	//InsertionSort_Ascending(random);
	//InsertionSort_Descending(random);
	//ShellSort_Ascending(inverselyOrdered);
	//ShellSort_Descending(inverselyOrdered);
	
	auto start = high_resolution_clock::now();
//	MergeSort_Ascending(random, 0, random.size() - 1);
//	QuickSort(random, 0, random.size() - 1);
//	QuickSort(inverselyOrdered, 0, inverselyOrdered.size() - 1);
	QuickSort_Descending(random, 0, random.size() - 1);
//	HeapSort_Descending(ordered);
	auto end = high_resolution_clock::now();

	auto time_taken = duration_cast<duration<double>>(end - start);
	cout << "\n\tTiempo: " << time_taken.count() << endl;
	Print(random);
}

void PrintInLine(vector<int> set)
{
	cout << endl;
	cout << '\t';
	
	for(const auto& i : set)
	{
		cout << i << " ";
	}
}

