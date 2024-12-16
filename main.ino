//acces point
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11

//DHT interface HTML code
"<!DOCTYPE html><html><head><title>Temp_and_humidity</title><meta name='mobile-web-app-capable' content='yes' />"
"<style>p {margin: 1%;font-size: 40px;text-align: center;color: black;}h1 {margin: 1%;text-align: center;color: black;}h2 {margin: 1%;text-align: center;color: black;}</style></head>"
"<body><h1>TEMPERATURE</h1><p>";

String Dht_html_II = "&ring;C</p><h1>HUMIDITY</h1><p>";

String Dht_html_III = "%</p><h2>Refresh website to get fresh data :)</h2></body></html>";


//color interface HTML code---------------

String webpage = ""
"<!DOCTYPE html><html><head><title>RGB control</title><meta name='mobile-web-app-capable' content='yes' />"
"<meta name='viewport' content='width=device-width' /></head><body style='margin: 0px; padding: 0px;'>"
"<canvas id='colorspace'></canvas></body>"
"<script type='text/javascript'>"
"(function () {"
" var canvas = document.getElementById('colorspace');"
" var ctx = canvas.getContext('2d');"
" function drawCanvas() {"
" var colours = ctx.createLinearGradient(0, 0, window.innerWidth, 0);"
" for(var i=0; i <= 360; i+=10) {"
" colours.addColorStop(i/360, 'hsl(' + i + ', 100%, 50%)');"
" }"
" ctx.fillStyle = colours;"
" ctx.fillRect(0, 0, window.innerWidth, window.innerHeight);"
" var luminance = ctx.createLinearGradient(0, 0, 0, ctx.canvas.height);"
" luminance.addColorStop(0, '#ffffff');"
" luminance.addColorStop(0.05, '#ffffff');"
" luminance.addColorStop(0.5, 'rgba(0,0,0,0)');"
" luminance.addColorStop(0.95, '#000000');"
" luminance.addColorStop(1, '#000000');"
" ctx.fillStyle = luminance;"
" ctx.fillRect(0, 0, ctx.canvas.width, ctx.canvas.height);"
" }"
" var eventLocked = false;"
" function handleEvent(clientX, clientY) {"
" if(eventLocked) {"
" return;"
" }"
" function colourCorrect(v) {"
" return Math.round(1023-(v*v)/64);"
" }"
" var data = ctx.getImageData(clientX, clientY, 1, 1).data;"
" var params = ["
" 'r=' + colourCorrect(data[0]),"
" 'g=' + colourCorrect(data[1]),"
" 'b=' + colourCorrect(data[2])"
" ].join('&');"
" var req = new XMLHttpRequest();"
" req.open('POST', '?' + params, true);"
" req.send();"
" eventLocked = true;"
" req.onreadystatechange = function() {"
" if(req.readyState == 4) {"
" eventLocked = false;"
" }"
" }"
" }"
" canvas.addEventListener('click', function(event) {"
" handleEvent(event.clientX, event.clientY, true);"
" }, false);"
" canvas.addEventListener('touchmove', function(event){"
" handleEvent(event.touches[0].clientX, event.touches[0].clientY);"
"}, false);"
" function resizeCanvas() {"
" canvas.width = window.innerWidth;"
" canvas.height = window.innerHeight;"
" drawCanvas();"
" }"
" window.addEventListener('resize', resizeCanvas, false);"
" resizeCanvas();"
" drawCanvas();"
" document.ontouchmove = function(e) {e.preventDefault()};"
" })();"
"</script></html>";

//user interface HTML code----------------
String html = R"***(
<!DOCTYPE html>
<head>
    <style>
    html, body{
        margin: 0;
        padding: 0;
    }
    .top_bar{
        margin: 0;
        padding: 0;
        width: 100%;
        height: 50px;
        background-color: rgb(134, 134, 134);
        text-align: center;
    }
    .top_bar p{
        margin: 0;
    }
    .table{
        margin: 2%;
        background-color: rgb(134, 134, 134);
        border-radius: 10px;
        border-style: solid;
        border-color: black;
        border-width: 2px;
    }
    .table p{
        margin: 1%;
        font-size: large;
        color: white;
    }
    .table a
    {
        -webkit-appearance: button;
        -moz-appearance: button;
        appearance: button;
        margin: 0.5%;
        text-decoration: none;
        color: initial;
    }
    .table_diff{
        margin: 2%;
        background-color: rgb(237, 245, 194);
        border-radius: 10px;
        border-style: solid;
        border-color: black;
        border-width: 2px;
    }
    .table_diff p{
        margin: 1%;
        font-size: large;
        text-align: center;
        color: black;
        
    }
    .insider_div{
        float: right;
        margin: 1%;
        background-color: violet;
    }
    .table_diff button{
        margin: 1%;
        font-size: large;
        text-align: center;
        background-color: rgb(134, 134, 134);

    }
    </style>
