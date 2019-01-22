#ifndef GAMEEE_HPP_INCLUDED
#define GAMEEE_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <SFML/Audio.hpp>
#include "Collision.h"

using namespace sf;
using namespace std;

int i, x = 1100, y = 600, score = 0, chance = 0, gamestate = 0, gamelevel = 1;

unsigned int menustate = 0;

float Yvelocity = 0, val = 10;

bool jumping = false, keycollected = false, levelup = false, gameplay = true,c1=false,c2=false, levelOneStarted = true, levelTwoStarted = false,levelThreeStarted = false, eaten=true;

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
    else if((x >= 1190 && x <= 1500) && y <= 160+35){
        return 160; // last
    }
    else if((x >= 852 && x <= 1028) && y <= 192+35){
        return 192; // middle mushroom
    }
    else if((x >= 300 && x <= 500) && y <= 448+35){
        return 448; // left middle
    }
    else if((x >= 716 && x <= 1116) && y <= 496+35){
        return 486; // middle upper
    }
    else if((x >= 600 && x <= 900) && y <= 288+35){
        return 288; // middle tree
    }
    else if((x >= 25 && x <= 188) && y <= 656+35){
        return 656; // arrow
    }
    else if((x >= 580 && x <= 1140) && y <= 656+35){
        return 640; // middle down
    }
    else if((x >= 28 && x <=372) && y <= 720+35){
        return 720; // arrow down
    }
    else if((x >= 1100 && x <= 1332) && y <= 728+35){
        return 728; // middle box
    }
    else{
        return 875;
    }
}

int ground3(int x, int y)
{
    if((x >= 900 && x <= 1068) && y <= 128+35){
        return 138;
    }
    else if((x >= 364 && x <= 804) && y <= 130+35){
        return 140;
    }
    else if((x >= 1190 && x <= 1500) && y <= 160+35){
        return 160;
    }
    else if((x >= 0 && x <= 204) && y <= 285+35){
        return 270;
    }
    else if((x >= 220 && x <= 428) && y <= 368+35){
        return 375;
    }
    else if((x >= 500 && x <= 692) && y <= 424+35){
        return 440;
    }
    else if((x >= 804 && x <= 1252) && y <= 432+35){
        return 442;
    }
    else if((x >= 740 && x <= 1124) && y <= 624+35){
        return 635;
    }
    else if((x >= 1290 && x <= 1500) && y <= 630+35){
        return 640;
    }
    else if((x >= 0 && x <= 380) && y <= 720+35){
        return 720;
    }
    else if((x >= 528 && x <= 755) && y <= 756+35){
        return 766;
    }
    else{
        return 875;
    }
}

