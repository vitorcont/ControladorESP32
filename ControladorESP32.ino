#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp32.h>
#include <SPI.h>
#include <IRremote.h>
#include "DHT.h"
#include <WidgetRTC.h>

#include <WiFi.h> //lib para configuração do Wifi
#include <ArduinoOTA.h> //lib do ArduinoOTA 
#include <ESPmDNS.h> //lib necessária para comunicação network
#include <WiFiUdp.h> //lib necessária para comunicação network

char auth[] = "P_dZlqXeRR2CzMmtcBhzmdx2uqYO6_cJ";
char ssid[] = "Conti 2.4GHz";
char pass[] = "Wolff2015";

const char* ssid2 = "Conti 2.4GHz"; //nome da rede
const char* password2 = "Wolff2015"; //senha da rede
unsigned long myTime;

int BUZZER = 25; //D1
//LED NA GPIO26
int LDR = 34;

int flag1 = 0;
int flag2 = 0;
int flag_controle=0;
int flag_restart=0;
int contador_atividade=0;
int AtualM=0;
int GraficoMin=0;
int GraficoCont=0;

IRsend irsend;
#define IR_SEND_PIN 26
#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); //D7
#define sensor 5

WidgetLED luz(V10);
WidgetLED flag(V13);
WidgetLED led_sensor(V17);
WidgetRTC rtc;
int hora[2];
int hora_restart=0;

int v4;
int v15;
int flag_alerta=0;
int v9 = 15;
int gps = 0;
int flag_luz = 0;

int i=0;
int alarme;
int alarme_flag;
float temp = 0;
float humi = 0;
int frequencia = 32; //32 TV e 48 AR
//TV
// BOTÃO LIGA / DESLIGA
unsigned int LD[] = {4600, 4500, 600, 1700, 650, 1650, 600, 1700, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 1700, 650, 1700, 600, 1700, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 600, 1700, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 600, 1700, 650, 550, 650, 1650, 650, 1650, 650, 1700, 650, 1650, 650, 1700, 650, 1700, 600}; //COLE A LINHA RAW CORRESPONDENTE DENTRO DAS CHAVES
//Source
unsigned int SC[] = {4600, 4500, 650, 1650, 650, 1650, 650, 1700, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 1650, 650, 1650, 650, 1650, 600, 550, 650, 550, 650, 550, 650, 550, 650, 550, 600, 1700, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 1700, 600, 1700, 650, 1700, 650, 1700, 650, 1700, 650, 1650, 650, 1650, 650};
//VOL++
unsigned int UP[] = {4600, 4500, 650, 1650, 650, 1650, 650, 1650, 650, 550, 650, 550, 650, 550, 600, 550, 650, 550, 650, 1700, 650, 1700, 650, 1650, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 1650, 650, 1700, 650, 1650, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 1700, 650, 1700, 650, 1650, 650, 1650, 650, 1650, 650};
//VOL--
unsigned int DOWN[] = {4600, 4500, 650, 1650, 650, 1700, 650, 1650, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 1700, 650, 1650, 650, 1700, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 600, 1700, 650, 1650, 650, 550, 650, 1650, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 550, 650, 1650, 650, 550, 650, 1700, 650, 1650, 650, 1650, 650, 1700, 650};

