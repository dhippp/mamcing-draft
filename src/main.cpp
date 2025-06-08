#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include <rtc.h>
#include <loadcell.h>
#include <firebase_auth.h>

//pin loadcell
#define PIN_SERVO 14

Servo servo_spiral;

const float berat_default = 100.0;
const float batas_minimal = 50.0;


//isih kudu diperhitungkan debit e
const float gram_per_detik = 10.0;
const float waktu_per_gram = 1.0 / gram_per_detik;

DateTime waktu_terakhir_pakan;

void setup() {
  Serial.begin(115200);
  rtc_setup();
  FirebaseSetup();
  loadcell_setup();
  // servo_spiral.attach(PIN_SERVO);
  pinMode(PIN_SERVO, OUTPUT);
  WiFi.begin("nctrn","88888888");
  Serial.print("Startig...");
}

void loop(){
  digitalWrite(PIN_SERVO, HIGH);

  // //==========RTC================
  
  // rtc_clock_now();
  // rtc_date_now();


  // //==========LOAD CELL============

  // float berat = loadcell_read();
  // Serial.print("berat: ");
  // Serial.println(berat);
  // Serial.println();

  // //===========SERVO============



  delay (1000);

}

// void loop() {
//   DateTime waktu_sekarang = rtc.now();

//   long selisih_detik = (waktu_sekarang.unixtime() - waktu_terakhir_pakan.unixtime());

//   //cek tiap 8 jam (8 x 3600 detik)
//   if (selisih_detik >= 8 * 3600) {
//     float berat_sekarang = load_cell.get_units(10); //rata-rata pembacaan data dari 10 kali pembacaan

//     Serial.print("Berat sekarang: ");
//     Serial.println(berat_sekarang);

//     if (berat_sekarang < batas_minimal) {
//       float selisih_berat = berat_default - berat_sekarang;
//       float durasi_putar = selisih_berat * waktu_per_gram * 1000; // dalam milidetik

//       Serial.print("Menambah pakan sebanyak: ");
//       Serial.print(selisih_berat);
//       Serial.println(" gram");

//       Serial.print("Servo menyala selama: ");
//       Serial.print(durasi_putar / 1000);
//       Serial.println(" detik");


//       servo_spiral.write(180); //muter
//       delay(durasi_putar);
//       servo_spiral.write(90); //stops

//       //nyimpen waktu pemberian pakan terakhir
//       waktu_terakhir_pakan = waktu_sekarang;
//     } else {
//       Serial.println("Pakan masih cukup, tidak menambah.");
//     }
//   }

//   delay(1000);
// }
