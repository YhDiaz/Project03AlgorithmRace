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

/*

	SETS DE DATOS COMUNES:
		
		SET DE DATOS ORDENADO (DIMENSION MAXIMA: DADA POR LA CARRERA TABLERO DE PUNTAJE)
		SET DE DATOS INVERSAMENTE ORDENADO (DIMENSION MAXIMA: DADA POR LA CARRERA TABLERO DE PUNTAJE)

	CARRERA 1: TABLERO DE PUNTAJE
		
		RANGO: 90.000 - 100.000
		
		MODO 1: SET DE DATOS ORDENADO (COPIAS: NINGUNA; DIMENSION: DIMENSION MAXIMA)
		MODO 2: SET DE DATOS INVERSAMENTE ORDENADO (COPIAS: 7; DIMENSION: DIMENSION MAXIMA)
		
		GENERACION DE SETS DE DATOS ALEATORIO Y ALEATORIO DUPLICADO (CON LAS MISMAS DIMENSIONES ANTERIORES)
		
		MODO 3: SET DE DATOS ALEATORIO (COPIAS: 7)
		MODO 4: SET DE DATOS ALEATORIO DUPLICADO (COPIAS: 7)
		
	CARRERA 2: DETERMINACION DE CAMINO ENTRE ALDEAS
		
		RANGO: 50.000 - 70.000
		
		MODO 1: SET DE DATOS ORDENADO (COPIAS: NINGUNA; DIMENSION: DIMENSION MAXIMA TRUNCADA)
		MODO 2: SET DE DATOS INVERSAMENTE ORDENADO (COPIAS: 7; DIMENSION: DIMENSION MAXIMA TRUNCADA)
		
		GENERACION DE SETS DE DATOS ALEATORIO Y ALEATORIO DUPLICADO (CON LAS MISMAS DIMENSIONES ANTERIORES)
		
		MODO 3: SET DE DATOS ALEATORIO (COPIAS: 7)
		MODO 4: SET DE DATOS ALEATORIO DUPLICADO (COPIAS: 7)
		
	CARRERA 3: RENDERIZADO DE OBJETOS
	
		RANGO: (500 - 1000) x15
		
		MODO 1: SET DE DATOS ORDENADO (COPIAS: NINGUNA; DIMENSION: DIMENSION MAXIMA TRUNCADA)
		MODO 2: SET DE DATOS INVERSAMENTE ORDENADO (COPIAS: 7; DIMENSION: DIMENSION MAXIMA TRUNCADA)
		
		GENERACION DE SETS DE DATOS ALEATORIO Y ALEATORIO DUPLICADO (CON LAS MISMAS DIMENSIONES ANTERIORES)
		
		MODO 3: SET DE DATOS ALEATORIO (COPIAS: 7)
		MODO 4: SET DE DATOS ALEATORIO DUPLICADO (COPIAS: 7)

*/

int race01Range = 0;
int race02Range = 0;
int race03Range = 0;
int numAlgorithms = 7;
unordered_map<string, int> algorithms;
int order = 0; //1: Ascendente; 2: Descendente

vector<int> ordered;
vector<int> inverselyOrdered;

void TestFunction();

void StartMessage(); //Eleccion de ordenamiento de datos
void GenerateRanges(); //Generacion de rangos
void InitializeAlgorithmsMap(); //Inicializacion del mapa de algoritmos
void GenerateCommonDataSet(); //Sets de datos comunes
void SelectionSort_Ascending(vector<int>&); //Algoritmo 01: Selection Sort (Orden ascendente)
void SelectionSort_Descending(vector<int>&); //Algoritmo 01: Selection Sort (Orden descendente)
void BubbleSort_Ascending(vector<int>&); //Algoritmo 02: Bubble Sort (Orden ascendente)
void BubbleSort_Descending(vector<int>&); //Algoritmo 02: Bubble Sort (Orden descendente)
void InsertionSort_Ascending(vector<int>&); //Algoritmo 03: Insertion Sort (Orden ascendente)
void InsertionSort_Descending(vector<int>&); //Algoritmo 03: Insertion Sort (Orden descendente)

int ShellSort_KnuthGap(int); //Secuencia de Knuth para el algoritmo 04
void ShellSort_Ascending(vector<int>&); //Algoritmo 04: Shell Sort (Orden ascendente)
void ShellSort_Descending(vector<int>&); //Algoritmo 04: Shell Sort (Orden descendente)

vector<int> MergeSort_Merge(vector<int> left, vector<int> right)
{
	vector<int> merged;
	
	while(!left.empty() && !right.empty())
	{
		if(left[0] <= right[0])
		{
			merged.push_back(left[0]);
			left.erase(left.begin());
		}
		else
		{
			merged.push_back(right[0]);
			right.erase(right.begin());
		}
	}
	
	for(const auto& val : left)
	{
		merged.push_back(val);
	}
	
	for(const auto& val : right)
	{
		merged.push_back(val);
	}
	
	return merged;
}

vector<int> MergeSort(vector<int>& set)
{
	if(set.size() <= 1)
	{
		return set;
	}
	
	int mid = set.size() / 2;
	
	vector<int> leftHalf, rightHalf;
	leftHalf.assign(set.begin(), set.begin() + mid);
	rightHalf.assign(set.end() - mid, set.end());	
	
	vector<int> left = MergeSort(leftHalf);
	vector<int> right = MergeSort(rightHalf);
	return MergeSort_Merge(left, right);
}

