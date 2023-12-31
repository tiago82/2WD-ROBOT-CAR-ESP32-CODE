possibilidade 

#ifdef __has_include
    #if __has_include("keys.h")
        #include "keys.h"
    #else
        #warning "Arquivo local de keys.h não encontrado, continuando a compilação sem ele. a senha do Wifi será definida abaixo"
        const char *ssid = "SeuWifi"; // Seu SSID de rede (nome)
        const char *password = "suasenha"; // Sua senha de rede
      
    #endif
#endif