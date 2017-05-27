#include <parser.h>
#include <iostream>
#include <vector>
#include <jansson.h>
#include <time.h>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

/**
    @brief subsidiary function to read file
    @param filePath - path to file that will be read
    @return string that represented content of file
*/
string readFile(string filePath);

string jsonServerInfo(void){
    json_t * json = json_object();
    json_object_set_new(json, "title", json_string("Server with all my pets. The task was to desribemy favorites, but I think all pets are cool"));
    json_object_set_new(json, "developer",json_string( "Denys Kolomiiets"));
    //get current time
    time_t seconds = time(0);
    tm* timeinfo = localtime(&seconds);
    //set current time
    string t = string(asctime(timeinfo));
    const char * correct = t.erase(t.length() - 1, t.length()).c_str();
    json_object_set_new(json, "time", json_string(correct));
    char * str = json_dumps(json, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
    string jsonString(str);
    free(str);
    json_decref(json);
    return jsonString;
}

string jsonPets(vector<Pet*> pets){
    json_t * json = json_array();
    for(Pet * pet : pets){
        json_t * pt = json_object();
        json_object_set_new(pt, "id", json_integer(pet->id()));
        json_object_set_new(pt, "name", json_string(pet->name().c_str()));
        json_object_set_new(pt, "age", json_integer(pet->age()));
        json_object_set_new(pt, "species", json_string(pet->species().c_str()));
        json_array_append(json, pt);
        json_decref(pt);
    }
    char * str = json_dumps(json, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
    string jsonString(str);
    free(str);
    json_decref(json);
    return jsonString;
}

string jsonPetsByKey(vector<Pet*> pets, string key, string value){
    Pet * check = new Pet (0,0,"","");
    if(check->requestOfString(key).compare("NOT FIELD")){
        json_t * json = json_array();
        bool Found = false;
        for(Pet * pet : pets){
            if(pet->requestOfString(key) == value){
                Found = true;
                json_t * pt = json_object();
                json_object_set_new(pt, "id", json_integer(pet->id()));
                json_object_set_new(pt, "name", json_string(pet->name().c_str()));
                json_object_set_new(pt, "age", json_integer(pet->age()));
                json_object_set_new(pt, "species", json_string(pet->species().c_str()));
                json_array_append(json, pt);
                json_decref(pt);
            } 
        }
        char * str = json_dumps(json, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
        string jsonString(str);
        free(str);
        json_decref(json);
        if(!Found) return "NOT FOUND";
        return jsonString;
    }
    delete check;
    return "NOT FOUND";
}

string jsonFile(string filePath){
    string fileContent = readFile(filePath.c_str());
    if (fileContent == "NOT FOUND") {
        cerr << "Can't open file" << endl;
        return fileContent;
    }
    json_t * json = json_object();
    json_object_set_new(json, "filename", json_string( "data.txt"));
    json_object_set_new(json, "size(bytes)",json_integer(fileContent.size()));
    json_object_set_new(json, "content",  json_string(fileContent.c_str()));
    char * str = json_dumps(json, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
    string jsonString(str);
    free(str);
    json_decref(json);
    return jsonString;
}


string jsonFileContent(string filePath){
    string fileContent = readFile(filePath.c_str());
    if (fileContent == "NOT FOUND") {
        cerr << "Can't open file" << endl;
        return fileContent;
    }
    int i = 0;
    long max = 0;
    while (fileContent[i]){
        if (isdigit(fileContent[i])){
            string number;
            while (isdigit(fileContent[i])){
                number += fileContent[i];
                i++;
            }
            if (max < stoi(number)) max = stoi(number);
            number.clear();
        }
        i++;
    }
    json_t * json = json_object();
    json_object_set_new(json, "filename", json_string( "data.txt"));
    json_object_set_new(json, "the number of symbols in file",  json_integer(i));
    json_object_set_new(json, "most significant digit", json_integer(max));
    
    char * str = json_dumps(json, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
    string jsonString(str);
    free(str);
    json_decref(json);
    return jsonString;
}


string readFile(string filePath){
    string buf;
    string result = "";
    ifstream myfile (filePath);
    if (!myfile.is_open()){
        return "NOT FOUND";
    }
    while (!myfile.eof()){
        getline(myfile, buf);
        result += buf;
    }
    myfile.close();
    return result;
}