void QuickSort(vector<int>& set)
{
	
}

void HeapSort(vector<int>& set)
{
	
}


auto ExecutionTime_Ascending(int, vector<int>&); //Tiempo de ejecucion (Orden ascendente)
auto ExecutionTime_Descending(int, vector<int>&); //Tiempo de ejecucion (Orden descendente)
auto ExecutionTime(int, vector<int>& = ordered); //Tiempo de ejecucion del algoritmo
void Race01(); //Carrera 01: Tablero de puntaje
void Races(); //Carreras

int main(int argc, char* argv[])
{
	/*
	StartMessage();
	GenerateRanges();
	InitializeAlgorithmsMap();
	GenerateCommonDataSet();	
	*/
	StartMessage();
	InitializeAlgorithmsMap();
	//TestFunction();
	GenerateCommonDataSet();
	
	Races();
	/*Race01();
	
	if(order == 1)
	{
		cout << "MODO ASCENDENTE";
	}
	else
	{
		cout << "MODO DESCENDENTE";
	}*/
	
	return 0;
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
}

//Generacion de rangos: Se generan los rangos de datos que tendra cada carrera
void GenerateRanges()
{
	srand(time(NULL));
	
	//FORMULA PARA OBTENCION DE UN VALOR DENTRO DEL RANGO
	//RANGO: min --- max
	//FORMULA: rand() % (max - min) + min
	
	race01Range = rand() % (100000 - 90000) + 90000;
	race02Range = rand() % (70000 - 50000) + 50000;
	race03Range = rand() % (7500 - 15000) + 7500;
	
	race01Range = 20;
	race02Range = 15;
	race03Range = 10;
	
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

//Generacion de sets de datos comunes: Set de datos comunes para todas las carreras
void GenerateCommonDataSet()
{
	cout << "\nGenerando...";
	
	int max = 0;
	
	//Obtencion del rango mayor para usarlo como dimension maxima de los sets de datos comunes
	if(race01Range > race02Range)
	{
		if(race01Range > race03Range)
		{
			max = race01Range;
		}
		else
		{
			max = race03Range;
		}
	}
	else if(race02Range > race03Range)
	{
		max = race02Range;
	}
	else
	{
		max = race03Range;
	}
	
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
	
	cout << "\nSet de datos generado";
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
			
		default:
		{
			auto time = high_resolution_clock::now();			
			return duration_cast<duration<double>>(time - time);
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
			
		default:
		{
			auto time = high_resolution_clock::now();			
			return duration_cast<duration<double>>(time - time);
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

//Carrera 01: Tablero de puntaje
void Race01()
{
	//Modo 1: Ordenado
	
	//AGREGAR UN MAP NumAlgorithm (Key) --- Time (Value)
	unordered_map<int, double> results;
	
	for(int i = 0; i < numAlgorithms; i++)
	{
		auto time_taken = ExecutionTime(i + 1);
		
		//Agregar al map
		results[i + 1] = time_taken.count();
	}
	
	double winnerTime = 0;
	string winnerName;
	
	cout << "\nCarrera por el tablero: Modo ordenado" << endl;
	
	//Recorrer el map y mostrar los datos
	for(int i = 0; i < 7; i++)
	{
		string algorithmName;
		double time = results[i + 1];
		
		for(const auto& pairAlg : algorithms)
		{
			if(i + 1 == pairAlg.second)
			{
				algorithmName = pairAlg.first;
			}
		}
		
		cout << i + 1 << ". " << algorithmName << ", " << time << endl;
		
		if(winnerTime == 0)
		{
			winnerName = algorithmName;
			winnerTime = time;
		}
		else if(winnerTime > time)
		{
			winnerName = algorithmName;
			winnerTime = time;
		}
	}
	
	cout << "El ganador es: " << winnerName << " un tiempo de " << winnerTime << " segundos" << endl;
	
	//Modo 2: Inversamente ordenado
	
	//Modo 3: Aleatorios unicos
	
	//Modo 4: Aleatorios duplicados
}

void Race02()
{
	
}

void Race03()
{
	
}

void Races()
{
	Race01(); //Carrera por el tablero
	Race02(); //Carrera por la determinacion de caminos
	Race03(); //Carrera por el renderizado
}

//Funcion de pruebas
void TestFunction()
{
	srand(time(NULL));
	vector<int> random;
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
	
	cout << "\n\nAlgoritmo...\n\n";
	//SelectionSort_Ascending(ordered);
	//SelectionSort_Descending(ordered);
	//BubbleSort_Ascending(ordered);
	//BubbleSort_Descending(ordered);
	//InsertionSort_Ascending(ordered);
	//InsertionSort_Descending(ordered);
	//ShellSort(ordered);
	//mergeSort(ordered, 0, ordered.size());
	//vector<int> receptor = MergeSort(ordered);
	
	/*for(const auto& i : receptor)
	{
		cout << i << endl;
	}*/
	
	for(int i = 0; i < 4; i++)
	{
		vector<int> randomCopy = random;
		auto time = ExecutionTime(i + 1, randomCopy);
		
		cout << "\nAlgoritmo " << i + 1 << endl;
		for(const auto& i : randomCopy)
		{
			cout << i << endl;
		}
	}	
	
	for(const auto& i : ordered)
	{
		cout << i << endl;
	}
}

