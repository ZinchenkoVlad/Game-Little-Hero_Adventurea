#pragma once

using namespace sf;


void menu(RenderWindow& window) {
	Texture menuTexture1, menuTexture2, menuTexture3, menuTexture4, aboutTexture, controlTexture, menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuTexture3.loadFromFile("images/333.png");
	menuTexture4.loadFromFile("images/444.png");
	aboutTexture.loadFromFile("images/about.png");
	controlTexture.loadFromFile("images/Menu_CONTROL.jpg");
	menuBackground.loadFromFile("images/Menu_Back_Ground.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture4), menu4(menuTexture3), about(aboutTexture), control(controlTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(50, 30);
	menu2.setPosition(50, 90);
	menu3.setPosition(50, 150);
	menu4.setPosition(50, 210);
	menuBg.setPosition(0, 0);

	

	while (isMenu)
	{
		Event event;
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menu4.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(50, 30, 190, 30).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(50, 90, 200, 30).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(50, 150, 150, 30).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 4; }
		if (IntRect(50, 210, 60, 30).contains(Mouse::getPosition(window))) { menu4.setColor(Color::Blue); menuNum = 3; }

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (menuNum == 1)
				{
					isMenu = false;
				}
				if (menuNum == 2)
				{
					window.draw(about);
					window.display();
					while (!Keyboard::isKeyPressed(Keyboard::Escape));
				}
				if (menuNum == 3)
				{
					window.close(); isMenu = false;
				}
				if (menuNum == 4)
				{
					window.draw(control);
					window.display();
					while (!Keyboard::isKeyPressed(Keyboard::Escape));
				}
			}
		}
		

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);

		window.display();
	}
}