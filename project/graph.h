/* 
 * File:   graph.h
 * Author: Ahmet Celik 2009400111
 *
 * Created on 08 Kasım 2011 Salı, 15:56
 */

#ifndef GRAPH_H
#define	GRAPH_H
#define SONSUZ 0x7FFFFFFF //biggest signed 4byte integer
#include "vertex.h"
using namespace std;

class graph{
public:
    graph(){actorEdge=0;  movieEdge=0;}
    void addEdge( vertex* , vertex* );//connects two vertex
    void shortestPath(vertex* ); // Breadth First Search

    my_hash_set<vertex*> * actorEdge; //holds edges of actors
    my_hash_set<vertex*> * movieEdge; //holds edges of movies
};

#endif	/* GRAPH_H */

