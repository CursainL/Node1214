#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

Servo myservo;
int val;

#define SSID "Liang's SE"                                   
#define PASS "qsczsead"     

ESP8266WebServer server(80);

void zero(){
  myservo.write(90); 
}



String webSite;


void buildWeb(){
    webSite += "<html>";
    webSite+="<head>\n";
    webSite+="<meta charset='UTF-8'/>\n";
  webSite+="<title>Servo control</title>\n";
    webSite+="<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>";
    webSite+="<script>";
    webSite+="$(document).ready(function(){";
    webSite+="$(\"[type = range]\").change(function(){";
    webSite+="var redval = $(\"#red\").val();";
    webSite+="$(\"#red-text\").text(redval);";
    webSite+="});";
    webSite+="});";
    webSite+="</script>";
    webSite+="</head>\n";
    webSite += "<body>";
    webSite += "<h1>Servo Motor Control</h1>";
    webSite += "<form action=\"/form1\">";
    webSite += "<p>Motor degree : <span id = \"red-text\">0</span></p>";
    webSite += "<input type=\"range\" id=\"red\" name=\"R-led\" min=\"-90\" max=\"89\" value=\"0\">";
webSite += "<input type=\"submit\" value=\"submit\"></form>";
webSite += "</body></html>";
}

void handleRoot(){
server.send(200,"text/html",webSite);
}

void ColorPicker(){
int red_color = server.arg("R-led").toInt();
int motordegree = map(red_color,-90,89,0,180);
  
  myservo.write(motordegree); 
    server.send(200,"text/html",webSite);

  delay(1000);
  zero();
    
}
void handleNotFound(){
server.send(404,"text/html","404 Error!");
}

void setup() {  
Serial.begin(115200);
myservo.attach(5); 
myservo.write(90); 
// put your setup code here, to run once:
buildWeb();
WiFi.begin(SSID, PASS); 

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}

server.on("/",handleRoot);
server.on("/form1",ColorPicker);
server.onNotFound(handleNotFound);

server.begin();
Serial.println(WiFi.localIP());  
}
void loop() {
// put your main code here, to run repeatedly:
server.handleClient();  
}

