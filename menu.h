//
// Created by littl on 07.04.2017.
//

#ifndef RACOONDAY_MENU_H
#define RACOONDAY_MENU_H

#include <SFML/Graphics.hpp>

const int Menu_weidth=640;
const int Menu_height =480;

using namespace sf;

void open_menu(){
RenderWindow menu_window(VideoMode(Menu_weidth, Menu_height),"Menu");

    int Font_size=32;

    Text start_text;
    Text exit_text;

    Font menu_font;

    menu_font.loadFromFile("C:\\Users\\littl\\ClionProjects\\RacoonDay\\res\\fonts\\menu_font.ttf");

    start_text.setString("Start");
    start_text.setPosition(Vector2f(Menu_weidth/2-Font_size,Menu_height/2-Font_size));
    start_text.setCharacterSize(Font_size);
    start_text.setFont(menu_font);

    exit_text.setString("Exit");
    exit_text.setPosition(Vector2f(Menu_weidth/2-Font_size,Menu_height/2+Font_size*2));
    exit_text.setCharacterSize(Font_size);
    exit_text.setFont(menu_font);

    while (menu_window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop

        menu_window.clear(Color::Transparent);

        Event event;
        while (menu_window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                menu_window.close();
        }

        start_text.setFillColor(Color::White);


        if(Keyboard::isKeyPressed(Keyboard::Space)){

            menu_window.close();

        }

        menu_window.draw(start_text);
        menu_window.draw(exit_text);

        menu_window.display();

    }

}
#endif //RACOONDAY_MENU_H
