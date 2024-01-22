#pragma once
#include <Arduino.h>

int timeCountEncoder = 50; // faixa em milisegundos de contagem dos pulsos.
volatile int pulseCountEncoder1 = 0;
volatile int pulseCountEncoder2 = 0;
volatile int pulseTotalCountEncoder1 = 0;
volatile int pulseTotalCountEncoder2 = 0;
volatile unsigned long lastUpdateTime = 0;
typedef void (*FuncPtr)(); // Define um tipo de ponteiro para função

void startEncoder(int pinEncoder1, int pinEncoder2);
void updateEncoder();             // Atualiza a contagem de pulsos
void updateEncoder(FuncPtr func); // Atualiza a contagem de pulsos e executa uma função passada como parâmetro, Importante para chamar funcao que calcula PID.
void updateEncoderPrint();        // Atualiza a contagem de pulsos e imprime o valor por serial.
int getpulse1();                  // Retorna o número atual de pulsos por segundo .
int getpulse2();                  // Retorna o número atual de pulsos por segundo .

void ICACHE_RAM_ATTR funcaoInterrupcao1()
{
  pulseCountEncoder1++;
  pulseTotalCountEncoder1++;
}
void ICACHE_RAM_ATTR funcaoInterrupcao2()
{
  pulseCountEncoder2++;
  pulseTotalCountEncoder2++;
}

void startEncoder(int pinEncoder1)
{
  pinMode(pinEncoder1, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(pinEncoder1), funcaoInterrupcao1, CHANGE);
}

void startEncoder(int pinEncoder1, int pinEncoder2)
{
  pinMode(pinEncoder1, INPUT_PULLDOWN);
  pinMode(pinEncoder2, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(pinEncoder1), funcaoInterrupcao1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinEncoder2), funcaoInterrupcao2, CHANGE);
}

void updateEncoder()
{
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= timeCountEncoder)
  {
    // Serial.print("Pulsos por segundo: ");
    // Serial.println(pulseCountEncoder);
    pulseCountEncoder1 = 0;
    pulseCountEncoder2 = 0;
    lastUpdateTime = currentTime;
  }
}

void updateEncoder(FuncPtr func)
{
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= timeCountEncoder)
  {
    func(); // Chama a função passada como argumento
    pulseCountEncoder1 = 0;
    pulseCountEncoder2 = 0;
    lastUpdateTime = currentTime;
  }
}

void updateEncoderPrint()
{
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= timeCountEncoder)
  {
    Serial.print("Pulsos por segundo1: ");
    Serial.print(pulseCountEncoder1);
    Serial.print(" Pulsos por segundo2: ");
    Serial.println(pulseCountEncoder2);
    pulseCountEncoder1 = 0;
    pulseCountEncoder2 = 0;
    lastUpdateTime = currentTime;
  }
}

/**
 * @brief Retorna o valor do pulso 1.
 *
 * @return O valor do pulso 1.
 */
int getpulse1()
{
  return pulseCountEncoder1;
}
/**
 * @brief Retorna o valor do pulso 2.
 *
 * @return O valor do pulso 2.
 */
int getpulse2()
{
  return pulseCountEncoder2;
}

int gettotalpulse1()
{
  return pulseTotalCountEncoder1;
}
int gettotalpulse2()
{
  return pulseTotalCountEncoder2;
}
int getdiferencetotalpulse()
{
  int diferenca1 = pulseTotalCountEncoder1 - pulseTotalCountEncoder2;
  return diferenca1;
}
void resettotalpulse()
{
  pulseTotalCountEncoder1 = 0;
  pulseTotalCountEncoder2 = 0;
}

// ======================= odometria =======================
void odometry()
{

  float xf, yf;
  float xr, yr;

  float Dx, Dy;
  Dx = xf - xr;
  Dy = yf - yr;

  int xr_ant;
  int yr_ant;
  int V;
  float theta;
  float theta_total;
  float deltatheta;

  int Dt;

  xr = xr_ant + V * Dt * cos(theta);
  yr = yr_ant + V * Dt * sin(theta);

  xr_ant = xr;
  yr_ant = yr;
  theta_total = theta + deltatheta;
}

