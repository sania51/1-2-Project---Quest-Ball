#ifndef GAMEEE_HPP_INCLUDED
#define GAMEEE_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Collision.h"

using namespace sf;
using namespace std;

int i, x = 1100, y = 600, score = 0, chance = 0, gamestate = 0, gamelevel = 1;

unsigned int menustate = 0;

float Yvelocity = 0, val = 10;

bool jumping = false, keycollected = false, levelup = false, gameplay = true, levelOneStarted = true, levelTwoStarted = false;

RenderWindow window(VideoMode(1500,900), "Quest Ball");

int ground(int x, int y)
{
    if((x >= 25 && x <=371) && y <= 224+35){
        return 224; //g1
    }
      else if((x >= 1004 && x <= 1124) && y <= 224+35){
        return 224;//g3
    }
      else if((x >= 1252 && x <= 1475) && y <= 224+35){
        return 224; //g4
    }
    else if((x >= 620 && x <= 750) && y <= 240+35){
        return 240;
    }///upper left
      else if((x >= 880 && x <= 1000) && y <= 350+35){
        return 350; //g5
    }
    else if((x >= 510 && x <= 880) && y <= 475+35){
        return 475;
    }
     else if((x >= 1000 && x <= 1250) && y <= 600+35 && y > 456+35){
        return 610;
    }
    else if((x >= 25 && x <= 479) && y <= 728+35){
        return 728; //g8
    }
    else if((x >= 761 && x <=1017) && y <= 728+35){
        return 728;//g9
    }
    else{
        return 875;
    }
}

int ground2(int x, int y)
{
    if((x >= 20 && x <= 388) && y <= 152+35){
        return 152; //upper left
    }
    else if((x >= 852 && x <= 1028) && y <= 192+35){
        return 192; // middle mushroom
    }
    else if((x >= 220 && x <= 500) && y <= 448+35){
        return 448; // left middle
    }
    else if((x >= 716 && x <= 1116) && y <= 496+35){
        return 496; // middle upper
    }
    else if((x >= 588 && x <= 756) && y <= 288+35){
        return 288; // middle tree
    }
    else if((x >= 25 && x <= 188) && y <= 656+35){
        return 656; // arrow
    }
    else if((x >= 580 && x <= 1140) && y <= 656+35){
        return 656; // middle down
    }
    else if((x >= 28 && x <=372) && y <= 720+35){
        return 720; // arrow down
    }
    else if((x >= 1172 && x <= 1332) && y <= 728+35){
        return 728; // middle box
    }
    else{
        return 875;
    }

}

