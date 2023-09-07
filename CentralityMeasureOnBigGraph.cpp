#include <iostream>			
#include <vector>			
#include <stdio.h>			
#include <string.h>			
#include <sstream>			
#include <string>
#include <typeinfo>			
#include <time.h>				
#include <fstream>			// Opening and reading .tsv Files		
#include "Functions.cpp" 	// Functions

int main()
{		
	clock_t start = clock();							
	Crea_Film_Attori();							// Creating Film_Attori Vector
	clock_t end = clock();
	cout << "\nFilm_Attori Pronto in:" << endl;
	printf("  %f secondi \n\n", ((double)(end - start)) / CLOCKS_PER_SEC);
	clock_t start1 = clock();
	Crea_Attori_Film();							// Creating Attori_Film Vector
	clock_t end1 = clock();
	cout << "\nAttori_Film Pronto in:" << endl;
	printf("  %f secondi \n\n", ((double)(end1 - start1)) / CLOCKS_PER_SEC);
	
	clock_t start2 = clock();
	Crea_Is_for_Adult();							// Creating Is_for_Adult
	clock_t end2 = clock();
	cout << "\nIs_for_Adult Pronto in:" << endl;
	printf("  %f secondi \n\n", ((double)(end2 - start2)) / CLOCKS_PER_SEC);
		
	clock_t start3 = clock();
	Crea_Nomi_Attori(); 							// Creating Nomi_Attori
	clock_t end3 = clock();
	cout << "\nCrea_Nomi_Attori Pronto in:" << endl;
	printf("  %f secondi \n\n", ((double)(end3 - start3)) / CLOCKS_PER_SEC);
	
	clock_t start4 = clock();
	Crea_Lista_Adiacenza();						// Creating Adjacency list
	clock_t end4 = clock();
	cout << "\nCrea_Lista_Adiacenza Pronto in:" << endl;
	printf("  %f secondi \n\n", ((double)(end4 - start4)) / CLOCKS_PER_SEC);

	clock_t start5 = clock();
	Sottografo_Principale_DFS_Iterativo(136);	// Creating sub-graph containing famous actors to avoid isolated graph - Starting 136 == Johnny Depp
	clock_t end5 = clock();
	cout << "\nSottografo_Principale Pronto in:" << endl;
	printf("  %f secondi \n\n", ((double)(end5 - start5)) / CLOCKS_PER_SEC);
	
			// Degree Centrality Measure //

	for(auto j = 0; j < 100; j++)					
  	{
    		Classifica[1][j] = 0;
  	}
  	
  	Crea_Tabella_Gradi_Sottografo();					// Creating Ranking using Degree Exact Centrality Measure
  	
  	for(auto j = 0; j < 100; j++)						
  	{
  	  cout << Nomi_Attori[conv[Classifica[0][j]]] << endl;
  	  cout << Classifica[1][j] << endl;
  	}
  	
    return 0;
}