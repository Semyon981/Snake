#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <SFML/Network.hpp>
#include <fstream>
#include <string>


using namespace std;
using namespace sf;

bool goplay = false;

int s1[1000][2];
int s2[1000][2];
int size1;
int size2;
int xa1;
int ya1;
int xa2;
int ya2;
int dir;
int qet = 0;

string str[250][2];
int n=0;
Text mastxt[100];
char serv[100];

int hui = 0;

int arr[1000][2];
int arrsize = 0;
Clock cl;
Time tim;

void menu(int w, int h, RenderWindow& window, int &GameType,int wx,int hy)
{
	tim = cl.getElapsedTime();


	int x = Mouse::getPosition(window).x;
	int y = Mouse::getPosition(window).y;
	Font font;
	font.loadFromFile("font.ttf");
	RectangleShape men1(Vector2f(400.f, 800.f));
	RectangleShape men2(Vector2f(400.f, 800.f));
	men1.move(wx, hy);
	men2.move(400+wx, hy);
	Text SP("SINGLE PLAYER", font);
	Text MP("MULTIPLAYER", font);
	SP.setCharacterSize(50);
	MP.setCharacterSize(50);
	SP.setPosition(18 + wx, 400 + hy);
	MP.setPosition(440 + wx, 400 + hy);
	men1.setFillColor(Color(255, 0, 0));
	men2.setFillColor(Color(0, 0, 255));
	if (!Keyboard::isKeyPressed(Keyboard::Escape)) hui = 1;
	if (Keyboard::isKeyPressed(Keyboard::Escape) && hui == 1) GameType = -1;



	



	if (x >= 400+wx && x <= 800 + wx)
	{
		
		men2.setPosition(Vector2f(wx+400, hy-10));
		men2.setSize(Vector2f(410.f, 820.f));
		SP.setCharacterSize(50);
		MP.setCharacterSize(55);
		
		MP.setPosition(437+wx, 397+hy);
		
		men2.setFillColor(Color(35, 35, 255));
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			GameType = 2;
			hui = 0;
		}
	}
	else if (x <= 400+wx && x>=wx)
	{
		
		men1.setPosition(Vector2f(wx-10, hy-10));
		men1.setSize(Vector2f(410.f, 820.f));
		SP.setCharacterSize(55);
		MP.setCharacterSize(50);
		SP.setPosition(12+wx, 397+hy);
		
		men1.setFillColor(Color(255, 35, 35));
		
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			GameType = 1;
			hui = 0;
		}		
	}
	

	if (Mouse::isButtonPressed(Mouse::Left) && (x <= wx || x >= 800+ wx))
	{
		if (x / 10 * 10 != arr[arrsize][0] && y / 10 * 10 != arr[arrsize][1])
		{
			arr[arrsize][0] = x / 10 * 10;
			arr[arrsize][1] = y / 10 * 10;
			arrsize++;
		}
	}
	window.clear(Color(0, 0, 0, 0));
	for (int i = 0;i < arrsize;i++)
	{
		RectangleShape menzm(Vector2f(10.f, 10.f));
		menzm.move(arr[i][0], arr[i][1]);
		menzm.setFillColor(Color(0, 255, 0));
		window.draw(menzm);
	}
	if (!Mouse::isButtonPressed(Mouse::Left))
	{
		if (tim.asSeconds() >= 10)
		{
			cl.restart();
			arrsize = 0;

		}
	}
	
	
	window.draw(men1);
	window.draw(men2);
	window.draw(SP);
	window.draw(MP);

}
void SORC(int w, int h, RenderWindow& window, int& GameType,int wx,int hy)
{
	if(qet == 0)
	{
		fstream file("servers.srv");
		while (getline(file, str[n][0],' '))
		{
			getline(file, str[n][1], '\n');
			n++;
		}
		qet = 1;
	}
	int x = Mouse::getPosition(window).x;
	int y = Mouse::getPosition(window).y;
	Font font;
	font.loadFromFile("font.ttf");
	RectangleShape men1(Vector2f(400.f, 800.f));
	RectangleShape men2(Vector2f(400.f, 800.f));
	men1.setFillColor(Color(255, 0, 0));
	men2.setFillColor(Color(0, 0, 255));
	men1.move(wx, hy);
	men2.move(400+wx, +hy);


	if (Keyboard::isKeyPressed(Keyboard::Escape)) GameType = 0;
	for (int i = 0;i < n;i++)
	{
		mastxt[i].setCharacterSize(30);
		mastxt[i].setFont(font);
		mastxt[i].setString(str[i][0]);
		mastxt[i].setFillColor(Color::White);
		mastxt[i].setPosition(10+wx, 30 + 50 * i+hy);
	}

	for (int i = 0;i < n;i++)
	{
		if (x < 400+wx)
		{
			if (y > 30+ i * 50+hy && y < 30 + (i + 1) * 50+hy)
			{
				mastxt[i].setCharacterSize(35);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					for (int j = 0;j < str[i][1].length();j++)
					{
						serv[j] = str[i][1][j];
					}
					str[i][1][str[i][1].length()] = '\n';
					

					qet = 0;
					GameType = 3;
				}
			}


		}
	}
	
	
	window.clear(Color(0, 0, 0, 0));
	window.draw(men1);
	window.draw(men2);
	for (int i = 0;i < n;i++)
	{
		window.draw(mastxt[i]);
	}

}
















#endif MENU_H
