#pragma once

using namespace sf;

class LifeBar
{
public:
	Image image;
	Texture t;
	Sprite s;
	int max;
	RectangleShape bar;
	LifeBar()
	{
		image.loadFromFile("images/life1.png");
		t.loadFromImage(image);
		s.setTexture(t);
		s.setTextureRect(IntRect(0, 0, 84, 15));
		bar.setFillColor(Color(0, 0, 0));//черный прямоугольник накладывается сверху и появляется эффект отсутствия здоровья
		max = 100;
	}
	void update(int damage, float positionOfHeroX, float positionOfHeroY)
	{
		if (damage > 0)
			if (damage < max)
				bar.setSize(Vector2f(-((max - damage) * 70 / max)+3, 8));
		s.setPosition(positionOfHeroX - offsetX - 165, 0);
		bar.setPosition(positionOfHeroX - offsetX -84, 3);
		if ((offsetX <= -250) || (offsetX >= 208))
		{
			s.setPosition(250, 0);
			bar.setPosition(331, 3);
		}
			
	}
	void draw(RenderWindow& window)
	{
		window.draw(s);
		window.draw(bar);
	}
};