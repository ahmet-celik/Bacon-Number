/* 
 * File:   main.cpp
 * Author: Ahmet Celik 2009400111
 *
 * Created on 08 Kasım 2011 Salı, 13:38
 */

#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

typedef  tr1::unordered_set<vertex*,MyHash<vertex*>,MyEq<vertex*> >::iterator my_itr;

my_hash_set<vertex*> actors; 
my_hash_set<vertex*> movies;

/**
 * Calculates maximum of the minimum distances between vertex
 * @param graph that has shortestPath method
 * @param first set of vertex 
 * @param second set of vertex
 * @return maximum of the minimum distances between these sets
 */
 int maxLen(graph & g,my_hash_set<vertex*>*  set1,my_hash_set<vertex*>* set2){
	 int maxlen=0;
	my_itr itr1 = set1->data->begin();
	for(;itr1!=set1->data->end();itr1++){
            g.shortestPath(*(itr1));
            my_itr itr2=set2->data->begin();
            for(;itr2!=set2->data->end();itr2++)
            {
                    if(((*(itr2))->dist)!=SONSUZ){
                            int aux=(((*itr2)->dist)+1)/2;
                            if(maxlen<aux)
                            {
                                    maxlen=aux;
                                    //to learn which is that:
                                    //cout<<(*(itr1))->name<<" - "<<(*(itr2))->name<<" = "<<maxlen<<endl;
                            }
                    }else{// found disconnected  pair of vertex, so there is INFINITY distance                             
                        //cout<<(*(itr1))->name<<" - "<<(*(itr2))->name<<" = ";
                        return -1;
                    }
            }

	}
	return maxlen;
}
/**
 * Calculates min distance to all actor vertex and print them in .dot format
 * @param graph
 */
void bonus(graph&g){
	ofstream myfile("actors.dot");
	my_hash_set<vertex*> aux=actors;//make copy of actors,since we need 
                                        //delete operation after going over
	const  int temp = maxLen(g,g.actorEdge,g.actorEdge);
        int uppBound;//to reverse weight need for an upper bound
        
	if(temp!=-1)
	     uppBound =(temp*temp*temp)+(temp*temp);
	else
             uppBound = aux.data->size();
        
	my_itr itr1 = actors.data->begin();
	myfile<<" graph G {"<<endl;

	for(;itr1!=actors.data->end();itr1++){
            
            myfile<<"act"<<((int)(*(itr1)))<<"[label=\""<<((*(itr1))->name)<<"\"];"<<endl;
            g.shortestPath(*(itr1));
            my_itr itr2=aux.data->begin();
            for(;itr2!=aux.data->end();itr2++)
            {
                if(*itr2!=*itr1)//to prevent a--a meaningless edge
                {
                  int weight=(((*itr2)->dist)+1)/2;
                  if(((*itr2)->dist)!=SONSUZ)
                  {
                      myfile<<"act"<<((int)(*(itr1)))<<" -- "<<"act"<<(int)(*(itr2))<<" [label= \""<<weight<<"\" ,weight= "<<(uppBound-(weight*weight*weight))<<" ];"<<endl;
                  }
                }
            }
            aux.data->erase(*(itr1));//Since it is undirected, delete iterated vertex
                                     //if there is a--b, no need for b--a
	}
	myfile<<"}"<<endl; 
        myfile.close();
}



/**
 * prints message for usage
 */
void invalidarg(){
	cout<<"author:Ahmet Celik number:2009400111\nInvalid arguments!"<<endl;
	cout<<"Try these:\n\\program_name txt_file_name actor_or_movie actor_or_movie"<<endl;
	cout<<"\\program_name txt_file_name -max actors|movies|actor-movie"<<endl;
	cout<<"\\program_name txt_file_name -bonus"<<endl;
}

/**
 * main program to handle arguments and making graph. calling function in
 * proper order
 * @param argc
 * @param argv
 * @return 
 */
int main (int argc,char*argv[]) 
{     
    
    if(argc==1||argc==2){
            invalidarg();
            return 1;
    }
    
    //creating graph
  ifstream myfile(argv[1]);
  graph myGraph; 
  if (myfile.is_open())
  {    
        string actor,movie;
        getline(myfile,actor,'|');
        while ( myfile.good())
        {
            
            vertex * act = new vertex(actor);
            actors.data->insert(act);
            string aux=actor;

              while(aux.compare(actor)==0&&myfile.good())
              {
                      getline(myfile,movie);

                      vertex* mov = new vertex(movie);
                      pair<my_itr,bool> mov_pair = movies.data->insert(mov);
                      if(mov_pair.second)
                      {
                              myGraph.addEdge(act,mov);
                      }
                      else   
                      {
                              myGraph.addEdge(act,*(mov_pair.first));
                              delete mov;
                      }
                      getline(myfile,actor,'|');
              }
        }
        myGraph.actorEdge = &actors; //add set * to field of graph 
        myGraph.movieEdge = &movies; // same here
        //cout<<"actor:"<<actors.data->size()<<" movies:"<<movies.data->size()<<endl;
        myfile.close();
  }
  else
  {
          cout << "Unable to open file";
          return 1;
  } 
  
  
  //argument handling
   
    if(argc==4){
        string  arg2(argv[2]);
        string  arg3(argv[3]);
        
        if(argv[2][0]!='-'){
         
           vertex *first= new vertex(arg2);  vertex *second=new vertex(arg3);
           int auxdist=0;
           if(actors.data->count(first)==1&&movies.data->count(second)==1)
           {
                   myGraph.shortestPath(*(actors.data->find(first)));
                   auxdist=(*(movies.data->find(second)))->dist;
           }
           else if(movies.data->count(first)==1&&movies.data->count(second)==1)
           {
                   myGraph.shortestPath(*(movies.data->find(first)));
                   auxdist=(*(movies.data->find(second)))->dist;
           }
           else if(movies.data->count(first)==1&&actors.data->count(second)==1)
           {

                   myGraph.shortestPath(*(actors.data->find(second)));
                   auxdist=(*(movies.data->find(first)))->dist;
           }
           else if(actors.data->count(first)==1&&actors.data->count(second)==1)
           {

                   myGraph.shortestPath(*(actors.data->find(first)));
                   auxdist=(*(actors.data->find(second)))->dist;
           }
           else
           {
                   cout<<-1<<endl; return 0;
           }
           if(auxdist!=SONSUZ)
               cout<<(auxdist+1)/2<<endl;
           else
               cout<<-1<<endl;
           delete first; delete second;
           
        }
        else if(arg2.compare("-max")==0)
        {
                if(arg3.compare("actors")==0) cout<<maxLen(myGraph,&actors,&actors)<<endl;
                else if(arg3.compare("movies")==0) cout<<maxLen(myGraph,&movies,&movies)<<endl;
                else if(arg3.compare("actor-movie")==0) cout<<maxLen(myGraph,&actors,&movies)<<endl;
                else{ invalidarg(); return 1;}
        }
        else
        {
                 invalidarg();
                 return 1;
        }

    }
    else if(argc==3&&string(argv[2]).compare("-bonus")==0)
    {
         bonus(myGraph);
    }	
    else
    {
        invalidarg();
        return 1;
    }
   
    //cout<<endl<<"Run Successful!"<<endl;
  return 0;
}


