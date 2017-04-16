//
// Created by littl on 08.04.2017.
//

#ifndef RACOONDAY_DEMO_LEVEL_H
#define RACOONDAY_DEMO_LEVEL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "levels.h"

using namespace sf;

const int enemies=5;

void open_demo_level(int Weidth,int Height) {


    Texture map;//текстура карты //MAP BLOCK
    Texture raccoon_base_texture; //Базовая текстура енота
    Texture raccoon_right_texture;
    Texture raccoon_left_texture;
    Texture raccoon_rear_texture;
    Texture bullet_base_texture;
    Texture bullet_right_texture;
    Texture bullet_left_texture;
    Texture bullet_rear_texture;
    Texture empty_texture;
    Texture enemy_base_texture;

    map.loadFromFile("C:\\Users\\littl\\ClionProjects\\RacoonDay\\res\\img\\map.png");//заряжаем текстуру картинкой
    raccoon_base_texture.loadFromFile(
            "C:\\Users\\littl\\ClionProjects\\RacoonDay\\res\\img\\raccoon_base.png"); //базовая текстура енота
    bullet_base_texture.loadFromFile("C:\\Users\\littl\\ClionProjects\\RacoonDay\\res\\img\\bullet.png");
    empty_texture.loadFromFile("C:\\Users\\littl\\ClionProjects\\RacoonDay\\res\\img\\empty.png");
    raccoon_right_texture.loadFromFile("C:\\Users\\littl\\ClionProjects\\RacoonDay\\res\\img\\raccoon_right.png");
    raccoon_left_texture.loadFromFile("C:\\Users\\littl\\ClionProjects\\RacoonDay\\res\\img\\raccoon_left.png");
    raccoon_rear_texture.loadFromFile("C:\\Users\\littl\\ClionProjects\\RacoonDay\\res\\img\\raccoon_rear.png");
    enemy_base_texture.loadFromFile("C:\\Users\\littl\\ClionProjects\\RacoonDay\\res\\img\\raccoon_rear.png");

    Sprite s_map;//создаём спрайт для карты
    s_map.setTexture(map);//заливаем текстуру спрайтом

    RectangleShape raccoon;
    RectangleShape bullet;
    RectangleShape enemy[enemies];

    View Camera;

    RenderWindow Level_Demo(VideoMode(Weidth, Height), "Demo_level");

    //Level_Demo.setVerticalSyncEnabled(true);
    Level_Demo.setFramerateLimit(60);

    float Player_x = 100;
    float Player_y = 100;
    float Player_speed = 1;
    float Camera_x;
    float Camera_y;
    float Bullet_x;
    float Bullet_y;
    float Bullet_speed_x = 0;
    float Bullet_speed_y = 0;
    int dx, dy;
    int enemy_dx = -1;
    int enemy_dy = 0;
    int enemies_counter = 0;
    float Enemy_x[enemies];
    float Enemy_y[enemies];
    float Enemy_speed = 0;
    int player_health=100;

    int buf = 0;

    bool act_exec;
    bool enemy_exec;

    while (Level_Demo.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop

        Level_Demo.clear(Color(128, 106, 89));

        Event event;
        while (Level_Demo.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                Level_Demo.close();
        }


        bullet.setTexture(&bullet_base_texture);
        bullet.setSize(Vector2f(16, 32));

        /////////////////////////////Рисуем карту/////////////////////
        for (int i = 0; i < map_height; i++)
            for (int j = 0; j < map_weidth; j++) {
                if (demo_level_map[i][j] == ' ')
                    s_map.setTextureRect(IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
                if (demo_level_map[i][j] == 'c')
                    s_map.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ c, то рисуем 2й квадратик
                if (demo_level_map[i][j] == '0')
                    s_map.setTextureRect(IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
                if (demo_level_map[i][j] == 'd') s_map.setTextureRect(IntRect(98, 0, 32, 32));
                if (demo_level_map[i][j] == 'e') {

                    if (enemies_counter != enemies) {
                        Enemy_x[enemies_counter] = j * 32;
                        Enemy_y[enemies_counter] = i * 32;
                        enemy[enemies_counter].setPosition(
                                Vector2f(Enemy_x[enemies_counter], Enemy_y[enemies_counter]));
                        enemies_counter++;
                    }
                }

                s_map.setPosition(j * 32, i *
                                          32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

                Level_Demo.draw(s_map);//рисуем квадратики на экран

            }


        //Проверяем положение игрока

        for (int i = Player_y / 32; i < (Player_y + 32) /
                                        32; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
            for (int j = Player_x / 32; j < (Player_x + 16) /
                                            32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
            {
                if (demo_level_map[i][j] ==
                    '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
                {

                    if (dy > 0)//если мы шли вниз,
                    {
                        Player_y -= Player_speed;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
                    }
                    if (dy < 0) {
                        Player_y += Player_speed;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
                    }
                    if (dx > 0) {
                        Player_x -= Player_speed;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
                    }
                    if (dx < 0) {
                        Player_x += Player_speed;//аналогично идем влево
                    }


                }

            }



        //BULLET COLLISION with enemy (and enemy ) NOT COMPLETED

        for (int i = Bullet_y / 32; i < (Bullet_y + 16) /
                                        32; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
            for (int j = Bullet_x / 32; j < (Bullet_x + 16) /
                                            32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
            {
                if (demo_level_map[i][j] ==
                    '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
                {
                    if (dy > 0)//если мы шли вниз,
                    {
                        bullet.setTexture(&empty_texture);
                        Bullet_speed_y = 0;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
                    }
                    if (dy < 0) {
                        bullet.setTexture(&empty_texture);
                        Bullet_speed_y = 0;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
                    }
                    if (dx > 0) {
                        bullet.setTexture(&empty_texture);
                        Bullet_speed_x = 0;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
                    }
                    if (dx < 0) {
                        bullet.setTexture(&empty_texture);
                        Bullet_speed_x = 0;//аналогично идем влево
                    }


                }

            }

        //////////Рисуем игрока////////

        //Действия игрока
        act_exec = false;
        raccoon.setTexture(&raccoon_base_texture); //ТЕКСТУРА ИГРОКА ТУТ//

        if (Keyboard::isKeyPressed(Keyboard::A) && !act_exec) {

            Player_x -= Player_speed;
            dx = -1;
            dy = 0;
            //enemy_dx=-1;
            act_exec = true;
            raccoon.setTexture(&raccoon_left_texture);


        }

        if (Keyboard::isKeyPressed(Keyboard::D) && !act_exec) {

            Player_x += Player_speed;
            dx = 1;
            dy = 0;
            act_exec = true;
            raccoon.setTexture(&raccoon_right_texture);

        }

        if (Keyboard::isKeyPressed(Keyboard::W) && !act_exec) {

            Player_y -= Player_speed;
            dx = 0;
            dy = -1;
            act_exec = true;
            raccoon.setTexture(&raccoon_rear_texture);

        }

        if (Keyboard::isKeyPressed(Keyboard::S) && !act_exec) {

            Player_y += Player_speed;
            dx = 0;
            dy = 1;
            act_exec = true;
            raccoon.setTexture(&raccoon_base_texture);

        }


        if (Keyboard::isKeyPressed(Keyboard::Space)) {

            Bullet_x = Player_x;
            Bullet_y = Player_y;

            bullet.setPosition(Bullet_x, Bullet_y);

            if (dx < 0) {

                Bullet_speed_x = -2;
                Bullet_speed_y = 0;

            }

            if (dx > 0) {

                Bullet_speed_x = 2;
                Bullet_speed_y = 0;

            }

            if (dy > 0) {

                Bullet_speed_y = 2;
                Bullet_speed_x = 0;
            }

            if (dy < 0) {

                Bullet_speed_y = -2;
                Bullet_speed_x = 0;

            }

        }

        //ENEMY

        for (int i = 0; i < enemies_counter; i++) {
            enemy[i].setFillColor(Color::White);
            enemy[i].setSize(Vector2f(16, 32));

            for (int k = Enemy_y[i] / 32; k < (Enemy_y[i] + 16) /
                                              32; k++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
            {
                for (int l = Enemy_x[i] / 32; l < (Enemy_x[i] + 16) /
                                                  32; l++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
                {
                    if (demo_level_map[k][l] ==
                        '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
                    {

                        if (enemy_dx == 1) {
                            Enemy_x[i]--;
                        }
                        if (enemy_dx == -1) {
                            Enemy_x[i]++;
                        }

                        if (enemy_dy == -1) {
                            Enemy_y[i]++;
                        }

                        if (enemy_dy == 1) {
                            Enemy_y[i]--;
                        }


                    }
                }
            }

            if (Enemy_x[i] == Player_x) {

                if (Enemy_y[i] > Player_y) {

                    while (Enemy_y[i] - 16 > Player_y) {
                        Enemy_y[i] -= 0.5;
                        enemy[i].setPosition(Enemy_x[i], Enemy_y[i]);
                        enemy_dy = -1;
                    }
                }

                if (Enemy_y[i] < Player_y) {

                    while (Enemy_y[i] + 16 < Player_y) {
                        Enemy_y[i] += 0.5;
                        enemy[i].setPosition(Enemy_x[i], Enemy_y[i]);
                        enemy_dy = 1;
                    }
                }

            }
            if (Enemy_y[i] == Player_y) {

                    if (Enemy_x[i] > Player_x) {

                        while (Enemy_x[i] - 16 > Player_x) {
                            Enemy_x[i] -= 0.5;
                            enemy[i].setPosition(Enemy_x[i], Enemy_y[i]);
                            enemy_dx = -1;

                        }
                    }

                    if (Enemy_x[i] < Player_x) {

                        while (Enemy_x[i] + 16 < Player_x) {
                            Enemy_x[i] += 0.5;
                            enemy[i].setPosition(Enemy_x[i], Enemy_y[i]);
                            enemy_dx = 1;
                        }
                    }
                }

                if(Enemy_y[i]==Player_y && Enemy_x[i]==Player_x){

                    Enemy_y[i]--;
                    Enemy_x[i]--;
                    player_health--;

                }

                enemy[i].setPosition(Enemy_x[i], Enemy_y[i] += enemy_dy);
                Level_Demo.draw(enemy[i]);
            }

            //Настройка камеры

            Camera_x = Player_x + 32;
            Camera_y = Player_y;

            //if (Player_x < 64) Camera_x = 64;//убираем из вида левую сторону
            // if (Player_y < 32+120) Camera_y = 64;//верхнюю сторону
            //if (Player_x > 320) Camera_y = 320;//нижнюю сторону

            Camera.setCenter(Camera_x, Camera_y);
            Camera.setSize(Vector2f(200, 200));
            Level_Demo.setView(Camera);


            raccoon.setSize(Vector2f(16, 32));
            raccoon.setPosition(Player_x, Player_y);

            bullet.setPosition(Bullet_x += Bullet_speed_x, Bullet_y += Bullet_speed_y);


            Level_Demo.draw(raccoon);
            Level_Demo.draw(bullet);


            Level_Demo.display();

        }

    }


#endif //RACOONDAY_DEMO_LEVEL_H