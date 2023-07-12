#include <iostream>
#include "LEDA/graph/graph.h"
#include "LEDA/graph/graph_alg.h"
#include "LEDA/system/timer.h"
#include "queue.h"

#define NODES 500 /*Initialization of nodes*/
#define LEVELS 4 /*Level declaration (k nodes per level where k is defined above)*/

using namespace leda; /*We avoid the dependency of using "leda::" in each leda attribute*/

list<node> my_BFS(const graph& G, node s, node_array<int>& dist,node_array<edge>& pred){ 
	node_array<bool> visited (G); /*Using this variable as information for visited nodes (if false then this node has not been visited by the algorithm,true if otherwise)*/
	node v; 
	list<node> result; /*When BFS ends results will be return in this list*/
	forall_nodes(v,G){ /*Initialization of all information*/
		dist[v] = 0;
		visited[v] = false;
	}
	Queue<node> Q(s); /*Forming a queue for BFS*/
	result.push(s); /*Starting from root that was picked up randomly (node s)*/
	visited[s] = true; /*We technically visited s since this is our starting point*/
	while (Q.size != 0){ /*This while loop works until all nodes are visited (only nodes that have "false" visited value will be added to the queue)*/
		node t = Q.pop(); /*node t will be given the top node of the queue, de-queueing it in the process*/
		edge e;
		forall_edges(e,G){ /*Looking for unvisited nodes, edgewise because it will be a big help with "pred" array that's used to check for an odd circle*/
			if (G.source(e) == t){ /*Because G is made bidirected (so that it is technically considered undirected) graph, we have to make sure that we are referring to the right edge*/
				if (!visited[G.target(e)]) { /*checks whether the node that edge "e" ends at is unvisited*/
					pred[G.target(e)] = e; /*Here the edge that was used to "discover" this node is saved within the respective index of "pred" array (i.e predecessor edge)*/
					dist[G.target(e)] = dist[G.source(e)] + 1; /*Here "dist" array saves the level that the discovered node ends up at the BFS hierarchy (used for Coloring later)*/
					result.append(G.target(e)); /*Since this node is "discovered", we must also add it to our results*/
					visited[G.target(e)] = true; /*Now this node is officially visited and no further "exploration" occurs.*/
					Q.push(G.target(e)); /*Now exploration begins at this node's neighboors (if they exist)*/
				}
			}
		}
	}
	
	return result; /*The complete BFS result is saved within this list*/
}

bool my_bipar_checker(const graph& G, list<node>& V1, list<node>& V2){
	node_array<edge> pred(G); /*Again "pred" is the array that is used to save predecessor edges of discovered nodes*/
	node_array<int> dist(G); /*Same functionality as "dist" array within "my_BFS" function*/
	list<node> res; /*list to save the results of "my_bfs()" function since it has a return type (not void)*/
	node_array<char> Color(G); /*This array will contain information about the color of a node ("g" value is for green and "b" value is for blue)*/
	bool result = true; /*Initialization of this function's return value. (The assumption here is that biportite attribute of the graph is considered true until proven wrong)*/
	node s = G.choose_node(); /*s is picked as a random node within the graph and will be considered the "root" of BFS algorithm*/

	res = my_BFS(G,s,dist,pred); /*Start running BFS algorithm*/
	node r;
	
	forall_nodes(r,G){ /*Within this loop color information is added for each node*/
		if (dist[r] % 2 == 0) Color[r] = 'g';
		else Color[r] = 'b';
	}
	
	edge checker;
	forall_edges(checker,G){ /*Within this loop we check edgewise whether an edge exists for which both nodes that are linked, have the same color*/
		if (Color[G.source(checker)] == Color[G.target(checker)]){ /*If there is such edge that links two nodes with the same color then we begin finding an odd circle and return it in list V1*/
			result = false; /*The assumption from before is proven wrong and therefore the graph is not biportite*/
			edge e1 = checker;
			edge e2 = G.reversal(checker);
			while(G.source(pred[G.source(e1)]) != G.source(pred[G.source(e2)])){
				V1.append(G.target(pred[G.source(e1)]));
				V1.append(G.target(pred[G.source(e2)]));
				e1 = pred[G.source(e1)];
				e2 = pred[G.source(e2)];
				
			}
			V1.append(G.target(pred[G.source(e1)]));
			V1.append(G.target(pred[G.source(e2)]));
			V1.append(G.source(pred[G.source(e1)]));
			break; /*here break is used because only 1 odd circle is to be returned. There's no need to find further such circles*/
		}
	}
	if (result) /*if the loop above is finished with "result" variable not changing to false then the assumption is correct and therefore graph G is biportite (Assumption was not proven wrong)*/
		forall_nodes(r,G){ /*since graph G is biportitve then lists V1 and V2 will contain the two subsets of nodes. (blue nodes end up at list V1 and green at V2)*/
			if (Color[r] == 'b') V1.append(r);
			else V2.append(r);
	}
	return result; 
	/*The only thing that is returned here is the bool value "true/false" depending on "result" variable. However this function's inputs V1 and V2 act as "inout" variables
	meaning that changes that occur in this function for V1 and V2, also affect their "copies" in main*/
}

