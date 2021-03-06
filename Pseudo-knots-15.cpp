//Author: Louis Petingi 08/06/14
//to detect pseudo-graph in dual graphs
//Designed and written by Louis Petingi. 
//we are reading AdJ Matrix thus we convert to Linked List DS
//Input is a two-dimensional array representing the adjacency list corresponding to a dual-graph represwntation of a 2D RNA.
//RAG database at New York University under the team lead by  Tamar Schlick.

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <stack>

using namespace std;


//node
struct edge
{ int v1;
  int v2;
};
struct node
{
    int vertex;
	int binary;
	float rel;
    node * next;
	
};
int nods =0;
int motif_counter= 0;
int edgs =0;
int dim = 0;
int iterat = 0;
int term = 0;
stack<edge> mystack;
stack<edge> mystack1;
bool * Visited;
int *d_cmpnt; 
node * glovalnode;
int  weight[100][100];
ifstream infile;
ofstream outfile;

 bool cycles=false;// determine if a graph has cycles.
 
 

class Graph {
private:
	int n;
    int e; // number of edges
	float A;
	int B;
	int b_num1;
	int b_low1;

	int * b_num;
	int * b_low;
	int D;
	edge x;
	int terminal;
	long counter;
	int * temp;
	
	bool * T;
	int * L;
	int * father;
	node * w;
    edge* edge_irrel;
    int * Ls;
    int * Lt;
public:  
	 node * headnodes;
	 node * headnodes_A;
	 Graph (int nods, int edgs, int dim, int term) 
	// construtor
	{  
		//infile.open("C:/users/petingi/desktop/RnaDv/V7adj.txt");
	    terminal=term;
        counter;
		n=nods;
		b_num1 = 0;
		b_low1 = 0;
		b_low = new int [n];
		b_num = new int [n];
		
		e = edgs;
		D= dim;
		counter=0;
        headnodes= new node [n];
		//int temp[200];			//temporary data structure which is needed to 
		T = new bool[n];
		L= new int[n];
		father = new int[n];
		d_cmpnt = new int [n];
        temp=new int[n];
        edge_irrel = new edge [e];
        Ls = new int [n];
        Lt = new int [n];
        //headnodes_A= new node [n];
		// cout << "ok until here 2" << endl;

		// headnodes is an array of nodes.
        for (int i=0; i < n; i++)
         {  
			 headnodes[i].vertex=i;
             headnodes[i].next=0;

			 b_num1 = 1;
		     b_low1 = 0;
		     b_low [i] = 0;
		     b_num [i] = 0;
			 d_cmpnt [i] = 0;
         }
		// cout << "ok until here 3" << endl;

	}
	  void init () 
	// construtor
	{  
		//infile.open("C:/users/petingi/desktop/RnaDv/V7adj.txt");
	    //terminal=term;
        counter=0;
		n=nods;
		b_num1 = 0;
		b_low1 = 0;
		//b_low = new int [n];
		//b_num = new int [n];
		
		//e = edgs;
		//D= dim;
		//counter=0;
        //headnodes= new node [n];
		//int temp[200];			//temporary data structure which is needed to 
		//T = new bool[n];
		//L= new int[n];
		//father = new int[n];
		//d_cmpnt = new int [n];
        //temp=new int[n];
        //edge_irrel = new edge [e];
        //Ls = new int [n];
        //Lt = new int [n];
        //headnodes_A= new node [n];
		//cout << "ok until here 2: " << n << endl;

		// headnodes is an array of nodes.
        for (int i=0; i < n; i++)
         {  
			 headnodes[i].vertex=i;
             headnodes[i].next=0;
		     b_num1 = 1;
		     b_low1 = 0;
		     b_low [i] = 0;
		     b_num [i] = 0;
			 d_cmpnt [i] = 0;
         } 
		    while ( !mystack.empty()) 
			  mystack.pop();
			while ( !mystack1.empty()) 
			  mystack1.pop(); 


	}
	 ~Graph ()
	 {  delete [ ] headnodes;
		//int temp[200];			//temporary data structure which is needed to 
		delete [] T;
		delete [] L;
		delete [] father;
        delete [] edge_irrel;
        delete [] Ls;
        delete [] Lt;
	 }
	 void Del ( )
	 {  delete [] headnodes;
	   //delete [] headnodes_A;
		delete [] T;
		delete [] L;
		delete [] father;
        delete [] edge_irrel;
        delete [] Ls;
        delete [] Lt;
		//delete [][] weight;
	 }
	
void setdiam (int diameter)
{ D=diameter;
}
	void create()
	//create function
	{   //cout << "create: " << endl;
		node *pre;
		node * nextn;
	    node *newnode;
		for (int i=0; i < n; i++)
		 for (int j=0; j < n; j ++)
		 {  
			infile >> A;
			//cout << "entry: " << A;

			if (i==j) A=A/2;
			weight [i][j] = A;
			if (A > 0 ) // exclude self-loops
			{ for (int k = 1; k <= A;  k++)
			   { newnode= new node;
                 newnode->vertex = j;
			     
                 if( headnodes[i].next == NULL )
			    {
			  	    newnode->next= NULL;
				
				    headnodes[i].next=newnode;
			   }
			else
			   {
				 pre= &headnodes[i];
				while( pre->next != NULL )
				{   
					 pre = pre->next;
				}
				newnode->next = NULL;
				pre->next = newnode;
				 }


		//ADJACENT NODES
		/*
			newnode= new node;
			newnode->vertex = i;

			if( headnodes[j].next == NULL )
			{
				newnode->next= NULL;
				headnodes[j].next=newnode;
			}
			else
			{
				pre= &headnodes[j];
				while( pre->next != NULL )
				{
					pre = pre->next;
				}
				newnode->next = NULL;
				pre->next = newnode;
			}
			*/
			} // for internal
			} // if
			} // for external
	
    

	}
	void DFS(int father, int v)
	// DFS function
	{  
	Visited [v]=true;
	bool adjtoa=true;

    node* adjnode=headnodes[v].next;
    while (adjnode) // visit all vertices adjacent to v
	{
		if (!Visited[adjnode->vertex])
		{//if adjacent vertex to v was not visited previously
                      DFS(v,adjnode->vertex);
		}
		else if (father !=adjnode->vertex) // if the vertex adjacent to v is not the father, we have a 
		{ 
			cycles=true;
        }

		adjnode = adjnode->next;

	}
	}

