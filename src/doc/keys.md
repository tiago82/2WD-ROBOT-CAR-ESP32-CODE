# Arquivo de Configuração (config.h)

O arquivo `config.h` contém informações sensíveis, como as credenciais de rede Wi-Fi (SSID e senha), que são utilizadas no código-fonte do projeto.

## Conteúdo

- `ssid`: Variável que armazena o nome da rede Wi-Fi (SSID).
- `password`: Variável que armazena a senha da rede Wi-Fi.
- Outras configurações sensíveis podem ser adicionadas conforme necessário.

**Atenção**: Este arquivo contém informações críticas. Certifique-se de mantê-lo em local seguro, evitando compartilhá-lo publicamente ou incluí-lo em repositórios Git visíveis ao público, para evitar exposição de dados sensíveis.

## Exemplo de Uso

O arquivo `config.h` é utilizado para armazenar informações de rede, como no exemplo abaixo:

```cpp
#ifndef KEYS_H
#define KEYS_H

const char *ssid = "SSID"; // Seu SSID de rede (nome)
const char *password = "YourPassword"; // Sua senha de rede

// Outras configurações sensíveis...

#endif