void game(){

    window.setFramerateLimit(30);

    Event event;

    Texture level, ball, coin, key, level1up, saw, spike, Over, life, menu, level2;
    Sprite slevel, sball, scoin, skey, coinAra[12], slevel1up, ssaw, sawAra[4],sspike, spikeAra[5], sover, slife, lifeAra[3], smenu, slevel2;

    Font fCoin;
    fCoin.loadFromFile("resources/COOPBL.TTF");
    ostringstream sscoin;
    sscoin << "COINS: " << score;

    Text tCoin;
    tCoin.setCharacterSize(50);
    tCoin.setPosition(1230, -8);
    tCoin.setFont(fCoin);
    tCoin.setString(sscoin.str());
    tCoin.setFillColor(Color::Yellow);

    Font totalCoin;
    totalCoin.loadFromFile("resources/ARLRDBD.TTF");
    ostringstream sstotalCoin;
    sstotalCoin << "Total Coin: " << score;

    Text ttotalCoin;
    ttotalCoin.setCharacterSize(100);
    ttotalCoin.setPosition(460,430);
    ttotalCoin.setFont(totalCoin);
    ttotalCoin.setString(sstotalCoin.str());
    ttotalCoin.setFillColor(Color::Yellow);

    Font fCongo;
    fCongo.loadFromFile("resources/berkshireswash-regular.ttf");

    Text tCongo("Congratulations!!", fCongo, 90);
    tCongo.setPosition(450, 270);
    tCongo.setFillColor(Color::Yellow);

    Font fname;
    fname.loadFromFile("resources/GROBOLD.ttf");
    Text tname("Quest Ball", fname, 150);
    tname.setPosition(400, 0);
    tname.setFillColor(Color::Yellow);

    Font fstart;
    fstart.loadFromFile("resources/berkshireswash-regular.ttf");

    Text tstart("START",fstart,45);
    tstart.setPosition(450, 270);
    tstart.setFillColor(Color::Yellow);

    Font fhelp;
    fhelp.loadFromFile("resources/berkshireswash-regular.ttf");

    Text thelp("HELP",fhelp,45);
    thelp.setPosition(450, 330);
    thelp.setFillColor(Color::Yellow);

    level.loadFromFile("resources/level1.jpg");
    level.setSmooth(true);
    slevel.setTexture(level);
    slevel.scale(1.5,1.5);

    level2.loadFromFile("resources/level2.jpg");
    level2.setSmooth(true);
    slevel2.setTexture(level2);
    slevel2.setScale(1.5,1.2);

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

    life.loadFromFile("resources/Life.png");
    life.setSmooth(true);
    slife.setTexture(life);

    saw.loadFromFile("resources/Saw.png");
    saw.setSmooth(true);
    ssaw.setTexture(saw);

    spike.loadFromFile("resources/Spike.png");
    spike.setSmooth(true);
    sspike.setTexture(spike);

    level1up.loadFromFile("resources/LevelOneUp.png");
    level1up.setSmooth(true);
    slevel1up.setTexture(level1up);
    slevel1up.scale(2.22,2.3);

    menu.loadFromFile("resources/menu.png");
    menu.setSmooth(true);
    smenu.setTexture(menu);
    smenu.setScale(2.442,2.499);

    Clock mclock;

    for(int i=0; i<12; i++){
        coinAra[i].setTexture(coin), coinAra[i].scale(0.07, 0.07);
    }
    for(i = 1; i<=3; i++){
        lifeAra[i].setTexture(life), lifeAra[i].scale(0.101,0.101);
    }
    for(i = 0; i<4; i++){
       sawAra[i].setTexture(saw), sawAra[i].scale(0.31,0.31), sawAra[i].setOrigin(sawAra[i].getLocalBounds().width/2, sawAra[i].getLocalBounds().height/2);
    }
    for(i = 0; i<5; i++){
        spikeAra[i].setTexture(spike), spikeAra[i].setScale(0.51,0.51);
    }

    while(window.isOpen()){

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            window.close();
        }

        if(gameplay){
            while(window.pollEvent(event)){
                if(event.type == Event::Closed){
                    window.close();
                }
            }

        if(gamestate == 0){
            ///menu
            switch(menustate){
            case 0:
                tstart.setFillColor(Color::Red);
                thelp.setFillColor(Color::Yellow);
                break;
            case 1:
                thelp.setFillColor(Color::Red);
                tstart.setFillColor(Color::Yellow);
                break;
            }
            if(Keyboard::isKeyPressed(Keyboard::Up) && mclock.getElapsedTime().asMilliseconds()>150){
                if(menustate > 0){
                    menustate--;
                }
                else {
                    menustate = 1;
                }
                mclock.restart();
            }
            if(Keyboard::isKeyPressed(Keyboard::Down) && mclock.getElapsedTime().asMilliseconds()>150){
                if(menustate < 1){
                    menustate++;
                }
                else {
                    menustate = 0;
                }
                mclock.restart();
            }
            if(Keyboard::isKeyPressed(Keyboard::Enter)){
                switch(menustate){
                case 0:
                    gamestate = 1;
                    break;
                case 1:
                    gamestate = 3;
                    break;
                }
            }
            window.clear();
            window.draw(smenu);
            window.draw(tname);
            window.draw(tstart);
            window.draw(thelp);
            window.display();
        }

        else if(gamestate == 1){

           /*                 ///control
            if (Keyboard::isKeyPressed(Keyboard::Right)){
                sball.move(8.f,0.f);
                sball.rotate(val);
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)){
                sball.rotate(-val);
                sball.move(-8.f,0.f);
            }*/

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

            /*///jumping
            if(sball.getPosition().y>=gr && sball.getPosition().y<=gr+35){
                Yvelocity=0;
            }
            else if(sball.getPosition().y<gr){
                Yvelocity++;
            }
            if(jumping){
                Yvelocity=-20;
                jumping=false;
            }

            sball.move(0, Yvelocity);*/
            //cout << "a=" << a << " b=" << b << " ground=" << gr << endl;

            /*///coin collect
            for(i = 0; i<12; i++){
                if(Collision::PixelPerfectTest(coinAra[i], sball)){
                    score++;
                    coinAra[i].setPosition(-200,-200);
                    sscoin.str("");
                    sscoin << "COINS: " << score;
                    tCoin.setString(sscoin.str());
                }
            }*/

            /*///key collect
            if(Collision::PixelPerfectTest(skey, sball)){
                skey.setPosition(-100,-100);
                keycollected = true;
            }*/

            /*///saw dead
            for(i = 0; i<4; i++){
                if(Collision::PixelPerfectTest(sawAra[i], sball)){
                    chance++;
                    if(chance < 3){
                        sball.setPosition(1100,600);
                        lifeAra[chance].setPosition(-300,-300);
                    }
                    else if(chance == 3){
                        gameplay = false;
                    }
                }
            }*/

            /*///spike dead
            for(i = 0; i<5; i++){
                if(Collision::PixelPerfectTest(spikeAra[i], sball)){
                    chance++;
                    if(chance < 3){
                        sball.setPosition(1100,600);
                        lifeAra[chance].setPosition(-300,-300);
                    }
                    else if(chance == 3){
                        gameplay = false;
                    }
                }
            }*/

            if(gamelevel == 1){

            int a = sball.getPosition().x;
            int b = sball.getPosition().y;
            int gr = ground(a, b);

            cout << "a=" << a << " b=" << b << " ground=" << gr << endl;

            if(levelOneStarted) {
                coinAra[1].setPosition(950,688); // spiral
                coinAra[2].setPosition(420,688); // white door 1
                coinAra[3].setPosition(265,190);  // grass
                coinAra[4].setPosition(330,688);  //white door3
                coinAra[5].setPosition(908,314);  //1
                coinAra[6].setPosition(1033,190); //2
                coinAra[7].setPosition(659,190); //3
                coinAra[8].setPosition(670,438); // green drum 1
                coinAra[9].setPosition(1250,190); // up right
                coinAra[10].setPosition(150,190); //  up 3
                coinAra[11].setPosition(775,438); // green drum
                coinAra[0].setPosition(25,190);  // up 5

                ///life
                lifeAra[1].setPosition(125,-8);
                lifeAra[2].setPosition(60,-8);
                lifeAra[3].setPosition(-5,-8);

                ///saw
                sawAra[0].setPosition(745, 365);
                sawAra[1].setPosition(263, 520);
                sawAra[2].setPosition(400, 400);
                sawAra[3].setPosition(90,370);

                ///spike
                spikeAra[0].setPosition(621, 658);
                spikeAra[1].setPosition(499, 658);
                spikeAra[2].setPosition(811,618);
                spikeAra[3].setPosition(1248,744);
                spikeAra[4].setPosition(1290,745);
                levelOneStarted = false;
            }

            ///control
            if (Keyboard::isKeyPressed(Keyboard::Right)){
                sball.move(8.f,0.f);
                sball.rotate(val);
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)){
                sball.rotate(-val);
                sball.move(-8.f,0.f);
            }

            if (Keyboard::isKeyPressed(Keyboard::Up) && sball.getPosition().y>=gr && sball.getPosition().y<=gr+35){
                jumping = true;
            }

            ///jumping
            if(sball.getPosition().y>=gr && sball.getPosition().y<=gr+35){
                Yvelocity=0;
            }
            else if(sball.getPosition().y<gr){
                Yvelocity++;
            }
            if(jumping){
                Yvelocity=-20;
                jumping=false;
            }
            sball.move(0, Yvelocity);

            ///coin collect
            for(i = 0; i<12; i++){
                if(Collision::PixelPerfectTest(coinAra[i], sball)){
                    score++;
                    coinAra[i].setPosition(-200,-200);
                    sscoin.str("");
                    sscoin << "COINS: " << score;
                    tCoin.setString(sscoin.str());
                }
            }

            ///key collect
            if(Collision::PixelPerfectTest(skey, sball)){
                skey.setPosition(-100,-100);
                keycollected = true;
            }

            ///saw dead
            for(i = 0; i<4; i++){
                if(Collision::PixelPerfectTest(sawAra[i], sball)){
                    chance++;
                    if(chance < 3){
                        sball.setPosition(1100,600);
                        lifeAra[chance].setPosition(-300,-300);
                    }
                    else if(chance == 3){
                        gameplay = false;
                    }
                }
            }

            ///spike dead
            for(i = 0; i<5; i++){
                if(Collision::PixelPerfectTest(spikeAra[i], sball)){
                    chance++;
                    if(chance < 3){
                        sball.setPosition(1100,600);
                        lifeAra[chance].setPosition(-300,-300);
                    }
                    else if(chance == 3){
                        gameplay = false;
                    }
                }
            }

            window.clear();

            window.draw(slevel);
            window.draw(sball);
            window.draw(skey);
            window.draw(tCoin);

            for(int i=0; i<12; i++){
                window.draw(coinAra[i]);
            }
            for(i = 1; i<=3; i++){
                window.draw(lifeAra[i]);
            }
            for(i = 0; i<4; i++){
              sawAra[i].rotate(-15);
              window.draw(sawAra[i]);
            }
            for(i = 0; i<5; i++){
                window.draw(spikeAra[i]);
            }

            window.display();

            ///to the next level
            if((keycollected == true) && ((a >= 50 && a <= 190) && (b >= 525 && b <= 875))){
               gamelevel++;
               levelup = true;
               levelTwoStarted = true;
            }
        }

            ///Level 2
            else if(gamelevel == 2){

                int a = sball.getPosition().x;
                int b = sball.getPosition().y;
                int gr = ground2(a, b);

                if(levelup){
                    Font fLevelOneUp;
                    fLevelOneUp.loadFromFile("resources/impact.ttf");

                    Text tLevelOneUp("You'VE Passed Level ONE!!", fLevelOneUp, 110);
                    tLevelOneUp.setPosition(190,400);
                    tLevelOneUp.setFillColor(Color::Cyan);

                    window.clear();

                    window.draw(slevel1up);
                    window.draw(tCongo);
                    window.draw(tLevelOneUp);

                    window.display();
                    if(Keyboard::isKeyPressed(Keyboard::Enter)){
                        levelup = false;
                    }
                }
                else if(levelup == false){
                    if(levelTwoStarted == true){
                        sball.setPosition(25, 656);

                        coinAra[1].setPosition(800,688);
                        coinAra[2].setPosition(700,688);
                        coinAra[3].setPosition(300,190);
                        coinAra[4].setPosition(600,688);
                        coinAra[5].setPosition(500,314);
                        coinAra[6].setPosition(400,190);
                        coinAra[7].setPosition(200,190);
                        coinAra[8].setPosition(100,438);
                        coinAra[9].setPosition(1000,190);
                        coinAra[10].setPosition(1100,190);
                        coinAra[11].setPosition(900,438);
                        coinAra[0].setPosition(50,100);

                        ///life
                        lifeAra[1].setPosition(125,-8);
                        lifeAra[2].setPosition(60,-8);
                        lifeAra[3].setPosition(-5,-8);

                        ///saw
                        sawAra[0].setPosition(600, 365);
                        sawAra[1].setPosition(500, 520);
                        sawAra[2].setPosition(300, 400);
                        sawAra[3].setPosition(150,370);

                        ///spike
                        spikeAra[0].setPosition(500, 658);
                        spikeAra[1].setPosition(600, 658);
                        spikeAra[2].setPosition(900,618);
                        spikeAra[4].setPosition(1000,745);
                        spikeAra[3].setPosition(800,744);
                        levelTwoStarted = false;
                    }

                    ///control
                    if (Keyboard::isKeyPressed(Keyboard::Right)){
                        sball.move(8.f,0.f);
                        sball.rotate(val);
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Left)){
                        sball.rotate(-val);
                        sball.move(-8.f,0.f);
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Up) && sball.getPosition().y>=gr && sball.getPosition().y<=gr+35){
                        jumping = true;
                    }

                    ///jumping
                    if(sball.getPosition().y>=gr && sball.getPosition().y<=gr+35){
                        Yvelocity=0;
                    }
                    else if(sball.getPosition().y<gr){
                        Yvelocity++;
                    }
                    if(jumping){
                        Yvelocity=-20;
                        jumping=false;
                    }
                    sball.move(0, Yvelocity);

                    cout << "a=" << a << " b=" << b << " ground=" << gr << endl;

                    ///coin collect
                    for(i = 0; i<12; i++){
                        if(Collision::PixelPerfectTest(coinAra[i], sball)){
                            score++;
                            coinAra[i].setPosition(-200,-200);
                            sscoin.str("");
                            sscoin << "COINS: " << score;
                            tCoin.setString(sscoin.str());
                        }
                    }

                    ///key collect
                    if(Collision::PixelPerfectTest(skey, sball)){
                        skey.setPosition(-100,-100);
                        keycollected = true;
                    }

                   /* ///saw dead
                    for(i = 0; i<4; i++){
                        if(Collision::PixelPerfectTest(sawAra[i], sball)){
                            chance++;
                            if(chance < 3){
                                sball.setPosition(1100,600);
                                lifeAra[chance].setPosition(-300,-300);
                            }
                            else if(chance == 3){
                                gameplay = false;
                            }
                        }
                    }

                    ///spike dead
                    for(i = 0; i<5; i++){
                        if(Collision::PixelPerfectTest(spikeAra[i], sball)){
                            chance++;
                            if(chance < 3){
                                sball.setPosition(1100,600);
                                lifeAra[chance].setPosition(-300,-300);
                            }
                            else if(chance == 3){
                                gameplay = false;
                            }
                        }
                    }*/

                    window.clear();

                    window.draw(slevel2);
                    window.draw(sball);
                    window.draw(skey);
                    window.draw(tCoin);

                    for(int i=0; i<12; i++){
                        window.draw(coinAra[i]);
                    }
                    for(i = 1; i<=3; i++){
                        window.draw(lifeAra[i]);
                    }
                    for(i = 0; i<4; i++){
                        sawAra[i].rotate(-15);
                        window.draw(sawAra[i]);
                    }
                    for(i = 0; i<5; i++){
                        window.draw(spikeAra[i]);
                    }
                    window.display();
                }
            }
        }
        if(gamestate == 3){
            Texture help;
            Sprite shelp;
            help.loadFromFile("resources/help.jpg");
            shelp.setTexture(help);
            window.clear();
            window.draw(shelp);
            window.display();
            if(Keyboard::isKeyPressed(Keyboard::Backspace)){
                gamestate = 0;
                window.clear();
            }
        }
    }

        else if(gameplay == false){
            while(window.pollEvent(event)){
                if(event.type == Event::Closed){
                    window.close();
                }
            }
            Over.loadFromFile("resources/Game Over.png");
            Over.setSmooth(true);
            sover.setTexture(Over);
            sover.setScale(1.18,1.25);

            Font gameover;
            gameover.loadFromFile("resources/KARNIVOT.ttf");

            Text GameOver("GAME OVER",gameover,120);
            GameOver.setPosition(320,265);
            GameOver.setFillColor(Color::Yellow);

            sstotalCoin.str("");
            sstotalCoin << "Total Coin: " << score;
            ttotalCoin.setString(sstotalCoin.str());

            window.clear();

            window.draw(sover);
            window.draw(GameOver);
            window.draw(ttotalCoin);

            window.display();
        }
    }
}

#endif // GAMEEE_HPP_INCLUDED
