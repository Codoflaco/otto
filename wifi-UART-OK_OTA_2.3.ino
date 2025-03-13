/*-----------------------------------------------------------------------------------------
 * En resumen, este código configura un servidor web en un modulo ESP8266-01 conectado a 
 * travez del puerto UART con un arduino Nano y permite controlar un robot "OTTO" 
 * a través de una interfaz web. Los comandos se envían desde la página web al robot 
 * a través de la conexión serie, y también se incluye la capacidad de actualizar el 
 * firmware del ESP8266 a través de OTA (Over-The-Air). La página web se genera como una 
 * cadena HTML en el código y permite controlar el movimiento, las expresiones faciales y 
 * los sonidos del robot, así como enviar comandos personalizados para desplegar texto en 
 * la matriz de leds.
 ----------------------------------------------------------------------------------------*/

#include <ArduinoOTA.h> // Librería para la actualización OTA (Over-The-Air)
#include <ESP8266WiFi.h> // Librería para la comunicación Wi-Fi
#include <ESPAsyncWebServer.h> // Librería para crear el servidor web

// WiFi credentials
const char* ssid = "SITE"; // Sustituya con el ssid de su red Wifi
const char* password = "colobringo"; // Sustituya con el password de su red Wifi

AsyncWebServer server(80); // Crear una instancia del servidor web en el puerto 80

