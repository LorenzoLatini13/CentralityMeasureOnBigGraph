# CentralityMeasuresOnGraphs

## Applied Centrality Measures on Big Graphs

### Project Description 

In this project we are gonna apply Centrality Measures from "F. Bonchi, G. De Francisci Morales, M. Riondato. Centrality Measures on Big Graphs: Exact, Approximated, and Distributed Algorithms. In *25th International World Wide Web Conference, Montreal, 2016*" to a Graph.

We will manipulate data from IMDb Datasets using AWK programming language to build a big graph where each node represent an Actor/Actress and two node are linked by an edge if and only if the actors partecipated in the same film.

Finally, we will apply two strategies to a sub-graph built starting from American actors: the former will be an Exact Centrality Measure while the latter will be a Random Centrality Measure.

The results from the first strategy will be satisfying while those from the second strategy strongly depend on computational power.

### How to run the code

1. Download CentralityMeasuresOnGraphs folder in your device.
2. In the same folder, download [name.basics.tsv.gz](https://datasets.imdbws.com/name.basics.tsv.gz), [title.basics.tsv.gz](https://datasets.imdbws.com/title.basics.tsv.gz) and [title.principals.tsv.gz](https://datasets.imdbws.com/title.principals.tsv.gz) and unzip them.
3. Use the following command to manipulate those files into a project compatible version.
  - awk -F"\t" 'NR>1 {print $1"\t"$5"\t"$6}' name.basics.tsv > name.basics1.tsv
  - awk -F"\t" '{print $1"\t"$5}' title.basics.tsv > title.basics1.tsv
  - awk -F"\t" 'NR>1 {print $1"\t"$3"\t"$4}' title.principals.tsv > title.principals1.tsv
  - awk -F"\t" 'NR>1{print $1"\t"$2"\t"$5}' Old.name.basics.tsv > name.basics.1.tsv
3. Run "CentralityMeasuresOnGraphs.cpp
