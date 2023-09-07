#include <iostream>		
#include <vector>			
#include <stdio.h>			
#include <sstream>			
#include <string>			
#include <fstream>		
#include <typeinfo>			
#include <list>			

using namespace std;

constexpr auto MAXN = 16000000;		          // We are using this constant to not exceed in memory
constexpr auto SUBG = 1200000;              // We are using this constant since it is big enough on the sub-Graph
vector<int> Film_Attori[MAXN];			        // Columns: Actors/Actress - Rows: Films where the Actor/Actress partecipated
vector<int> Attori_Film[MAXN];   		        // Columns: Film - Rows: Actors/Actress who partecipated in the film
int Is_for_Adult[MAXN];         		        // Columns: Films - Rows: Boolean representing if the film is porn or not
vector<int> adj[MAXN];				              // Graph Adjacency list
string Nomi_Attori[MAXN];                   // Columns: Actor/Actress Code - Rows: name
bool Visitato[MAXN];                      	
int conv[SUBG];                          	  
vector<int> sub_adj[SUBG];               	  // Sub-Graph Adjacency list
int inv_conv[MAXN];                      	  
int Tabella_Gradi_Sottografo[2][SUBG];		  
int Classifica[2][100];               

//* Print Functions *//

void Stampa_Vettore(vector<int> v)			 
{
  auto n = v.size();
  if (n > 0)
  {
    cout << "[";
    if (n == 1)
      cout << v[0];
    else
    {
      for (auto i = 0; i < n; i++)
      {
        if (i == n - 1)
          cout << v[i];
        else
          cout << v[i] << ",";
      }
    }
    cout << "]" << endl;
  }
  else
    cout << "[]" << endl;
  return;
}

void Conv_Stampa_Vettore(vector<int> v) 		
{
  auto n = v.size();
  if (n > 0)
  {
    cout << "[";
    if (n == 1)
      cout << conv[v[0]];
    else
    {
      for (auto i = 0; i < n; i++)
      {
        if (i == n - 1)
          cout << conv[v[i]];
        else
          cout << conv[v[i]] << ",";
      }
    }
    cout << "]" << endl;
  }
  else
    cout << "[]" << endl;
  return;
}


//* Function to create Film_Attori from .tsv *//

void Crea_Film_Attori()  				
{

  string line;						

  ifstream fileaperto("name.basics1.tsv");		

  if (fileaperto.is_open())				
  {

    while (getline(fileaperto, line))			
    {
      
      string tab = "\t", nline = "\n", virgola = ",";	
      int k, h = 1;					
      k = line.find(tab);				
      string attore = line.substr(2, k-2);   		
      int codice_attore = atoi(attore.c_str()); 	
      if (codice_attore < (MAXN - 1))     
      {      string name;						
	      string aux1 = line, aux2;			
	      aux2 = aux1.substr(k + 1, line.length());	
	      aux1 = aux2;					
	      h = aux2.find(tab);				
	      string professioni;				
	      professioni = aux2.substr(0, h); 		
	      
	      string films;					

	      if (professioni.find("actor") != string::npos || professioni.find("actress") != string::npos) 
	      { 
		k = aux1.find(tab);				
		aux2 = aux1.substr(k + 1, line.length());	
		h = aux2.find(nline);				
		films = aux2.substr(0, h);			

		while (films.length() >= 9)			
		{ 

		  string film;					
		  int film_code = 0;				

		  if (films.find(virgola) != string::npos)	
		  { 
		    k = films.find(virgola);			
		    film = films.substr(2, k - 2);		
		    film_code = atoi(film.c_str());		
		    if (film_code < (MAXN - 1)) 
		    {
		      Film_Attori[codice_attore].push_back(film_code);	
		    }
		    films = films.substr(k + 1, h);		
		  }
		  else						
		  { 
		    film = films.substr(2, h);			
		    film_code = atoi(film.c_str());		
		    if (film_code < (MAXN - 1)) 
		    {
		      Film_Attori[codice_attore].push_back(film_code);	
		    }
		    films = "";			
		  }
		}
	      }
        }
    }

    fileaperto.close();
  }

  return;
}

//* Function to create Attori_Film from .tsv *//

void Crea_Attori_Film()  				
{
  string line;

  ifstream fileaperto("title.principals1.tsv");

  if (fileaperto.is_open())
  {

    while (getline(fileaperto, line))
    {
       int film_code;
       int k,h,t;					
       string nline = "\n", tab = "\t";
       k = line.find(tab);
       string string_film_code = line.substr(2,k-2);	
       film_code = atoi(string_film_code.c_str());	
       if (film_code < (MAXN - 1)) 
       {
		string code_actor_string;			
		string aux1 = line, aux2;			         
		aux2 = aux1.substr(k + 1, line.length());
		aux1 = aux2;
		t = aux1.find(tab);
		code_actor_string = aux1.substr(2,t-2);        
		int code_actor = atoi(code_actor_string.c_str());
		if (code_actor < (MAXN - 1)) 
		{
			string is_actor;				
			k = aux1.find(tab);
			aux2 = aux1.substr(k + 1, line.length());
			aux1 = aux2;
			h = aux2.find(nline);
			is_actor = aux2.substr(0, h);                	

			if(is_actor == "actor" || is_actor == "actress")  
			{
			  Attori_Film[film_code].push_back(code_actor);
			}
		}
	}
    }

    fileaperto.close();
  }
  
  return;
}

//* Function to create Is_for_Adult from .tsv *//

