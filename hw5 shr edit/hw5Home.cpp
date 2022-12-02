
// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "hw5server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

// ecs36b
#include "IOT_Thing.h"
#include "Person.h"
#include "Thing.h"
#include <time.h>
#include "Shadow_Thing.h"
#include "hw5server.cpp"
#include <jsonrpccpp/server/connectors/httpserver.h>

using namespace jsonrpc;
using namespace std;

int main(){
    Person LittleRedRidingHood;
    LittleRedRidingHood.setDescription("Little Red")
    
    Thing cap, cake, wine;
    cap.setName("red cap");
    cake.setName("cake");
    wine.setName("wine");

    HttpClient httpclient("http://127.0.0.1:7374");
    hw5Client myClient(httpclient, JSONRPC_CLIENT_V2);
    Json::Value myv;

    try {
    std::cout << LittleRedRidingHood.dump2JSON().toStyledString() << std::endl;
    myv = myClient.move("move", "Person",
      LittleRedRidingHood.dump2JSON(),
      meetingSpot.dump2JSON(),
			"987654321");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

    HttpServer httpserver(7374);
    Myhw5Server s(httpserver,
	 	JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
    s.StartListening();
    std::cout << "Hit enter to stop the server" << endl;
    getchar();

    s.StopListening();

}