	void Bi_Connect(int father, int v)
	// DFS function
	{  
	  Visited [v]=true;
	  bool adjtoa=true;
	  edge b_e;
	  int b_min;
	  b_num [v] = b_num1; //tree edge 
	  b_low [v] = b_num [v]; b_num1 ++;

    node* adjnode=headnodes[v].next;
    while (adjnode) // visit all vertices adjacent to v
	{   if ((adjnode -> vertex !=father) && (b_num [adjnode -> vertex] < b_num [v])) // push edge to the stack
		//if ((b_num [adjnode -> vertex] < b_num [v])) // push edge to the stack
     	{  
		   b_e.v1 = v;
	       b_e.v2 = adjnode->vertex;
		         mystack.push (b_e);
		         mystack1.push (b_e); // auxiliary stack
		   
		   //cout << endl << "stack size: " << mystack.size(); //pushing it but not popping it.

	    }
	    if (!b_num[adjnode->vertex]) {
			Bi_Connect(v,adjnode->vertex);
		    if (b_low [v] > b_low [adjnode->vertex])
			    b_low [v] = b_low [adjnode->vertex];

			//cout << endl << "b-low of w= " << adjnode->vertex << "-" << b_low [adjnode->vertex] << "b_num v=" << v << "-" << b_num [v];
			      if (b_low [adjnode->vertex] >= b_num [v]) { 
					  
					//if (Exm_cmpnt (v, adjnode->vertex)) // PSEUDO-KNOT FOUND
					 // {

				          outfile << endl << "==========New BiConnected Component============\n";
				          do { 
						      
					           // delete an edge from the stack of the stack
				      	        b_e=mystack.top();
					            mystack.pop();
								for (int l=1; l <= weight [b_e.v1] [b_e.v2]; l++)
					                  outfile << "(" << b_e.v1 << "," << b_e.v2 <<") - ";
				                } while ( !((b_e.v1==adjnode->vertex && b_e.v2==v) || (b_e.v2==adjnode->vertex && b_e.v1==v))); 
					       outfile << endl;
						   if (Exm_cmpnt (v, adjnode->vertex)) 
							   outfile << endl << "this component is a pseudoknot: "<< endl ;
						   else outfile << endl << "this component is NOT a pseudoknot: " << endl;
					 // }
				  }
                 
		}
				  
		else if ( adjnode->vertex != father) 

		          {  if (b_num [adjnode->vertex] < b_low [v])
					 b_low [v]=b_num [adjnode->vertex];
		          }
		adjnode = adjnode->next;
	}
		
	}

	
	bool Exm_cmpnt (int v, int w)
    {    bool pseudoknot = false; 
	     edge b_e;
		
		         for (int i = 0 ; i < n ; i++) {
					 //T[i] = false;
					 d_cmpnt [i] = 0; 
				 }

		         do { 
						      
					           // delete an edge from the stack
				      	        b_e=mystack1.top();
					            mystack1.pop();
								for (int l=1; l <= weight [b_e.v1] [b_e.v2]; l++){ // parallel edges
					                  //outfile << "(" << b_e.v1 << "," << b_e.v2 <<") - ";
								     d_cmpnt [b_e.v1]++; 
								     d_cmpnt [b_e.v2]++;
				                
								//outfile << endl << "degree of " << b_e.v1 << " is " << d_cmpnt [b_e.v1] ;
							    //outfile << endl << "degree of " << b_e.v2<< " is " << d_cmpnt [b_e.v2] ;
								}
								if (d_cmpnt [b_e.v1] > 2 || d_cmpnt [b_e.v2] > 2) 
									{pseudoknot = true;//biconnected component has a vertex of degree 3
								     //outfile << endl << "degree of " << b_e.v1 << " is " << d_cmpnt [b_e.v1] ;
									 //outfile << endl << "degree of " << b_e.v2<< " is " << d_cmpnt [b_e.v2] ;
								}
			    	 } while ( !((b_e.v1==w && b_e.v2==v) || (b_e.v2==w && b_e.v1==v))); 
					      
				return pseudoknot;
	}