</head>
<body>
    <div class="top_bar">
        <p>CONTROL STATION<br>LAMP</p>
    </div>
    <div class="table">
        <a href=/custom><b>CUSTOM   COLOR</b></a>
    </div>
    <div class="table_diff">
        <p><b>COLOR MODES</b></p>
    </div>
    <div class="table">
        <a href=/rainbow><b>RAINBOW MODE</b></a>
    </div>
    <div class="table">
        <a href=/fire><b>FIRE MODE</b></a>
    </div>
    <div class="table">
        <a href=/warm><b>WARM MODE</b></a>
    </div>
    <div class="table">
        <a href=/cold><b>COLD MODE</b></a>
    </div>
    <div class="table">
        <a href=/water><b>WATER MODE</b></a>
    </div>
    <div class="table">
        <a href=/bright><b>BRIGHT MODE</b></a>
    </div>
    <div class="table">
        <a href=/hacker><b>HACKER MODE</b></a>
    </div>
    <div class="table">
        <a href=/r_blink><b>RANDOM BLINK MODE</b></a>
    </div>
   
</body>
</html>
)***";
//--------------------------------------
#define R 13
#define G 12
#define B 15
#define Dh 5
#define randomPin 16
//DHT displaying
String wholeDHT_string;
float dh;
float dt;
//RAinbow
int rVal = 254;
int gVal = 1;
int bVal = 127;

int rDir = -1;
int gDir = 1;
int bDir = -1;
//LED
long randomNumR;
long randomNumG;
long randomNumB;
int option = 0;
//AP
const char* ssid = "lamp";
const char* password = "12345678";
IPAddress IPaddr (192, 168, 1, 1);
IPAddress IPmask(255, 255, 255, 0);
ESP8266WebServer server(80);
//dht
float h = 0;
float h_display = 0;
//
int Rvalue;
int Gvalue;
int Bvalue;
bool change_dirR;//used for color changing
bool change_dirG;
bool change_dirB;
DHT dht(5,DHTTYPE);
//--------------------------------------
//bellow functions of displayijng light problably int to switch and that all in loop function| I DUNNO| OK IT WORKED :)
//--------------------------------------
void handleRoot()
{
  server.send(200, "text/html", html);
}
void Displ_TH(){
  
  dt = dht.readTemperature();
  dh = dht.readHumidity();
  wholeDHT_string = Dht_html_I + dt + Dht_html_II + dh + Dht_html_III;
  server.send(200,"text/html",wholeDHT_string);
}
void Custom()//custom color website
{
  option = 1;
  
  // read RGB arguments
  String red = server.arg(0); 
  String green = server.arg(1);
  String blue = server.arg(2);
  
  if((red != "") && (green != "") && (blue != ""))
  {
    analogWrite(R, 1023 - red.toInt());
    analogWrite(G, 1023 - green.toInt());
    analogWrite(B, 1023 - blue.toInt());
  }

  server.send(200, "text/html", webpage);
}
void ToHumidity()
{
  option = 2;
  
  server.send(200, "text/html", html);
}
void Rainbow()
{
  option = 3;
 
  server.send(200, "text/html", html);
}
void Fire(){
  option = 4;
  
  server.send(200, "text/html", html);
}
void Warm(){
  option = 5;
  
  server.send(200, "text/html", html);
}
void Cold(){
  option = 6;
  
  server.send(200, "text/html", html);
}
void Water(){
  option = 7;
  
  server.send(200, "text/html", html);
}
void Bright(){
  option = 8;
  
  server.send(200, "text/html", html);
}
void Hacker(){
  option = 9;
  
  server.send(200, "text/html", html);
}
void R_blink(){
  option = 10;
  
  server.send(200, "text/html", html);
}


