//MovieTree.cpp

#include "MovieTree.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

MovieTree::MovieTree()
{
  root=NULL;
}

MovieTree::~MovieTree()
{

}


// all functions for Assignment 6 implementation

#include <iostream>
#include "MovieTree.hpp"

using namespace std;

// helper function to add the node to the linked list

MovieNodeLL *addHelper(MovieNodeLL *head, MovieNodeLL *mnl)
{
  if(head->title > mnl->title)
  {
    mnl->next = head;
    return mnl;
  }
  else
  {
    MovieNodeLL *temp = head;
    while(temp != NULL)
    {
      if(temp->next == NULL)
      {
        temp->next = mnl;
        break;
      }
      else
      {
        if(temp->next->title > mnl->title)
        {
          mnl->next = temp->next;
          temp->next = mnl;
          break;
        }
      }
      temp = temp->next;
    }
  }
  return head;
}



void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity)
{
  // check if the movie is already in the linked list
  // by searching for the first letter of the given title
  // if the first letter of the title does not exist, add it to the BST

  // create new node
  MovieNodeLL *n = new MovieNodeLL(ranking, title, releaseYear, quantity);
  MovieNodeBST *b = new MovieNodeBST(title[0]);

  if(root == NULL)
  {
      root = new MovieNodeBST(title[0]);
      root->head = n;
  }
  else if(root->letter == title[0])
  {
      // add to the linked list (head node)
      root->head = addHelper(root->head, n);
  }
  else
  {
      // tree already has a root
      MovieNodeBST *w = root;
      while(w->letter != title[0])
      {
          // go through the left children
          if(w->letter > title[0])
          {
              if(w->leftChild == NULL)
              {
                  w->leftChild = b;
                  b->parent = w;
                  b->head = n; // set the head of the BST to the new movies linked list

              }
              else if(w->leftChild->letter == title[0])
              {
                  // if the letter is in the tree
                  // add the movie to the linked list
                  w->leftChild->head = addHelper(w->leftChild->head, n);
                  w->leftChild = b;
                  b->parent = w;
                  b->head = n;
              }
              w = w->leftChild;
          }

          else
          {
              // go through the right children
              if(w->rightChild == NULL)
              {
                  w->rightChild = b;
                  b->parent = w;
                  b->head = n;
              }
              else if(w->rightChild->letter == title[0])
              {
                  // if the letter is in the tree
                  // add the movie to the linked list
                  w->rightChild->head = addHelper(w->rightChild->head, n);
              }
              w = w->rightChild;
          }
      }
  }
}



