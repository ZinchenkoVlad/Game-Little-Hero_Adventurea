#include <SFML/Graphics.hpp>
#include "Classes.h"
#include "Map1.h"
#include "Map2.h"
#include "Map3.h"
#include <iostream>
#include <vector>
#include <list>
#include "LifeBar.h"
#include <sstream>
#include <String>
#include "Menu.h"
#include <fstream>
//#include <thread>

using namespace sf;
using namespace std;


#pragma region Variables

const int widthOfWindow = 1000;
const int heightOfWindow = 600;

int Score_money = 0;
int player_Health = 100;
int dir; // for bullet and enemy
float moveTimer, phitTimet;
float positionOfHeroX, positionOfHeroY, positionOfEnemyX, positionOfEnemyY, positionOfHeroXTemp;
bool phit = true; // enemies unable to hit player
bool secretRoom = false;

int const H1 = 18;

#pragma endregion


void lelel_draw(RenderWindow& window, Sprite& tile, string *map_drawing[], float positionOfHeroX, float positionOfHeroY, int level, float offsetX)
{
    switch (level)
    {
    case 1:
        if (offsetX == -250)
        {
            positionOfHeroX = 0;
            for (int i = 0; i < 18; i++)
            {
                for (int j = 0; j < 24; j++)
                {
                    if (map_drawing[i][j] == 'S')  tile.setTextureRect(IntRect(0, 61, 16, 16)); // ground 

                    if (map_drawing[i][j] == 'f') // secret room level 1
                    {
                        tile.setTextureRect(IntRect(0, 61, 16, 16));
                        if ((positionOfHeroX < 40 * 16) && (positionOfHeroY > 14 * 16))
                        {
                            map_drawing[i][j] = ' ';
                        }
                        else tile.setTextureRect(IntRect(0, 61, 16, 16));
                    }

                    if (map_drawing[i][j] == 'M') //extra money level 1
                    {
                        tile.setTextureRect(IntRect(0, 61, 16, 16));
                        if ((positionOfHeroX < 40 * 16) && (positionOfHeroY >= 14 * 16))
                        {
                            secretRoom = true;
                            tile.setTextureRect(IntRect(32, 61, 16, 16));
                        }
                        else if (secretRoom)
                            map_drawing[i][j] = ' ';
                    }

                    if (map_drawing[i][j] == 'm') // money
                    {
                        tile.setTextureRect(IntRect(32, 61, 16, 16));
                    }

                    if (map_drawing[i][j] == 'j') // secret room enter level 1
                    {
                        tile.setTextureRect(IntRect(0, 61, 16, 16));
                    }

                    if (map_drawing[i][j] == 'd')  tile.setTextureRect(IntRect(16, 44, 16, 16)); // top of cactus

                    if (map_drawing[i][j] == 'k')  tile.setTextureRect(IntRect(0, 44, 16, 16)); // cactus

                    if (map_drawing[i][j] == 'r')  tile.setTextureRect(IntRect(32, 44, 16, 16)); // broken cactus

                    if (map_drawing[i][j] == 'L')  tile.setTextureRect(IntRect(16, 61, 16, 16)); // lava

                    if (map_drawing[i][j] == 'h')  tile.setTextureRect(IntRect(48, 61, 16, 16)); // health

                    if (map_drawing[i][j] == 'e')  tile.setTextureRect(IntRect(64, 61, 16, 16)); // exit

                    if (map_drawing[i][j] == ' ') continue;

                    tile.setPosition(j * 16 - offsetX, i * 16);
                    window.draw(tile);
                }
            }
        }
        else if (offsetX == 208)

        {
            for (int i = 0; i < 18; i++)
            {
                for (int j = 28; j < 51; j++)
                {
                    if (map_drawing[i][j] == 'S')  tile.setTextureRect(IntRect(0, 61, 16, 16)); // ground 

                    if (map_drawing[i][j] == 'f') // secret room level 1
                    {
                        tile.setTextureRect(IntRect(0, 61, 16, 16));
                        if ((positionOfHeroX < 40 * 16) && (positionOfHeroY > 14 * 16))
                        {
                            map_drawing[i][j] = ' ';
                        }
                        else tile.setTextureRect(IntRect(0, 61, 16, 16));
                    }

                    if (map_drawing[i][j] == 'M') //extra money level 1
                    {
                        tile.setTextureRect(IntRect(0, 61, 16, 16));
                        if ((positionOfHeroX < 40 * 16) && (positionOfHeroY >= 14 * 16))
                        {
                            secretRoom = true;
                            tile.setTextureRect(IntRect(32, 61, 16, 16));
                        }
                        else if (secretRoom)
                            map_drawing[i][j] = ' ';
                    }

                    if (map_drawing[i][j] == 'm') // money
                    {
                        tile.setTextureRect(IntRect(32, 61, 16, 16));
                    }

                    if (map_drawing[i][j] == 'j') // secret room enter level 1
                    {
                        tile.setTextureRect(IntRect(0, 61, 16, 16));
                    }

                    if (map_drawing[i][j] == 'd')  tile.setTextureRect(IntRect(16, 44, 16, 16)); // top of cactus

                    if (map_drawing[i][j] == 'k')  tile.setTextureRect(IntRect(0, 44, 16, 16)); // cactus

                    if (map_drawing[i][j] == 'r')  tile.setTextureRect(IntRect(32, 44, 16, 16)); // broken cactus

                    if (map_drawing[i][j] == 'L')  tile.setTextureRect(IntRect(16, 61, 16, 16)); // lava

                    if (map_drawing[i][j] == 'h')  tile.setTextureRect(IntRect(48, 61, 16, 16)); // health

                    if (map_drawing[i][j] == 'e')  tile.setTextureRect(IntRect(64, 61, 16, 16)); // exit

                    if (map_drawing[i][j] == ' ') continue;

                    tile.setPosition(j * 16 - offsetX, i * 16);
                    window.draw(tile);
                }
            }
        }
        else
        {
            for (int i = 0; i < 18; i++)
            {
                for (int j = positionOfHeroX / 16 - 11; j < positionOfHeroX / 16 + 13; j++)
                {
                    if (map_drawing[i][j] == 'S')  tile.setTextureRect(IntRect(0, 61, 16, 16)); // ground 

                    if (map_drawing[i][j] == 'f') // secret room level 1
                    {
                        tile.setTextureRect(IntRect(0, 61, 16, 16));
                        if ((positionOfHeroX < 40 * 16) && (positionOfHeroY > 14 * 16))
                        {
                            map_drawing[i][j] = ' ';
                        }
                        else tile.setTextureRect(IntRect(0, 61, 16, 16));
                    }

                    if (map_drawing[i][j] == 'M') //extra money level 1
                    {
                        tile.setTextureRect(IntRect(0, 61, 16, 16));
                        if ((positionOfHeroX < 40 * 16) && (positionOfHeroY >= 14 * 16))
                        {
                            secretRoom = true;
                            tile.setTextureRect(IntRect(32, 61, 16, 16));
                        }
                        else if (secretRoom)
                            map_drawing[i][j] = ' ';
                    }

                    if (map_drawing[i][j] == 'm') // money
                    {
                        tile.setTextureRect(IntRect(32, 61, 16, 16));
                    }

                    if (map_drawing[i][j] == 'j') // secret room enter level 1
                    {
                        tile.setTextureRect(IntRect(0, 61, 16, 16));
                    }

                    if (map_drawing[i][j] == 'd')  tile.setTextureRect(IntRect(16, 44, 16, 16)); // top of cactus

                    if (map_drawing[i][j] == 'k')  tile.setTextureRect(IntRect(0, 44, 16, 16)); // cactus

                    if (map_drawing[i][j] == 'r')  tile.setTextureRect(IntRect(32, 44, 16, 16)); // broken cactus

                    if (map_drawing[i][j] == 'L')  tile.setTextureRect(IntRect(16, 61, 16, 16)); // lava

                    if (map_drawing[i][j] == 'h')  tile.setTextureRect(IntRect(48, 61, 16, 16)); // health

                    if (map_drawing[i][j] == 'e')  tile.setTextureRect(IntRect(64, 61, 16, 16)); // exit

                    if (map_drawing[i][j] == ' ') continue;

                    tile.setPosition(j * 16 - offsetX, i * 16);
                    window.draw(tile);
                }
            }
        }
        
        break;
    case 2:
        for (int i = 0; i < 18; i++)
        {
            for (int j = 0; j < 22; j++)
            {
                if (map_drawing[i][j] == 'S')  tile.setTextureRect(IntRect(0, 61, 16, 16)); // ground 

                if (map_drawing[i][j] == 'm') // money
                    tile.setTextureRect(IntRect(32, 61, 16, 16));

                if (map_drawing[i][j] == 'd')  tile.setTextureRect(IntRect(16, 44, 16, 16)); // top of cactus

                if (map_drawing[i][j] == 'e')  tile.setTextureRect(IntRect(64, 61, 16, 16)); // exit

                if (map_drawing[i][j] == 'k')  tile.setTextureRect(IntRect(0, 44, 16, 16)); // cactus

                if (map_drawing[i][j] == 'r')  tile.setTextureRect(IntRect(32, 44, 16, 16)); // broken cactus

                if (map_drawing[i][j] == ' ') continue;

                tile.setPosition(j * 16 - offsetX, i * 16);
                window.draw(tile);
            }
        }
        break;
    case 3:
        for (int i = 0; i < 18; i++)
        {
            for (int j = 0; j < 23; j++)
            {
                if (map_drawing[i][j] == 'S')  tile.setTextureRect(IntRect(0, 61, 16, 16)); // ground 

                if (map_drawing[i][j] == 'm') // money
                    tile.setTextureRect(IntRect(32, 61, 16, 16));

                if (map_drawing[i][j] == 'd')  tile.setTextureRect(IntRect(16, 44, 16, 16)); // top of cactus

                if (map_drawing[i][j] == 'e')  tile.setTextureRect(IntRect(64, 61, 16, 16)); // exit

                if (map_drawing[i][j] == 'k')  tile.setTextureRect(IntRect(0, 44, 16, 16)); // cactus

                if (map_drawing[i][j] == 'L')  tile.setTextureRect(IntRect(16, 61, 16, 16)); // lava

                if (map_drawing[i][j] == 'r')  tile.setTextureRect(IntRect(32, 44, 16, 16)); // broken cactus

                if (map_drawing[i][j] == '1')  tile.setTextureRect(IntRect(32+48, 61-16, 16, 16)); //клад 
                if (map_drawing[i][j] == '2')  tile.setTextureRect(IntRect(32+64, 61-16, 16, 16)); // 
                if (map_drawing[i][j] == '3')  tile.setTextureRect(IntRect(48+32, 61, 16, 16)); // 
                if (map_drawing[i][j] == '4')  tile.setTextureRect(IntRect(48+48, 61, 16, 16)); // 

                if (map_drawing[i][j] == ' ') continue;

                tile.setPosition(j * 16 - offsetX, i * 16);
                window.draw(tile);
            }
        }
        break;
    
    default:
        break;
    }
    

        
}


