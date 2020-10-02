#include <WiFi.h>
#include <WiFiUdp.h>

// WiFi network name and password:
const char ssid[] = "ENSIMElec";
const char password[] = "***";

// Port d'écoute UDP
const uint16_t PORT = 1234;

// Taille du tampon de réception
const uint16_t BUFFER_SIZE = 512;
// Tampon de réception
char buffer[BUFFER_SIZE];
// Taille du paquet reçu;
uint16_t len = 0;

// L'instance du serveur UDP
WiFiUDP udp;

void setup() {
 
  Serial.begin(115200);
  // On attend "un peu" que le buffer soit prêt
  delay(10);
  // On efface la configuration précédente
  WiFi.disconnect(true);
  // Initialisation de la connection
  WiFi.begin(ssid, password);
  // Test pour déterminer quand la connection est prete
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  // Affichage des informations
  Serial.print("\nConnecte a ");
  Serial.print(ssid);
  Serial.print(" avec l'ip ");
  Serial.println(WiFi.localIP());

  // Démarrage de l'écoute
  udp.begin(PORT);
  Serial.print("Démarrage de l'ecoute sur le port ");
  Serial.println(PORT);

}

// lecture du packet
void readPacket() {
  len = udp.available(); // taille du packet
  Serial.print("Paquet de ");
  Serial.print(len);
  Serial.print(" octets recu de ");
  Serial.print(udp.remoteIP());
  Serial.print(":");
  Serial.print(udp.remotePort());
  Serial.print(" contenant '");
  // Mise en tampon du paquet
  udp.read(buffer, len);
  // Affichage du contenu du paquet
  for (int i = 1; i <= len; i++) {
    Serial.print(buffer[i - 1]);
  }
  Serial.println("'");
}
void sendPacket(uint8_t content, IPAddress ip, uint16_t port) {
  udp.beginPacket(ip, port);
  udp.write(content);
  udp.endPacket();
}
void loop() {
  if (udp.parsePacket() > 0) {
    readPacket();
  }
}
