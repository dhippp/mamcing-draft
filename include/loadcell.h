#include <HX711.h>
#include <SimpleKalmanFilter.h>

#define PIN_DATA 2
#define PIN_CLOCK 18

HX711 loadcell;

// SimpleKalmanFilter rawData(2, 2, 0.01);

// void loadcell_calibrate(){
    // float test_berat = 100; //gram //input berat benda yang digunakan untuk kalibrasi
    // loadcell.tare(); //meng-nol-kan nilai mentah
    // long raw = loadcell.get_value(10); //mendapatkan nilai mentah baru dengan start di 0 dan dari rata-rata 10 bacaan
    // Serial.print("Raw value: ");
    // Serial.println(raw);
    // float scale_baru = raw / test_berat; //buat rasio
    // loadcell.set_scale(scale_baru);
// }

void loadcell_setup(){
    loadcell.begin(PIN_DATA, PIN_CLOCK);
    loadcell.set_scale(1203);
    loadcell.tare();
    // loadcell_calibrate();
}

int loadcell_read(){
    int berat = loadcell.get_units(5); //rata-rata pembacaan data dari 10 kali pembacaan
    return berat ;
}