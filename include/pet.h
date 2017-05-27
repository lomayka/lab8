/** 
    @file
    @brief Describing type pet
*/
#ifndef PET_H
#define PET_H

#include <iostream>

using namespace std;

class Pet{
    int _id;
    int _age;
    string _name;
    string _species;
public:
    /**
        @brief default public constructor for Pet
    */
    Pet(int id, int age, string name, string species);
    /**
        @brief delete the request
    */
    ~Pet();
    /**
        @brief get age of Pet
        @return the string of the Petname
    */
    int age();
    /**
        @brief get id of Pet
        @return the string of the id of Pet
    */    
    int id();
    
    /**
        @brief get name of Pet
        @return the string of Pet name
    */
    string name();
    /**
        @brief get species of Pet
        @return the string of Pet species
    */
    string species();


    /**
        @brief get data that contain the field of Place
        @param field - string that defines field data to return
        @return string that of data at the field
    */
    string requestOfString(string field);
};

#endif //PET_H