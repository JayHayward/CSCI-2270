//
//  CommunicationNetwork.h
//  Assignment3
//
//  Created by Josiah Buxton on 2/4/2018
//
#ifndef COMMUNICATIONNETWORK_H
#define COMMUNICATIONNETWORK_H
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

// Struct
struct city{
    std::string cityName;
    std::string message;
    city *next;

    city(){}; // default constructor

    city(std::string initName, city *initNext, std::string initMessage)
    {
        cityName = initName;
        next = initNext;
        message = initMessage;
    }

};

/*Add a new city to the linked list between the city *previous and the city that
follows it in the network. The name of the new city is in the argument cityName.
Return  the head of  the linked  list.
*/
city *addCity(city *head, city *previous, std::string cityName);

/*Open the file messageIn.txt and transmit the message between all cities in the
network word by word. A word needs to be received at the end of the network
before sending the next  word. Only one city can hold the message at a time; as soon
as it is passed to the next city, it needs to be deleted from the sender city.
*/
void transmitMsg(city *head);

// Go through each city in the network starting at the head and print the name of the city.
void printPath(city *head);

// Create a linked list from the list of cities provided above and return the head of the list.
city *buildNetwork();

#endif // COMMUNICATIONNETWORK_H
