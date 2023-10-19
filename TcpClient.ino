/*
 * UIPEthernet TcpClient example.
 *
 * UIPEthernet is a TCP/IP stack that can be used with a enc28j60 based
 * Ethernet-shield.
 *
 * UIPEthernet uses the fine uIP stack by Adam Dunkels <adam@sics.se>
 *
 *      -----------------
 *
 * This TcpClient example gets its local ip-address via dhcp and sets
 * up a tcp socket-connection to 192.168.0.1 port 5000 every 5 Seconds.
 * After sending a message it waits for a response. After receiving the
 * response the client disconnects and tries to reconnect after 5 seconds.
 *
 * Copyright (C) 2013 by Norbert Truchsess <norbert.truchsess@t-online.de>
 */

#include <UIPEthernet.h>

EthernetClient client;
signed long next;

void setup() {

  Serial.begin(9600);

  //the MAC for the shield:
  uint8_t mac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0xED};
  //the IP address for the shield:
  byte ip[] = { 169, 254, 102, 173 };
  //the gateway for the shield:
  byte gateway[] = { 169, 254, 1, 1 };
  //the sbnet for the shield:
  byte subnet[] = {255,255,0,0};
  byte myDns[] = { 169, 254, 1, 1 };

  
  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  delay(1000);
  Serial.print("localIP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("subnetMask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("gatewayIP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("dnsServerIP: ");
  Serial.println(Ethernet.dnsServerIP());

}

void loop() 
{      
      Serial.println("Client connecting........");
      //Try to connect socket of TCP Server
      if (client.connect(IPAddress(169,254,102,172),8077))
       {
        Serial.println("Client connected");
        delay(500);     
        int size;
        //When client is connected...
        while(client.connected())
        {
          delay(500);
          //Check dada from server
          while((size = client.available()) > 0)
            { 
              //Read data from server..
              uint8_t* msg = (uint8_t*)malloc(size);
              size = client.read(msg,size);
              Serial.write(msg,size);
              //Send data back to server
              client.write(msg,size);
              free(msg);
              delay(500);
            }
        }
       }   
      else
       {
        Serial.println("Client connect failed");
       }
      delay(1000);
}
