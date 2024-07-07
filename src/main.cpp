#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Pin untuk sensor ultrasonik
#define SENSOR_TRIG D5
#define SENSOR_ECHO D6

// Kredensial Wi-Fi Anda
const char* ssid = "ZTE_2.4G_gwnh36";
const char* password = "L2V6Hpvb";

// Kredensial Firebase Anda
#define FIREBASE_HOST "seatec-9fdf1-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "YOUR_FIREBASE_AUTH"

FirebaseData firebaseData;
FirebaseConfig firebaseConfig;

// Deklarasi prototipe fungsi
long UltrasonicRead(int echoPin, int trigPin);

void setup() {
  Serial.begin(9600);

  // Mulai koneksi Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);

  // Konfigurasi Firebase
  firebaseConfig.host = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;

  // Mulai Firebase
  Firebase.begin(&firebaseConfig, nullptr);
}

void loop() {
  // Baca jarak dari sensor ultrasonik
  long duration = UltrasonicRead(SENSOR_ECHO, SENSOR_TRIG);
  // Konversi jarak menjadi level air (misalnya dalam sentimeter)
  float waterLevel = (duration * 0.0343 / 2); // Menggunakan float untuk nilai level air
  Serial.println(waterLevel);
  Serial.println(duration);
  // Unggah data ke Firebase
  if (Firebase.setFloat(firebaseData, "/sensor/water_level", waterLevel)) {
    Serial.println("Data dikirim ke Firebase");
  } else {
    Serial.println("Gagal mengirim data ke Firebase");
    Serial.println(firebaseData.errorReason());
  }
  
  delay(10000); // Tunggu selama 10 detik sebelum mengambil pembacaan berikutnya
}

long UltrasonicRead(int echoPin, int trigPin) {
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  pinMode(echoPin, INPUT);
  long duration = pulseIn(echoPin, HIGH);
  
  return duration; // Mengembalikan durasi pulsa dari sensor ultrasonik
}
