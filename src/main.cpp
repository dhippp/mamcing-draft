#include <Arduino.h>
#include <WiFi.h>
#include <rtc.h>
#include <loadcell.h>
#include <servo.h>
#include <firebase_auth.h>

#define username_wifi "yubi"
#define pass_wifi "udinganteng123"

int last_berat_wadah;


char path[50];
int last_hour;
DateTime jam;

void setup() {
  Serial.begin(115200);
  WiFi.begin(username_wifi, pass_wifi);

  rtc_setup();
  loadcell_setup();
  servo_setup();
  FirebaseSetup();

  jam = rtc.now();
  last_hour = jam.hour();

  // loadcell_rata(); //untuk mendapatkan nilai rata-rata loadcell

  Serial.println("Mamcing Starting........");
  Serial.println();
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

  if ((rtc_clock_insecond_now() >= jamMam1_insecond && rtc_clock_insecond_now() <= jamMam1_insecond + 10) || (rtc_clock_insecond_now() >= jamMam2_insecond && rtc_clock_insecond_now() <= jamMam2_insecond + 10)){
    Serial.println("sekarang JamMam!");
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
    DateTime now = rtc.now();
    // rtc_logger();
    sprintf(path, "/data/profile/ciko/log/%ld", now.unixtime());
    Firebase.RTDB.setInt(&fbdo, path, loadcell_read());
  } 
  else{
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
  }

  jam = rtc.now();
  if(jam.hour() != last_hour){
    DateTime now = rtc.now();
    // rtc_logger();
    sprintf(path, "/data/profile/ciko/log/%ld", now.unixtime());
    Firebase.RTDB.setInt(&fbdo, path, loadcell_read());
    last_hour = jam.hour();
    Serial.println("================BERHASIL LOG================");
  }
  Serial.println(rtc_clock_insecond_now());
  Serial.println(jamMam2_insecond);
  // rtc_logger();
  Serial.println();
  delay(2000);
}