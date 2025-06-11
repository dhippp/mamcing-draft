#include <RTClib.h>

#define SET_RTC_TIME  // KOMENTARI BARIS INI SETELAH RTC DISET DENGAN BENAR

RTC_DS3231 rtc;

char logger[12];


void rtc_setup() {
  if (! rtc.begin()) {
    Serial.print("Couldn't find RTC");
    while (1){
      Serial.print(".");
      delay(100);
    };
  }
  #ifdef SET_RTC_TIME
    rtc.adjust(DateTime(2025, 6, 11, 22, 59, 30)); // Year, Month, Day, Hour, Minute, Second
  #endif
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, set time again!");
    rtc.adjust(DateTime(2025, 6, 11, 22, 59, 30));
  }
}

void rtc_clock_now(){
  DateTime now = rtc.now();
  char buffer[9];
  snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  Serial.println(buffer);
}

void rtc_logger(){
  DateTime now = rtc.now();
  snprintf(logger, sizeof(logger), "%ld", now.unixtime());
  // Serial.println(logger);
  // Serial.print(now.unixtime());
}


unsigned long rtc_clock_insecond_now() {
  DateTime now = rtc.now();
  unsigned long jam = now.hour();
  unsigned long menit = now.minute();
  unsigned long detik = now.second();
  jam = jam * 3600;
  menit = menit * 60;
  unsigned long clock_insecond = jam + menit + detik;
  return clock_insecond;
}

void rtc_date_now() {
  char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
  DateTime now = rtc.now();
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%s, %02d-%02d-%04d",
           daysOfTheWeek[now.dayOfTheWeek()],
           now.day(), now.month(), now.year());
  Serial.print("Current Date: ");
  Serial.println(buffer);
}