int main(){
	srand(time(0)); /*To make this graph, "rand" function is going to be used so to change the sequence of random number generator we use "srand".*/
	graph G;
	for(int i=0; i<NODES*4; i++){ /*First the total number of nodes are added into the graph*/
		G.new_node();
	}
	list<node> n = G.all_nodes(); /*Keep a list of all nodes*/

	node v1 = n.contents(n.get_item((int)(rand()%NODES + 0*NODES))); /*Randomly select a node from level 1*/
	node v2 = n.contents(n.get_item((int)(rand()%NODES + 1*NODES))); /*Randomly select a node from level 2*/
	node v3 = n.contents(n.get_item((int)(rand()%NODES + 2*NODES))); /*Randomly select a node from level 3*/

	node vt1,vt2,vt3,vt4;
	for(int i = 0; i<NODES; i++){ /*Assuming that this graph represents a matrix with k rows (where k = NODES) and 4 columns, within this for we link nodes of row i (both nodes) and columns j and j+1 respectively (where j represents the level). Also the nodes v1,v2,v3 that were picked above, will be linked with all nodes of level 2,3 and 4 respectively*/

		vt1 = n.contents(n.get_item(0*NODES + i));
		vt2 = n.contents(n.get_item(1*NODES + i));
		vt3 = n.contents(n.get_item(2*NODES + i));
		vt4 = n.contents(n.get_item(3*NODES + i));

		G.new_edge(vt1,vt2);
		G.new_edge(vt2,vt3);
		G.new_edge(vt3,vt4);
		G.new_edge(v1,vt2);
		G.new_edge(v2,vt3);
		G.new_edge(v3,vt4);
	}
	/*Finally, we pick 4 random nodes again (1 node per level) and we link selected nodes from level 1 and 3 with an edge and nodes of level 2 and 4 with another*/
	vt1 = n.contents(n.get_item((int)(rand()%NODES + 0*NODES)));
	vt2 = n.contents(n.get_item((int)(rand()%NODES + 1*NODES)));
	vt3 = n.contents(n.get_item((int)(rand()%NODES + 2*NODES)));
	vt4 = n.contents(n.get_item((int)(rand()%NODES + 3*NODES)));
	G.new_edge(vt1,vt3);
	G.new_edge(vt2,vt4);

	std::cout << "Number of nodes = " << G.number_of_nodes() << "\nand number of edges = " << G.number_of_edges() << "\n"; /*Used for debugging but i kept it as it might be useful information*/
	list<edge> reversed; /*Since i make each graph bidirected to make it appear as undirected, i have to create an edge list to store reversed information (e' for each e)*/
	G.make_bidirected(reversed); /*Here G not only becomes bidirected, but also reversed list is filled with all the information for each edge (e')*/
	int counter = 0; /*Here counter is used as an "early stop" method for the loop following below (Because we only want to access our initial edges and not the reversed ones)*/
	edge e;
	
	forall_edges(e,G){ /*for each initial edge (e) we set its reversal (e')*/
		G.set_reversal(e,reversed.contents(reversed.get_item(counter)));
		counter++;
		if (counter == reversed.size()) break;
	}
	
	timer my_bipar; /*Timer for my algorithm*/
	timer leda_bipar; /*Timer for LEDA's respective algorithm*/
	
	list<node> A,B,C,D; /*Here lists A and B are going to be used as the subsets V1 and V2 for my algorithm and C,D as subsets V1 and V2 for LEDA's algorithm*/
	/*From this point on, we simply use both functions and print the results for each*/
	my_bipar.start();
	bool res = my_bipar_checker(G,A,B);
	my_bipar.stop();
	std::cout<< "my_bipar is "<< res << "\n";
	std::cout<<"Total time elapsed for my bipar at " << my_bipar.elapsed_time() << " seconds\n";
	leda_bipar.start();
	res = Is_Bipartite(G,C,D);
	leda_bipar.stop();
	std::cout<< "leda_bipar is "<< res << "\n";
	std::cout<<"Total time elapsed for LEDA bipar at " << leda_bipar.elapsed_time() << " seconds\n";
	
	return 0;
}