void Crea_Is_for_Adult()  				
{

  for(int k = 0; k < MAXN; k++)			
  {
    Is_for_Adult[k] = 0;
  }
  
  string line;

  ifstream fileaperto("title.basics1.tsv");

  if (fileaperto.is_open())
  {
    while (getline(fileaperto, line))
    {

      int k, h, film_code;				
      string aux1 = line, aux2, film;
      string nline = "\n", tab = "\t";
      k = line.find(tab);
      film = line.substr(2, k - 2);			
      film_code = atoi(film.c_str());			
      if (film_code < (MAXN - 1)) 
      {
	      aux1 = line.substr(k + 1, line.length());
	      string adult_code;
	      adult_code = aux1.substr(0, 1);			
	      
	      if(adult_code == "1"){				
		Is_for_Adult[film_code] = 1;
	      }
      }
    }
    fileaperto.close();   
  }
  return;
}

//* Function to create Nomi_Attori from .tsv *//

void Crea_Nomi_Attori()  					
{
  string line;

  ifstream fileaperto("name.basics.1.tsv");

  if (fileaperto.is_open())
  {

    while (getline(fileaperto, line))
    {

      int k, h;
      int code;
      string tab = "\t", nline = "\n";
      k = line.find(tab);
      string act = line.substr(2, k-2);   		
      int act_code = atoi(act.c_str()); 		
      if (act_code < (MAXN - 1))
      {      
	      string name;					
	      string aux1 = line, aux2;
	      aux2 = aux1.substr(k + 1, line.length());
	      aux1 = aux2;
	      h = aux2.find(tab);
	      name = aux2.substr(0, h);         		
	      aux2 = aux1.substr(h + 1, line.length());
	      aux1 = aux2;
	      h = aux2.find(nline);
	      string profession;				
	      profession = aux1.substr(0, h);  		
	      if (profession.find("actor") != string::npos || profession.find("actress") != string::npos)
	      { 
		Nomi_Attori[act_code] = name;

	      }
      }
    }
    
    fileaperto.close();
  }
  return;
}

//* Function to create the adjacency list of the graph *//

void Crea_Lista_Adiacenza()  					
{
  for(auto c = 0; c < MAXN; c++)     				
  {
    auto n = Film_Attori[c].size();   				
    for(auto i = 0; i < n; i++)				
    {
      if(Is_for_Adult[Film_Attori[c][i]] == 0)			
      {
        auto m = Attori_Film[Film_Attori[c][i]].size(); 	

        for(auto j = 0; j < m; j++)  				
        {
          if(c != Attori_Film[Film_Attori[c][i]][j])  		
          {
            auto l = adj[c].size();				
            auto k = 0;            				
            if(l == 0){
              adj[c].push_back(Attori_Film[Film_Attori[c][i]][j]);          
            }
            else
            {
              while((k < l) && (adj[c][k] != Attori_Film[Film_Attori[c][i]][j])) 
              {
                if(k == l-1){					
                  adj[c].push_back(Attori_Film[Film_Attori[c][i]][j]);
                }
                k++;
              }
            }
          }
        }

      }
    }
  }
 
  return;
}

//* Iterative DFS to create the adjacency list of the sub-graph *//

void Sottografo_Principale_DFS_Iterativo(int v)
{
  for (auto u=0; u < MAXN; u++)
  {
    Visitato[u] = false;				
  }

  vector<int> stack;                    		
  stack.push_back(v);                   		
  int i = 0;						
 
  while (!stack.empty())                		
  {
    int s = stack.size();				
    v = stack[s-1];					
    stack.pop_back();					

    if(Visitato[v] == false)            		
    {
      Visitato[v] = true;				
      conv[i] = v;					
      inv_conv[v] = i;					
      i++;						
      s = adj[v].size();				
      for (auto j = 0; j < s; j++)			
      {
        int u = adj[v][j];				

        if (Visitato[u] == false) stack.push_back(u);	
        else if(Visitato[u] == true)      		
        {
          sub_adj[inv_conv[u]].push_back(inv_conv[v]);
          sub_adj[inv_conv[v]].push_back(inv_conv[u]);
        }
      }
    }
  }
  return;
}

//* Calcuating Degree Exact Centrality Measure of the sub-graph *//

void Scambia(int arr[100], int pos, int x)		
{
  for(auto i = pos; i < 99; i++)
  {
    int aux = arr[i];					
    arr[i] = x;    
    x = aux;
  }
  arr[99] = x; 

  return;
}

void Classifica_Primi_100_Sottografo(int c, int sx, int dx, int arr[2][SUBG])
{
  while(sx < dx)
  {
    if(arr[1][c] > Classifica[1][(sx+dx)/2])  dx = (sx+dx)/2; 
    
    else  sx = (sx+dx)/2 +1;
  }
  
  Scambia(Classifica[1], sx, arr[1][c]);		
  Scambia(Classifica[0], sx, arr[0][c]);

  return;
}


void Crea_Tabella_Gradi_Sottografo()  			
{
  
  for(auto c = 0; c < SUBG; c++)
  {
    auto s = sub_adj[c].size();
    Tabella_Gradi_Sottografo[0][c] = c;
    Tabella_Gradi_Sottografo[1][c] = s;
  }

 
  for(auto c = 1; c < SUBG; c++)
  {
    if(Tabella_Gradi_Sottografo[1][c] > Classifica[1][99])  Classifica_Primi_100_Sottografo(c, 0, 99, Tabella_Gradi_Sottografo);
  }

  return;
}