//===============================================
void setup()
{
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  Serial.begin(115200);
  randomSeed(analogRead(16));
  dht.begin();
  Serial.println();
  Serial.print("Configuring access point...");//AP config 
  WiFi.softAPConfig(IPaddr, IPaddr, IPmask);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  WiFi.begin();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.print("name: ");
  Serial.println(ssid);
  server.on("/", handleRoot);
  server.on("/temphum", Displ_TH);
  server.on("/custom", Custom);
  server.on("/tohumid", ToHumidity);
  server.on("/rainbow", Rainbow);
  server.on("/fire", Fire);
  server.on("/cold", Cold);
  server.on("/water", Water);
  server.on("/warm", Warm);
  server.on("/bright", Bright);
  server.on("/hacker", Hacker);
  server.on("/r_blink", R_blink);
  server.begin();
  Serial.println("HTTP server started");
}
//===============================================
void loop()
{
  //COLOR DISPLAY OPTIONS --------------------------------------------------------------------
  switch(option){ 
    case 0:
    //off
      analogWrite(R,0);
      analogWrite(G,0);
      analogWrite(B,0);
      delay(50);
    break;
    case 1:
    //display custom color
    break;
    case 2:
    //humidity
      h = dht.readHumidity();
      h_display = (255 * h)/100;
      analogWrite(R,255 - h_display);
      analogWrite(G,0);
      analogWrite(B,h_display);
    break;
    case 3:
    //rainbow
      analogWrite(R, rVal);
      analogWrite(G, gVal);
      analogWrite(B, bVal);
      // change the values of the LEDs
      rVal = rVal + rDir;
      gVal = gVal + gDir;
      bVal = bVal + bDir;
      // for each color, change direction if
      // you reached 0 or 255
      if (rVal >= 255 || rVal <= 0) {
        rDir = rDir * -1;
      }
      if (gVal >= 255 || gVal <= 0) {
        gDir = gDir * -1;
      }
      if (bVal >= 255 || bVal <= 0) {
        bDir = bDir * -1;
      }
      // slight delay so it doesn't rotate color too quicky
      delay(33);

    break;
    case 4:
    //fire
    
      if(Rvalue < 102){
        change_dirR = false;
      }

      if(Rvalue > 255){
        change_dirR = true;
      }

      if(change_dirR == false){
        Rvalue++;
      }
      else{
        Rvalue--;
      }
      
      analogWrite(R,Rvalue);
      analogWrite(G,50);
      analogWrite(B,0);
      delay(10);
    break;
    case 5:
    //warm
      if(Rvalue < 0){
        change_dirR = false;
      }

      if(Rvalue > 255){
        change_dirR = true;
      }

      if(change_dirR == false){
        Rvalue++;
      }
      else{
        Rvalue--;
      }
      analogWrite(R,Rvalue);
      analogWrite(G,0);
      analogWrite(B,0);
      delay(30);
    break;
    case 6:
    //cold
      if(Rvalue > 150){
        change_dirR = true;
      }

      if(Rvalue < 0){
        change_dirR = false;
      }
      
      if(change_dirR == false){
        Rvalue++;
      }
      else{
        Rvalue--;
      }

      if(Gvalue < 50){
        change_dirG = false;
      }

      if(Gvalue > 250){
        change_dirG = true;
      }

      if(change_dirG == false){
        Gvalue++;
      }
      else{
        Gvalue--;
      }
      analogWrite(R,Rvalue);
      analogWrite(G,Gvalue);
      analogWrite(B,255);
      delay(10);
    break;
    case 7:
    //water

      if(Gvalue < 123){
        change_dirB = false;
      }

      if(Gvalue > 254){
        change_dirB = true;
      }

      if(change_dirB == false){
        Bvalue++;
      }
      else{
        Bvalue--;
      }
      
      analogWrite(R,0);
      analogWrite(G,123);
      analogWrite(B,Bvalue);
      delay(10);
    break;
    case 8:
    //bright
      analogWrite(R,255);
      analogWrite(G,255);
      analogWrite(B,255);
      delay(10);
    break;
    case 9:
      //hacker
      if(Gvalue < 0){
        change_dirG = false;
      }

      if(Gvalue > 255){
        change_dirG = true;
      }

      if(change_dirG == false){
        Gvalue++;
      }
      else{
        Gvalue--;
      }
      
      analogWrite(R,0);
      analogWrite(G,Gvalue);
      analogWrite(B,0);
      delay(20);
    break;
    case 10:
      //random blink
      randomNumR = random(255);
      randomNumG = random(255);
      randomNumB = random(255);
      analogWrite(R,randomNumR);
      analogWrite(G,randomNumG);
      analogWrite(B,randomNumB);
      delay(500);
    break;
  }
  server.handleClient();
}