	void setup_counter ()
	{ counter = 0;
	}
	long get_counter ()
	{ return counter;
	}
	void Dijkstra_B (int &val,edge &x1)//disjtra modified for factoring
		//Dijkstra function
       {   
		   bool all1s = true;
		   x1.v1= -1;
		   x1.v2= -1;
           int INFINITY = 1000;
		   int s =0,Minimum,u;
		   //int temp[40];			//temporary data structure which is needed to 
		   //T = new bool[n];
		   //L= new int[n];
		   //father = new int[n];
		   
		//INITIALIZING DATA STRUCTURES
		   for(int i =0;i<n;i++)
			{
			T[i] = false;			//T=V; all the vertices are eligible to be visited
			L[i]=INFINITY;			// at the beginning every vertex is at distance , from s
			temp[i] = INFINITY;		
			father[i] =-1;
			}
		   //WE ASSUME THE SOURCE IS 0 FOR EVERY GRAPH
		   L[s]=0;					// s is at distance 0 of itself
		   temp[s] =0;				// Temp has the same contents of L 
		  
		  // Let u be the vertex in T that has minimum L clearly at the beginning u=s 
		   for(int i = 0; i < n; i++)				//LOOP TROUGH ALL THE VERTICES OF THE GRAPH
		  {  
			  //cout<<endl<<"STEP "<<i<<":\n________ ";
			  Minimum = INFINITY;
		      for(int j = 0; j < n; j++)
			  {   if (!T[j]){
				  if( Minimum > temp[j])
					   {
						   Minimum = temp[j];			//finding minimum L[s]
						   u = j;
					   }
			   }
			  }
			  //temp[u] = INFINITY;				//Assigning INIFINITY to the data structure allready visited to find the next minimum L
			  //cout<<"\nU : "<<u;
			  w = &headnodes[u];
			  w=w->next;
			  //Assigning address of headnodes[u] to find adjacent nodes for u
			  //cout<<"\tW = "<<w->vertex;
			  while( w!=NULL )					//while w adjacent to u 
			  {
				  if(T[w->vertex]==false && w->binary)		// if w Exist in T, proceed
				  {   if (all1s && w->rel==0.5)// not all edges are 1
				       {all1s = false;
				          x1.v1=u;
						  x1.v2=w->vertex;
				       }
					  if (L[w->vertex]> L[u]+ weight[u][w->vertex])
					  { 
						  // if by reaching w from u has less weight
                                L[w->vertex]= L[u]+ weight[u][w->vertex]; // w is closer to s by using u;
								//cout<<"\nL[w]= L[u]+ weight(u,w)\n";
								//cout<<L[w->vertex]<<"  =   "<<L[u]<<"   +   "<<weight[u][w->vertex]<<endl;
								temp[w->vertex] = L[w->vertex];
                                father[w->vertex]=u;
								//cout<<"father[w] = "<<u<<endl;
						}
				  }
			
				w = w->next;   // tranfer the address of 'temp->next' to 'temp'
			  }
			  T[headnodes[u].vertex] = true;//Discard visited vertex u from T
			 // if (u == n-1)
              if (u == terminal)
				  break;	  
		   }

			  if (all1s)
				  //if (L[n-1] <= D)
				  if (L[terminal] <= D)
					  val = 1;
				  else val =0;
				  
			  else { // no all paths have value 1
				  //if ( L[n-1] > D )
				  if ( L[terminal] > D )
					   val = 0;
				  else val = 2;  //continue
			  }
			  

	}

	
	void display_val ()
	{   node *temp1;
		 for(int i = 0;i<n;i++)
		{
			temp1 = &headnodes[i];
			while( temp1->next!=NULL )
			{   if (temp1->next->binary)
			{
				cout << endl;
				cout<< "(" << i << "),(" << temp1->next->vertex<<")"; 
			}      
				temp1 = temp1->next; // tranfer the address of 'temp->next' to 'temp'
			}   

		}
	}
		