void setup() {
Serial.begin(9600); // Iniciar comunicación serial con una velocidad de 9600 baudios
delay(10);

    // Configurar el ESP8266 como Access Point
    WiFi.softAP(ssid, password);

/* Conectarse a la red Wi-Fi
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.println("Connecting to WiFi...");
}
Serial.println("Connected to WiFi");*/

 // Obtener la IP del servidor
    IPAddress IP = WiFi.softAPIP();
    Serial.print("Servidor WiFi iniciado. Dirección IP: ");
    Serial.println(IP);

// Definir las rutas del servidor web
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
// Aquí se crea la página web que muestra botones para enviar comandos al robot
// El HTML se genera como una cadena de texto
// Se definen botones para control de movimiento, expresiones faciales y sonidos
// También se incluye un formulario para enviar comandos de texto personalizado al robot
// que despliegan el texto secuencialmente en la matriz de leds del robot
// Se adjunta código JavaScript para manejar los eventos de clic en los botones y el formulario
// El código HTML se envía como respuesta al cliente
String html = "<html>";
html += "<head>";
html += "<meta charset='UTF-8'>";
html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
html += "<title>OTTO Control</title>";
html += "<style>";
html += "body {";
html += "font-family: Arial, sans-serif;";
html += "margin: 0;";
html += "padding: 0;";
html += "background-color: #f2f2f2;";
html += "}";

html += "h1 {";
html += "text-align: center;";
html += "}";

html += ".button-grid {";
html += "display: grid;";
html += "grid-template-columns: repeat(auto-fit, minmax(150px, 1fr));";
html += "gap: 10px;";
html += "padding: 10px;";
html += "}";

html += ".button-container {";
html += "text-align: center;";
html += "}";

html += "button {";
html += "background-color: #008CBA;";
html += "width: 100%;";
html += "color: white;";
html += "padding: 10px;";
html += "border: none;";
html += "cursor: pointer;";
html += "font-size: 16px;";
html += "}";

html += "label {";
html += "display: block;";
html += "margin-bottom: 10px;";
html += "}";

html += "input[type='text'] {";
html += "width: 100%;";
html += "padding: 5px;";
html += "margin-bottom: 10px;";
html += "}";

html += "#commandX {";
html += "background-color: #008CBA;";
html += "width: 100%;";
html += "color: white;";
html += "padding: 10px;";
html += "border: none;";
html += "cursor: pointer;";
html += "font-size: 16px;";
html += "}";

html += "p {";
html += "text-align: center;";
html += "}";

html += "@media screen and (max-width: 768px) {";
html += ".button-grid {";
html += "grid-template-columns: repeat(auto-fit, minmax(120px, 1fr));";
html += "gap: 5px;";
html += "}";
html += "}";
html += "</style>";
html += "</head>";
html += "<body>";
html += "<h1>OTTO SE MUEVE</h1>";
html += "<div class='button-grid'>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 1 1000'>ATRAS</button>";
html += "</form>";
html += "<p id='status1'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 2 1000'>ADELANTE</button>";
html += "</form>";
html += "<p id='status2'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 3 1000'>DERECHA</button>";
html += "</form>";
html += "<p id='status3'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 4 1000'>IZQUIERDA</button>";
html += "</form>";
html += "<p id='status4'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 5 1000 30'>ARRIBA Y ABAJO</button>";
html += "</form>";
html += "<p id='status5'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 6 1000 30'>MOONWAKER 1</button>";
html += "</form>";
html += "<p id='status6'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 7 1000 30'>MOONWAKER 2</button>";
html += "</form>";
html += "<p id='status7'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 8 1000 30'>SWING</button>";
html += "</form>";
html += "<p id='status8'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 9 1000 30'>CRUZAITO 1</button>";
html += "</form>";
html += "<p id='status9'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 10 1000 30'>CRUZAITO 2</button>";
html += "</form>";
html += "<p id='status10'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 11 1000'>BRINCO</button>";
html += "</form>";
html += "<p id='status11'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 12 1000 30'>ALETEO 1</button>";
html += "</form>";
html += "<p id='status12'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 13 1000 30'>ALETEO 2</button>";
html += "</form>";
html += "<p id='status13'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 14 1000 20'>GIRAR PIES</button>";
html += "</form>";
html += "<p id='status14'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 15 500'>INCLINA 1</button>";
html += "</form>";
html += "<p id='status15'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 16 500'>INCLINA 2</button>";
html += "</form>";
html += "<p id='status16'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 17 500'>SACUDE PIERNA DERECHA</button>";
html += "</form>";
html += "<p id='status17'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 18 500'>SACUDE PIERNA IZQUIERDA</button>";
html += "</form>";
html += "<p id='status18'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 19 500 20'>NERVIOSO</button>";
html += "</form>";
html += "<p id='status19'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='M 20 500 15'>VUELTA ASCENDENTE</button>";
html += "</form>";
html += "<p id='status20'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<br>";
html += "<br>";
html += "<form action='/send-command' method='post'>";
html += "<button style='font-size: 18px;' name='command' value='M 0'>PARAR</button>";
html += "</form>";
html += "<p id='status21'></p>";
html += "</div>";

html += "</div> ";

html += "<h1>OTTO SE EXPRESA</h1>";
html += "";
html += "<div class='button-grid'>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='H 1'>FELIZ</button>";
html += "</form>";
html += "<p id='status22'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='H 2'>SUPER FELIZ</button>";
html += "</form>";
html += "<p id='status23'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='H 3'>TRISTE</button>";
html += "</form>";
html += "<p id='status24'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='H 4'>DORMIDO</button>";
html += "</form>";
html += "<p id='status25'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='H 5'>PUN</button>";
html += "</form>";
html += "<p id='status26'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='H 6'>CONFUNDIDO</button>";
html += "</form>";
html += "<p id='status27'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='H 7'>AMOR</button>";
html += "</form>";
html += "<p id='status28'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='H 8'>ENOJADO</button>";
html += "</form>";
html += "<p id='status29'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='H 9'>BUCHES</button>";
html += "</form>";
html += "<p id='status30'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='H 10'>GENIAL</button>";
html += "</form>";
html += "<p id='status31'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='H 11'>ONDA</button>";
html += "</form>";
html += "<p id='status32'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='H 12'>VICTORIA</button>";
html += "</form>";
html += "<p id='status33'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='H 13'>FALLA</button>";
html += "</form>";
html += "<p id='status34'></p>";
html += "</div>";

html += "</div>";
html += "";
html += "<h1>OTTO SUENA</h1>";
html += "";
html += "<div class='button-grid'>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 1'>CONEXION</button>";
html += "</form>";
html += "<p id='status35'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 2'>DESCONEXION</button>";
html += "</form>";
html += "<p id='status36'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 3'>SORPRESA</button>";
html += "</form>";
html += "<p id='status37'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 4'>0H00H</button>";
html += "</form>";
html += "<p id='status38'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 5'>0H00H 2</button>";
html += "</form>";
html += "<p id='status39'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 6'>CHIPIL</button>";
html += "</form>";
html += "<p id='status40'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 7'>DORMIDO</button>";
html += "</form>";
html += "<p id='status41'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 8'>FELIZ</button>";
html += "</form>";
html += "<p id='status42'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 9'>SUPER FELIZ</button>";
html += "</form>";
html += "<p id='status43'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 10'>FELIZ CORTO</button>";
html += "</form>";
html += "<p id='status44'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 11'>TRISTE</button>";
html += "</form>";
html += "<p id='status45'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 12'>CONFUSO</button>";
html += "</form>";
html += "<p id='status46'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 13'>PUN 1</button>";
html += "</form>";
html += "<p id='status47'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 14'>PUN 2</button>";
html += "</form>";
html += "<p id='status48'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 15'>PUN 3</button>";
html += "</form>";
html += "<p id='status49'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 16'>MODO 1</button>";
html += "</form>";
html += "<p id='status50'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 17'>MODO 2</button>";
html += "</form>";
html += "<p id='status51'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 18'>MODO 3</button>";
html += "</form>";
html += "<p id='status52'></p>";
html += "</div>";

html += "<div class='button-container'>";
html += "<form action='/send-command' method='post'>";
html += "<button name='command' value='K 19'>BOTON OPRIMIDO</button>";
html += "</form>";
html += "<p id='status53'></p>";
html += "</div>";

html += "</div> ";

html += "<h1>OTTO DESPLIEGA TEXTO</h1> ";

html += "<p>Introduce un texto de maximo 9 letras mayusculas o numeros sin espacios</p>";
html += "<form>";
html += "<input type='text' id='inputText' placeholder=''>";
html += "</form>";

html += "<form action='/send-command' method='post'>";
html += "<button id='commandX'value='X' onclick='modifyButton()'>ENVIAR TEXTO</button>";
html += "</form>";
html += "<p id='errorMessage' style='color: red;'></p>";
html += "<p id='status54'></p>";

html += "<script>";
html += "var forms = document.getElementsByTagName('form');";
html += "for (var i = 0; i < forms.length; i++) {";
html += "forms[i].addEventListener('submit', function(e) {";
html += "e.preventDefault();";
html += "var command = this.querySelector('button').value;";
html += "var statusId = 'status' + (i + 1);";
html += "var xhr = new XMLHttpRequest();";
html += "xhr.open('POST', '/send-command', true);";
html += "xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');";
html += "xhr.onload = function() {";
html += "if (xhr.status === 200) {";
html += "document.getElementById(statusId).innerHTML = 'Command sent: ' + xhr.responseText;";
html += "}";
html += "};";
html += "xhr.send('command=' + encodeURIComponent(command));";
html += "});";
html += "}";

html += "function modifyButton() {";
html += "var newText = document.getElementById('inputText').value;";
html += "var button = document.getElementById('commandX');";
html += "var errorMessage = document.getElementById('errorMessage');";
html += "var regex = /^[A-Z0-9]{1,9}$/;";
html += "if (regex.test(newText)) {";
html += "button.value = newText;";
html += "document.getElementById('commandX').value = 'R ' + button.value;";
html += "errorMessage.textContent = '';"; // Clear any previous error message
html += "} else {";
html += "errorMessage.textContent = 'Introduzca de 1 a 9 letras mayusculas o numeros sin espacios por favor.';";
html += "document.getElementById('commandX').value = 'X';";
html += "}";
html += "}";

html += "</script>";

html += "</body></html>";
request->send(200, "text/html", html);
});
// Esta ruta se utiliza para procesar los comandos enviados desde la página web
// Los comandos se obtienen de los argumentos POST y se envían al robot a través del puerto serie (Serial1)
// Luego se envía una respuesta al cliente que indica que el comando se ha enviado con éxito
/*server.on("/send-command", HTTP_POST, [](AsyncWebServerRequest *request){
String command = request->arg("command");
Serial.println(command);



request->send(200, "text/plain", "Command sent: " + command);
});*/

server.on("/send-command", HTTP_POST, [](AsyncWebServerRequest *request){
if (request->hasParam("command", true)) {
String command = request->getParam("command", true)->value();
Serial.println(command);

// Send the command to the UART (Serial)
Serial1.println(command);

request->send(200, "text/plain", "Comando recibido: " + command);
} else {
request->send(400, "text/plain", "Error: No se recibió ningún comando");
}
});

// Iniciar el servidor// Start the server
server.begin();
ArduinoOTA.begin(); // Iniciar la actualización OTA
ArduinoOTA.setHostname("otto"); // Establecer el nombre de host del dispositivo para la actualización OTA
}
void loop() {
ArduinoOTA.handle(); // Manejar las actualizaciones OTA
}
