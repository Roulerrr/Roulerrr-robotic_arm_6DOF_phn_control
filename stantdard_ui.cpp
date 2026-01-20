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

// Servo servos[5];
// int servoPins[5] = {13, 12, 14, 27, 26};
// // void defaultServo(){
// //     baseServo.write(90);
// //     shoulderServo.write(90);
// //     elbowServo.write(90);
// //     wristServo.write(90);
// //     gripperServo.write(90);
// // }

// void handleRoot() {
//     String html = R"rawliteral(
//     <!DOCTYPE html>
//     <html>
//     <head>
//         <title>ESP32 Servo Control</title>
//         <meta name="viewport" content="width=device-width, initial-scale=1">
//         <style>
//         #joy {
//             width:200px;
//             height:200px;
//             background: #ddd;
//             border-radius: 50%;
//             position: relative;
//             touch-action: none;
//             }
//             #stick {
//             width: 60px;
//             height: 60px;
//             background: #555;
//             border-radius: 50%;
//             position: absolute;
//             left: 70px; top: 70px;
//             }
//         </style>
//     </head>
//     <body>
//     <h3>ESP32 Control Servo</h3>
//     <div id="joy">
//         <div id="stick"></div>
//     </div>
//     <div>
//         <label>Elbow</label><br>
//         <input type="range" min="0" max="180" value="90" id="elbow">
//     </div>
//     <div>
//         <label>Wrist</label><br>
//         <input type="range" min="0" max="180" value="90" id="wrist">
//     </div>
//     <div>
//         <label>Gripper</label><br>
//         <input type="range" min="0" max="180" value="90" id="gripper">
//     </div>
//     <script>
//         const joy = document.getElementById('joy');
//         const stick = document.getElementById('stick');
//         const elbowSlider = document.getElementById('elbow');
//         const wristSlider = document.getElementById('wrist');
//         const gripperSlider = document.getElementById('gripper');

//         const center = 100;
//         let lastX = 90;
//         let lastY = 90;

//         joy.addEventListener("touchmove", e =>{
//          e.preventDefault();
//          let t = e.touches[0];
//          let rect = joy.getBoundingClientRect(); // เก็บค่าผลลพธ์ทั้งหมดที่ broswer คำนวณออกมาในขณะนั้น ค่าหน้าจอจริง
//          let x = t.clientX - rect.left;
//          let y = t.clientY - rect.top;
//          x = Math.max(0, Math.min(200, x));
//          y = Math.max(0, Math.min(200, y));

//          let dx = x -center;
//          let dy = y -center;

//          const deadZone = 10; // กำหนดขอบเขตความตายตัว (Dead Zone) เพื่อป้องกันการสั่นไหวเล็กน้อย
//          if (Math.abs(dx) < deadZone) {
//                 dx = 0;
//          }
//          if (Math.abs(dy) < deadZone) {
//                 dy = 0;
//          }  

//     /*  clamp ค่าตำแหน่งให้อยู่ในช่วง 0-200 ทำ Math,min ก่อนเพราะถ้าไม่ทำจะเกิด error ได้ เลือกค่าที่น้อยกว่า ระหวาง 200 กับ x
//         ex x = 50 -> Math.min(200, 50) = 50
//         ex x = 250 -> Math.min(200, 250) = 200
//          จากนั้นค่อยทำ Math.max เพื่อเลือกค่าที่มากกว่า ระหวาง 0 กับ ค่าที่ได้จากขั้นตอนก่อนหน้า
//         ex x = 150 -> Math.max(0, 150) = 150
//         ex x = -50 -> Math.max(0, -50) = 0
//         ถ้าติดลบจะได้ 0 ถ้าติดบวกจะได้ 200
//     */

//         stick.style.left = (center + dx - 30) + "px";
//         stick.style.top = (center + dy - 30) + "px";

//         let base = Math.round(map(dx, -100, 100, 0, 180));
//         let shoulder = Math.round(map(dy, -100, 100, 0, 180));

//         if (base !== lastX){
//             fetch(`/setServo?id=0&angle=${base}`);
//             lastX = base;
//         }
//         if (shoulder !== lastY){
//             fetch(`/setServo?id=1&angle=${shoulder}`);
//             lastY = shoulder;
//         }           
// });
//     joy.addEventListener("touchend", e =>{
//         stick.style.left = "70px";
//         stick.style.top = "70px";
//         /* joy.width = 200
//             stick.width = 60
//             center = 100
//             left = center - stick.width/2 = 100 - 30 = 70  
//             position center      */
//         });
//         elbowSlider.oninput = () => {
//         fetch(`/setServo?id=2&angle=${elbowSlider.value}`)
//         };

//         wristSlider.oninput = () => {
//         fetch(`/setServo?id=3&angle=${wristSlider.value}`)
//         };

//         gripperSlider.oninput = () => {
//         fetch(`/setServo?id=4&angle=${gripperSlider.value}`)
//         };
//         function map(v, in_min, in_max, out_min, out_max){
//             return (v - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
//         }
//         </script>
//     </body>
//     </html>
//     )rawliteral";
//     server.send(200, "text/html", html);    
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
//     for (int i = 0; i < 5; i++){
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
//     server.begin();
//     Serial.println("HTTP server started");
// } 

// void loop() {
//     server.handleClient();



    
// }

