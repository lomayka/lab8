/**
    @file
    @brief Wrapper for client request
*/
#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>

using namespace std;

/**
    @class Request
    @brief defines a client request
*/
class Request{
    string _method;
    string _path;
    string _key;
    string _value;
public:
    /**
        @brief default public constructor for Request
    */
    Request();

    /**
        @brief public constructor for Request that process string as request
        @param request - string for processing request
    */
    Request(string request);

    /**
        @brief default public destructor for Request
    */
    ~Request();

    /**
        @brief get method from client Request
        @return string that defines method of Request
    */
    string method();

    /**
        @brief get path from client Request
        @return string that defines path of Request
    */
    string path();
    
    /**
        @brief get specified key in path from client Request
        @return string that defines specified key in path of Request
    */
    string key();
    
    /**
        @brief get specified value in path from client Request
        @return string that defines specified value in path of Request
    */
    string value();
};

#endif //REQUEST_H