/*
 * File:   graph.cpp
 * Author: Ahmet Celik 2009400111
 *
 * Created on 08 Kasım 2011 Salı, 15:56
 */

#include "graph.h"
#include <queue>
using namespace std;
typedef  tr1::unordered_set<vertex*,MyHash<vertex*>,MyEq<vertex*> >::iterator my_itr;
/**
 * Adds an edge to graph. adds a-b and b-a both.
 * @param frst
 * @param scnd
 */
void graph::addEdge(vertex* frst, vertex* scnd)
{
	frst->adj.data->insert(scnd);
	scnd->adj.data->insert(frst);
}
/**
 * find shortest distance to s from all actor vertex if there is any 
 * 
 * @param s
 */
void graph::shortestPath(vertex*  s)
{
	queue<vertex*> q;
	my_itr itr =actorEdge->data->begin();
	for(;itr!=actorEdge->data->end();itr++)
	{
			(*itr)->dist=SONSUZ;
	}
	for(itr =movieEdge->data->begin();itr!=movieEdge->data->end();itr++)
	{
			(*itr)->dist=SONSUZ;
	}
	s->dist=0;

	q.push(s);
	while(!q.empty())
	{
            vertex * v = (q.front()); q.pop();
            for(my_itr itr=v->adj.data->begin();itr!=v->adj.data->end();itr++)
            {
                    if((*itr)->dist==SONSUZ)
                    {
                            (*itr)->dist=((v->dist)+1);
                            q.push((*itr));
                    }
            }
	}
}


