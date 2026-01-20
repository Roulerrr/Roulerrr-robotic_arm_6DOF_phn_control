// #include <Arduino.h>
// #include <ESP32Servo.h>
// #include <WiFi.h>
// #include <WebServer.h>

// // create servo objects to control up to 16 servos

// const char* ssid     = "OPPO A53";
// const char* password = "0825680994";

// WebServer server(80);

// Servo baseServo;  // create servo object to control a servo
// Servo shouderServo;


// void handleRoot() {
//   String html = R"rawliteral(
//   <!DOCTYPE html>
//   <html>
//   <head>
//     <title>ESP32 Servo Control</title>
//     <meta name="viewport" content="width=device-width, initial-scale=1">
//     <style>
//       #joy {
//         width:200px;
//         height:200px;
//         background: #ddd;
//         border-radius: 50%;
//         position: relative;
//         touch-action: none;
// }
//         #stick {
//         width: 60px;
//         height: 60px;
//         background: #555;
//         border-radius: 50%;
//         position: absolute;
//         left: 70px; top: 70px;
//         }
//     </style>
//     </head>
//     <body>
//     <h1>ESP3 Control Servo</h1>
//     <div id="joy">
//       <div id="stick"></div>
//     </div>
//     <script>
//       const joy = document.getElementById('joy');
//       const stick = document.getElementById('stick');
//       let center = 100;
//       joy.addEventListener("touchmove", e => {
//        e.preventDefault();
//        let t = e.touches[0];
//        let rect = joy.getBoundingClientRect();
       
//        let x = t.clientX - rect.left;
//        x = Math.max(0, Math.min(200, x));

//        stick.style.left = (x  - 30) + "px";
//        let angle = Math.round((x / 200) * 180);
//        fetch("/setServo?angle=" + angle);
//     });
//       joy.addEventListener("touchend", e => {
//         stick.style.left = "70px";
//         // fetch("/setServo?angle=90");       
//        });
//        </script>
//     </body>
//     </html>
// )rawliteral";
//   server.send(200, "text/html", html);
// }

// void defaultServo(){
//   baseServo.write(90);
// }

// void handleSet() {
//   int angle = server.arg("angle").toInt();
//   constrain(angle, 0, 180);
//   int currentAngle = angle;
//   baseServo.write(angle);
//   server.send(200, "text/plain", "OK");
// }

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(115200, SERIAL_8N1);
//   baseServo.attach(13);  // attaches the servo on pin 13 to the servo object
//   defaultServo();

//   WiFi.begin(ssid, password);
//   Serial.println("Connecting to WiFi..");
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(300);
//     Serial.print(".");
//   }
//     Serial.println(WiFi.localIP());
//     server.on("/", handleRoot);
//     server.on("/setServo", handleSet);
//     server.begin();
//     Serial.println("HTTP server started");

//   }

// void loop() {
//   // put your main code here, to run repeatedly:
//   server.handleClient();
// }
