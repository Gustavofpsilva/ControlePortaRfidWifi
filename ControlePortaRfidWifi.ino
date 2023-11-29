#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>

#define SS_PIN 5     // Pino de seleção (SDA)
#define RST_PIN 18   // Pino de reset
MFRC522 mfrc522(SS_PIN, RST_PIN);

const char *ssid = "Sua Rede WiFi";
const char *password = "Sua Senha WiFi";

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();

  // Conectar ao WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");
}

void loop() {
  // Verificar a presença de uma tag RFID
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Obter o UID da tag RFID
    String rfidUid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      rfidUid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      rfidUid += String(mfrc522.uid.uidByte[i], HEX);
    }
    rfidUid.toUpperCase();

    Serial.print("Tag RFID detectada. UID: ");
    Serial.println(rfidUid);

    // Verificar se o UID corresponde a um UID autorizado
    if (isAuthorized(rfidUid)) {
      Serial.println("Acesso autorizado. Porta aberta!");
      // Adicione aqui qualquer ação que deseja executar quando o acesso é autorizado
    } else {
      Serial.println("Acesso negado. Porta fechada!");
      // Adicione aqui qualquer ação que deseja executar quando o acesso é negado
    }

    delay(1000); // Aguarde um tempo antes de verificar a próxima tag
  }
}

bool isAuthorized(String rfidUid) {
  // Aqui você pode implementar lógica para verificar se o UID está na lista de autorizações
  // Neste exemplo, consideraremos que apenas um UID específico é autorizado
  String authorizedUid = "DEMOUID"; // Substitua pelo UID autorizado

  return rfidUid.equals(authorizedUid);
}
