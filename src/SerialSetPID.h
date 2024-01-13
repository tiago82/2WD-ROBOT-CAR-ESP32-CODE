#pragma once
#include <Arduino.h>

class SerialSetPID{
private:
    double kp, ki, kd;
    double setpoint;

    String input; 
    
public:
  
  /**
   * @brief Ajusta os parâmetros do controlador PID com base em uma entrada de string.
   * 
   * Este método processa uma string de entrada que começa com "kp", "ki", "kd" ou "se", seguida por um valor numérico.
   * O valor numérico é convertido para float e usado para ajustar o parâmetro correspondente do controlador PID.
   * Se a string de entrada não começar com "kp", "ki", "kd" ou "se", ela será dividida em espaços e os valores resultantes
   * serão usados para ajustar os parâmetros kp, ki e kd, respectivamente.
   * 
   * @param Input A string de entrada contendo os novos valores dos parâmetros.
   */
  void ajustarPIDBT(String Input) {

    input = Input;

    // Verifica se a entrada começa com "kp"
    if (input.startsWith("kp")) {
      String valueStr = input.substring(2);  // Pega os caracteres depois de "kp"
      kp = valueStr.toFloat();               // Converte para float
      // SerialBT.print("Novo valor de kp: ");
      // SerialBT.println(kp);
    }
    // Verifica se a entrada começa com "ki"
    else if (input.startsWith("ki")) {
      String valueStr = input.substring(2);  // Pega os caracteres depois de "ki"
      ki = valueStr.toFloat();               // Converte para float
      // SerialBT.print("Novo valor de ki: ");
      // SerialBT.println(ki);
    }
    // Verifica se a entrada começa com "kd"
    else if (input.startsWith("kd")) {
      String valueStr = input.substring(2);  // Pega os caracteres depois de "kd"
      kd = valueStr.toFloat();               // Converte para float
      // SerialBT.print("Novo valor de kd: ");
      // SerialBT.println(kd);
    }
    else if (input.startsWith("se")) {
      String valueStr = input.substring(2);  // Pega os caracteres depois de "kd"
      setpoint = valueStr.toFloat();               // Converte para float
      // Serial.print("Novo valor de setpoint: ");
      // Serial.println(setpoint);
    }
    // Processa valores de kp, ki e kd separados por espaços
    else {
      char charArray[input.length() + 1];
      input.toCharArray(charArray, input.length() + 1);

      char *token = strtok(charArray, " ");

      // Obtendo kp
      if (token != NULL) {
        kp = atof(token);

        token = strtok(NULL, " ");
      }

      // Obtendo ki
      if (token != NULL) {
        ki = atof(token);

        token = strtok(NULL, " ");
      }

      // Obtendo kd
      if (token != NULL) {
        kd = atof(token);
      }
      // SerialBT.print("kp: ");
      // SerialBT.print(kp);
      // SerialBT.print(" ki: ");
      // SerialBT.print(ki);
      // SerialBT.print(" kd: ");
      // SerialBT.println(kd);

 
    }
  }

  std::tuple<double, double, double> getconstants(){
   return std::make_tuple(kp, ki, kd);
  }

};

