//#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x28, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

#define echoPin 4
#define trigPin 2
//#define LEDPin 13

EthernetClient client;
 
int maximumRange = 50;
int minimumRange = 00;
long duration, distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println("Initialize DHCP....");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    while (true) {
      delay(1);
    }
  }
  Serial.println(Ethernet.localIP());
}


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distance = duration/58.2;

  if(distance >= maximumRange || distance <= minimumRange){
//    Serial.println("-1");
  }else{
    Serial.println(distance);

    String kiriman = "jarak=";
    kiriman += distance;
    
    if (client.connect("192.168.196.130",80)){
     Serial.println("Sending to Server: ");
     client.println("POST /pkl/terima3.php HTTP/1.1");
     Serial.println("POST /pkl/terima3.php HTTP/1.1");
     client.println("Host: 192.168.196.130");
     client.println("Content-Type: application/x-www-form-urlencoded");
     client.println("Connection: close");
     client.println("User-Agent: Arduino/1.0");
     client.print("Content-Length: ");
     client.println(kiriman.length());
     client.println();
     client.print(kiriman);
     client.println();
     Serial.println("terkoneksi");
   }else {
    Serial.println("tidak terkoneksi");  
   }
   
   if (client.connected()){
    client.stop(); 
   }
    delay(1000);
  }

}
