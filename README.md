# tacos

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/be6d1ff50d6e427c9b512f906f37c238)](https://app.codacy.com/gh/fvalle1/tacos?utm_source=github.com&utm_medium=referral&utm_content=fvalle1/tacos&utm_campaign=Badge_Grade)

Tool for Analysis of COmponents Systems

```
mkdir master && cd master
cmake ..
make data_mining
make tacos
```

When run `./data_mining` an *help* is printed about

```bash
Running TCGA
threads: 2
Please write some options
0 ---> read mainTable.csv
1 ---> read and extimate correlation mainTable.csv
2 ---> extimate means and variances
3 ---> GenerateNullData
4 ---> read nullTable.csv
5 ---> nullTable.csv read and extimate correlation
6 ---> nullTable.csv extimate means and variances
7 ---> read and make bipartite graph
 0.811598s wall, 0.160000s user + 0.010000s system = 0.170000s CPU (20.9%)
```

Options with **read** are able to create
* *A.dat* file with **abundances**
* *O.dat* file with **occurrences**
* *heaps.dat* file with **sizes** and **vocabulary sizes**

Options with **extimate correlations** create a *correlations.dat* file with **H(X:Y)** for each couple of words.

**Generate null data** option create a *nullTable.csv* file with null model generated data.

**Make bipartite graph** option creates a *graph.xml.gz* file which is a great input *hieratical Stochastic Block Model*

## python
tacos can be used as a python library

```python
import tacos
```
