#include <iostream>
#include <vector>
#include <progbase-cpp/net.h>

#include <request.h>
#include <response.h>
#include <pet.h>

using namespace std;
using namespace progbase::net;

#define BUFFER_LENGTH 10000

vector<Pet*> createPets(void);
void closingEvent(vector<Pet*> pets);

int main(void){
    vector<Pet*> pets = createPets();
	const int serverPort = 8082;
    TcpListener listener;
    NetMessage message(BUFFER_LENGTH);
    try {
        listener.bind(IpAddress("127.0.0.1", serverPort));
        listener.start();
        while (true) {
            cout << ">> Waiting for clients at " << serverPort << "..." << endl;
            TcpClient * client = listener.accept();
            client->receive(message);
            cout << ">> Received: " << endl << message.dataAsString() << endl;
            Request * req = new Request(message.dataAsString());
            Response * res = new Response(req, pets);
            message.setDataString(res->message());
            client->send(message);
            cout << ">> Response sent." << endl;
            delete client;
            delete req;
            delete res;
        }
    } catch(NetException const & exc) {
        cerr << exc.what() << endl;
    }
    closingEvent(pets);
    return 0;
}

vector<Pet*> createPets(void){
    vector<Pet*> pets = {};
    pets.push_back(new Pet(0001, 15, "Jim", "dog"));
    pets.push_back(new Pet(0002, 2, "Patsan", "tortle"));
    pets.push_back(new Pet(0003, 1, "Musya", "cat"));
    pets.push_back(new Pet(0004, 2, "Lisa", "cat"));
    pets.push_back(new Pet(0005, 2, "Sonya", "cat"));
    pets.push_back(new Pet(0006, 6, "Fedya", "dog"));
    return pets;
}

void closingEvent(vector<Pet*> pets){
    for(Pet * pt : pets) delete pt;
}

