#define BLYNK_TEMPLATE_ID "TMPL3zmPQ_v0P"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "M2Ze1VOP1shAptsIflLyKfNQcXa1Y-tj"
#include "esp_camera.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define CAMERA_MODEL_AI_THINKER // Has PSRAM
#include "camera_pins.h"
#define LDR 13
#define PHOTO 14
#define LED 4
#define Laser 12

const char* ssid = "TD";
const char* password = "12345678";
char auth[] = "M2Ze1VOP1shAptsIflLyKfNQcXa1Y-tj";

String local_IP;

void startCameraServer();

void sync() {
  Blynk.syncVirtual(V2); // Synchronize virtual pin V2
  Blynk.syncVirtual(V4); // Synchronize virtual pin V4
}

BLYNK_WRITE(V2) {
  int pinValue = param.asInt(); // Get value as integer
  digitalWrite(Laser, pinValue); // Set the laser to the pin value
}

BLYNK_WRITE(V4) {
  int pinValue = param.asInt(); // Get value as integer
  if(pinValue == 1) {
    takePhoto();
  }
}


void takePhoto()
{
  digitalWrite(LED, HIGH);
  delay(200);
  uint32_t randomNum = random(50000);
  Serial.println("http://"+local_IP+"/capture?_cb="+ (String)randomNum);
  Blynk.setProperty(V1, "urls", "http://"+local_IP+"/capture?_cb="+(String)randomNum);
  digitalWrite(LED, LOW);
  delay(5000);
}

void setup() {
  sync();
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  pinMode(Laser,OUTPUT);
  pinMode(LDR,INPUT);
  Serial.setDebugOutput(true);
  Serial.println();
  digitalWrite(Laser, HIGH);
  
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1); // flip it back
    s->set_brightness(s, 1); // up the brightness just a bit
    s->set_saturation(s, -2); // lower the saturation
  }
  s->set_framesize(s, FRAMESIZE_QVGA);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  local_IP = WiFi.localIP().toString();
  Serial.println("' to connect");
  Blynk.begin(auth, ssid, password);
}

void loop() {
  Blynk.run();
  int pinValue = digitalRead(LDR);
  if(digitalRead(13) == LOW){
  Serial.println("Send Notification");
  Blynk.logEvent("intruder_alert");
  takePhoto();
  delay(5000);
  }
  else{
    Serial.println("No Intruder");
  }
   sync();
}