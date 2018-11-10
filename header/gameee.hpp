#ifndef GAMEEE_HPP_INCLUDED
#define GAMEEE_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Collision.h"

using namespace sf;
using namespace std;

int ground(int x, int y)
{
    if((x >= 1000 && x <= 1250) && y <= 600 && y > 456){
        return 610;
    }
    else if((x >= 510 && x <= 880) && y <= 475){
        return 475;
    }
    else{
        y--;
        return 900;
    }
}

void game(){
    RenderWindow window(VideoMode(1500,900), "Quest Ball");
    window.setFramerateLimit(30);

    Event event;

    Texture level, ball, coin, key;
    Sprite slevel, sball, scoin, skey, coinAra[13];

    int x = 1100, y = 600, i;

    float Yvelocity = -20, val = 10;

    bool jumping = false, keycollected = false;

    level.loadFromFile("resources/level.jpg");
    level.setSmooth(true);
    slevel.setTexture(level);
    slevel.scale(1.5,1.5);

    ball.loadFromFile("resources/ball.png");
    ball.setSmooth(true);
    sball.setTexture(ball);
    sball.scale(0.17,0.17);
    sball.setPosition(x,y);
    FloatRect ballBound = sball.getLocalBounds();
    sball.setOrigin(ballBound.width/2,ballBound.height/2);

    coin.loadFromFile("resources/coin.png");
    coin.setSmooth(true);
    scoin.setTexture(coin);

    key.loadFromFile("resources/Cortex-key.png");
    key.setSmooth(true);
    skey.setTexture(key);
    skey.setScale(0.1, 0.1);
    skey.setPosition(750,682);


    for(int i=0; i<13; i++){
        coinAra[i].setTexture(coin), coinAra[i].scale(0.07, 0.07);
    }

    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)){
                sball.move(10.f,0.f);
                sball.rotate(val);

            }
             if (Keyboard::isKeyPressed(Keyboard::Left)){
                 sball.rotate(-val);
                 sball.move(-10.f,0.f);
             }
            if (Keyboard::isKeyPressed(Keyboard::Up)){
                jumping = true;
            }
            /*
            if (Keyboard::isKeyPressed(Keyboard::Down)){
                sball.move(0.f,10.f);
            }*/
        }

        ///border line start
        if(sball.getPosition().x >= 1475){
            x = 1475;
            sball.setPosition(x,sball.getPosition().y);
        }
        if(sball.getPosition().x <= 25){
            x = 25;
            sball.setPosition(x,sball.getPosition().y);
        }
        if(sball.getPosition().y <= 25){
            y = 25;
            sball.setPosition(sball.getPosition().x,y);
        }
        if(sball.getPosition().y >= 875){
            y = 875;
            sball.setPosition(sball.getPosition().x,y);
        }
        ///border line end

        ///initial ground
        //if(x >= 980 && x <= 1215 && y == 600) ground = 600;
        //else if(x >= 570 && x <= 795 && y == 456) ground = 456;

        //ground = 438;
        if(!(x >= 1000 && x <= 1250) && !(x >= 510 && x <= 880)){
            Yvelocity++;
        }
        int a = sball.getPosition().x;
        int b = sball.getPosition().y;

        int gr = ground(a, b);

        if(jumping){
            sball.move(0,Yvelocity);
            Yvelocity++;
            y += Yvelocity;
            if(Yvelocity > 20) Yvelocity = -20;
        }



        cout << "a=" << a << " b=" << b << " ground=" << gr << endl;

        if(sball.getPosition().y >= gr && jumping) {
            jumping = false;
            sball.setPosition(sball.getPosition().x, gr);
        }

        ///coin
        coinAra[1].setPosition(950,688); // spiral
        coinAra[2].setPosition(420,688); // white door 1
        coinAra[3].setPosition(595,728);  // grass
        coinAra[4].setPosition(330,688);  //white door3
        coinAra[5].setPosition(908,314);  //1
        coinAra[6].setPosition(1033,190); //2
        coinAra[7].setPosition(659,190); //3
        coinAra[8].setPosition(670,438); // green drum 1
        coinAra[12].setPosition(265,190); // upper left 1
        coinAra[9].setPosition(1250,190); // up right
        coinAra[10].setPosition(150,190); //  up 3
        coinAra[11].setPosition(775,438); // green drum
        coinAra[0].setPosition(25,190);  // up 5

        ///coin collect
        for(i = 0; i<13; i++){
            if(Collision::PixelPerfectTest(coinAra[i], sball)){
            coinAra[i].setColor(Color::Transparent);
        }
        }

         a = sball.getPosition().x;
         b = sball.getPosition().y;

        ///key collect
        if(Collision::PixelPerfectTest(skey, sball)){
            skey.setColor(Color::Transparent);
            keycollected = true;
        }

        ///to the next level
        if(keycollected && a >= 180 && a <= 190 && b == 720){
            window.close();
        }

        window.clear();
        window.draw(slevel);
        window.draw(sball);
        for(int i=0; i<13; i++){
            window.draw(coinAra[i]);
        }
        window.draw(skey);
        window.display();
    }
}

#endif // GAMEEE_HPP_INCLUDED