void MovieTree::deleteMovieNode(string title)
{
    // flag is like a boolean- in order to see what node needs to be deleted
    int flag = -1;
    MovieNodeBST* movieLetter = searchBST(root, title);
    if(movieLetter == NULL)
    {
        cout << "Movie not found."<< endl;
    }
    else
    {
        MovieNodeLL* deleteMovie = searchLL(movieLetter->head, title);
        if(deleteMovie == NULL)
        {
            cout << "Movie not found."<< endl;
            return;
        }
        else if(movieLetter->head != deleteMovie)
        {
            MovieNodeLL* temp = movieLetter->head;
            MovieNodeLL* prev = NULL;
            while(temp!= NULL)
            {
                if(temp->title == title)
                {
                    if(temp->next == NULL)
                        prev->next = NULL;
                    else
                    {
                        prev->next = temp->next;

                    }
                    delete deleteMovie;
                    return;
                }
                prev = temp;
                temp = temp->next;
            }
        }
        else
        {
            if(movieLetter->head->next == NULL)
            {
                delete deleteMovie;
                flag = 0;
            }
            else
            {
                movieLetter->head = deleteMovie->next;
                delete deleteMovie;

            }

            if(flag == 0)
            {
                if(movieLetter->leftChild == NULL && movieLetter->rightChild == NULL)
                // no children
                {
                    if(movieLetter == root)
                    {
                        delete movieLetter;
                        root = NULL;
                    }
                    else
                    {
                        MovieNodeBST* prev = movieLetter->parent;
                        if(prev->leftChild == movieLetter)
                        {
                            delete movieLetter;
                            prev->leftChild = NULL;
                        }
                        else
                        {
                            delete movieLetter;
                            prev->rightChild = NULL;
                        }
                    }
                }
                else if(movieLetter->leftChild != NULL && movieLetter->rightChild == NULL)
                // one child
                {
                    if(movieLetter != root)
                    {
                        MovieNodeBST *prev = movieLetter->parent;
                        if(prev->leftChild == movieLetter)
                        {
                            prev->leftChild = movieLetter->leftChild;
                            movieLetter->leftChild->parent = prev;
                        }
                        else
                        {
                            prev->rightChild = movieLetter->leftChild;
                            movieLetter->leftChild->parent = prev;
                        }
                        delete movieLetter;
                    }
                    else
                    {
                        root = movieLetter->leftChild;
                        movieLetter->leftChild->parent = NULL;
                        delete movieLetter;
                    }

                }

                else if(movieLetter->leftChild == NULL && movieLetter->rightChild != NULL)
                // one child
                {
                    if(movieLetter != root)
                    {
                        MovieNodeBST *prev = movieLetter->parent;
                        if(prev->rightChild == movieLetter)
                        {

                            prev->rightChild = movieLetter->rightChild;
                            movieLetter->rightChild->parent = prev;
                        }
                        else
                        {

                            prev->leftChild = movieLetter->rightChild;
                            movieLetter->rightChild->parent = prev;
                        }
                        delete movieLetter;
                    }
                    else
                    {

                        root = movieLetter->rightChild;
                        movieLetter->rightChild->parent = NULL;
                        delete movieLetter;

                    }
                }
                else
                //two child case
                {

                    MovieNodeBST* min = treeMinimum(movieLetter->rightChild);
                    movieLetter->head = min->head;
                    movieLetter->letter = min->letter;

                    if(min->rightChild)
                    {

                        min->rightChild->parent = min->parent;

                    }
                    if(movieLetter->rightChild == min)
                    {
                        movieLetter->rightChild = min->rightChild;
                        delete min;
                        return;
                    }
                    min->parent->leftChild = min->rightChild;
                    delete min;
                }
            }
        }
    }
}


MovieNodeBST *MovieTree::treeMinimum(MovieNodeBST *node)
{
    // traverse through the left side of the tree where the minimum values would be
    if(node != NULL)
    {
        while(node->leftChild != NULL)
        {
            node = node->leftChild;
        }
        return node;
    }
    else
    {
        return NULL;
    }
}




MovieNodeBST* MovieTree::searchBST(MovieNodeBST *node, string value)
{
  MovieNodeBST *n = new MovieNodeBST;
  n = node;
  if(n == NULL)
  {
    return n;
  }
  else
  {
    if(n->letter == value[0])
    {
      return n;
    }
    else if(n->letter > value[0])
    {
      return searchBST(n->leftChild, value);
    }
    else
    {
      return searchBST(n->rightChild, value);
    }
  }
}



void MovieTree::findMovie(string title)
{
  MovieNodeBST *f = new MovieNodeBST;
  l = searchBST(root, title);
  if(l == NULL)
  {
    cout << "Movie not Found." << endl;
  }
  else
  {
    MovieNodeLL *m = searchLL(l->head, title);
    cout << "Movie Info:" << endl;
    cout << "===========" << endl;
    cout << "Ranking:" << m->ranking << endl; cout << "Title:" << m->title << endl;
    cout << "Year:" << m->year << endl;
    cout << "Quantity:" << m->quantity << endl;
  }
}


void MovieTree::rentMovie(string title)
{
    MovieNodeBST *l = new MovieNodeBST;
    l = searchBST(root, title);
    if(l == NULL)
        {
            cout << "Movie not Found." << endl;
        }
        else
        {
            MovieNodeLL *m = searchLL(l->head, title);
            m->quantity--;
            cout << "Movie has been rented." << endl;
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << m->ranking << endl; cout << "Title:" << m->title << endl;
            cout << "Year:" << m->year << endl;
            cout << "Quantity:" << m->quantity << endl;


        }

}


void MovieTree::countMovieNodes(MovieNodeBST *node, int *c)
{
    *c = *c + 1;

    if(node == NULL)
    {
        *c = 0;
        return;
    }
    if(node == root)
    {
        *c = *c + 1;
    }
    if(node->leftChild != NULL)
    {
        countMovieNodes(node->leftChild, c);
    }
    if(node->rightChild != NULL)
    {
        countMovieNodes(node->rightChild, c);
    }
}
