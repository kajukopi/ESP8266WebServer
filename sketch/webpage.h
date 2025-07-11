#ifndef WEBPAGE_H
#define WEBPAGE_H

const char MAIN_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta charset="UTF-8">
  <title>ESP8266 Control</title>
  <link href="https://payunghitam.web.app/css/core.min.css" rel="stylesheet">
  <style>
    body {
      padding: 2rem;
      background-color: #f9f9f9;
    }
    .slider-label, .switch {
      margin-top: 2rem;
    }
    .card {
      margin-top: 2rem;
    }
  </style>
</head>
<body class="container text-center">

  <h1 class="mb-4 fw-bold text-primary">ESP8266 Control Panel</h1>

  <div class="card shadow-3-strong">
    <div class="card-body">
      <p><strong>IP Address:</strong> %IP%</p>
      <p><strong>WiFi Strength:</strong> %SIGNAL%</p>

      <div class="mt-4">
        <label class="form-label">Servo Angle: <span id="angleValue">0%</span></label>
        <input type="range" class="form-range" id="slider" min="0" max="100" value="0" oninput="updateSlider(this.value)">
      </div>

      <div class="form-check form-switch switch mt-4">
        <input class="form-check-input" type="checkbox" id="ledSwitch" onchange="toggleLED(this.checked)">
        <label class="form-check-label" for="ledSwitch">Built-in LED</label>
      </div>

      <a href="/update" class="btn btn-primary mt-4">Firmware Update</a>
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
  </script>
  <script src="https://payunghitam.web.app/js/core.min.js"></script>
</body>
</html>
)rawliteral";

const char UPDATE_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Firmware Update</title>
  <link href="https://payunghitam.web.app/css/core.min.css" rel="stylesheet">
  <style>
    body {
      padding: 2rem;
      background-color: #f1f1f1;
    }
  </style>
</head>
<body class="container text-center">
  <div class="card shadow-3-strong p-4">
    <h2 class="mb-4 text-success">Firmware Update</h2>
    <form method="POST" action="/update" enctype="multipart/form-data">
      <input type="file" name="firmware" class="form-control my-3">
      <input type="submit" value="Upload" class="btn btn-success">
    </form>
    <a href="/" class="btn btn-secondary mt-4">⬅ Back to Home</a>
  </div>
  <script src="https://payunghitam.web.app/js/core.min.js"></script>
</body>
</html>
)rawliteral";

#endif