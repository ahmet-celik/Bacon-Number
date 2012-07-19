/*
 * vertex.h
 *
 *  Created on: 12 Kas 2011
 *  Author: Ahmet Celik 2009400111
 */

#ifndef VERTEX_H_
#define VERTEX_H_
#include "my_hash_set.h"
#include <string>
using namespace std;

class vertex
{
public:
   string name;  //name of vertex
   int  dist;    //need for shortest path
   my_hash_set<vertex*> adj; //adjacency vertex set
   
   explicit vertex(const string s="N/A"):name(s),dist(0),adj(){}
};




#endif /* VERTEX_H_ */
