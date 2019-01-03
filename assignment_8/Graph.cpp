#include "Graph.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

Graph::Graph()
{

}

Graph::~Graph()
{
    //dtor
}

void Graph::addEdge(string v1, string v2, int weight){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction
                    // adjVertex av2;
                    // av2.v = &vertices[i];
                    // av2.weight = weight;
                    // vertices[j].adj.push_back(av2);
                }
            }
        }
    }
}
void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        vertices.push_back(v);

    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout<<vertices[i].adj[j].v->name;
            if(j != vertices[i].adj.size()-1)
            {
              cout<<"***";
            }
        }
        cout<<endl;
    }

}

int Graph::isAdjacent(std::string v1, std::string v2)
{
  for(int i=0; i<vertices.size(); i++)
  {
    if(vertices[i].name == v1)
    {
      for(int j=0; j<vertices[i].adj.size(); j++)
      {
        if(vertices[i].adj[j].v->name == v2)
        {
          return 1;
        }
      }
    }
  }
  return 0;
}