float ssa = 0;
float deltaS(int pulse1, int pulse2); // prototipo da funcao deltaS

/**
 * Calcula a distância percorrida com base nos valores de pulso de dois encoders.
 *
 * @param pulse1 O valor de pulso do primeiro encoder.
 * @param pulse2 O valor de pulso do segundo encoder.
 * @return A distância percorrida.
 */
float s(int pulse1, int pulse2)
{

  float a = deltaS(pulse1, pulse2);

  return ssa += a;
}

const float pi = 3.14159265359;
const int rev = 1265;     // numero de pulsos por revolucao do encoder(Obtido experimentalmente)
const int L = 0.15;       // distancia entre as rodas
const float circ = 0.207; // circunferencia aproximada em metro da roda (Obtido experimentalmente)

float deltaS(int pulse1, int pulse2)
{

  float raio = circ / (2 * pi); // raio da roda

  float deltathetaa = (2 * pi * pulse1) / rev;        // variacao no angulo de rotacao da roda a
  float deltathetab = (2 * pi * pulse2) / rev;        // variacao no angulo de rotacao da roda b
  float deltatheta = (deltathetaa - deltathetab) / L; // variacao no angulo de rotacao do robo

  float deltaSa = raio * deltathetaa; // variacao na distancia percorrida pela roda a
  float deltaSb = raio * deltathetab; // variacao na distancia percorrida pela roda b

  float deltaS = (deltaSa + deltaSb) / 2; // variacao na distancia percorrida pelo robo

  return deltaS;
}

void rotate()
{

  float diamrot = L * pi * 2; // diametro da roda de rotacao
}

/**
 * Calcula o número de pulsos necessários para mover o robô por uma determinada distância.
 * 
 * @param distancia A distância em metros que o robô deve percorrer.
 * @return O número de pulsos necessários para mover o robô pela distância especificada.
 */
int moverrobotdistancia(float distancia) // em metros
{
  int npulsos = (distancia * rev) / (circ); 
  return npulsos;
}

/**
 * Calcula o número de pulsos necessários para uma determinada quantidade de revoluções.
 * 
 * @param quantidadederev A quantidade de revoluções desejada. // Documentação para o parâmetro "quantidadederev"
 * @return O número de pulsos necessários.
 */
int revolucoesdasrodas(int quantidadederev) // em metros
{
  int npulsos = rev*quantidadederev;

  return npulsos;
}

/**
 * Calcula o número de rotações necessárias para percorrer uma determinada distância com base na largura do robô.
 * 
 * @param larguraRobo A largura do robô em unidades de medida.
 * @return O número de rotações necessárias para percorrer a distância especificada.
 */
// float calcularRotações(float larguraRobo) {
//     // A circunferência de uma rotação é 2 * pi
//     float circunferenciaRotacao = 2 * pi;

//     // Calcular o número de rotações com base na largura do robô
//     float numRotações = circunferenciaRotacao / larguraRobo;

//     return numRotações;
// }

int girarroborGraus(int graus) {
  float larguraRobo = L;  // Largura do robô em metros
  float raioRodas = circ / (2 * pi);;    // Raio das rodas em metros
  int pulsosPorRevolucao = rev;

  // Calcule a quantidade de pulsos necessários para girar a quantidade desejada de graus
  float distanciaEntreRodas = larguraRobo;  // Distância entre as rodas
  float circunferenciaTrajetoria = PI * distanciaEntreRodas * graus / 360.0;  // Circunferência da trajetória
  int pulsosParaGirar = static_cast<int>((circunferenciaTrajetoria / (2 * PI * raioRodas)) * pulsosPorRevolucao);

  return pulsosParaGirar;
}