//AR CONDICIONADO
//LIGA
unsigned int LDAC[] = {3350,1550, 500,350, 500,350, 450,1200, 450,350, 500,1150, 500,350, 450,400, 500,350, 450,1200, 450,1200, 450,350, 500,350, 500,350, 500,1150, 450,1200, 500,350, 450,350, 500,350, 500,350, 500,350, 450,350, 500,350, 500,350, 500,350, 450,350, 500,350, 500,350, 500,350, 500,1150, 500,350, 450,350, 500,350, 500,350, 450,400, 450,350, 500,350, 500,1150, 500,350, 500,350, 450,350, 500,350, 500,1150, 500,1150, 500,1150, 500,1150, 500,1150, 500,1150, 500,1150, 500,1150, 450,400, 500,350, 450,1200, 450,350, 500,350, 500,350, 500,350, 450,400, 450,350, 500,350, 450,400, 500,1150, 500,1150, 500,350, 450,350, 500,1150, 500,350, 500,350, 500,350, 450,350, 500,1150, 500,350, 500,350, 500,1150, 500,350, 450,350, 500,350, 500,350, 500,350, 450,350, 500,350, 500,1150, 500,350, 500,350, 450,400, 450,350, 500,350, 500,350, 450,400, 450,350, 500,350, 500,350, 500,350, 450,350, 500,350, 500,350, 500,350, 450,350, 500,350, 450,400, 500,350, 450,350, 500,350, 500,350, 500,350, 450,350, 500,350, 500,350, 450,400, 500,350, 450,350, 500,350, 500,350, 500,350, 450,350, 500,350, 450,400, 450,400, 450,1200, 450,350, 500,350, 500,1150, 500,350, 500,1150, 450,1200, 450,400, 450,350, 500,350, 500,1150, 500};
unsigned int DSAC[] = {3350, 1600, 500, 400, 500, 400, 500, 1200, 500, 400, 500, 1200, 500, 400, 500, 400, 500, 400, 500, 1200, 500, 1200, 500, 400, 500, 400, 500, 400, 500, 1200, 500, 1200, 500, 400, 500, 400, 500, 400, 500, 400, 500, 400, 500, 400, 500, 400, 500, 400, 500, 400, 500, 400, 500, 400, 500, 400, 500, 400, 500, 1200, 500, 400, 500, 400, 500, 400, 500, 400, 500, 400, 500, 400, 500, 400, 500, 1200, 500, 400, 500, 400, 500, 400, 500, 400, 500, 1200, 500, 400, 500, 400, 500, 400, 500, 400, 500, 400, 500, 400, 500, 1200, 500, 400, 500, 1200, 500, 1200, 500, 1200, 500, 1200, 500, 1200, 500, 1200, 500};

void setup()
{
  // Debug console
  pinMode(BUZZER, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(sensor, INPUT);
  Blynk.begin(auth, ssid, pass);
  rtc.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid2, password2);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    //caso falha da conexão, reinicia wifi
    Serial.println("Connection Failed! Rebooting...");
    delay(500);
    ESP.restart();
  }

  ArduinoOTA.setHostname("esp32");
  ArduinoOTA.setPassword("senha123");
  ArduinoOTA.onStart( startOTA ); //startOTA é uma função criada para simplificar o código
  ArduinoOTA.onEnd( endOTA ); //endOTA é uma função criada para simplificar o código
  ArduinoOTA.onProgress( progressOTA ); //progressOTA é uma função criada para simplificar o código
  ArduinoOTA.onError( errorOTA );//errorOTA é uma função criada para simplificar o código
  ArduinoOTA.begin();

  Serial.println(WiFi.localIP());

  Serial.begin(115200);
  dht.begin();

}

void startOTA()
{
  String type;

  //caso a atualização esteja sendo gravada na memória flash externa, então informa "flash"
  if (ArduinoOTA.getCommand() == U_FLASH)
    type = "flash";
  else  //caso a atualização seja feita pela memória interna (file system), então informa "filesystem"
    type = "filesystem"; // U_SPIFFS
  //exibe mensagem junto ao tipo de gravação
  Serial.println("Start updating " + type);
}

void endOTA()
{
  Serial.println("\nEnd");
}

//exibe progresso em porcentagem
void progressOTA(unsigned int progress, unsigned int total)
{
  Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
}

//caso aconteça algum erro, exibe especificamente o tipo do erro
void errorOTA(ota_error_t error)
{
  Serial.printf("Error[%u]: ", error);

  if (error == OTA_AUTH_ERROR)
    Serial.println("Auth Failed");
  else if (error == OTA_BEGIN_ERROR)
    Serial.println("Begin Failed");
  else if (error == OTA_CONNECT_ERROR)
    Serial.println("Connect Failed");
  else if (error == OTA_RECEIVE_ERROR)
    Serial.println("Receive Failed");
  else if (error == OTA_END_ERROR)
    Serial.println("End Failed");
}

BLYNK_CONNECTED()
{
  rtc.begin();
}

BLYNK_WRITE(V0)
{
  int pino = param.asInt();
  if (pino == 1)
  {
    frequencia = 32;
    irsend.sendRaw(LD, sizeof(LD) / sizeof(LD[0]), frequencia);
    delay(25);
    irsend.sendRaw(LD, sizeof(LD) / sizeof(LD[0]), frequencia);
    delay(25);
    irsend.sendRaw(LD, sizeof(LD) / sizeof(LD[0]), frequencia);
    delay(25);
    irsend.sendRaw(LD, sizeof(LD) / sizeof(LD[0]), frequencia);
  }
}

