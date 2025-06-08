#include <HX711.h>
#include <RTClib.h>
#include <ESP32Servo.h>

//pin loadcell
#define PIN_DATA 2
#define PIN_CLOCK 18

#define PIN_SERVO 14

HX711 load_cell;
RTC_DS3231 rtc;
Servo servo_spiral;

const float berat_default = 100.0;
const float batas_minimal = 50.0;


//isih kudu diperhitungkan debit e
const float gram_per_detik = 10.0;
const float waktu_per_gram = 1.0 / gram_per_detik;

DateTime waktu_terakhir_pakan;

void setup() {
  Serial.begin(9600);

  load_cell.begin(PIN_DATA, PIN_CLOCK);
  // load_cell.set_scale(nilai_kalibrasi); // Ganti dengan nilai hasil kalibrasi
  // load_cell.tare(); // Nol-kan load_cell

  rtc.begin();

  servo_spiral.attach(PIN_SERVO);

  waktu_terakhir_pakan = rtc.now();
}

void loop() {
  DateTime waktu_sekarang = rtc.now();

  long selisih_detik = (waktu_sekarang.unixtime() - waktu_terakhir_pakan.unixtime());

  //cek tiap 8 jam (8 x 3600 detik)
  if (selisih_detik >= 8 * 3600) {
    float berat_sekarang = load_cell.get_units(10); //rata-rata pembacaan data dari 10 kali pembacaan

    Serial.print("Berat sekarang: ");
    Serial.println(berat_sekarang);

    if (berat_sekarang < batas_minimal) {
      float selisih_berat = berat_default - berat_sekarang;
      float durasi_putar = selisih_berat * waktu_per_gram * 1000; // dalam milidetik

      Serial.print("Menambah pakan sebanyak: ");
      Serial.print(selisih_berat);
      Serial.println(" gram");

      Serial.print("Servo menyala selama: ");
      Serial.print(durasi_putar / 1000);
      Serial.println(" detik");


      servo_spiral.write(180); //muter
      delay(durasi_putar);
      servo_spiral.write(90); //stops

      //nyimpen waktu pemberian pakan terakhir
      waktu_terakhir_pakan = waktu_sekarang;
    } else {
      Serial.println("Pakan masih cukup, tidak menambah.");
    }
  }

  delay(1000);
}
