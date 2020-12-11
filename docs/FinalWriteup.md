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
the PageRank algorithm, a method actually used by Google to rank the importance
of webpages. PageRank could be used in this data set to find the most trustworthy
traders as well as the least trustworthy ones. Secondly, we chose to implement
Betweenness Centrality which allows us to find out through which trader the most
number of transactions passes through. Finally we implemented a simple BFS to
traverse the graph and find paths between vertices. Overall, the main goal was
to create a working, efficient codebase to extrapolate important information about
the dataset.

  Given that such algorithms are so universal in application, it was not so difficult to implement them.
We simply had to tailor the methods to fit our requirements and test them in
several ways to ensure accuracy.
