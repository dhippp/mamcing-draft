#include <Arduino.h>
#include <WiFi.h>
#include <rtc.h>
#include <loadcell.h>
#include <servo.h>
#include <firebase_auth.h>

#define username_wifi "nctrn"
#define pass_wifi "88888888"

int last_berat_wadah;
unsigned long jamMam1_insecond = ((jamMam1%100)*60) + ((jamMam1/100)*3600);
unsigned long jamMam2_insecond = ((jamMam2%100)*60) + ((jamMam2/100)*3600);

void setup() {
  Serial.begin(115200);
  WiFi.begin(username_wifi, pass_wifi);

  rtc_setup();
  loadcell_setup();
  servo_setup();
  FirebaseSetup();

  Serial.print("Mamcing Starting........");
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
    read_database();

    Serial.print("sekarang = ");
    Serial.println(loadcell_read());
    Serial.println();

  if ((rtc_clock_insecond_now()!=jamMam1_insecond) || (rtc_clock_insecond_now()!=jamMam2_insecond)){
    if (kasihMam>0){

      Serial.println("kasihMam aktif!");
      Serial.print("kasihMam sebanyak = ");
      Serial.print(kasihMam);
      Serial.println();

      last_berat_wadah = loadcell_read();
      while (loadcell_read()<(last_berat_wadah + kasihMam)){
        
        servo_counterclockwise_move();
        // servo_clockwise_move();

        Serial.print("tujuan = ");
        Serial.println(last_berat_wadah+kasihMam);
        Serial.print("sekarang = ");
        Serial.println(loadcell_read());
        Serial.println();
      }
      Serial.println("kasihmam selesai!");
      servo_stop_move();
      Firebase.RTDB.setInt(&fbdo, "/data/kasihmam", 0);
    }
  } else{
    Serial.println("sekarang JamMam!");
    }
    while (loadcell_read()<sekaliMam){
      
        servo_counterclockwise_move();
        // servo_clockwise_move();

        Serial.print("terus ditambah sampai = ");
        Serial.println(sekaliMam);
        Serial.print("sekarang = ");
        Serial.println(loadcell_read());
        Serial.println();

    }
    servo_stop_move();
    if(loadcell_read()>=sekaliMam){
      Serial.println("wadah sesuai sekaliMam!");
  }
  delay(2000);
}
