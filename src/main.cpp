#include <Arduino.h>
#include <WiFi.h>
#include <rtc.h>
#include <loadcell.h>
#include <servo.h>
#include <firebase_auth.h>

Servo servo_spiral;

bool servo_direction = true;
static unsigned long lastToggle = 0;
int last_berat_wadah;
unsigned long jamMam1_insecond = ((jamMam1%100)*60) + ((jamMam1/100)*3600);
unsigned long jamMam2_insecond = ((jamMam2%100)*60) + ((jamMam2/100)*3600);


DateTime waktu_terakhir_pakan;

void setup() {
  Serial.begin(115200);
  WiFi.begin("nctrn","88888888");

  rtc_setup();
  loadcell_setup();
  servo_setup();
  // FirebaseSetup();

  Serial.print("Starting...");
}

void loop(){  

  // unsigned long currentMillis = millis();

  //========== RTC ================
  // Serial.print("Waktu: ");
  // rtc_clock_now();
  
  // Serial.print("Waktu konversi full detik: ");
  // Serial.println(rtc_clock_insecond_now());

  //========== LOAD CELL ============
  // float berat = loadcell_read();
  // Serial.print("berat: ");
  // Serial.println(berat);
  // Serial.println();

  //=========== SERVO ============

  // if (currentMillis - lastToggle >= 1000) {
  //   lastToggle = currentMillis;
  //   servo_direction = !servo_direction;
  // }

  // if (servo_direction == 0){
  //   servo_counterclockwise_move();
  //   Serial.println("servo counter clockwise");
  // } else{
  //   servo_clockwise_move();
  //   Serial.println("servo clockwise");
  // }

  //================== MAIN PROGRAM =====================
  if ((rtc_clock_insecond_now()!=jamMam1_insecond) || (rtc_clock_insecond_now()!=jamMam2_insecond)){
    if (kasihMam>0){
      last_berat_wadah = loadcell.read();
      while (loadcell.read()<(last_berat_wadah + kasihMam)){
        servo_counterclockwise_move();
        // servo_clockwise_move();
        delay(100);
      }
      kasihMam = 0;
    }
  } else{
    while (loadcell.read()<sekaliMam){
        servo_counterclockwise_move();
        // servo_clockwise_move();
        delay(100);
    }
  }

  delay(100);
}
