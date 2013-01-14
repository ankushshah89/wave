wave
====

Wave is an algorithm to find the blocking flow in a network. The complexity of algorithm is O(n^2), which is same as MPM or Karzanov's algorithm. But this, wave algorithm, is very easy to understand and simple to implement. 

More details can be found at http://dl.acm.org/citation.cfm?id=2308840

Testcases have the following format

The first line contains 2 integers n and m. n is the number of vertices and m is the number of edges. This is followed by  m lines, each having three integers u, v, and c. This specify an edge from vertex u to v with a capacity c.

Example:

3 2

0 1 10

1 2 5

