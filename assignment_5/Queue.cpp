//Queue.cpp
//CSCI 2270
//Assignment 5
//Justin Hayward

#include "Queue.h"
#include <sstream>
#include <string>
using namespace std;

Queue::Queue(int qs)
{
  queueSize = qs;
  arrayQueue = new string[queueSize];
  queueHead = 0;
  queueTail = 0;
  queueCount = 0;
}

Queue::~Queue()
{
  delete [] arrayQueue;
  arrayQueue = nullptr;
}

void Queue::enqueue(string word)
{
  bool full=queueIsFull();
  if(!full)
  {
    arrayQueue[queueTail]=word;
    queueTail = (queueTail+1) % queueSize;
    queueCount++;

    cout<<"E: "<<word<<endl;
    cout<<"H: "<<queueHead<<endl;
    cout<<"T: "<<queueTail<<endl;
    // cout<<"C: "<<queueCount<<endl;
  }
  else
  {
    cout<<"Queue is full\n";
    //connectail to head
  }
}

void Queue::dequeue()
{
  bool empty=queueIsEmpty();
  if(!empty)
  {
    string word=arrayQueue[queueHead];
    queueHead = (queueHead+1) % queueSize;
    queueCount--;

    cout<<"H: "<<queueHead<<endl;
    cout<<"T: "<<queueTail<<endl;
    cout<<"word: "<<word<<endl;
  }
  else
  {
    cout<<"Queue is empty\n";
  }
}

void Queue::printQueue()
{
  bool empty=queueIsEmpty();
  if(!empty)
  {
    int printcount=0;
    for(int i=queueHead;;i++)
    {

      if(queueCount==0)
        return;

      if(i==queueSize)
      {
        i=0;
      }

      if(printcount==queueCount)
      {
        return;
      }
      cout<<i<<": "<<arrayQueue[i]<<endl;
      printcount++;
    }
    return;
  }
  else
  {
    cout<<"Empty"<<endl;
    return;
  }
}

void Queue::enqueueSentence(string sentence)
{
  bool full=queueIsFull();
  cout<<sentence<<endl;
  string word;
  stringstream ss(sentence);
  // cout<<"inSentence: ";
  while(ss>>word)
  {
    enqueue(word);
  }
}

bool Queue::queueIsFull()
{
  if(queueCount==queueSize)
    return true;
  return false;
}

bool Queue::queueIsEmpty()
{
  if(queueCount==0)
    return true;
  return false;
}
