//Assignment6.cpp

#include "MovieTree.cpp"
// #include <stdlib.h>
// #include <iostream>
// #include <fstream>
// #include <sstream>
// using namespace std;

MovieTree mt;


void readFile(string filename) //going to use the title to call a build function
{
  ifstream file(filename);
  if(file)
  {
    string line, title, ele;
    int ranking, year, quant;

    while(getline(file,line))
    {
      stringstream linestream(line);

      getline(linestream,ele,',');
      ranking=stoi(ele);
      // cout<<ranking<<"\t";

      getline(linestream,ele,',');
      title=ele;
      // cout<<title<<"\t";

      getline(linestream,ele,',');
      year=stoi(ele);
      // cout<<year<<"\t";

      getline(linestream,ele,'\n');
      quant=stoi(ele);
      // cout<<quant<<"\n";

      mt.addMovieNode(ranking,title,year,quant);
    }
    // cout<<"file successfully read"<<endl;
  }
  else
  {
    cout<<"Error reading file"<<endl;
  }
}

int printMenu()
{
  cout<<"======Main Menu======\n";
  cout<<"1. Find a Movie\n";
  cout<<"2. Rent a Movie\n";
  cout<<"3. Print the inventory\n";
  cout<<"4. Delete a Movie\n";
  cout<<"5. Count the Movies\n";
  cout<<"6. Quit\n";

  string selection;
  // int a=0;
  // while(a==0) //makes sure avalid input is collected
  // {
  //   cin>>selection;
  //   if((selection<"1")||(selection>"6"))
  //     cout<<"Invalid"<<endl;
  //   else
  //     a=1;
  // }
  cin>>selection;
  return stoi(selection);
  // return selection;
}

int main(int argc, char *argv[])
{
  readFile(argv[1]);
  // readFile("Assignment6Movies.txt");

  cout<<"\n\n";
  int sel=printMenu();

  string ttl; //title
  while(true)
  {
    if(sel==1) //find
    {
      cout<<"Enter title:"<<endl;
      getline(cin.ignore(),ttl);
      // cout<<ttl;
      mt.findMovie(ttl);
      sel=printMenu();
      continue;
    }
    if(sel==2) //rent
    {
      cout<<"Enter title:"<<endl;
      getline(cin.ignore(),ttl);
      mt.rentMovie(ttl);
      sel=printMenu();
      continue;
    }
    if(sel==3) //print
    {
      cout<<"\n\n\n";
      mt.printMovieInventory();
      cout<<"\n\n";
      sel=printMenu();
      continue;
    }
    if(sel==4) //delete
    {
      cout<<"Enter title:\n";
      getline(cin.ignore(),ttl);
      mt.deleteMovieNode(ttl);
      sel=printMenu();
      continue;
    }
    if(sel==5) //count
    {
      int c = mt.countMovieNodes();
      cout<<"count: "<<c<<endl;
      sel=printMenu();
      continue;
    }
    if(sel==6) //quit
    {
      // mt.DeleteAll()
      cout<<"Goodbye!\n";
      return 0;
    }
    else
    {
      cout<<"invalid\n";
      sel=printMenu();
      continue;
    }
  }
}
