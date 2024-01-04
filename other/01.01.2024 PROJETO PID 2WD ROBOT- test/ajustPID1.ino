float kp, ki, kd;


void setup() {
  Serial.begin(115200);
}

void loop() {
  ajustarPID();
}

void ajustarPID() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  // Ler a entrada serial até encontrar um caractere de nova linha

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
