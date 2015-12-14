
Analysis  and syntheses of algorithms project. 

Description:

The number of Paul Erdos is the number of co-authors after Paul Erdos. We can display this problem as a graph problem, where every node is a author and every connection is a co-authoracy. With this we can then use the Bellman-Ford algorithm for checking how far every author is from Paul Erdos(how many co-authoracies existed before him). With Bellman-Ford we can also check for cycles in the graph.

Description of the algorithm:

For this algorithm we consider 3 structures:
  -local which is a an author with pi(author before him) and next(next author)  
  -path which is a bond that has the weight of the same 
  -Queue auxiliary structure for BFS algorithm.
  
In the Bellman-Ford we essentially just Relax all nodes and when they all have the weights recalculated we just apply BFS.


For any doubts about the algorithm or the program contact me.

