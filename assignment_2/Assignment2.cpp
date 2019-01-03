#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct wordItem
{
  string word;
  int count;
  wordItem(){} //default constructor
};

wordItem *wordItemList = new wordItem[100];

string ignoreWords[50];

wordItem *doubleArray(wordItem *arr1, int size)
{
  int newSize = size*2;
  wordItem *arr2=new wordItem[newSize];
  for(int i=0; i<size; i++)
  {
    arr2[i]=arr1[i];
  }
  delete[] arr1;
  arr1=arr2;
  size=newSize;

  return arr1;
}

void getStopWords(char *ignoreWordFilename, string ignoreWords[]) //param1 is string
{
  ifstream myWords(ignoreWordFilename);
  if(myWords)
  {
    // cout<<"ignoreWords.txt successfully read"<<endl;
    string line;
    int i=0;
    while(getline(myWords,line))
    {
      ignoreWords[i]=line;
      i++;
    }
  }
  else
    cout<<"error reading ignoreWords.txt"<<endl;
}

bool isStopWord(string word, string ignoreWords[])
{
  bool stopWord=false;
  for(int i=0; i<50; i++)
  {
    if(ignoreWords[i]==word)
      return true;
  }
  return stopWord;
}

bool isCounted(string wordName, int length, wordItem *wordItemList) //check if a word item already occurs in the array
{
  bool counted=false;
  for(int i=0; i<length; i++)
  {
    if(wordItemList[i].word==wordName)
    {
      wordItemList[i].count++;
      return true;
    }
  }
  return counted;
}

int readFile(string filename, int *numWords, int *finIndex, int *doubleCount) //personal function
// Create the wordItemList array of structs
{
  // wordItem *wordItemList = new wordItem[100];
  int length = 0; // length of the array of structs.
  // increment for every nonStop word
  *finIndex=100; //the value at which the array needs to double in size
  *numWords=0; //count of total words, including repeats

  ifstream file(filename);
  if(file)
  {
    string indivWord; //singular word
    while(file >> indivWord)
    {
      //check if length > size of struct array
      if(length==*finIndex) //this value needs to change with dynamic array size
      {
        wordItemList = doubleArray(wordItemList, length);
        *doubleCount = *doubleCount+1;
        *finIndex = *finIndex*2; //size of the doubled array
      }

      //check if a word read is in ignoreWords[]
      if(isStopWord(indivWord, ignoreWords)==false)
      {
        *numWords=*numWords+1;
        //check if the word item hhas already been counted
        if(isCounted(indivWord, length, wordItemList)==false) //if the word is NOT already in the array
        {
          wordItemList[length].word=indivWord;
          wordItemList[length].count=1;
          length++;
        }
      }
    } //close while loop
  }
  return length; //length of array of wordItems
}

int getTotalNumberNonStopWords(wordItem list[], int length)
{
  int totWords=0;
  for(int i=0; i<length; i++)
  {
    totWords = totWords + list[i].count;
  }
  return totWords;
}

void arraySort(wordItem list[], int length) //sort descending
{
  bool sorted=false;
  while(sorted==false)
  {
    sorted=true;
    for(int i=0; i<length; i++)
    {
      if (list[i].count<list[i+1].count)
      {
        swap(list[i], list[i+1]);
        sorted=false;
      }
    }
  }
}

void printTopN(wordItem wordItemSorted[], int topN)
{
  int size=0;
  for(int i=0; i<topN; i++)
  {
    size++;
    cout<<wordItemSorted[i].count<<" - "<<wordItemSorted[i].word<<endl;
  }
}

int main(int argc, char *argv[])
{
  // wordItem *wordItemList = new wordItem[100]; //would declaring this in main and readFile cause issues?

  // string ignoreWords[50];

  getStopWords(argv[3], ignoreWords);

  int numWords=0, finIndex=0, doubleCount=0;
  int length = readFile(argv[2], &numWords, &finIndex, &doubleCount); //changes the value of numWords, finIndex, and doubleCount

  getTotalNumberNonStopWords(wordItemList, length);

  arraySort(wordItemList, length);

  printTopN(wordItemList, stoi(argv[1]));
  cout<<"#"<<endl;
  cout<<"Array doubled: "<<doubleCount<<endl;
  cout<<"#"<<endl;
  cout<<"Unique non-common words: "<<length<<endl;
  cout<<"#"<<endl;
  cout<<"Total non-common words: "<<numWords<<endl;

  return 0;
}
