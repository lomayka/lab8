/**
    @file
    @brief Wrapper for server response
*/
#ifndef RESPONSE_H
#define RESPONSE_H

#include <request.h>
#include <pet.h>
#include <iostream>
#include <vector>

using namespace std;

/**
    @class Response
    @brief defines a server response
*/
class Response{
    string _message;
public:
    /**
        @brief public constructor for Response that process vector of pets according to request
        @param request - Request from client to process data
        @param pets vector of places that processed according to request
    */
    Response(Request * request, vector<Pet*> pets);

    /**
        @brief default public destructor for Response
    */
    ~Response();

    /**
        @brief get message from Response
        @return message that contained in Response
    */
    string message();
};


#endif //RESPONSE_H
