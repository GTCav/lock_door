/*
    27-04-2024
    INSTITUTO FEDERAL DE EDUCAÇÃO, CIÊNCIA E TECNOLOGIA - ITAJAÍ
    Projeto 1: Lock Door
        Projeto desenvolvido para obtenção de nota na disciplina de Microcontroladores
        Professora: Fernanda Marques Argoud
        Aluno: Gabriel Thiago Cavalcante da Silva
*/
#ifndef lock_door
#define lock_door

// BIBLIOTECAS DE TERCEIROS UTILIZADAS NO PROJETO
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include <Servo.h>
#include <stdint.h>

class LockDoor {
public:
    LockDoor(MCUFRIEND_kbv TFT, TouchScreen TS);  // Construtor
    void begin();// Inicializar monitor
    void clearScreen(uint16_t c);// Limpa a tela
    /*
    - Desenha a tela de apresentação.
    */
    void startScreen();
    /*
    - Verifica se a tela foi tocada.
    - Parâmetro: 
        * int MINPRESSURE: sensibilidade de resposta ao toque.
    - Retorna os valores um objeto TSPoint(x, y, z).
    */
    TSPoint wasTouched(int MINPRESSURE);
    /*
    - Desenha menu de seleção de portas.
    */
    void doorSelectMenu();
    /*
    - Verifica o status de cada botão.
    */
    void detectPressedButton(int x, int y);

private:
    MCUFRIEND_kbv tft;
    TouchScreen ts;
    Servo door_1;
    Servo door_2;

    uint8_t LCD_RESET;
    uint8_t LCD_CS;
    uint8_t LCD_RS;
    uint8_t LCD_WR;
    uint8_t LCD_RD;

    uint8_t YP;
    uint8_t XM;
    uint8_t YM;
    uint8_t XP;

    int TS_LEFT;
    int TS_RT;
    int TS_TOP;
    int TS_BOT;

    /*
    - Desenha o teclado para digitar a senha.
    */
    void drawKeyboard(int key);
    /*
    - Verifica se o acesso está bloqueado.
    */
    bool isLocked();
    /*
    - Detecta os botões do teclado quando pressionados.
    */
    int isKeyPressed(int x, int y);
    /*
    - Faz animação do click nas teclas d teclado.
    */
    void clickAnimation(int key);
    /*
    - Imprime a tecla pressionada no display.
    */
    void showPressedKeyOnDisplay(int key, int cont);
    void clearDisplay();//Limpa o display do teclado.
    /*
    - Solicita a senha de acesso.
    */
    bool requestPassword();
    /*
    - Verifica senha de acesso.
    */
    bool isPasswordCorrect(short password[3]);
    /*
    - Controla a fechadura.
    Parâmetro:
        * Servo lock: servo para controle.
        * int act: define se é abertura ou fechamento.
        * int door: informa à qual porta se refere.
    */
    void lockControl(Servo lock, int act, int door);
};


#endif