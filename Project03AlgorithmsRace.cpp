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

vector<int> ordered;
vector<int> inverselyOrdered;

void StartMessage(int*); //Eleccion de ordenamiento de datos
void GenerateRanges(); //Generacion de rangos

void GenerateCommonDataSet(/*vector<int>& ordered, vector<int>& inverselyOrdered*/)
{
	cout << "\nGenerando...";
	
	int max = 0;
	
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
	
	for(int i = 0; i < max; i++)
	{
		ordered.push_back(i + 1);
		inverselyOrdered.push_back(max - i);
	}
	
	cout << "\nSet de datos generado";
}

void SelectionSort(vector<int>& arr)
{
	int n = arr.size();
	
	for(int i = 0; i < n ; ++i)
	{
		for(int j = i; j < n ; ++j)
		{
			if(arr[j] < arr[i])
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

double getResultFromAlg(vector<int>& arr, int option)
{
	time_t start, end;
	double time_taken;
	time(&start);
	ios_base::sync_with_stdio(false);
	
	SelectionSort(arr);
	time(&end);
	time_taken = double(end - start);
	return time_taken;
}

auto myFunction(int algorithm, vector<int> arr = ordered)
{	
	switch(algorithm)
	{
		case 1: //Selection Sort
		{
			auto start = high_resolution_clock::now();
			SelectionSort(arr);
			auto end = high_resolution_clock::now();
			
			return duration_cast<duration<double>>(end - start);
		}
			
		default:
		{
			auto start = high_resolution_clock::now();
			auto end = high_resolution_clock::now();
			
			return duration_cast<duration<double>>(end - end);
		}	
	}
}

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

void Race01()
{
	//Modo 1: Ordenado
	
	//AGREGAR UN MAP NumAlgorithm (Key) --- Time (Value)
	unordered_map<int, double> results;
	
	for(int i = 0; i < numAlgorithms; i++)
	{
		auto time_taken = myFunction(i + 1);
		
		//Agregar al map
		results[i + 1] = time_taken.count();
	}
	
	int place = 1;
	double winnerTime = 0;
	string winnerName;
	
	cout << "\nCarrera por el tablero: Modo ordenado" << endl;
	
	//Recorrer el map y mostrar los datos
	for(const auto& pairRes : results)
	{
		string algorithmName;
		double time = pairRes.second;
		
		for(const auto& pairAlg : algorithms)
		{
			if(pairRes.first == pairAlg.second)
			{
				algorithmName = pairAlg.first;
			}
		}
		
		cout << place << ". " << algorithmName << ", " << time << endl;
		
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
		
		place++;
	}
	
	cout << "El ganador es: " << winnerName << " un tiempo de " << winnerTime << " segundos" << endl;
}

int main(int argc, char* argv[])
{
	int option = 0;
	
	StartMessage(&option);
	GenerateRanges();
	InitializeAlgorithmsMap();
	
	/*race01Range = 20;
	race02Range = 15;
	race03Range = 10;*/
	
	//GenerateCommonDataSet(ordered, inverselyOrdered);
	GenerateCommonDataSet();
	Race01();
	
	/*for(const auto& i : ordered)
	{
		cout << i << endl;
	}
	
	for(const auto& i : inverselyOrdered)
	{
		cout << i << endl;
	}
	
	vector<int> arr1Ord;
	vector<int> arr1Inv;
	vector<int> arr2Ord;
	vector<int> arr2Inv;
	
	arr1Ord.assign(ordered.begin(), ordered.begin() + race02Range);
	arr2Ord.assign(ordered.begin(), ordered.begin() + race03Range);
	arr1Inv.assign(ordered.end() - race02Range, ordered.end());
	arr2Inv.assign(ordered.end() - race03Range, ordered.end());
	
	cout << "\nArreglo 2 ordenado:\n";
	
	for(const auto& i : arr1Inv)
	{
		cout << i << endl;
	}
	
	cout << "\nArreglo 3 ordenado:\n";
	
	for(const auto& i : arr2Inv)
	{
		cout << i << endl;
	}*/
	
	if(option == 1)
	{
		cout << "MODO ASCENDENTE";
	}
	else
	{
		cout << "MODO DESCENDENTE";
	}
	
	vector<int> arr01;
	//GenerateDataSet(arr01);
	
	//auto time_taken = myFunction(arr01);
	//cout << "Execution time: " << time_taken.count() << " seconds" << endl;
	return 0;

	/*
	cout << "Generando set de datos: " << endl;
	
	for(int i = 0; i < amount ; ++i)
	{
		arrSorted.push_back(i+1);
		arrReverse.push_back(amount-i);
		
		if ( i == 0 )
		{
			random_value = 1 + rand() % (amount);
			arr.push_back(random_value);
		}
		else
		{
			random_value = 1 + rand() % (amount);
			arr.push_back(random_value);
		}
	}
		
	unordered_map<string, double> results;
	results["SeleciontSort"] = getResultFromAlg(arr);
	vector<int> arr1,arr2;
	arr1.assign(arr.begin(), arr.end());
	arr2.assign(arr.begin(), arr.end());
	
	int id = 1;
	
	for(const auto& pair : results)
	{
		const string& key = pair.first;
		double value = pair.second;
		cout << id << ". " << key << ", " << fixed << value << setprecision(5)
		<< endl;
		id++;
	}
	
	return 0;
	*/
}

//Mensaje de inicio: El usuario decide si desea que el orden de los sets de datos sea ascendente o descendente
void StartMessage(int* option)
{
	do
	{
		cout << "Carreras de algoritmos\n1. Ascendente.\n2. Descendente\nOpcion elegida: ";
		cin >> *option;
		
		if(*option != 1 && *option != 2)
		{
			cout << "\n\t* Error *\n" << endl;
		}
	}
	while(*option != 1 && *option != 2);	
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
	
	cout << "\n\tRangos:\n\t- Carrera 1: " << race01Range << "\n\t- Carrera 2: " << race02Range << "\n\t- Carrera 3: " << race03Range << endl;
}

