#include <Firebase_ESP_Client.h>
// Provide the token generation process info.
#include <addons/TokenHelper.h>
// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

// setup firebase
#define DATABASE_URL "https://projectep-abbca-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "ChecdgjtQWSexTEzs3gn7i4WDp9bVvvXZl6wOrjM"
#define API_KEY "AIzaSyAVAgUbn0L5J8LXeQP9C2-CijAqy-51Cp0"

// setup user
#define USER_EMAIL "ayubisal1345@gmail.com"
#define USER_PASSWORD "udinganteng123"
// Firebase objects
FirebaseData fbdo;
FirebaseData firebaseData;
FirebaseAuth auth;          // FirebaseAuth object
FirebaseConfig config;      // FirebaseConfig object
FirebaseJson json;       // or constructor
//  with contents e.g. FirebaseJson json("{\"a\":true}");
FirebaseJsonArray arr;   // or constructor with contents e.g. FirebaseJsonArray arr("[1,2,true,\"test\"]");
FirebaseJsonData result; // object that keeps the deserializing result
unsigned long sendDataPrevMillis = 0;

int kasihMam;
int sekaliMam;
int jamMam1;
int jamMam2;

void FirebaseSetup(){
    // initialize Firebase
  /* Assign the api key (required) */
  config.api_key = API_KEY;

  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("SignUp successful");
  } else {
    Serial.printf("SignUp failed, %s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;

  // Wait for token generation
  while (auth.token.uid == "" && !config.signer.signupError.message.length()) {
    delay(100);
  }
  
  Firebase.begin(&config, &auth);
  // check if the connection is successful
  Firebase.reconnectWiFi(true);
}

void kasihmam(){
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
    // get data from firebase database
    if (Firebase.RTDB.getInt(&fbdo, "/data/kasihmam")){
      if (fbdo.dataType() == "int"){
        kasihMam = fbdo.intData();
      }
    }
  }
};

void sekelimam(){
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
    // get data from firebase database
    if (Firebase.RTDB.getInt(&fbdo, "/data/profile/ciko/Sekalimam")){
      if (fbdo.dataType() == "int"){
        sekaliMam = fbdo.intData();
      }
    }
  }
};

void jammam(){
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
    // get data from firebase database
    if (Firebase.RTDB.getInt(&fbdo, "/data/profile/ciko/jamMakan/makan-1")){
      if (fbdo.dataType() == "int"){
        jamMam1 = fbdo.intData();
      }
    }
    if (Firebase.RTDB.getInt(&fbdo, "/data/profile/ciko/jamMakan/makan-2")){
      if (fbdo.dataType() == "int"){
        jamMam2 = fbdo.intData();
      }
    }
  }
};

void read_database(){
  kasihmam();
  sekelimam();
  jammam();
  sendDataPrevMillis = millis();
}
