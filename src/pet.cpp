#include <pet.h>

Pet::Pet(int id,int age, string name, string species){
    _id = id;
    _age = age;
    _name = name;
    _species = species;
}

Pet::~Pet() {};

int Pet::age() { return _age; }
int Pet::id() { return _id; }
string Pet::name() { return _name; }
string Pet::species() { return _species; }
string Pet::requestOfString(string field){
    if (!field.compare("id")) return to_string(_id);
    if (!field.compare("age")) return to_string(_age);
    if (!field.compare("name")) return _name;
    if (!field.compare("species")) return _species;
    return "NO SUCH FIELD";
}