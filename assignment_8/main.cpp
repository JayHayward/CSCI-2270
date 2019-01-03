#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Graph.cpp"
using namespace std;

Graph gp;

void readFile(string filename)
{
  vector<string> names;
  fstream file;
  file.open(filename);

  if(file)
  {
    string line, name, first;
    // int ele = 0;

    while(getline(file, line, '\n'))
    {
      stringstream ss(line);
      int i=0;

      getline(ss, first, ','); //handles "cities"

      while(getline(ss, name, ','))
      {
        if(first == "cities")
        {
          gp.addVertex(name);
          names.push_back(name);
        }
        else
        {
          if(stoi(name) > 0)
            gp.addEdge(first, names[i], stoi(name));
          i++;
        }
      }
    }
  }
  else
    cout<<"error reading file\n";
}

void test()
{
  gp.addVertex("Boulder");
  gp.addVertex("Denver");
  gp.addVertex("Detroit");
  gp.addVertex("Los Angeles");
  gp.addVertex("New York");
  gp.addVertex("Chicago");

  gp.addEdge("Boulder","Denver",100);
  gp.addEdge("Los Angeles","Detroit",125);
  gp.addEdge("Denver","New York",150);
  gp.addEdge("Chicago","Denver",200);
  gp.addEdge("Boulder","Detroit",200);
}

int printMenu()
{
  cout<<"======Main Menu======\n";
  cout<<"1. Print vertices\n";
  cout<<"2. Vertecx adjacent\n";
  cout<<"3. Quit\n";

  string selection;
  getline(cin, selection);
  return stoi(selection);
  // return selection;
}

int main(int argc, char *argv[])
{
  readFile(argv[1]);

  // test();

  // gp.displayEdges();
  // gp.isAdjacent("Boulder","Denver");
  // if(gp.isAdjacent("Boston","Chicago") == 1)
  //   cout<<"true";
  // else
  //   cout<<"false";

  string v1, v2;
  while(true)
  {
    int sel = printMenu();
    if(sel == 1)
    {
      gp.displayEdges();
    }
    if(sel == 2)
    {
      cout<<"Enter first city:\n";
      getline(cin, v1);
      cout<<"Enter second city:\n";
      getline(cin, v2);

      if(gp.isAdjacent(v1,v2)==1)
        cout<<"True\n";
      else
        cout<<"False\n";
    }
    if(sel == 3)
    {
      cout<<"Goodbye!\n";
      return 0;
    }
  }
}