void game(){

    window.setFramerateLimit(30);

    Event event;

    Texture level, ball, coin, key, level1up, saw, spike, Over, life, menu, level2, level2up, level3, TheEnd;
    Sprite slevel, sball, scoin, skey, coinAra[12], slevel1up, ssaw, sawAra[4],sspike, spikeAra[5], slevel3, sover, slife, lifeAra[3], sTheEnd, smenu, slevel2, slevel2up;

    Music menuMusic,eatMusic;
    menuMusic.openFromFile("resources/music.wav");
    menuMusic.setVolume(20);
    menuMusic.play();

    SoundBuffer eatBuf;
    eatBuf.loadFromFile("resources/eet.wav");
    Sound eatSound;
    eatSound.setBuffer(eatBuf);

    SoundBuffer crashBuf;
    crashBuf.loadFromFile("resources/crash.wav");
    Sound crashSound;
    crashSound.setBuffer(crashBuf);

    Font fCoin;
    fCoin.loadFromFile("resources/COOPBL.TTF");
    ostringstream sscoin;
    sscoin << "Coins: " << score;

    Text tCoin;
    tCoin.setCharacterSize(50);
    tCoin.setPosition(1230, -8);
    tCoin.setFont(fCoin);
    tCoin.setString(sscoin.str());
    tCoin.setFillColor(Color::Green);

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

    Text tstart("START",fstart,70);
    tstart.setPosition(400, 290);
    tstart.setFillColor(Color::Yellow);

    Font finst;
    finst.loadFromFile("resources/berkshireswash-regular.ttf");

    Text tinst("INSTRUCTION",finst,70);
    tinst.setPosition(400, 380);
    tinst.setFillColor(Color::Yellow);

    Font fexit;
    fexit.loadFromFile("resources/berkshireswash-regular.ttf");

    Text texit("EXIT",finst,70);
    texit.setPosition(400, 470);
    texit.setFillColor(Color::Yellow);

    level.loadFromFile("resources/level1.jpg");
    level.setSmooth(true);
    slevel.setTexture(level);
    slevel.scale(1.5,1.5);

    level2.loadFromFile("resources/level2.jpg");
    level2.setSmooth(true);
    slevel2.setTexture(level2);
    slevel2.setScale(1.5,1.2);

    level3.loadFromFile("resources/level3.png");
    level3.setSmooth(true);
    slevel3.setTexture(level3);
    slevel3.setScale(1.42,1.15);

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

    level2up.loadFromFile("resources/LevelTwoUp.png");
    level2up.setSmooth(true);
    slevel2up.setTexture(level2up);
    slevel2up.scale(1.5,1.3);

    TheEnd.loadFromFile("resources/gameend.jpg");
    TheEnd.setSmooth(true);
    sTheEnd.setTexture(TheEnd);
    sTheEnd.setScale(1.5,1.3);

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
                texit.setFillColor(Color::Yellow);
                tinst.setFillColor(Color::Yellow);
                break;
            case 1:
                tinst.setFillColor(Color::Red);
                tstart.setFillColor(Color::Yellow);
                texit.setFillColor(Color::Yellow);
                break;
            case 2:
                texit.setFillColor(Color::Red);
                tstart.setFillColor(Color::Yellow);
                tinst.setFillColor(Color::Yellow);
                break;
            }
            if(Keyboard::isKeyPressed(Keyboard::Up) && mclock.getElapsedTime().asMilliseconds()>150){
                if(menustate > 0){
                    menustate--;
                }
                else {
                    menustate = 2;
                }
                mclock.restart();
            }
            if(Keyboard::isKeyPressed(Keyboard::Down) && mclock.getElapsedTime().asMilliseconds()>150){
                if(menustate < 2){
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
                    gamestate = 2;
                    break;
                case 2:
                    gamestate = 3;
                    break;
                }
            }
            window.clear();
            window.draw(smenu);
            window.draw(tname);
            window.draw(tstart);
            window.draw(tinst);
            window.draw(texit);
            window.display();
        }

        else if(gamestate == 1){

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

            ///Level 1
            if(gamelevel == 1){
            int a = sball.getPosition().x;
            int b = sball.getPosition().y;
            int gr = ground(a, b);

            cout << "a=" << a << " b=" << b << " ground=" << gr << endl;

            if(levelOneStarted){
                coinAra[1].setPosition(950,688); // spiral
                coinAra[2].setPosition(420,688); // white door 1
                coinAra[3].setPosition(265,190);  // grass
                coinAra[4].setPosition(330,688);  //white door3
                coinAra[5].setPosition(908,314);  //1
                coinAra[6].setPosition(1033,190); //2
                coinAra[7].setPosition(659,190); //3
                coinAra[8].setPosition(650,438); // green drum 1
                coinAra[9].setPosition(1250,190); // up right
                coinAra[10].setPosition(150,190); //  up 3
                coinAra[11].setPosition(755,438); // green drum
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

                ///key
                skey.setPosition(750,682);
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
                    if(eaten) eatSound.play();
                    coinAra[i].setPosition(-200,-200);
                    sscoin.str("");
                    sscoin << "Coins: " << score;
                    tCoin.setString(sscoin.str());
                }
            }

            ///key collect
            if(Collision::PixelPerfectTest(skey, sball)){
                if(eaten) eatSound.play();
                skey.setPosition(-100,-100);
                keycollected = true;
            }

            ///saw dead
            for(i = 0; i<4; i++){
                if(Collision::PixelPerfectTest(sawAra[i], sball)){
                    chance++;
                    c1=true;
                    if(c1) crashSound.play();
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
                    c2=true;
                    if(c2) crashSound.play();
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
               keycollected = false;
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

                    chance = 0;
                    sball.setPosition(25, 656);

                    coinAra[0].setPosition(20,113);
                    coinAra[1].setPosition(1310,120);
                    coinAra[2].setPosition(1220,120);
                    coinAra[3].setPosition(600,614);
                    coinAra[4].setPosition(267,688);
                    coinAra[5].setPosition(908,152);
                    coinAra[6].setPosition(637,248);
                    coinAra[7].setPosition(420,410);
                    coinAra[8].setPosition(165,113);
                    coinAra[9].setPosition(300,113);
                    coinAra[10].setPosition(750,456);
                    coinAra[11].setPosition(1000,456);

                    ///life
                    lifeAra[1].setPosition(125,-8);
                    lifeAra[2].setPosition(60,-8);
                    lifeAra[3].setPosition(-5,-8);

                    ///saw
                    sawAra[0].setPosition(460, 670);
                    sawAra[1].setPosition(1260, 600);
                    sawAra[2].setPosition(1120, 240);
                    sawAra[3].setPosition(114,448);

                    ///spike
                    spikeAra[0].setPosition(290, 340);
                    spikeAra[1].setPosition(410, 770);
                    spikeAra[2].setPosition(1360, 770);
                    spikeAra[3].setPosition(840, 389);
                    spikeAra[4].setPosition(-1000, -745);

                    ///key
                    skey.setPosition(1150,676);

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
                        if(eaten) eatSound.play();
                        coinAra[i].setPosition(-200,-200);
                        sscoin.str("");
                        sscoin << "COINS: " << score;
                        tCoin.setString(sscoin.str());
                    }
                }

                ///key collect
                if(Collision::PixelPerfectTest(skey, sball)){
                    if(eaten) eatSound.play();
                    skey.setPosition(-100,-100);
                    keycollected = true;
                }

               ///saw dead
                for(i = 0; i<4; i++){
                    if(Collision::PixelPerfectTest(sawAra[i], sball)){
                        chance++;
                        c1=true;
                    if(c1) crashSound.play();
                        if(chance < 3){
                            sball.setPosition(25, 656);
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
                        c2=true;
                    if(c2) crashSound.play();
                        if(chance < 3){
                            sball.setPosition(25, 656);
                            lifeAra[chance].setPosition(-300,-300);
                        }
                        else if(chance == 3){
                            gameplay = false;
                        }
                    }
                }

                window.clear();

                window.draw(slevel2);
                window.draw(sball);
                window.draw(skey);
                tCoin.setFillColor(Color::Red);
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
                if((keycollected == true) && ((a >= 1360 && a <= 1500) && (b >= 30 && b <= 400))){
                   gamelevel++;
                   levelup = true;
                   levelThreeStarted = true;
                   keycollected = false;
                }
            }
        }

        else if(gamelevel == 3){

            int a = sball.getPosition().x;
            int b = sball.getPosition().y;
            int gr = ground3(a, b);

            if(levelup){
                Font fLevelUp;
                fLevelUp.loadFromFile("resources/impact.ttf");

                Text tLevelUp("You'VE Passed Level TWO!!", fLevelUp, 110);
                tLevelUp.setPosition(190,400);
                tLevelUp.setFillColor(Color::Blue);

                window.clear();

                window.draw(slevel2up);
                tCongo.setFillColor(Color::Green);
                window.draw(tCongo);
                window.draw(tLevelUp);

                window.display();
                if(Keyboard::isKeyPressed(Keyboard::Enter)){
                    levelup = false;
                }
            }
            else if(levelup == false){
                    if(levelThreeStarted == true){

                    chance = 0;
                    sball.setPosition(25, 656);

                    coinAra[0].setPosition(900,416);
                    coinAra[1].setPosition(604,414);
                    coinAra[2].setPosition(380,352);
                    coinAra[3].setPosition(60,229);
                    coinAra[4].setPosition(1012,616);
                    coinAra[5].setPosition(1318,152);
                    coinAra[6].setPosition(988,120);
                    coinAra[7].setPosition(804,616);
                    coinAra[8].setPosition(742,110);
                    coinAra[9].setPosition(428,110);
                    coinAra[10].setPosition(520,736);
                    coinAra[11].setPosition(1380,616);

                    ///life
                    lifeAra[1].setPosition(125,-8);
                    lifeAra[2].setPosition(60,-8);
                    lifeAra[3].setPosition(-5,-8);

                    ///saw
                    sawAra[0].setPosition(610, 290);
                    sawAra[1].setPosition(99, 590);
                    sawAra[2].setPosition(1390, 430);
                    sawAra[3].setPosition(-220,280);

                    ///spike
                    spikeAra[0].setPosition(394, 768);
                    spikeAra[1].setPosition(620, 667);
                    spikeAra[2].setPosition(1150, 761);
                    spikeAra[3].setPosition(222,280);
                    spikeAra[4].setPosition(980, 352);

                    ///key
                    skey.setPosition(1150,415);

                    levelThreeStarted = false;
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
                        if(eaten) eatSound.play();
                        coinAra[i].setPosition(-200,-200);
                        sscoin.str("");
                        sscoin << "COINS: " << score;
                        tCoin.setString(sscoin.str());
                    }
                }

                ///key collect
                if(Collision::PixelPerfectTest(skey, sball)){
                    if(eaten) eatSound.play();
                    skey.setPosition(-100,-100);
                    keycollected = true;
                }

               ///saw dead
                for(i = 0; i<4; i++){
                    if(Collision::PixelPerfectTest(sawAra[i], sball)){
                        chance++;
                        c1=true;
                    if(c1) crashSound.play();
                        if(chance < 3){
                            sball.setPosition(25, 656);
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
                        c2=true;
                    if(c2) crashSound.play();
                        if(chance < 3){
                            sball.setPosition(25, 656);
                            lifeAra[chance].setPosition(-300,-300);
                        }
                        else if(chance == 3){
                            gameplay = false;
                        }
                    }
                }

                window.clear();

                window.draw(slevel3);
                window.draw(sball);
                window.draw(skey);
                tCoin.setFillColor(Color::Yellow);
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

                ///game end
                if((keycollected == true) && ((a >= 1190 && a <= 1500) && (b >= 0 && b <= 180))){
                   gamelevel++;
                   levelup = true;
                   levelThreeStarted = true;
                   keycollected = false;
                }
            }
        }
        else if(gamelevel == 4){
            Font fLevelUp;
            fLevelUp.loadFromFile("resources/impact.ttf");

            Text tLevelUp("You'VE Passed EVERY Level!!", fLevelUp, 110);
            tLevelUp.setPosition(190,400);
            tLevelUp.setFillColor(Color::Blue);

            window.clear();

            window.draw(sTheEnd);
            tCongo.setFillColor(Color::Yellow);
            window.draw(tCongo);
            window.draw(tLevelUp);

            window.display();
            if(Keyboard::isKeyPressed(Keyboard::Backspace)){
                window.clear();
                gamestate = 0;
            }
        }
    }
    else if(gamestate == 2){
        Texture help;
        Sprite shelp;
        help.loadFromFile("resources/helppage.jpg");
        shelp.setTexture(help);
        shelp.setScale(1.5,1.73);
        window.clear();
        window.draw(shelp);
        window.display();
        if(Keyboard::isKeyPressed(Keyboard::Backspace)){
            gamestate = 0;
            window.clear();
        }
    }
    else if(gamestate == 3){
        window.close();
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
