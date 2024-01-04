double kp = 0.0;
double ki = 0.0;
double kd = 0.0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  ajustarPID();
}


void ajustarPID() {

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');

    // Verifica se a entrada começa com "kp"
    if (input.startsWith("kp")) {
      String valueStr = input.substring(2);  // Pega os caracteres depois de "kp"
      kp = valueStr.toFloat();               // Converte para float
      Serial.print("Novo valor de kp: ");
      Serial.println(kp);
    }
    // Verifica se a entrada começa com "ki"
    else if (input.startsWith("ki")) {
      String valueStr = input.substring(2);  // Pega os caracteres depois de "ki"
      ki = valueStr.toFloat();               // Converte para float
      Serial.print("Novo valor de ki: ");
      Serial.println(ki);
    }
    // Verifica se a entrada começa com "kd"
    else if (input.startsWith("kd")) {
      String valueStr = input.substring(2);  // Pega os caracteres depois de "kd"
      kd = valueStr.toFloat();               // Converte para float
      Serial.print("Novo valor de kd: ");
      Serial.println(kd);
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
      Serial.print("kp: ");
      Serial.print(kp);
      Serial.print(" ki: ");
      Serial.print(ki);
      Serial.print(" kd: ");
      Serial.println(kd);
    }
  }
}
