# CS 225 Final Project
- This program organizes the Bitcoin OTC trust weighted signed network into graph structure. It uses the PageRank algorithm to find the most trusted/distrusted traders as well as Betweeness Centrality as a means of finding through which trader the most transactions pass through. There are a variety of real world applications for such a collection of algorithms, and in this case this program can be used in investigations and research in regards to Bitcoin transactions.

## Team Members

- Adit Kapoor (aditk3)
- Aliva Panigrahi (alivabp2)
- Anit Kapoor (anityak2)
- Chirag Gupta (chiragg4)  

## Team Contract

- [Contract](https://github-dev.cs.illinois.edu/cs225-fa20/chiragg4-anityak2-aditk3-alivabp2/blob/master/docs/Team%20Contract.pdf)

## Project Details

- Dataset used: [Bitcoin OTC trust weighted signed network](http://snap.stanford.edu/data/soc-sign-bitcoin-otc.html) (Processed)
- Specifications: [Project Goals](https://github-dev.cs.illinois.edu/cs225-fa20/chiragg4-anityak2-aditk3-alivabp2/blob/master/docs/Project%20Goals.md)
- Assignments/Issues: [Task Board](https://github-dev.cs.illinois.edu/cs225-fa20/chiragg4-anityak2-aditk3-alivabp2/projects/1)
### How To Run: ###
- Clone/download the repository
- Run "**make**" in your terminal
- The command to run our program has several parameters:
  - **Command:** "**./final_proj**"
  - **Argument 2:** filepath to CSV data
  - **Argument 3:** a boolean signifying whether or not the CSV file has headings
  - **Argument 4:** the vertex wanted by the user (or "**all**")
  - **Argument 5:** a boolean signifying whether or not the CSV file has headings
  - **Argument 6:** program code
    - "**p**" is for PageRank
    - "**b**" is for Betweenness Centrality
    - "**f**" is to find path using BFS
  - **Argument 7:** 
    - integer number of iterations for PageRank (defaults to 100); **optional**
    or
    - integer target to find path; **optional**
- **Example CLI Command:** "**./final_proj assets/data.csv true all f 20 13**"
