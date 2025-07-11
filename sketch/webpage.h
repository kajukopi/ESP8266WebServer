#ifndef WEBPAGE_H
#define WEBPAGE_H

const char MAIN_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP8266 Control</title>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
  <style>
    body { padding: 2rem; }
    .slider-label, .switch { margin-top: 2rem; }
  </style>
</head>
<body class="container text-center">
  <h1 class="mb-3">ESP8266 Control Panel</h1>
  <p><strong>IP Address:</strong> %IP%</p>
  <p><strong>WiFi Strength:</strong> %SIGNAL%</p>

  <div class="mt-4">
    <label class="form-label">Servo Angle: <span id="angleValue">0%</span></label>
    <input type="range" class="form-range" id="slider" min="0" max="100" value="0" oninput="updateSlider(this.value)">
  </div>

  <div class="form-check form-switch switch">
    <input class="form-check-input" type="checkbox" id="ledSwitch" onchange="toggleLED(this.checked)">
    <label class="form-check-label" for="ledSwitch">Built-in LED</label>
  </div>

  <a href="/update" class="btn btn-primary mt-4">Firmware Update</a>

  <script>
    function updateSlider(value) {
      document.getElementById('angleValue').innerText = value + "%";
      fetch("/setServo?percent=" + value);
    }

    function toggleLED(state) {
      fetch("/toggleLED?state=" + (state ? "on" : "off"));
    }
  </script>
</body>
</html>
)rawliteral";

const char UPDATE_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Firmware Update</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
  <style> body { padding: 2rem; } </style>
</head>
<body class="container text-center">
  <h2>Firmware Update</h2>
  <form method="POST" action="/update" enctype="multipart/form-data">
    <input type="file" name="firmware" class="form-control my-3">
    <input type="submit" value="Upload" class="btn btn-success">
  </form>
  <a href="/" class="btn btn-secondary mt-4">⬅ Back to Home</a>
</body>
</html>
)rawliteral";

#endif