BLYNK_WRITE(V1)
{
  int pino = param.asInt();
  if (pino == 1)
  {
    frequencia = 32;
    irsend.sendRaw(SC, sizeof(SC) / sizeof(SC[0]), frequencia);
    delay(25);
    irsend.sendRaw(SC, sizeof(SC) / sizeof(SC[0]), frequencia);
    delay(25);
    irsend.sendRaw(SC, sizeof(SC) / sizeof(SC[0]), frequencia);
    delay(25);
    irsend.sendRaw(SC, sizeof(SC) / sizeof(SC[0]), frequencia);
  }
}

BLYNK_WRITE(V2)
{
  int pino = param.asInt();
  if (pino == 1)
  {
    frequencia = 32;
    irsend.sendRaw(UP, sizeof(UP) / sizeof(UP[0]), frequencia);
    delay(25);
    irsend.sendRaw(UP, sizeof(UP) / sizeof(UP[0]), frequencia);
    delay(25);
    irsend.sendRaw(UP, sizeof(UP) / sizeof(UP[0]), frequencia);
    delay(25);
    irsend.sendRaw(UP, sizeof(UP) / sizeof(UP[0]), frequencia);
  }
}

BLYNK_WRITE(V3)
{
  int pino = param.asInt();
  if (pino == 1)
  {
    frequencia = 32;
    irsend.sendRaw(DOWN, sizeof(DOWN) / sizeof(DOWN[0]), frequencia);
    delay(25);
    irsend.sendRaw(DOWN, sizeof(DOWN) / sizeof(DOWN[0]), frequencia);
    delay(25);
    irsend.sendRaw(DOWN, sizeof(DOWN) / sizeof(DOWN[0]), frequencia);
    delay(25);
    irsend.sendRaw(DOWN, sizeof(DOWN) / sizeof(DOWN[0]), frequencia);
  }
}

BLYNK_WRITE(V4)
{
  v4 = param.asInt();
  Blynk.virtualWrite(V4,v4);
}

BLYNK_WRITE(V5)
{
  alarme = param.asInt();
  Blynk.virtualWrite(V5,alarme);
}

BLYNK_WRITE(V6)
{
  alarme_flag = param.asInt();
  Blynk.virtualWrite(V6,alarme_flag);
}

BLYNK_WRITE(V9)
{
  v9 = param.asInt();
  Blynk.virtualWrite(V9,v9);
}

BLYNK_WRITE(V12)
{
  gps = param.asInt();
  Blynk.virtualWrite(V12,gps);
}

BLYNK_WRITE(V15) //Notificação
{
  v15 = param.asInt();
}



void f_alarme()
{
  if (alarme_flag == 1 && alarme == 1)
  {
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
    delay(200);
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
  }
  else
  {
    alarme = 0;
  }
}

void f_temp()
{
  humi = dht.readHumidity();
  temp=dht.readTemperature();

  Serial.println(temp);
  Blynk.virtualWrite(V7, temp);
  Blynk.virtualWrite(V8, humi);
  if (temp > 26)
    Blynk.setProperty(V7, "color", "#FF6417");
  else if (temp > 22 && temp < 27)
    Blynk.setProperty(V7, "color", "#D5FF4D");
  else
    Blynk.setProperty(V7, "color", "#32FCD7");

  if (humi <= 30)
    Blynk.setProperty(V8, "color", "#FF6417");
  else if (humi > 30 && temp <= 60)
    Blynk.setProperty(V8, "color", "#D5FF4D");
  else
    Blynk.setProperty(V7, "color", "#32FCD7");
  if (v9 > 15)
  {
    Blynk.setProperty(V9, "color", "#43C43F");
    int variacao = temp - v9;
    if(variacao<=0)
    {
      flag_controle=1;
    }
    if(flag_controle==1)
    {
      if (variacao > 2)
      {
        v4 = 1;
        flag_controle=0;
      }
      else
        v4 = 0;
    }
    else
      v4=1;
    
  }
  else
  {
    Blynk.setProperty(V9, "color", "#D3435C");
  }

}

