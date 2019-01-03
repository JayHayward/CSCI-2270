//CSCI 2270
//Assignment3
//Justin Hayward

#include <iostream>
#include <fstream>
using namespace std;

struct city
{
  string cityName;
  string message;
  city *next;
  city(){} //default constructor
  city(string initName, city *initNext, string initMessage)
  {
    cityName=initName;
    message=initMessage;
    next=initNext;
  }
};

int printMenu()
{
  cout<<"======Main Menu======"<<endl;
  cout<<"1. Build Network"<<endl;
  cout<<"2. Print Network Path"<<endl;
  cout<<"3. Transmit Message Coast-To-Coast"<<endl;
  cout<<"4. Add City"<<endl;
  cout<<"5. Quit"<<endl;

  string selection;
  int a=0;
  while(a==0) //makes sure avalid input is collected
  {
    cin>>selection;
    if((selection<"1")||(selection>"5"))
      cout<<"Invalid"<<endl;
    else
      a=1;
  }
  return stoi(selection);
}

city *buildNetwork() // return the head
{
  city *head=new city("", NULL, "");

  city *Bos=new city("Boston", NULL,"");
  city *Ny=new city("New York", Bos,"");
  city *Was=new city("Washington, D.C.", Ny,"");
  city *Atl=new city("Atlanta", Was,"");
  city *Chi=new city("Chicago", Atl,"");
  city *Lou=new city("St. Louis", Chi,"");
  city *Dal=new city("Dallas", Lou,"");
  city *Den=new city("Denver", Dal,"");
  city *Pho=new city("Phoenix", Den,"");
  city *La=new city("Los Angeles", Pho,"");

  head->next=La;
  // city *head=La;y
  city *walker=head->next;
  while(walker!=NULL)
  {
    if(walker->cityName!="")
      // cout<<walker->cityName<<" -> ";
    walker=walker->next;
  }
  // cout<<"NULL"<<endl;

  return head;
}

void printPath(city *head)
{
  cout<<"===CURRENT PATH==="<<endl;

  city *walker=head->next;
  // city *walker=head;
  while(walker!=NULL)
  {
    if(walker->cityName!="")
      cout<<walker->cityName<<" -> ";
    walker=walker->next;
  }
  cout<<" NULL";
  cout<<"\n=================="<<endl;
}

void transmitMsg(city *head)
{
  ifstream file("messageIn.txt");
  if(file)
  {
    string word;
    while(file>>word)
    {
      city *walker=head;
      while(walker!=NULL)
      {
        walker->message=word;
        if(walker->cityName!="")
          cout<<walker->cityName<<" received "<<walker->message<<endl;
        walker->message="";
        walker=walker->next;
      }
    }
  }
  else
    cout<<"error reading file";
}

city *addCity(city *head, city *previous, string cityName)
{
  if(previous->next==NULL) //adding to tail
  {
    city *t=new city(cityName,NULL,"");
    t->next=NULL;
    // previous->next=t;
  }

  // if(head->next->cityName=="Los Angeles") //adding to beginning
  // {
  //
  // }

  city *walker=head;
  while(walker!=NULL)
  {
    if(walker==previous)
    {
      city *n=new city(cityName,NULL,"");
      n->next=walker->next;
      walker->next=n;
      break;
    }
    walker=walker->next;
  }
}

int main()
{
  city *root=new city("",NULL,"");
  int sel=printMenu();
  for(;;)
  {
    if(sel==1)
    {
      root=buildNetwork();
      sel=printMenu();
    }
    if(sel==2)
    {
      printPath(root);
      sel=printMenu();
    }
    if(sel==3)
    {
      transmitMsg(root);
      sel=printMenu();
    }
    if(sel==4)
    {
      // cout<<root->cityName<<"  "<<root->next<<endl;
      string inName;
      string inPrev;
      cout<<"Enter a City name:"<<endl;
      cin>>inName;
      cout<<"Enter a previous City name:"<<endl;
      cin>>inPrev;

      if(inPrev=="")
        inPrev="Boston";

      city *walker=root;
      while(walker!=NULL)
      {
        // cout<<"\n\nSTART WHILE LOOP\n\n";
        if(walker->cityName==inPrev) //find the previous city ptr
        {
          // cout<<"\n\nFOUND CITY\n\n";
          addCity(root, walker, inName);
          break;
        }
        walker=walker->next;
      }

      // cout<<inName<<'\t'<<inPrev<<endl;

      sel=printMenu();
    }

    if(sel==5)
    {
      cout<<"Goodbye!";
      return 0;
    }
  }
}
