# CentralityMeasuresOnGraphs

## Applied Centrality Measure on a Big Graph

### Project Description 

In this project we are gonna apply a centrality measures from "F. Bonchi, G. De Francisci Morales, M. Riondato. Centrality Measures on Big Graphs: Exact, Approximated, and Distributed Algorithms. In *25th International World Wide Web Conference, Montreal, 2016*" to a Graph.

We will manipulate data from IMDb Datasets using AWK programming language to build a big graph where each node represent an Actor/Actress and two node are linked by an edge if and only if the actors partecipated in the same film.

Our objective is to identify the actors who have collaborated with the highest number of other actors.

To do so we will apply the degree centrality measure to a sub-graph built starting from American actors.

The results from this strategy will be satisfying showing a ranking of famous actors.

### How to run the code

1. Download CentralityMeasureOnGraph folder in your device.
2. In the same folder, download [name.basics.tsv.gz](https://datasets.imdbws.com/name.basics.tsv.gz), [title.basics.tsv.gz](https://datasets.imdbws.com/title.basics.tsv.gz) and [title.principals.tsv.gz](https://datasets.imdbws.com/title.principals.tsv.gz) and unzip them.
3. Use the following command to manipulate those files into a project compatible version.
    - awk -F"\t" 'NR>1 {print $1"\t"$5"\t"$6}' name.basics.tsv > name.basics1.tsv
    - awk -F"\t" '{print $1"\t"$5}' title.basics.tsv > title.basics1.tsv
    - awk -F"\t" 'NR>1 {print $1"\t"$3"\t"$4}' title.principals.tsv > title.principals1.tsv
    - awk -F"\t" 'NR>1{print $1"\t"$2"\t"$5}' Old.name.basics.tsv > name.basics.1.tsv
3. Run "CentralityMeasureOnGraph.cpp"