void f_ar()
{
  if (v4 == 1 && flag1 == 0)
  {
    frequencia = 38;
    irsend.sendRaw(LDAC, sizeof(LDAC) / sizeof(LDAC[0]), frequencia);
    delay(10);
    irsend.sendRaw(LDAC, sizeof(LDAC) / sizeof(LDAC[0]), frequencia);
    delay(10);
    irsend.sendRaw(LDAC, sizeof(LDAC) / sizeof(LDAC[0]), frequencia);
    delay(10);
    irsend.sendRaw(LDAC, sizeof(LDAC) / sizeof(LDAC[0]), frequencia);
    delay(10);
    irsend.sendRaw(LDAC, sizeof(LDAC) / sizeof(LDAC[0]), frequencia);
    flag1 = 1;
    flag2 = 0;
  }
  else if (v4 == 0 && flag2 == 0)
  {
    frequencia = 38;
    irsend.sendRaw(DSAC, sizeof(DSAC) / sizeof(DSAC[0]), frequencia);
    delay(10);
    irsend.sendRaw(DSAC, sizeof(DSAC) / sizeof(DSAC[0]), frequencia);
    delay(10);
    irsend.sendRaw(DSAC, sizeof(DSAC) / sizeof(DSAC[0]), frequencia);
    delay(10);
    irsend.sendRaw(DSAC, sizeof(DSAC) / sizeof(DSAC[0]), frequencia);;
    delay(10);
    irsend.sendRaw(DSAC, sizeof(DSAC) / sizeof(DSAC[0]), frequencia);
    flag2 = 1;
    flag1 = 0;
  }
}

void f_ldr()
{
  Serial.println(hora[0]);
  float ld = 0;
    ld = analogRead(LDR);
    
  if (ld < 3650)
  {
    luz.on();
    if (gps == 1 && flag_luz == 0)
    {
      if (hora[0] >= 18 || hora[0] <= 8) {
        flag.on();
        flag_luz = 1;
        Blynk.notify("AVISO: LUZ DO QUARTO LIGADA");
      }
    }
  }
  else
  {
    flag_luz = 0;
    luz.off();
    flag.off();
  }
  if (gps == 1)
  {
    Blynk.setProperty(V12, "color", "#D3435C");
    Serial.println("GPS VERMELHO");
  }
  else
  {
    Blynk.setProperty(V12, "color", "#32FCD7");
    Serial.println("GPS VERDE");
  }
  Serial.println(ld);
  float up=0;
  up=(100-(ld*0.02442));
  Serial.println(up);
  Blynk.virtualWrite(V11,up);
}

void f_sensor()
{
  float UltimaH;
  float UltimaM;
  int sinal = digitalRead(sensor);
  Serial.println("SINAL: ");
  Serial.print(sinal);
  if (sinal == HIGH)
  {
    led_sensor.on();
    if (v15 == true)
    {
      Blynk.notify("AVISO DE PRESENÇA");
    }
    if (flag_alerta == 0)
    {
      flag_alerta = 1;
      contador_atividade++;
    }
    UltimaH = float(hora[0]);
    UltimaM = float(hora[1]);
    UltimaH=UltimaH+(UltimaM*0.01);
    Blynk.virtualWrite(V16,UltimaH);
  }
  else
  {
    led_sensor.off();
    flag_alerta = 0;
  }

  if (hora[1]/15 != GraficoMin/15)
  {
    GraficoMin = hora[1];
    GraficoCont = contador_atividade - GraficoCont;
    Blynk.virtualWrite(V18, GraficoCont);
    GraficoCont = contador_atividade;
  }
  
}



void f_reset()
{
  myTime=millis();
  if(myTime>20000)
  {
    if(!Blynk.connected())
    {
      Serial.println(i);
      Serial.println("CONNECT_RESTART");
      ESP.restart();
    }
  }
  
  if(myTime>(14400000))
  {
     ESP.restart();
  }
  Serial.println("TEMPO: ");
  Serial.print(myTime);
}



void loop()
{
  
  hora[0] = int(hour());
  hora[1] = int(minute());
  f_reset();
  if(Blynk.connected() && myTime>10000)
  {
    if(hora[1]%30==0 || myTime<40000)
    {
      Blynk.syncVirtual(V4);
      Blynk.syncVirtual(V6);
      Blynk.syncVirtual(V12); 
      Blynk.syncVirtual(V15); 
    }
    f_sensor();
    f_alarme();
    f_temp();
    f_ar();
    f_ldr();
  }
  Blynk.run();
  ArduinoOTA.handle();
}
