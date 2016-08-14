# StateTree
A C++ data strcutre (essentially a standard tree, but with features needed for state systems)

### Initialisation and usage

* Include header file in project
* Initialise State tree with type
* Add nodes

![image](https://github.com/bryan-pakulski/StateTree/tree/master/images/Initialise.png?raw=true)

Which should result in output as follows:
![image](https://github.com/bryan-pakulski/StateTree/tree/master/images/Output.png?raw=true)

### TODO:

* Delete/Trim subtrees
* Different search options BFS, DFS for tree

### NOTE:
when using struct data types make sure to include an operator overload for " == " i.e. a struct of the following:

![image](https://github.com/bryan-pakulski/StateTree/tree/master/images/Structs.png?raw=true)

Will need a overload operator like this in order for the library to function:

![image](https://github.com/bryan-pakulski/StateTree/tree/master/images/Overload.png?raw=true)