		void display()
	{
		node *temp1;
		outfile << endl << "==============================================";
		outfile << endl;
		
		for(int i = 0;i<n;i++)
		{
			temp1 = &headnodes[i];
			while( temp1!=NULL )
			{
				outfile << temp1->vertex<<" -> ";// show the data in the linked list
				temp1 = temp1->next;   // tranfer the address of 'temp->next' to 'temp'
			}
			outfile <<endl;
		}
		
		//cout<<"Number of vertices: "<<n<<endl;
        //cout<<"Number of edges: "<<e<<endl;
	
	}	

	
//;// end class



void Dijkstra_A (int a, node headnodes_A[],int L[])
{
		   int INFINITY = 1000;
		   int s =a,Minimum,u;
		   //int temp[30];			//temporary data structure which is needed to 
		   //T = new bool[n];
		   //L= new int[n];
		   //father = new int[n];
		   //int weight [n] [n];
		//INITIALIZING DATA STRUCTURES
		   for(int i =0;i<n;i++)
			{
			T[i] = false;			//T=V; all the vertices are eligible to be visited
			L[i]=INFINITY;			// at the beginning every vertex is at distance , from s
			temp[i] = INFINITY;		
			father[i] =-1;
			}
		   //WE ASSUME THE SOURCE IS 0 FOR EVERY GRAPH
		   L[s]=0;					// s is at distance 0 of itself
		   temp[s] =0;				// Temp has the same contents of L 
		  
		  // Let u be the vertex in T that has minimum L clearly at the beginning u=s 
		   for(int i = 0; i < n; i++)				//LOOP TROUGH ALL THE VERTICES OF THE GRAPH
		  {  
			  //cout<<endl<<"STEP "<<i<<":\n________ ";
			  Minimum = INFINITY;
		      for(int j = 0; j < n; j++)
			  {   if (T[j]==0){
				  if( Minimum > temp[j])
					   {
						   Minimum = temp[j];			//finding minimum L[s]
						   u = j;
					   }
			      }
			  }
			  //temp[u] = INFINITY;				//Assigning INIFINITY to the data structure allready visited to find the next minimum L
			  //cout<<"\nU : "<<u;
			  w = &headnodes_A[u];
			  w = w->next;
			  //Assigning address of headnodes[u] to find adjacent nodes for u
			  //cout<<"\tW = "<<w->vertex;
			  while( w!=NULL )					//while w adjacent to u 
			  {
				  if(T[w->vertex]==false && w->binary)		// if w Exist in T, proceed
				  {
					  if (L[w->vertex]> L[u]+ weight[u][w->vertex])
					  { 
						  // if by reaching w from u has less weight
                                L[w->vertex]= L[u]+ weight[u][w->vertex]; // w is closer to s by using u;
								//cout<<"\nL[w]= L[u]+ weight(u,w)\n";
								//cout<<L[w->vertex]<<"  =   "<<L[u]<<"   +   "<<weight[u][w->vertex]<<endl;
								temp[w->vertex] = L[w->vertex];
                                father[w->vertex]=u;
								//cout<<"father[w] = "<<u<<endl;
						}
					}
			
				w = w->next;   // tranfer the address of 'temp->next' to 'temp'
			  }
			  T[u] = true;				//Discard visited vertex u from T
		
		   }
}
};// end class


int main()

{  

   
	outfile.open("C:/users/petingi/desktop/RnaDv/V7adjout.txt");
    infile.open("C:/users/petingi/desktop/RnaDv/V7adj.txt");

	clock_t start;
	clock_t end;
	float facto_time;
	float facto_irr_time;
	float facto_irr_e_time;
	cout<<"Please enter the number of vertices: ";
	cin >>nods;
	edgs=0;
	dim=0;
	term = 0;
    Visited=new bool [nods];
	int b_counter = 0;
	
    int Nmbrcmpnts=0; //we initialize the counter for the number of components

    outfile << " +++++++++++++++ number of vertices: " << nods << "    ====================" << endl;
	Graph G(nods,edgs,dim,term);
	do {G.init();
	    //cout << endl << "ok";
	    b_counter ++;
		outfile << endl << "============   motif number (record number): " << b_counter << " ================" << endl;
	    G.create ();
		 //cout << endl << "ok2";
		G.display();
		//cout << endl << "ok3";
	    G.Bi_Connect(-1, 0);
		outfile << endl << " =================";
	} while ( !infile.eof () && b_counter < 10);
	
    infile.close();
	outfile.close();
    system("pause");
  return 0;
 
}




