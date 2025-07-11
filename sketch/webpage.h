#ifndef WEBPAGE_H
#define WEBPAGE_H

const char MAIN_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <title>ESP8266 Control</title>
  <link rel="stylesheet" href="https://payunghitam.web.app/css/core.min.css" />
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.15.4/css/all.css" />
  <style>
    body {
      padding: 2rem;
      background-color: #f0f2f5;
    }
    .card {
      margin-top: 2rem;
    }
    .signal-bar {
      width: 100%;
      height: 20px;
      background-color: #e0e0e0;
      border-radius: 10px;
      overflow: hidden;
      margin-top: 0.5rem;
    }
    .signal-fill {
      height: 100%;
      background-color: #4caf50;
      width: 0%;
      transition: width 0.5s ease;
    }
    .footer {
      margin-top: 4rem;
      font-size: 0.9rem;
      color: #888;
    }
    .social a {
      margin: 0 0.5rem;
      color: #555;
      text-decoration: none;
    }
  </style>
</head>
<body class="container text-center">

  <h1 class="fw-bold text-primary mb-4">
    <i class="fas fa-microchip me-2"></i>ESP8266 Control Panel
  </h1>

  <div class="card shadow-3-strong">
    <div class="card-body">
      <p><strong><i class="fas fa-network-wired"></i> IP Address:</strong> <span id="ip">%IP%</span></p>
      <p><strong><i class="fas fa-signal"></i> WiFi Strength:</strong> <span id="signalText">%SIGNAL%</span></p>
      <div class="signal-bar">
        <div class="signal-fill" id="signalBar"></div>
      </div>

      <div class="mt-4">
        <label class="form-label"><i class="fas fa-sliders-h me-2"></i>Servo Angle: <span id="angleValue">0%</span></label>
        <input type="range" class="form-range" id="slider" min="0" max="100" value="0" oninput="updateSlider(this.value)">
      </div>

      <div class="form-check form-switch d-flex align-items-center justify-content-center mt-4">
        <input class="form-check-input me-2" type="checkbox" id="ledSwitch" onchange="toggleLED(this.checked)">
        <label class="form-check-label fs-5" for="ledSwitch"><i class="fas fa-lightbulb me-1"></i>Built-in LED</label>
      </div>

      <a href="/update" class="btn btn-primary mt-4">
        <i class="fas fa-upload me-1"></i>Firmware Update
      </a>
    </div>
  </div>

  <div class="footer mt-5">
    <p>Created by <strong>Karim Roy Tampubolon</strong></p>
    <div class="social">
      <a href="https://github.com/kajukopi/ESP8266WebServer" target="_blank"><i class="fab fa-github"></i> GitHub</a> |
      <a href="https://www.tiktok.com/@karimroy.digital" target="_blank"><i class="fab fa-tiktok"></i> TikTok</a> |
      <a href="https://www.facebook.com/karimroy" target="_blank"><i class="fab fa-facebook"></i> Facebook</a>
    </div>
  </div>

  <script>
    function updateSlider(value) {
      document.getElementById('angleValue').innerText = value + "%";
      fetch("/setServo?percent=" + value);
    }

    function toggleLED(state) {
      fetch("/toggleLED?state=" + (state ? "on" : "off"));
    }

    function setSignalBar(strengthText) {
      const rssi = parseInt(strengthText.split(" ")[0]);
      let percent = 0;
      if (rssi > -50) percent = 100;
      else if (rssi > -60) percent = 80;
      else if (rssi > -70) percent = 60;
      else if (rssi > -80) percent = 40;
      else percent = 20;
      document.getElementById('signalBar').style.width = percent + "%";
    }

    document.addEventListener("DOMContentLoaded", () => {
      const signal = document.getElementById("signalText").innerText;
      setSignalBar(signal);
    });
  </script>
  <script src="https://payunghitam.web.app/js/core.min.js"></script>
  <script src="https://use.fontawesome.com/releases/v5.15.4/js/all.js"></script>
</body>
</html>
)rawliteral";

const char UPDATE_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <title>Firmware Update</title>
  <link rel="stylesheet" href="https://payunghitam.web.app/css/core.min.css" />
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.15.4/css/all.css" />
  <style>
    body {
      padding: 2rem;
      background-color: #f1f1f1;
    }
  </style>
</head>
<body class="container text-center">
  <div class="card shadow-3-strong p-4">
    <h2 class="mb-4 text-success"><i class="fas fa-upload me-2"></i>Firmware Update</h2>
    <form method="POST" action="/update" enctype="multipart/form-data">
      <input type="file" name="firmware" class="form-control my-3" required>
      <input type="submit" value="Upload" class="btn btn-success">
    </form>
    <a href="/" class="btn btn-secondary mt-4"><i class="fas fa-arrow-left me-1"></i>Back to Home</a>
  </div>
  <script src="https://payunghitam.web.app/js/core.min.js"></script>
  <script src="https://use.fontawesome.com/releases/v5.15.4/js/all.js"></script>
</body>
</html>
)rawliteral";

#endif
