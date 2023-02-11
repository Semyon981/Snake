#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "menu.hpp"
#include <SFML/System.hpp>
#include <WinSock2.h>
#include <fstream>
using namespace std;
using namespace sf;


#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable: 4996)

class Zmeyka
{
public:

	int size = 1;
	int dir = 0;
	int s[1000][2];
	void key()
	{
		for (int i = size - 1;i >= 1;i--)
		{
			s[i][0] = s[i - 1][0];
			s[i][1] = s[i - 1][1];
		}
		if (dir == 1) s[0][1] -= 10;
		if (dir == 2) s[0][1] += 10;
		if (dir == 3) s[0][0] -= 10;
		if (dir == 4) s[0][0] += 10;

	}
	void key2()
	{
		if (Keyboard::isKeyPressed(Keyboard::Up) && dir !=2) dir = 1;
		else if (Keyboard::isKeyPressed(Keyboard::Down) && dir != 1) dir = 2;
		else if (Keyboard::isKeyPressed(Keyboard::Left) && dir != 4)	dir = 3;
		else if (Keyboard::isKeyPressed(Keyboard::Right) && dir != 3) dir = 4;
	}
	void drawsnake(RenderWindow& window,int wx, int hy)
	{
		for (int i = 0;i < size;i++)
		{
			RectangleShape asd(Vector2f(10.f, 10.f));
			asd.move(s[i][0]+wx, s[i][1]+hy);
			asd.setFillColor(Color(0, 255, 0));
			window.draw(asd);
		}

	}
	int appx;
	int appy;
	void appcus(int w, int h)
	{
		if (s[0][0] == appx && s[0][1] == appy)
		{
			size++;
			s[size - 1][0] = 1000;
			s[size - 1][1] = 1000;
			appx = (1 + rand() % w / 10 - 1) * 10;
			appy = (1 + rand() % h / 10 - 1) * 10;
		}
	}
private:
};


class ZmeykaEnemy
{
public:

	int size = 1;
	int s[1000][2];
	void drawsnake(RenderWindow& window)
	{
		for (int i = 0;i < size;i++)
		{
			RectangleShape asd(Vector2f(10.f, 10.f));
			asd.move(s[i][0], s[i][1]);
			asd.setFillColor(Color(0, 0, 255));
			window.draw(asd);
		}

	}

private:
};
class Apple
{
public:
	int x;
	int y;
	int size = 1;
	void drawApple(RenderWindow& window)
	{
		RectangleShape apple(Vector2f(10.f, 10.f));
		apple.move(x, y);
		apple.setFillColor(Color(255, 0, 0));
		window.clear(Color(0, 0, 0, 0));
		window.draw(apple);
	}

};

SOCKET Connection;
SOCKET ConnectionMes;
int mas[260][2];

string soobshenie[100];
string message;
string str1;
int soobsize = 0;
bool aaabbb = true;
bool bbbb = false;


void thrrecv()
{
	while(aaabbb)
	{
		if (recv(ConnectionMes, (char*)&message, sizeof(message), NULL) != SOCKET_ERROR)
		{
			soobshenie[soobsize] ="Enemy: " + message;
			soobsize++;
			bbbb = true;
		}				
	}
}






