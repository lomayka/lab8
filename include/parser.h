/**
    @file
    @brief Json parser for responce strings
*/
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <pet.h>

using namespace std;

/**
    @brief get server information
    @return return Json string of server information
*/
string jsonServerInfo(void);

/**
    @brief get all Pets converted to JSon string
    @param pets - vector of all my Pets (cannot pick my favorites, becouse all of pets are cool)
    @return Json string of my pets
*/
string jsonPets(vector<Pet*> pets);

/**
    @brief get all Pets with keys mathing values
    @param pets - vector of all my pets 
    @param key - field of used data
    @param value - content of the field to search by
    @return 
*/
string jsonPetsByKey(vector<Pet*> pets, string key, string value);

/**
    @brief get information about file
    @param filePath - path to file
    @return string in Json format that contain information about file
*/
string jsonFile(string filePath);

/**
    @brief get information about file content
    @param filePath - path to file
    @return string in Json format that contain information about file content
*/
string jsonFileContent(string filePath);

#endif //PARSER_H