
#include <response.h>
#include <parser.h>
#include <pet.h>


Response::~Response() {};

Response::Response(Request * request, vector<Pet*> pets){
    string file = "/home/pestis/cprojects/lab8/data/data.txt";
    string headers = 
        "Server: Cowboy\r\n"
        "Connection: close\r\n\r\n";
    string status = "";
    string content = "";
    string contentInfo = "";

    if(request->method() == "GET"){
        if(request->path() == "/") content = jsonServerInfo();
        else if(request->path() == "/favorites") content = jsonPets(pets);
        else if(request->path().find("/favorites?") != string::npos ||
                request->path().find("/favorites/") != string::npos) {
            content = jsonPetsByKey(pets, request->key(), request->value());
        } else if(request->path() == "/file") content = jsonFile(file);
        else if(request->path() == "/file/data") content = jsonFileContent(file);
        else {
            content = "NOT FOUND";
        }

        if(content != "NOT FOUND"){
            status = "HTTP/1.1 200 OK\r\n";
            contentInfo = "Content-Type: application/json; charset=utf-8\r\n"
                          "Content-Length: " + to_string(content.length()) + "\r\n";
        } else {
            status = "HTTP/1.1 404 NOT FOUND\r\n";
            contentInfo = "Content-Type: text; charset=utf-8\r\n"
                          "Content-Length: " + to_string(content.length()) + "\r\n";
        }
    } else {
        status = "HTTP/1.1 400 Bad Request\r\n";
    }
    _message = status + contentInfo + headers + content;
}

string Response::message(){ return _message; }