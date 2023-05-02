#pragma once
using namespace sf;

float offsetX = 0;



class Entity
{
public:
	float dx, dy;
	Sprite sprite;
	FloatRect rect;
	String name;
	String Name;
	float curFrame;
	bool life;
	int health;

	Entity(Texture& texture, String name, int x, int y)
	{
		sprite.setTexture(texture);
		dx = 0.05;
		curFrame = 0;
		life = true;
	}

	void draw(RenderWindow& window)
	{
		window.draw(sprite);
	}
};


class Player :public Entity
{
public:
	bool onGround;
	
	Player(Texture& texture, String name, int x, int y, int &health) :Entity(texture, name, x, y)
	{
			sprite.setTextureRect(IntRect(0, 0, 30, 36));
			rect = FloatRect(x, y, 30, 35);
			dx = dy = 0;
			curFrame = 1;
			//health = 100;
	}

	void update(float time, int level, int& Score_money, int& health, std::string* map_drawing[])
	{
		rect.left += dx * time;
			Collision(0, level, Score_money, health, map_drawing);
		if (!onGround)
			dy = dy + 0.0005 * time;
		rect.top += dy * time;
		onGround = false;
			Collision(1, level, Score_money, health, map_drawing);

		if (health > 100)
			health = 100;
		if (health <= 0)
			life = false;

		/////animation/////
	   /* curFrame += 0.005 * time;
		if (curFrame > 2) curFrame = -1;
			if ((dy == 0) && (dx == 0))  sprite.setTextureRect(IntRect(30 * int(curFrame), 0, 30, 35));
			*/

		sprite.setPosition(rect.left - offsetX, rect.top);
		/////animation/////
		dx = 0;
	}

	void Collision(int dir, int level, int & Score_money, int& health, std::string* map_drawing[])
	{
		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width - 8) / 16; j++)
			{
				if (level <= 3)
				{
					if ((map_drawing[i][j] == 'S') || (map_drawing[i][j] == 'k') || (map_drawing[i][j] == 'j'))
					{
						if ((dx > 0) && (dir == 0)) rect.left = j * 16 - rect.width + 8;
						if ((dx < 0) && (dir == 0)) rect.left = j * 16 + 16;
						if ((dy > 0) && (dir == 1)) { rect.top = i * 16 - rect.height;  dy = 0;   onGround = true; }
						if ((dy < 0) && (dir == 1)) { rect.top = i * 16 + 16;   dy = 0; }
					}

					if (map_drawing[i][j] == '0')
					{
						map_drawing[i][j] = ' ';
					}

					if ((map_drawing[i][j] == 'm') || (map_drawing[i][j] == 'M'))
					{
						map_drawing[i][j] = ' ';
						Score_money += 10;
					}

					if (map_drawing[i][j] == 'h')
					{
						map_drawing[i][j] = ' ';
						health += 5;
					}


					if ((map_drawing[i][j] == 'k') && (Mouse::isButtonPressed(Mouse::Left)))
					{
						map_drawing[i][j] = 'r';
					}

					if ((map_drawing[i][j] == 'j') && (Mouse::isButtonPressed(Mouse::Left)))
					{
						map_drawing[i][j] = ' ';
					}

					if ((map_drawing[i][j] == 'd') && (Mouse::isButtonPressed(Mouse::Left)))
					{
						map_drawing[i][j] = ' ';
					}
				}
				

			}
	}


	void Control() {
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			dx = 0.1;            
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			dx = -0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			if (onGround)
			{
				dy = -0.27;
				onGround = false;
			}
		}
	}
};


class Enemy :public Entity
{
public:
	int dir;
	Enemy(Texture &texture, String name, int x, int y) :Entity(texture, name, x, y)
	{
		Name = name;
		if (name == "squirell")
		{
			sprite.setTextureRect(IntRect(62, 78, 62, 61));
			sprite.setScale(0.4, 0.4);
			rect = FloatRect(x, y, 62 / 4, 61 / 4);
			dx = 0;
			health = 2;
		}
	}


	void update(float time, int dir, float positionOfHeroX, int level, std::string* map_drawing[])
	{
		if (health <= 0)
			life == false;

		if ((rect.left - positionOfHeroX > 4 * 16)||(positionOfHeroX - rect.left > 4*16)) // ворог рухається, якщо герой в межах 4-х квадратів
			dx = 0.008;
			rect.left += dx * dir * time;
		
		
		Collision(dir, level, map_drawing);
		
			curFrame += 0.005 * time;
			//if (curFrame > 2) curFrame = -1;
			if (dx * dir > 0) sprite.setTextureRect(IntRect(62, 78, -62, 61));
			if (dx * dir < 0) sprite.setTextureRect(IntRect(62, 78, 62, 61));
			if (!life) sprite.setTextureRect(IntRect(0, 67, 16, 16));

		sprite.setPosition(rect.left - offsetX, rect.top);
	}

	void Collision(int dir, int level, std::string* map_drawing[])
	{
		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				if (Name == "squirell")
				{
					if ((map_drawing[i][j] == 'k') || (map_drawing[i][j] == 'S'))
					{
						if (dx * dir > 0)
						{
							rect.left = j * 16 - rect.width; dx *= -1;
								

						}
						else if (dx * dir < 0)
						{
							rect.left = j * 16 + 16; dx *= -1;
						}
					}
				}    
			}
		
	}
};


class Bullet :public Entity
{
public:
	String Name;
	int DirOfBullet;

	Bullet(Texture& texture, String name, int x, int y, int dir) :Entity(texture, name, x, y)
	{
		Name = name;
		DirOfBullet = dir;

		if (name == "rock")
		{
			sprite.setTextureRect(IntRect(0, 140, 5, 5));
			rect = FloatRect(x, y, 5, 5);
			dx = 0.05 * DirOfBullet;
			life = true;
		}
	}

	void update(float time, std::string* map_drawing[])
	{
		rect.left += dx * time;
		rect.top += -0.02 * time;
		Collision(map_drawing);

		sprite.setPosition(rect.left - offsetX, rect.top);
	}

	void Collision(std::string* map_drawing[])
	{
		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				if (Name == "rock")
				{
					if ((map_drawing[i][j] == 'k') || (map_drawing[i][j] == 'S') || (map_drawing[i][j] == 'e'))
					{
						dx = 0;
						life = false;
					}
				}
			}
	}
};


class MovingPlatform :public Entity
{
public:
	String Name;

	MovingPlatform(Texture& texture, String name, int x, int y) :Entity(texture, name, x, y)
	{
		Name = name;

		if (name == "platform")
		{
			sprite.setTextureRect(IntRect(0, 61, 16, 16));
			rect = FloatRect(x, y, 16, 16);
			dx = 0.08;
		}
	}

	void update(float time, std::string* map_drawing[])
	{
		rect.left += dx * time;
		//rect.top += -0.02 * time;
		Collision(map_drawing);

		sprite.setPosition(rect.left - offsetX, rect.top);
	}

	void Collision(std::string* map_drawing[])
	{
		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				if (Name == "platform")
				{
					if ((map_drawing[i][j] == 'k') || (map_drawing[i][j] == 'S') || (map_drawing[i][j] == 'e'))
					{
						dx *= -1;
					}
				}
			}
	}

};