bool startGame(RenderWindow& window, int level)
{
    int playerDefCoordinateX, playerDefCoordinateY;
    Clock clock;
    Texture All;
    All.loadFromFile("images/1.png");
    Sprite tile(All);

    Texture end, gameOver;
    end.loadFromFile("images/Win.png");
    gameOver.loadFromFile("images/GameOver.png");
    Sprite endOfGame(end);
    Sprite GameOver(gameOver);

    

    View view;
    if (level <= 3)
        view.setViewport(sf::FloatRect(-0.7f, -0.0f, 2.8f, 3.5f));
    else 
        view.setViewport(sf::FloatRect(-0.0f, -0.02f, 1.0f, 1.7f));


    LifeBar lifeBarPlayer;

    Font font;
    font.loadFromFile("Fonts/Akademische schmalfette.ttf");
    Text text("", font, 15);
    text.setFillColor(Color::Green);
    Text text1("", font, 15);
    text1.setFillColor(Color::Green);
    Text text2("", font, 15);
    text2.setFillColor(Color::Green);

    list<Bullet*> bullets;
    list<Bullet*>::iterator it;

    list<Enemy*> enemies;
    list<Enemy*>::iterator it1;

    string* level_map1[18];
    string* level_map2[18];
    string* level_map3[18];

    ofstream fout;
    ifstream fin;

    switch (level)
    {
    case 1:
        enemies.push_back(new Enemy(All, "squirell", 32 * 16, 11 * 16 + 8));
        enemies.push_back(new Enemy(All, "squirell", 19 * 16, 11 * 16 + 8));
        playerDefCoordinateX = 4 * 16;
        playerDefCoordinateY = 5 * 16;

        for (int i = 0; i < 18; i++)
            level_map1[i] = TileMap1[i];

        break;
    case 2:
        enemies.push_back(new Enemy(All, "squirell", 4 * 16, 11 * 16 + 8));
        enemies.push_back(new Enemy(All, "squirell", 11 * 16, 11 * 16 + 8));
        playerDefCoordinateX = 2 * 16;
        playerDefCoordinateY = 1 * 16;

        for (int i = 0; i < 18; i++)
            level_map2[i] = TileMap2[i];

        break;
    case 3:
        playerDefCoordinateX = 2 * 16;
        playerDefCoordinateY = 1 * 16;

        for (int i = 0; i < 18; i++)
            level_map3[i] = TileMap3[i];
        break;
    case 4:
    case 5:
        playerDefCoordinateX = 2 * 16;
        playerDefCoordinateY = 1 * 16;
        break;
    default:
        break;
    }
    
    
    Player p(All, "player1", playerDefCoordinateX, playerDefCoordinateY, player_Health);
    string ScoreMenu;
    fin.open("Score_menu.txt");
    
    if (fin.peek() == EOF)
    {
        fin.close();
        fout.open("Score_menu.txt");

        if (!fout.is_open())
        {
            cout << "error in score_menu" << endl;
        }
        else
        {
            ScoreMenu = to_string(1);
            fout << Score_money;
        }
        fout.close();
    }
    else
    {
        fin >> ScoreMenu;
        fin.close();
    }
        
    



    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        moveTimer += time;
        phitTimet += time;

        // for interaction with bullets
        positionOfHeroX = p.rect.left + p.rect.width / 2;
        positionOfHeroY = p.rect.top + p.rect.height / 2;


        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                if (Score_money >= stoi(ScoreMenu))
                {
                    fout.open("Score_menu.txt");

                    if (!fout.is_open())
                    {
                        cout << "error in score_menu" << endl;
                    }
                    else
                    {

                        fout << Score_money;
                    }
                    fout.close();
                }
                

                window.close();
            }
                



            // створення пуль
            if (moveTimer > 1000) // for bullet (1000 = 1sec)
            {
                moveTimer = 0;

                for (it1 = enemies.begin(); it1 != enemies.end(); it1++)
                {
                    Enemy* b = *it1;


                    if (p.rect.left > (b)->rect.left) // for bullet
                        dir = 1;
                    else dir = -1;



                        positionOfEnemyX = b->rect.left + b->rect.width / 2;
                        positionOfEnemyY = b->rect.top + b->rect.height / 2;
                        // зона видимості пулі
                        if (((positionOfHeroX > positionOfEnemyX - 8 * 16) && (positionOfHeroX < positionOfEnemyX)) || ((positionOfHeroX < positionOfEnemyX + 8 * 16) && (positionOfHeroX > positionOfEnemyX)))
                        {
                            if (((positionOfHeroY < positionOfEnemyY + 1 * 16) && (positionOfHeroY > positionOfEnemyY)) || ((positionOfHeroY > positionOfEnemyY - 8 * 16) && (positionOfHeroY < positionOfEnemyY)))
                            {
                                if ((((dir == 1) && (b->dx > 0)) || ((dir == -1) && (b->dx > 0)))) // білка не стріляє задом
                                {
                                    bullets.push_back(new Bullet(All, "rock", (b)->rect.left, (b)->rect.top, dir));
                                }

                            }
                        }
                }
            }
        }


        // bullet
        if (phit)
        {
            for (it = bullets.begin(); it != bullets.end();)
            {
                Bullet* b = *it;
                if (level == 1)
                    b->update(time, level_map1);
                if (level == 2)
                    b->update(time, level_map2);

                if (p.rect.intersects(b->rect))
                {
                    player_Health -= 2;
                    b->life = false;
                }

                if (b->life == false)
                {
                    it = bullets.erase(it);
                    delete b;
                }
                else it++;
            }
        }
        else
        {
            for (it = bullets.begin(); it != bullets.end();)
            {
                Bullet* b = *it;
                if (level == 1)
                    b->update(time, level_map1);
                if (level == 2)
                    b->update(time, level_map2);

                    b->life = false;

                if (b->life == false)
                {
                    it = bullets.erase(it);
                    delete b;
                }
                else it++;
            }
        }
        
        
        
        
        // enemies
        for (it1 = enemies.begin(); it1 != enemies.end();)
        {
            Enemy* b = *it1;

            // INTERACTION WIHT ENEMY
            if (phitTimet > 5000)
                phit = true;

            if ((p.rect.intersects(b->rect)) && (phit))
            {
                phitTimet = 0;
                player_Health -= 8;
                phit = false;
            }
            // INTERACTION WIHT ENEMY
            if (phit)
            {
                if (p.rect.left > (b)->rect.left)
                {
                    dir = 1;

                }
                else
                {
                    dir = -1;
                }
            }
            else
            {
                    dir = 0;
                    b->sprite.setTextureRect(IntRect(62, 148, -62, 61));
            }
           



            if (b->life == false)
            {
                it1 = enemies.erase(it1);
                delete b;
            }
            else it1++;
            if(level == 1)
                b->update(time, dir, positionOfHeroX, level, level_map1);
            if(level == 2)
                b->update(time, dir, positionOfHeroX, level, level_map2);
        }
        

        p.Control();
        

        if (Keyboard::isKeyPressed(Keyboard::Escape)) 
        {
            if (Score_money >= stoi(ScoreMenu))
            {
                fout.open("Score_menu.txt");

                if (!fout.is_open())
                {
                    cout << "error in score_menu" << endl;
                }
                else
                {

                    fout << Score_money;
                }
                fout.close();
            }
            
            return false; 
        }
        
        switch (level)
        {
        case 1:
            p.update(time, level, Score_money, player_Health, level_map1);

            if ((positionOfHeroX >= 399) && (positionOfHeroY == 190.5) && (positionOfHeroX <= 425))
                player_Health -= 1;

            if (player_Health <= 0)
            {
                level = 4;
                return true;
            }

            if ((positionOfHeroX <= 809) && (positionOfHeroX >= 793) && (positionOfHeroY == 126.5))
            {
                level++;
                return true;
            }

            break;
        case 2:
            p.update(time, level, Score_money, player_Health, level_map2);
            if (player_Health <= 0)
            {
                level = 4;
                return true;
            }
            if ((positionOfHeroX >= 19 * 16) && (positionOfHeroY >= 16 * 16))
            {
                level++;
                return true;
            }

            break;
        case 3:
            p.update(time, level, Score_money, player_Health, level_map3);
            if (player_Health <= 0)
            {
                level = 4;
                return true;
            }

            if ((positionOfHeroX >= 223) && (positionOfHeroY == 190.5) && (positionOfHeroX <= 233))
                player_Health -= 1;

            if ((positionOfHeroX >= 287) && (positionOfHeroY == 190.5) && (positionOfHeroX <= 297))
                player_Health -= 1;

            if ((positionOfHeroX >= 127) && (positionOfHeroY == 190.5) && (positionOfHeroX <= 185))
                player_Health -= 1;

            if ((positionOfHeroX >= 316) && (positionOfHeroX <= 329) && (positionOfHeroY == 174.5))
            {
                level++;
                return true;
            }

            break;
        default:
            break;
        }

        
        lifeBarPlayer.update(player_Health, positionOfHeroX, positionOfHeroY);
        

        ////SCORE
        std::ostringstream playerScoreString;    // объявили переменную
        playerScoreString << Score_money;		//занесли в нее число очков, то есть формируем строку
        text.setString("Score: " + playerScoreString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
        text.setPosition(positionOfHeroX - offsetX - 75, 0);//задаем позицию текста, центр камеры
            

        ////Score_Level
        std::ostringstream playerScoreLevelString;
        playerScoreLevelString << level;
        text1.setString("Level: " + playerScoreLevelString.str());
        text1.setPosition(positionOfHeroX - offsetX + 135, 0);
        ////Highscore
        std::ostringstream ScoreMenuString;
        ScoreMenuString << ScoreMenu;
        text2.setString("Hight score: " + ScoreMenuString.str());
        text2.setPosition(positionOfHeroX - offsetX + 30, 0);
        

        if ((offsetX <= -250) || (offsetX >= 208))
        {
            text.setPosition(340, 0);
            text1.setPosition(550, 0);
            text2.setPosition(445, 0);
        }


        offsetX = p.rect.left - 400;


        if (offsetX < -250)
            offsetX = -250;
        if (level == 1)
            if (offsetX >= 208)
                offsetX = 208;
        if (level == 2)
                offsetX = -250;
        if (level == 3)
            offsetX = -250;
        
        
        //cout << positionOfHeroX << "\t" << positionOfHeroY << endl;
        window.setView(view);//"оживляем" камеру в окне sfml
        window.clear(Color::Color(51, 32, 0));


        switch (level)
        {
        case 1:
            lelel_draw(window, tile, level_map1, positionOfHeroX, positionOfHeroY, level, offsetX);
            break;
        case 2:
            lelel_draw(window, tile, level_map2, positionOfHeroX, positionOfHeroY, level, offsetX);
            break;
        case 3:
            lelel_draw(window, tile, level_map3, positionOfHeroX, positionOfHeroY, level, offsetX);
            break;
        default:
            break;
        }

        if (level <= 3)
        {
            p.draw(window);
            for (it = bullets.begin(); it != bullets.end(); it++)
                (*it)->draw(window);
            for (it1 = enemies.begin(); it1 != enemies.end(); it1++)
                (*it1)->draw(window);
            lifeBarPlayer.draw(window);
            window.draw(text);
            window.draw(text1);
            window.draw(text2);
        } 
        else if (level == 4)
        {
            if (player_Health <= 0)
            {
                window.draw(GameOver);
            }
            else
                window.draw(endOfGame);
        }
        else if (level == 5)
            window.draw(GameOver);

        window.display();
        
    }
}


void changeLevel(RenderWindow& window, int level)
{
    if (startGame(window, level))
    {
        level++;
        changeLevel(window, level);
    }
}


int main()
{
    //RenderWindow window(VideoMode(widthOfWindow, heightOfWindow), "Little hero adventure!", Style::Titlebar | Style::Close);
    RenderWindow window(VideoMode::getDesktopMode(), "Little hero adventure!");// Style::Titlebar | Style::Close);
    menu(window);
    int level = 1; // start level
    changeLevel(window, level);
    return 0;
}