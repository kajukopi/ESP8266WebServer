# 📡 ESP8266 Web Server + OTA + Servo Control

Repositori ini berisi contoh implementasi **ESP8266 Web Server** yang mampu:
- Menyediakan antarmuka web sederhana untuk kontrol perangkat (seperti servo).
- Mendukung **Over-the-Air (OTA)** firmware update.
- Mendukung fitur **static IP** dan dapat dikembangkan untuk mDNS/dynamic DNS.
- Cocok untuk perangkat seperti **Lolin NodeMCU ESP8266 v1.0**.

## 🧰 Library yang Digunakan

```cpp
#include <ESP8266WiFi.h>              // Untuk koneksi WiFi
#include <ESP8266WebServer.h>         // Web server HTTP
#include <ESP8266HTTPUpdateServer.h>  // OTA update lewat browser
#include <ArduinoOTA.h>               // OTA programming via Arduino IDE
#include <Servo.h>                    // Kontrol Servo motor
```

## 📶 Konfigurasi WiFi

```cpp
const char* ssid = "karimroy";
const char* password = "09871234";
```

## 🌐 Setup Web Server dan OTA

```cpp
ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;
```

## ⚙️ Setup Servo

```cpp
Servo myServo;
const int servoPin = D5;  // Pin yang digunakan untuk servo
```

## 🏗️ Fungsi Setup

```cpp
void setup() {
  Serial.begin(115200);
  myServo.attach(servoPin);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // OTA via browser (upload firmware .bin)
  httpUpdater.setup(&server);

  // Web route
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", "<h1>Hello from ESP8266 Web Server</h1>");
  });

  server.on("/servo", HTTP_GET, []() {
    if (server.hasArg("angle")) {
      int angle = server.arg("angle").toInt();
      myServo.write(angle);
      server.send(200, "text/plain", "Servo moved to " + String(angle));
    } else {
      server.send(400, "text/plain", "Missing 'angle' parameter");
    }
  });

  server.begin();
  ArduinoOTA.begin();
}
```

## 🔁 Fungsi Loop

```cpp
void loop() {
  server.handleClient();  // Menangani request HTTP
  ArduinoOTA.handle();    // Menangani OTA dari Arduino IDE
}
```

## 🧪 Contoh Penggunaan

### 🌍 Akses Halaman Web
Buka browser dan kunjungi IP device (contoh: `http://192.168.1.100/`) untuk melihat pesan utama.

### 🎛️ Kontrol Servo
Kirim permintaan seperti berikut:
```
http://192.168.1.100/servo?angle=90
```
Servo akan bergerak ke sudut 90°.

### ⬆️ OTA Firmware Update
Kunjungi:
```
http://192.168.1.100/update
```
Unggah file `.bin` dari hasil kompilasi Arduino IDE.

## 🛠️ Tambahan (Optional)
- Tambahkan fitur sensor suhu/humidity untuk IoT dashboard.
- Ganti HTML menjadi tampilan dashboard menggunakan **MDBootstrap** atau **Chart.js**.
- Gunakan **LittleFS** atau **SPIFFS** untuk menyimpan halaman HTML/CSS terpisah dari program utama.

## ⚠️ Catatan Penting
- Hanya satu client dapat terhubung pada satu waktu (karakteristik `ESP8266WebServer`).
- Gunakan `ESPAsyncWebServer` jika ingin handle banyak client dengan performa tinggi.
- Perhatikan batasan memori ketika menambahkan banyak fitur (RAM ESP8266 sangat terbatas).

## 🔗 Referensi
- [ESP8266 Arduino Core](https://github.com/esp8266/Arduino)
- [ESP8266WebServer Class Reference](https://arduino-esp8266.readthedocs.io/en/latest/libraries.html#esp8266webserver)
- [Servo Arduino Library](https://www.arduino.cc/en/Reference/Servo)