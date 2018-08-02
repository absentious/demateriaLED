#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>

#define WSout 5                                     // Pin D1
#define ARTNET_PORT 6454

#define PIXELCOUNT 100


byte hData[318];

const int number_of_channels=30; //512 for 512 channels

const char* ssid     = "homegirls";
const char* password = "claradebcarrie!";

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXELCOUNT,WSout,NEO_GRB+NEO_KHZ800);

WiFiUDP udp;


IPAddress local_ip(192, 168, 1, 190);
IPAddress gateway_ip(192, 168, 1, 1);
IPAddress subnet_ip(255, 255, 255, 0);

void setup() {
  
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.print("Connecting");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  WiFi.config(local_ip, gateway_ip, subnet_ip);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  udp.begin(ARTNET_PORT); // Open ArtNet port

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


pixels.begin();

  for(byte i=0;i<PIXELCOUNT;i++){
    pixels.setPixelColor(i, Color(0,0,0));
  }
  pixels.show();
  
}

void loop() {
  if (udp.parsePacket()) {
    udp.read(hData, 318);
   // pixels.setPixelColor(0, Color(hData[19], hData[20],hData[21]));
  for ( int n=0; n<30; n++){   
     pixels.setPixelColor(n, Color(hData[(n * 3) + 19], hData[(n *3)+20],hData[(n *3)+21]));
    }
   pixels.show();
  }
}

uint32_t Color(byte r, byte g, byte b){
  uint32_t c;
  c = r;
  c <<=8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}
