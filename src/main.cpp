// #include <Arduino.h>
// #include <ArduinoJson.h>

// String mensagem;
// String mensagemAlt;

// void setup()
// {
//   Serial.begin(115200);
//   Serial.setTimeout(5000);

//   // Serial.println("Digite uma mensagem");
// }

// void loop()
// {
// If (Serial.available()){
//   mensagem = Serial.readStringUntil('\n');
// }

// // Serial.print("Mensagem recebida");
// // Serial.println(mensagem);

// mensagemAlt = "Mensagem recebida: " + mensagem + "!";

// Serial.println(mensagemAlt);
// Serial.println(mensagemAlt.length());

// String parte = mensagemAlt.substring(0, 5); //caracter inicial e até qual eu quero
// Serial.println(parte);

// parte.toLowerCase(); //vai colocar tudo da variável em minúsculo
// parte.toUpperCase(); //caixa alta

// String msg = "Temp: 25.5";

// if (msg.startsWith("Temp")) // tem também endsWith
// {
//   Serial.println("Temperatura recebida");
// }

// JSON = Javascript Object Notation -----------------------------

//   { //funciona como uma caixa de dados
//     "temperatura": 25.5,
//     "umidade": 50,
//     "chovendo" = true,
//     "ceu" = "nublado" // não precisa de vírgula depois do último atributo
//   }

//   delay(3000);
// }

//==================================================

// #include <Arduino.h>
// #include <ArduinoJson.h>

// void setup(){
//   Serial.begin(115200);

//   JsonDocument doc; //cria o objeto json

//   doc ["Temp"] = 25.5; //adicionando dados ao objeto
//   doc ["Umi"] = 60;
//   doc ["Sensor"] = "DHT22";

//   serializeJsonPretty(doc, Serial); //enviando um objeto presente em doc pra serial

//   float temperatura = doc["Temp"];
//   float umidade = doc["Umi"];
//   String sensor = doc["Sensor"]; //guardando os valores do json em variáveis pra poder trabalhar com eles

//   Serial.println(sensor);
// }

// void loop(){

// }

//==============================================

#include <Arduino.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>
#include <LiquidCrystal_I2C.h>

JsonDocument pasta;
String frase;
BluetoothSerial BT;
unsigned long marcoZero = 0;
unsigned long intervalo = 2000;
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  if (BT.begin("BtSlaveLara"))
  { // verificação pra ver se o bluetooth tá com defeito
    Serial.println("Bluetooth iniciado com sucesso");
    Serial.print("Endereco bluetooth: ");
    Serial.println(BT.getBtAddressString());
  }
  else
  {
    Serial.println("Erro ao iniciar o bluetooth");
  }

  // EXERCICIO 2 ----------------------------------------

  delay(2000); // tempo para a outra ESP32 ficar pronta

  BT.println("Digite seu nome");
  delay(500);

  BT.println("Digite sua idade");
  delay(500);

  BT.println("Usuario habilitado?");
  delay(500);

   if (Serial.available())
  {
    String mensagemEnviada = Serial.readStringUntil('\n');
    mensagemEnviada.trim();

    BT.println(mensagemEnviada);
  }

  pasta["nome"] = "Gabriel";
  pasta["idade"] = 17;
  pasta["habilitado"] = "Sim";

  serializeJsonPretty(pasta, Serial);

  serializeJsonPretty(pasta, Serial); //minha serial
  Serial.println();

  serializeJson(pasta, BT); //transferência bluetooth
  BT.println();

  if (BT.available())
  {
    String msgRecebida = BT.readStringUntil('\n');
    DeserializationError erro = deserializeJson(pasta, msgRecebida); // verifico se tem erro nos dados recebidos e tira os dados da mensagem e coloca na pasta
  
    if (erro)
    {
      Serial.println("ERRO AO INTERPRETAR JSON");
    }

    Serial.println(msgRecebida);
}
}

void loop()
{

  // ENVIO DE DADOS -----------------------------

  // le os dados e envia, quem vai enviar precisa montar o pacote pra envio

  // ler os dados do dht22

  // salvar os dados na pasta
  // pasta["temp"] = variavel;

  // String mensagem;
  // serializeJson(pasta, mensagem);

  // BT.println(mensagem);

  // RECEBIMENTO DE DADOS -------------------------------

  // ETAPA 3 -------------------------------------------

  // também precisa de json criado, pois vai receber textos e precisa converter

  // if (BT.available())
  // {
  //   String msgRecebida = BT.readStringUntil('\n');
  //   DeserializationError erro = deserializeJson(pasta, msgRecebida); // verifico se tem erro nos dados recebidos e tira os dados da mensagem e coloca na pasta

  //   if (erro)
  //   {
  //     Serial.println("ERRO AO INTERPRETAR JSON");
  //   }

  //   float tempC = pasta["temp"];
  //   float umidade = pasta["umi"];

  //   //SERIAL -------------------------------------------------------------------

  //   frase = "Temperatura = " + String(tempC) + " e Umidade = " + String(umidade);

  //   Serial.println(frase);

  //   // LCD --------------------------------------------------------------------

  //   unsigned long marcoAtual = millis();
  //   static float ultimaTempC = -999;
  //   static float ultimaUmid = -999;

  //   if (marcoAtual - marcoZero >= intervalo)
  //   {
  //     if (tempC != ultimaTempC)
  //     {
  //       lcd.setCursor(0, 0);
  //       lcd.print("Temp em C = ");
  //       lcd.print(tempC);

  //       ultimaTempC = tempC;
  //     }
  //     else
  //     {
  //       lcd.setCursor(0, 0);
  //       lcd.print("Temp em C = ");
  //       lcd.print(ultimaTempC);

  //       ultimaTempC = tempC;
  //     }

  //     if (umidade != ultimaUmid)
  //     {
  //       lcd.setCursor(0, 1);
  //       lcd.print("Umidade = ");
  //       lcd.print(umidade);

  //       ultimaUmid = umidade;
  //     }
  //     else
  //     {
  //       lcd.setCursor(0, 1);
  //       lcd.print("Umidade = ");
  //       lcd.print(ultimaUmid);

  //       ultimaUmid = umidade;
  //     }

  //     //------------minha serial ------------
  //     Serial.print("Temp C = ");
  //     Serial.println(ultimaTempC);
  //     Serial.print("Umidade = ");
  //     Serial.println(ultimaUmid);
  //     Serial.println("---------------");

  //     marcoZero = marcoAtual;
  //   }
  // }

}