int main()
{
	srand(time(NULL));
	int width = GetSystemMetrics(SM_CXSCREEN);
	int heigh = GetSystemMetrics(SM_CYSCREEN);

	
	

	//int width = 800;
	//int heigh = 800;
	int wx = width / 2 - 400;
	int hy = heigh / 2 - 400;
	
	int GameType = 0;
	int w = 800;
	int h = 800;
	srand(time(0));
	Clock clock;
	Zmeyka zm;
	ZmeykaEnemy zme1;
	ZmeykaEnemy zme2;
	Apple ap1;
	Apple ap2;
	zm.appx = (rand() % (w / 10) - 1) * 10;
	zm.appy = (rand() % (h / 10) - 1) * 10;
	zm.s[0][0] = w / 2;
	zm.s[0][1] = h / 2;
	setlocale(LC_ALL, "ru");
	RenderWindow window(VideoMode(width, heigh), "ZMEYKA",Style::Fullscreen);
	Time time;
	
	bool bol = true;
	
	int a = 0;
	bool qazqaz = true;
	char gopl[250] = "f";
	
	char m[2];
	m[1] = 'f';
	int dirr = 0;
	
	
	WSAData WsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &WsaData) != 0)
	{
		cout << "Oops! Error code 1" << endl;
		exit(1);
	}

	

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_port = htons(50000);
	addr.sin_family = AF_INET;

	SOCKADDR_IN addr1;
	int sizeofaddr1 = sizeof(addr1);
	addr1.sin_port = htons(50001);
	addr1.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	ConnectionMes = socket(AF_INET, SOCK_STREAM, NULL);

	int pause = 0;
	
	Font font2;
	font2.loadFromFile("font2.ttf");
	Text texts1;
	Text texts2;
	texts1.setFont(font2);
	texts2.setFont(font2);
	texts1.setCharacterSize(50);
	texts2.setCharacterSize(50);
	texts1.setFillColor(Color::White);
	texts2.setFillColor(Color::White);


	Text pauza;
	pauza.setFont(font2);
	pauza.setCharacterSize(100);
	pauza.setFillColor(Color(180, 180, 180,180));
	pauza.setStyle(Text::Bold);
	int paza;


	

	
	Font font;
	font.loadFromFile("font2.ttf");

	Text text("", font, 25);
	text.setColor(Color::White);

	Clock clll;
	Time tttt;
	
	int pomogator = 0;
	
	
	bool uiu = false;
	
	bool isPassEnter = false;
	text.setPosition(25, heigh-40);


	HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thrrecv, 0, 0, NULL);
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::TextEntered && isPassEnter)
			{
				// отсекаем не ASCII символы
				if (event.text.unicode < 128)
				{
					if (static_cast<char>(event.text.unicode) != '\u0008')
						str1 += static_cast<char>(event.text.unicode);
					else if (str1.length() > 0)
						str1.pop_back();

					text.setString(String::fromUtf8(str1.begin(), str1.end()));					
				}
			}
		}
		


		
		

		


		if (GameType == 1)
		{
			
			

			if (Keyboard::isKeyPressed(Keyboard::Enter) && !isPassEnter && !uiu)
			{
				isPassEnter = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter) && isPassEnter && uiu)
			{
				if (str1.length() > 1)
				{
					soobshenie[soobsize] ="Green: "+ str1;
					soobsize += 1;
					bbbb = true;
					pomogator = 1;
					
				}
				else if(str1.length() <= 1 && pomogator == 0)
				{
					isPassEnter = false;
				}												
				str1.clear();
				text.setString("");
			}
			if (!Keyboard::isKeyPressed(Keyboard::Enter) && isPassEnter)
			{
				uiu = true;
				pomogator = 0;
			}
			else if (!Keyboard::isKeyPressed(Keyboard::Enter) && !isPassEnter)
			{
				uiu = false;			
			}
				
			



			time = clock.getElapsedTime();
			zm.key2();
			zm.appcus(w, h);
			if (time.asSeconds() >= 0.08)
			{
				time = clock.restart();
				zm.key();
			}

			
			if (Keyboard::isKeyPressed(Keyboard::Escape)) GameType = 0;


			RectangleShape pole(Vector2f(800.f, 800.f));
			pole.move(wx, hy);
			pole.setFillColor(Color(0, 0, 0));


			RectangleShape apple(Vector2f(10.f, 10.f));
			apple.move(zm.appx+wx, zm.appy + hy);
			apple.setFillColor(Color(255, 0, 0));
			window.clear(Color(50, 50, 50, 0));
			
			window.draw(pole);
			if (isPassEnter)
			{
				
				RectangleShape tixt(Vector2f(250, 33));
				tixt.move(25, heigh - 40);
				tixt.setFillColor(Color(0, 0, 0));
				window.draw(tixt);

				int j = 0;
				for (int i = soobsize-1; i >= 0;i--)
				{
					Text texx(soobshenie[i], font, 20);
					texx.setFillColor(Color(255, 255, 255));
					texx.setPosition(10, heigh - 70 - (20*j));
					window.draw(texx);
					j++;
				}
			}
			else 
			{
				if (soobsize > 0)
				{
					if (bbbb)
					{
						clll.restart();
						bbbb = false;
					}
					tttt = clll.getElapsedTime();					
					if (tttt.asSeconds() < 5)
					{					
						Text texx(soobshenie[soobsize-1], font, 20);
						texx.setFillColor(Color(255, 255, 255));
						texx.setPosition(10, heigh - 70);
						window.draw(texx);								
					}
				}
			}



			window.draw(text);
			window.draw(apple);

			zm.drawsnake(window,wx,hy);
			if (zm.s[0][0] >= w || zm.s[0][0] < 0 || zm.s[0][1] >= h || zm.s[0][1] < 0)
			{
				zm.dir = 0;
				zm.size = 1;
				zm.s[0][0] = w / 2;
				zm.s[0][1] = h / 2;
			}
			for (int i = 1;i <= zm.size;i++)
			{
				if (zm.s[0][0] == zm.s[i][0] && zm.s[0][1] == zm.s[i][1])
				{
					zm.dir = 0;
					zm.size = 1;
					zm.s[0][0] = w / 2;
					zm.s[0][1] = h / 2;
				}
			}
		}
		else if (GameType == -1)
		{

			return 0;

		}
		else if (GameType == 0)
		{

			menu(width, heigh, window, GameType,wx,hy);
		
		}
		else if (GameType == 2)
		{
			if (a == 0)
			{
				time = clock.restart();
				a = 1;
			}
			time = clock.getElapsedTime();

			if (time.asMilliseconds() >= 100)
			{
				SORC(width, heigh, window, GameType,wx,hy);
			}

		}
		else if (GameType == 3)
		{

		
			if (Keyboard::isKeyPressed(Keyboard::Escape)) GameType = 0;

			if (gopl[0] == 't')
			{				

				if (Keyboard::isKeyPressed(Keyboard::Enter) && !isPassEnter && !uiu)
				{
					isPassEnter = true;
				}
				if (Keyboard::isKeyPressed(Keyboard::Enter) && isPassEnter && uiu)
				{
					if (str1.length() > 1)
					{
						send(ConnectionMes, (char*)&str1, sizeof(str1), NULL);

						soobshenie[soobsize] = "Sexy boy: " + str1;
						soobsize += 1;
						bbbb = true;
						pomogator = 1;

					}
					else if (str1.length() <= 1 && pomogator == 0)
					{
						isPassEnter = false;
					}
					str1.clear();
					text.setString("");
				}
				if (!Keyboard::isKeyPressed(Keyboard::Enter) && isPassEnter)
				{
					uiu = true;
					pomogator = 0;
				}
				else if (!Keyboard::isKeyPressed(Keyboard::Enter) && !isPassEnter)
				{
					uiu = false;
				}



				time = clock.getElapsedTime();
				if (Keyboard::isKeyPressed(Keyboard::Up) && dirr != 2)
				{
					dirr = 1;

				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) && dirr != 1)
				{
					dirr = 2;

				}
				else if (Keyboard::isKeyPressed(Keyboard::Left) && dirr != 4)
				{
					dirr = 3;

				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) && dirr != 3)
				{
					dirr = 4;
					
				}
				if (Keyboard::isKeyPressed(Keyboard::F9) && pause == 0)
				{
					pause = 1;
					if (m[1] == 'f')
					{
						m[1] = 't';
					}
					else if (m[1] == 't')
					{
						m[1] = 'f';
					}

				}
				else if (!Keyboard::isKeyPressed(Keyboard::F9) && pause == 1)
				{
					pause = 0;
				}

				m[0] = dirr;
				


				send(Connection, m, sizeof(m), NULL);
				recv(Connection, (char*)&mas, sizeof(mas), NULL);

				zme1.size = mas[0][0];
				zme2.size = mas[0][1];

				for (int i = 1;i <= zme1.size;i++)
				{
					zme1.s[i - 1][0] = mas[i][0];
					zme1.s[i - 1][1] = mas[i][1];
				}
				for (int i = zme1.size + 1;i <= zme1.size + zme2.size + 1;i++)
				{
					zme2.s[i - zme1.size - 1][0] = mas[i][0];
					zme2.s[i - zme1.size - 1][1] = mas[i][1];
				}


				ap1.x = mas[zme1.size + zme2.size + 2][0];
				ap1.y = mas[zme1.size + zme2.size + 2][1];
				ap2.x = mas[zme1.size + zme2.size + 3][0];
				ap2.y = mas[zme1.size + zme2.size + 3][1];
				ap1.size = mas[zme1.size + zme2.size + 4][0];
				ap2.size = mas[zme1.size + zme2.size + 4][1];
				paza = mas[zme1.size + zme2.size + 5][0];

				texts1.setString(to_string(zme1.size));
				texts2.setString(to_string(zme2.size));
				if (zme1.size <= 9)
				{
					texts1.setPosition(Vector2f(wx - 25, hy));
				}
				else if (zme1.size >= 10 && zme1.size <= 99)
				{
					texts1.setPosition(Vector2f(wx - 50, hy));
				}
				else if (zme1.size >= 100 && zme1.size <= 999)
				{
					texts1.setPosition(Vector2f(wx - 75, hy));
				}

				texts2.setPosition(Vector2f(wx + 800, hy));

				RectangleShape apple(Vector2f(10.f, 10.f));
				apple.move(ap1.x+wx, ap1.y+hy);

				if (ap1.size == 1)
					apple.setFillColor(Color(0, 255, 0));
				else
					apple.setFillColor(Color(255, 255, 0));


				RectangleShape apple2(Vector2f(10.f, 10.f));
				apple2.move(ap2.x+wx, ap2.y+hy);


				if (ap2.size == 1)
					apple2.setFillColor(Color(0, 255, 0));
				else
					apple2.setFillColor(Color(255, 255, 0));


				RectangleShape pole(Vector2f(800.f, 800.f));
				pole.move(wx, hy);
				pole.setFillColor(Color(0, 0, 0));




				window.clear(Color(50, 50, 50, 0));				
				window.draw(pole);


				if (isPassEnter)
				{

					RectangleShape tixt(Vector2f(250, 33));
					tixt.move(25, heigh - 40);
					tixt.setFillColor(Color(0, 0, 0));
					window.draw(tixt);

					int j = 0;
					for (int i = soobsize - 1; i >= 0;i--)
					{
						Text texx(soobshenie[i], font, 20);
						texx.setFillColor(Color(255, 255, 255));
						texx.setPosition(10, heigh - 70 - (20 * j));
						window.draw(texx);
						j++;
					}
				}
				else
				{
					if (soobsize > 0)
					{
						if (bbbb)
						{
							clll.restart();
							bbbb = false;
						}
						tttt = clll.getElapsedTime();
						if (tttt.asSeconds() < 5)
						{
							Text texx(soobshenie[soobsize - 1], font, 20);
							texx.setFillColor(Color(255, 255, 255));
							texx.setPosition(10, heigh - 70);
							window.draw(texx);
						}
					}
				}

				window.draw(texts1);
				window.draw(texts2);
				window.draw(text);
				window.draw(apple);
				window.draw(apple2);
				
				


				for (int i = 0;i < zme1.size;i++)
				{
					RectangleShape asd(Vector2f(10.f, 10.f));
					asd.move(zme1.s[i][0]+wx, zme1.s[i][1]+hy);
					asd.setFillColor(Color(255, 0, 0));
					window.draw(asd);
				}

				for (int i = 0;i < zme2.size;i++)
				{
					RectangleShape asd1(Vector2f(10.f, 10.f));
					asd1.move(zme2.s[i][0]+wx, zme2.s[i][1]+hy);
					asd1.setFillColor(Color(0, 0, 255));
					window.draw(asd1);
				}

				if (paza == 4)
				{
					
					pauza.setString("PAUSE");
					pauza.setPosition(width/2-160, heigh/2-50);
					window.draw(pauza);
				}
				else if (paza == 3)
				{
					
					pauza.setString("3");
					pauza.setPosition(width / 2 - 50, heigh / 2-50);
					window.draw(pauza);
				}
				else if (paza == 2)
				{
					
					pauza.setString("2");
					pauza.setPosition(width / 2 - 50, heigh / 2 - 50);
					window.draw(pauza);
				}
				else if (paza == 1)
				{
					
					pauza.setString("1");
					pauza.setPosition(width / 2 - 50, heigh / 2 - 50);
					window.draw(pauza);
				}
				

			}
			else
			{
				Font font;
				font.loadFromFile("font.ttf");
				RectangleShape men1(Vector2f(400.f, 800.f));
				RectangleShape men2(Vector2f(400.f, 800.f));
				men1.move(wx, hy);
				men2.move(400+wx, hy);
				Text vait("WAITIND FOR THE SECOND PLAYER...", font);

				vait.setCharacterSize(50);
				vait.setPosition(10+wx, 400+hy);
				men1.setFillColor(Color(255, 0, 0));
				men2.setFillColor(Color(0, 0, 255));

				window.clear(Color(0, 0, 0, 0));
				window.draw(men1);
				window.draw(men2);
				window.draw(vait);

				window.display();
			}


			if (qazqaz)
			{
				addr.sin_addr.s_addr = inet_addr(serv);
				addr1.sin_addr.s_addr = inet_addr(serv);

				
				if (connect(ConnectionMes, (SOCKADDR*)&addr1, sizeof(addr1)) != 0) {
					std::cout << "Error: failed connect to server.\n";
					return 1;
				}
				cout << "Connected!\n";
				qazqaz = false;
				recv(Connection, gopl, sizeof(gopl), NULL);
				cout << gopl << endl;
			}

		}
		else if (GameType == 4)
		{
			

		}

		window.display();
	}
	aaabbb = false;
	WaitForSingleObject(thread, INFINITE);
	CloseHandle(thread);

	return 0;
}
