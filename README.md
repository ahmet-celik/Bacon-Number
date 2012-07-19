BACON NUMBER CALCULATION
-------------------------

Kevin Bacon Game is to link a movie actor to Kevin Bacon via shared movie roles. The minimum  
number of links is an actor’s Bacon number.  

For instance, Tom Hanks has a Bacon number of 1;  
he was in Apollo 12 with Kevin Bacon. Sally Fields has a Bacon number of 2, because she was in  
Forrest Gump with Tom Hanks, who was in Apollo 12 with Kevin Bacon. Almost all well-known  
actors have a Bacon number of 1 or 2.  
In this project I have calculated a generalized version of Bacon number. In this version  
I worked with a bipartite graph *G* where actors and movies are the nodes.

1. *The distance between two actors* is defined as the number of movie nodes on the shortest path
between them.  
2. *The distance between an actor and a movie* is defined as the number of movie nodes on the
shortest path between the actor and the target movie, counting the movie itself.  
3. *The distance between two movies* is defined as the number of actors on the shortest path.  


*Compile with GNU C++ Compiler*  
**DO NOT COMPILE ON MAC SYSTEMS**

