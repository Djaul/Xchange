#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();   // Invoke library

const char* ssid = "YOUR_SSID_HERE";
const char* password = "YOUR_PASSWORD_HERE";

void setup() {
  Serial.begin(115200);
  
  tft.begin();     // initialize a ST7789 chip
  tft.fillScreen(TFT_BLACK);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  //can be looped after here
  DynamicJsonDocument doc(100);

    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin("https://free.currconv.com/api/v7/convert?q=USD_TRY&compact=ultra&apiKey=......................................................");
      int httpCode = http.GET();

      if (httpCode > 0) {

        String payload = http.getString();
        //Serial.println(httpCode);
        Serial.println(payload);
        deserializeJson(doc, payload);
        float curr = doc["USD_TRY"];
        Serial.println(curr);
        testdrawtext(curr, TFT_WHITE);
        delay(1000);
  
      }
      //{"USD_TRY":8.4399}
      else {
        Serial.println("Error on HTTP request");
      }

      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }



}

void loop() {

  
}


void testdrawtext(float text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.setTextSize(3);
  tft.print("USD/TRY");

  tft.setCursor(0, 40);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.setTextSize(3);
  tft.print(text);
 
}
