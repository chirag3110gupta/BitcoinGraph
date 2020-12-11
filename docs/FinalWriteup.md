## CS 225 Final Project Report

  Our group decided to implement a graph structure based on the Bitcoin OTC trust
weighted signed network, which contains rankings of different traders in regards
to mutual trust.

  While coding the graph class, we were first going to use a very abstract adjacency
list which was initially becoming very hard to implement. We then decided to work
on a more logical and minimalist graph blueprint that was comprehensive enough
to complete all the algorithms we wanted to implement.

  We agreed that the best way to analyze such data in an effective manner would be
through more complex algorithms. Therefore, it was decided to first implement
the PageRank algorithm. PageRank could be used in this data set to find the most trustworthy
traders as well as the least trustworthy ones. Secondly, we chose to implement
Betweenness Centrality which allows us to find out through which trader the most
number of transactions passes through. Finally we implemented a simple BFS to
traverse the graph and find paths between vertices; we unintentionally partially implemented Djikstra's. Overall, the main goal was
to create a working, efficient codebase to extrapolate important information about
the dataset. Given that such algorithms are so universal in application, it was not so difficult to implement them.
We simply had to tailor the methods to fit our requirements and test them in
several ways to ensure accuracy.

While writing PageRank, it was cool to know that it is an important algorithm used by Google to measure the importance of web pages for their search engine. This prevents users to cheat the PageRank algorithm to make their webpage popular using bots. We found this real world implementation really interesting and this motivated us to choose PageRank as one of our algorithms to implement.
The PageRank algorithm works by first initializing it to a default value, then it checks the outlinks and the inlinks of the vertices, and keeps adding values to the ones with more transactions. After every iteration, we get a clearer picture of which bitcoin user is most trusted by other users. It starts off as equal, and keeps getting more and more accurate based on the number of iterations. There were a few problems with it when we used vectors due to some users with no transactions, but that was easily fixed by using a unordered_map instead.

The betweenness centrality algorithm that we implemented is the Brande's Algorithm which calculates the centrality number using an expression which uses a particular vertex's dependencies, which itself is derived from the number of shortest paths passing through the particular vertex. The algorithm first iterates through every single source and target pair and calculates the distance from the source using a map of predecessors, and then processes the number of shortest paths to each of the nodes from the source. This algorithm makes the entire process much more efficient than the traditional method where all of the shortest paths would be discovered, and the paths would be checked for the required vertex and counted, which is a lot slower than the method we used.

To verify our outcomes and test our algorithms, we ran a variety of procedures. Firstly, we used the NetworkX Python library in Jupyter Notebooks to run our algorithms. We additionally wrote assertions, to do unit testing which proved the accuracy and functionality of our algorithms.

At the end of this project, it was nice to see that we successfully achieved the goals that we had set for ourselves as a team. Our workflow was extremely efficient, and the project was a productive experience which allowed us to learn about the implementation of extremely complex algorithms. 
