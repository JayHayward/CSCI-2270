//Array Doubling

#include <iostream>
#include <fstream>
using namespace std;

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
