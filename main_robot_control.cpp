// #include <Arduino.h>
// #include <ESP32Servo.h>
// #include <WiFi.h>
// #include <WebServer.h>

// const char* ssid = "OPPO A53";
// const char* password = "0825680994";

// WebServer server(80);

// // Servo baseServo;  // create servo object to control a servo
// // Servo shoulderServo;  // create servo object to control a servo
// // Servo elbowServo;  // create servo object to control a servo
// // Servo wristServo;  // create servo object to control a servo
// // Servo gripperServo;  // create servo object to control a servo

// Servo servos[6];
// int servoPins[6] = {13, 12, 14, 27, 26, 25};
// // void defaultServo(){
// //     baseServo.write(90);
// //     shoulderServo.write(90);
// //     elbowServo.write(90);
// //     wristServo.write(90);
// //     gripperServo.write(90);
// // }

// void handleRoot() {
//   String html = R"rawliteral(
// <!DOCTYPE html>
// <html>
// <head>
//   <title>ESP32 Robot Arm Controller</title>
//   <meta name="viewport" content="width=device-width, initial-scale=1">

//   <style>
//     :root {
//       --bg: #0f172a;
//       --card: #1e293b;
//       --accent: #22d3ee;
//       --text: #e5e7eb;
//       --muted: #94a3b8;
//     }

//     * {
//       box-sizing: border-box;
//       font-family: system-ui, -apple-system, sans-serif;
//     }

//     body {
//       margin: 0;
//       background: var(--bg);
//       color: var(--text);
//     }

//     header {
//       padding: 16px 20px;
//       background: #020617;
//       border-bottom: 1px solid #1e293b;
//     }

//     header h1 {
//       font-size: 18px;
//       margin: 0;
//     }

//     header span {
//       font-size: 12px;
//       color: var(--accent);
//     }

//     main {
//       display: grid;
//       grid-template-columns: 1fr 1fr;
//       gap: 16px;
//       padding: 16px;
//     }

//     .card {
//       background: var(--card);
//       border-radius: 12px;
//       padding: 16px;
//     }

//     .card h2 {
//       margin-top: 0;
//       font-size: 14px;
//       color: var(--muted);
//       letter-spacing: 1px;
//     }

//     /* ---------- Joystick ---------- */
//     #joy {
//       width: 220px;
//       height: 220px;
//       background: #020617;
//       border-radius: 50%;
//       position: relative;
//       touch-action: none;
//       margin: 20px auto;
//       border: 2px solid var(--accent);
//     }

//     #stick {
//       width: 64px;
//       height: 64px;
//       background: var(--accent);
//       border-radius: 50%;
//       position: absolute;
//       left: 78px;
//       top: 78px;
//       opacity: 0.85;
//     }

//     /* ---------- Sliders ---------- */
//     .joint {
//       margin-bottom: 16px;
//     }

//     .joint label {
//       display: block;
//       font-size: 13px;
//       margin-bottom: 6px;
//       color: var(--muted);
//     }

//     input[type=range] {
//       width: 100%;
//       accent-color: var(--accent);
//     }

//     footer {
//       padding: 12px 16px;
//       font-size: 12px;
//       color: var(--muted);
//       border-top: 1px solid #1e293b;
//       text-align: center;
//     }

//     @media (max-width: 768px) {
//       main {
//         grid-template-columns: 1fr;
//       }
//     }
//   </style>
// </head>

// <body>
//   <header>
//     <h1>ESP32 ROBOT ARM CONTROLLER</h1>
//    <span id="wifiStatus">Connected WiFi</span>
//   </header>

//   <main>
//     <!-- Joystick Panel -->
//     <div class="card">
//       <h2>ARM MOVEMENT</h2>
//       <div id="joy">
//         <div id="stick"></div>
//       </div>
//       <p style="text-align:center;font-size:12px;color:#94a3b8">
//         Base / Shoulder
//       </p>
//     </div>

//     <!-- Joint Control -->
//     <div class="card">
//       <h2>JOINT CONTROL</h2>

//       <div class="joint">
//         <label>Elbow</label>
//         <input type="range" min="0" max="180" value="90" id="elbow">
//       </div>

//       <div class="joint">
//         <label>Wrist</label>
//         <input type="range" min="0" max="180" value="90" id="wrist">
//       </div>

//       <div class="joint">
//         <label>WristRoll</label>
//         <input type="range" min="0" max="180" value="90" id="wrist">
//       </div>

//       <div class="joint">
//         <label>Gripper</label>
//         <input type="range" min="0" max="180" value="90" id="gripper">
//       </div>
//     </div>
//   </main>

//   <footer>
//     Robot Control Panel • ESP32 Web Interface
//   </footer>

// <script>
//   const joy = document.getElementById('joy');
//   const stick = document.getElementById('stick');
//   const elbowSlider = document.getElementById('elbow');
//   const wristSlider = document.getElementById('wrist');
//   const wristrollSlider = document.getElementById('wristRoll');
//   const gripperSlider = document.getElementById('gripper');

