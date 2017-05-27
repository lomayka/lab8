#include <request.h>
#include <iostream>
#include <cctype>

using namespace std;

Request::Request(){
    _method = "";
    _path = "";
    _key = "";
    _value = "";
}

Request::Request(string request){
    //find method
    size_t endMethod = request.find(" ");
    _method = string(request, 0, endMethod);
    //find path
    size_t endPath = request.find(" HTTP/1.");
    string path = string(request, endMethod + 1, endPath - endMethod - 1);
    _path = path;
    //parse path
    size_t quest = path.find("?");
    size_t equal = path.find("=");
    if(quest != string::npos && equal != string::npos){
        _key = string(path, quest + 1, equal - quest - 1);
        _value = string(path, equal + 1, path.length() - equal);
    } else {
        size_t slash = path.find("/", 1);
        _key = "id";
        _value = string(path, slash + 1, path.length() - slash);
    }
}

Request::~Request(){}

string Request::method() { return _method; }
string Request::path(){ return _path; }
string Request::key(){ return _key; }
string Request::value(){ return _value; }