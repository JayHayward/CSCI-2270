//Assgnment5.cpp
//CSCI 2270
//Assignment 5
//Justin Hayward

#include "Queue.cpp"

int printMenu()
{
  cout<<"=====Main Menu=====\n";
  cout<<"1. Enqueue Word\n";
  cout<<"2. Dequeue Word\n";
  cout<<"3. Print Queue\n";
  cout<<"4. Enqueue Sentence\n";
  cout<<"5. Quit\n";
  // cout<<"==================="<<endl;

  int input;
  cin>>input;
  return input;
}

int main(/*int argc, char *argv[]*/)
{
  Queue qn(10);
  int sel=printMenu();

  for(;;)
  {
    if(sel==1)
    {
      string input;
      cout<<"word: ";
      cin>>input;
      qn.enqueue(input);
      sel=printMenu();
      continue;
    }
    if(sel==2)
    {
      qn.dequeue();
      sel=printMenu();
      continue;
    }
    if(sel==3)
    {
      qn.printQueue();
      sel=printMenu();
      continue;
    }
    if(sel==4)
    {
      string inSen;
      cout<<"sentence: ";
      cin.ignore();
      getline(cin,inSen);
      // cin>>inSen;
      // inSen="the quick brown fox jumped over the lazy dog";
      qn.enqueueSentence(inSen);
      sel=printMenu();
      continue;
    }
    if(sel==5)
    {
      cout<<"Goodbye!\n";
      return 0;
    }
    // else
    // {
    //   cout<<"invalid\n";
    //   sel=printMenu();
    //   continue;
    // }
  }
}