//   const wifiStatus = document.getElementById('wifiStatus'); 

//   const center = 110;
//   let lastX = 90;
//   let lastY = 90;


//   function updateWiFiStatus() {
//     fetch("/status")
//       .then(res => res.json())
//       .then(data => {
//         if (data.connected) {
//         wifiStatus.textContent = `Connected (${data.ip})`;
//         wifiStatus.style.color = "#06e62b";
//         } else {
//           wifiStatus.textContent = `Connected (${data.ip})`;
//           wifiStatus.style.color = "red";
//         }
//       })
//         .catch(() => {
//         wifiStatus.textContent = "ESP32 Offline";
//         wifiStatus.style.colr = "orange";
        
//         })
  
//   }
//   updateWiFiStatus();
//   setInterval(updateWiFiStatus, 2000);


//   joy.addEventListener("touchmove", e =>{
//     e.preventDefault();
//     let t = e.touches[0];
//     let rect = joy.getBoundingClientRect();
//     let x = t.clientX - rect.left;
//     let y = t.clientY - rect.top;

//     x = Math.max(0, Math.min(220, x));0
//     y = Math.max(0, Math.min(220, y));

//     let dx = x - center;
//     let dy = y - center;

//     const deadZone = 10;
//     if (Math.abs(dx) < deadZone) dx = 0;
//     if (Math.abs(dy) < deadZone) dy = 0;

//     stick.style.left = (center + dx - 32) + "px";
//     stick.style.top  = (center + dy - 32) + "px";

//     let base = Math.round(map(dx, -110, 110, 0, 180));
//     let shoulder = Math.round(map(dy, -110, 110, 0, 180));

//     if (base !== lastX) {
//       fetch(`/setServo?id=0&angle=${base}`);
//       lastX = base;
//     }
//     if (shoulder !== lastY) {
//       fetch(`/setServo?id=1&angle=${shoulder}`);
//       lastY = shoulder;
//     }
//   });

//   joy.addEventListener("touchend", () => {
//     stick.style.left = "78px";
//     stick.style.top  = "78px";
//   });

//   elbowSlider.oninput = () => {
//     fetch(`/setServo?id=2&angle=${elbowSlider.value}`);
//   };

//   wristSlider.oninput = () => {
//     fetch(`/setServo?id=3&angle=${wristSlider.value}`);
//   };

//   wristrollSlider.oninput = () => {
//     fetch(`/setServo?id=4&angle=${wristrollSlider.value}`);
//   };

//   gripperSlider.oninput = () => {
//     fetch(`/setServo?id=4&angle=${gripperSlider.value}`);
//   };

//   function map(v, in_min, in_max, out_min, out_max) {
//     return (v - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
//   }
// </script>

// </body>
// </html>
// )rawliteral";

//   server.send(200, "text/html", html);
// }


// void handleStatus() {
//   String json = "{";
  
//   if (WiFi.status() == WL_CONNECTED) {
//     json += "\"connected\":true,";
//     json += "\"ip\":\""+ WiFi.localIP().toString() + "\"";
//   } else {
//     json += "\"connected\":false,";
//     json += "\"ip\":\"-\"";
//   }
  
//   json += "}";
//   server.send(200, "application/json", json);
// }

// // void handleSet() {
// //     int angleX  = server.arg("angleX").toInt();
// //     int angleY  = server.arg("angleY").toInt();
// //     angleX = constrain(angleX, 0, 180);
// //     angleY = constrain(angleY, 0, 180);
// //     baseServo.write(angleX);
// //     shoulderServo.write(angleY);
// //     server.send(200, "text/plain", "OK");
// // }

// void handleSet() {
//     int id = server.arg("id").toInt();
//     int angle = server.arg("angle").toInt();
//     angle = constrain(angle, 0, 180);

//     if (id >= 0 && id < 5){
//         servos[id].write(angle);
//     }
//     server.send(200, "text/plain", "OK");
// }


// void setup() {
//     Serial.begin(115200);
//     // baseServo.attach(13);  // attaches the servo on pin 13 to the servo object
//     // shoulderServo.attach(12);  // attaches the servo on pin 12 to the servo object
//     // elbowServo.attach(14);  // attaches the servo on pin 14 to the servo object
//     // wristServo.attach(27);  // attaches the servo on pin 27 to the servo object
//     // gripperServo.attach(26);  // attaches the servo on pin 26 to the servo object
//     // defaultServo();
//     for (int i = 0; i < 6; i++){
//         servos[i].attach(servoPins[i]);
//         servos[i].write(90);
//     }
//     WiFi.begin(ssid, password);
//     Serial.println("Connecting to WiFi..");
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(300);
//         Serial.print(".");
//     }
//     Serial.println(WiFi.localIP());
//     server.on("/", handleRoot);
//     server.on("/setServo", handleSet);
//     server.on("/status", handleStatus);
//     server.begin();
//     Serial.println("HTTP server started");
// } 

// void loop() {
//     server.handleClient();



    
// }

