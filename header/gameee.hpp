#ifndef GAMEEE_HPP_INCLUDED
#define GAMEEE_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Collision.h"

using namespace sf;
using namespace std;

bool gameplay = true;

int ground(int x, int y)
{
    if((x >= 1000 && x <= 1250) && y <= 600 && y > 456){
        return 610;
    }
    else if((x >= 510 && x <= 880) && y <= 475){
        return 475;
    }
      else if((x >= 880 && x <= 1000) && y <= 350){
        return 350; //g5
    }
      else if((x >= 25 && x <=371) && y <= 224){
        return 224; //g1
    }
      else if((x >= 1004 && x <= 1124) && y <= 224){
        return 224;//g3
    }
      else if((x >= 1252 && x <= 1475) && y <= 224){
        return 224; //g4
    }
      else if((x >= 25 && x <= 479) && y <= 728){
        return 728; //g8
    }
      else if((x >= 761 && x <=1017) && y <= 728){
        return 728;//g9
    }
    else{
        y--;
        return 875;
    }
}

void game(){
    RenderWindow window(VideoMode(1500,900), "Quest Ball");
    window.setFramerateLimit(30);

    Event event;

    Texture level, ball, coin, key, level1up;
    Sprite slevel, sball, scoin, skey, coinAra[13], slevel1up;

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

    level1up.loadFromFile("resources/level1up.jpg");
    level1up.setSmooth(true);
    slevel1up.setTexture(level1up);
    slevel1up.scale(0.9,0.9);


    for(int i=0; i<13; i++){
        coinAra[i].setTexture(coin), coinAra[i].scale(0.07, 0.07);
    }

    while(window.isOpen()){
        if(gameplay){
            while(window.pollEvent(event)){
                if(event.type == Event::Closed){
                    window.close();
                }

                if (Keyboard::isKeyPressed(Keyboard::Right)){
                    sball.move(8.f,0.f);
                    sball.rotate(val);

                }
                 if (Keyboard::isKeyPressed(Keyboard::Left)){
                     sball.rotate(-val);
                     sball.move(-8.f,0.f);
                 }
                if (Keyboard::isKeyPressed(Keyboard::Up)){
                    jumping = true;
                    //sball.move(0.f,-8.f);
                }

                if (Keyboard::isKeyPressed(Keyboard::Down)){
                    sball.move(0.f,8.f);
                }
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


            if(!(x >= 1000 && x <= 1250) && !(x >= 510 && x <= 880)){
                Yvelocity++;
            }
            int a = sball.getPosition().x;
            int b = sball.getPosition().y;

            int gr = ground(a, b);

            ///jump
            if(jumping){
                sball.move(0,Yvelocity);
                Yvelocity++;
                y += Yvelocity;
                if(Yvelocity > 20) Yvelocity = -20;
            }



            //cout << "a=" << a << " b=" << b << " ground=" << gr << endl;

            if(sball.getPosition().y >= gr && jumping) {
                jumping = false;
                sball.setPosition(sball.getPosition().x, gr);
            }
            ///

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
            if(keycollected && a >= 180 && a <= 190 && b >= 720 && b <= 733){
               gameplay=false;
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

    else {
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }
        window.clear();

        window.draw(slevel1up);

        window.display();
    }
}
}

#endif // GAMEEE_HPP_INCLUDED
