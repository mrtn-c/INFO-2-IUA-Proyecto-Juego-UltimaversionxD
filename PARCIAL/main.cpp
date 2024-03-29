#include <iostream>
#include "vibora.h"
#include "comida.h"
#include <SFML/Graphics.hpp>
#include "vida.h"
#include "score.h"
#include "textos.h"
#include "menu.h"
using namespace sf;


int main() {
    srand(time(NULL));
    RenderWindow pantalla(VideoMode(640,480), "ProyectoSnake");
    pantalla.setFramerateLimit(15);
    pantalla.getSize();
    Texture tFondoDePantalla;
    Sprite sFondoDePantalla;
    tFondoDePantalla.loadFromFile("IMAGENES/fondodepantalla.png");
    sFondoDePantalla.setTexture(tFondoDePantalla);

    score Score;                //
    vida vidas;                //
    vidas.constructor();      //
    vibora jugador;          //Constructores.
    jugador.constructor();  //y aca creamos las variables para las clases
    comida Comida;         //
    Comida.constructor(); //
    menu menu;           //
    menu.constructor(); //

    bool salirMenu= true;    //
    int bida=4;             //
    bool Comer = true;     //
    int direccion=0;      //Variables.
    std::string puntuacion="s"; //

   textos texto1;
   texto1.constructor(200,0,24,"SNAKE GAME",Color::Red);
   textos texto2;
   texto2.constructor(140,400,36,"PRESS ENTER TO PLAY", Color::Red);
   textos texto3;
   texto3.constructor(300,0,24,puntuacion, Color::Red);



   while (pantalla.isOpen()) {
        Event e;
        while (pantalla.pollEvent(e)) {
            switch (e.type) {
                case Event::Closed:
                    pantalla.close();
                    break;
                case Event::TextEntered:
                    std::cout << "ENTRADADETEXTO" << std::endl;
                    break;
            }
        }
        pantalla.clear();

        //MENU CICLO

        while (salirMenu==true){
            pantalla.clear();
            menu.inicio(&pantalla);
            texto2.dibujar(&pantalla);
            pantalla.display();
                if(Keyboard::isKeyPressed(Keyboard::Enter)){
                salirMenu=false;
                }
        }




        if (Keyboard::isKeyPressed(Keyboard::D) && direccion!=1){
            direccion = 0;


        }
        if (Keyboard::isKeyPressed(Keyboard::A) && direccion!=0){
            direccion = 1;

        }
        if (Keyboard::isKeyPressed(Keyboard::W) && direccion!=3){
            direccion = 2;

        }
        if (Keyboard::isKeyPressed(Keyboard::S) && direccion!=2){
            direccion = 3;

        }
        if (Keyboard::isKeyPressed(Keyboard::Space)){
           jugador.crecer();
        }
        if (Comer){
            Comida.setearposicion();
            Comer = false;
        }



        puntuacion=Score.devolverscore();
        texto3.constructor(500,0,24,puntuacion, Color::Red);
        Score.tiempo();
        jugador.moverse(direccion);
        pantalla.draw(sFondoDePantalla);
        texto1.dibujar(&pantalla);
        texto3.dibujar(&pantalla);
        Comida.dibujar(&pantalla);

        if (bida>=1){
        vidas.dibujar(&pantalla);
        } else {
            break;
        }

        Sprite aux3=Comida.retornarSprite();





        if (jugador.comio(aux3)){
            jugador.crecer();
            Score.gano();
            Comer = true;
        }


        if(jugador.detectarColisionesFondo() || jugador.choco() ){
            bida--;
            vidas.deletear();
            jugador.constructor();
            direccion = 0;
            Comer = true;

            sleep(milliseconds(1000));

        }

        if(bida>=1){
            jugador.dibujar(&pantalla,direccion);
        }else{
           salirMenu=false;
            Score.highscore();
            Score.cambiarArchivos();
            do{
               pantalla.clear();
               menu.perdio(&pantalla);
               Score.dibujarhigscore(&pantalla);
               pantalla.display();



           }while (!Keyboard::isKeyPressed(Keyboard::Enter));
        pantalla.clear(Color::White);
            return 0;
        }

        pantalla.display();
    }

    return 0;
}