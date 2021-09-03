#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class TicTacToe{
 private:
	sf::Texture boardTexture;
	sf::Sprite board;
	sf::Texture nothingTexture;
	sf::Texture oTexture;
	sf::Texture redOTexture;
	sf::Texture xTexture;
	sf::Texture redXTexture;
	sf::Texture xInSquareTexture;
	sf::Texture oInSquareTexture;
	sf::Sprite square;
	sf::Sprite fields[9];
	sf::Texture restartTexture;
	sf::Sprite restart;
	sf::Font font;
	sf::Text text;
	sf::Text restartText;
	int cntMoves;
	char taken[9];
	char turn;
	void restartTheGame();
	void changeColour(int);
	bool check(int,int,int);
	bool hasWon();
	void makeMove(int);
	void mouseButtonPressed(sf::Vector2f coordinates);
	void setFieldsCordinates();
	void loadGraphics();
	void startTheGame();
 public:	
	TicTacToe(){
		loadGraphics();
		startTheGame();	
	}
	~TicTacToe(){	
	}
};
void TicTacToe::restartTheGame(){
	loadGraphics();
}
void TicTacToe::changeColour(int id){
	if(taken[id] == 'O')
		fields[id].setTexture(redOTexture);
	else
		fields[id].setTexture(redXTexture);
}
bool TicTacToe::check(int id1, int id2, int id3){
	if(taken[id1] == taken[id2] && taken[id2] == taken[id3] && taken[id1] != -1){
		changeColour(id1);
		changeColour(id2);
		changeColour(id3);
		return 1;
	}
	return 0;
}
bool TicTacToe::hasWon(){
	/*  0 1 2
		3 4 5
		6 7 8  */
	for(int i = 0; i < 9; i += 3)
		if(check(i,i+1,i+2))
			return 1;
	for(int i = 0; i < 3; i++)
		if((check(i,i+3,i+6)))
			return 1;
	if((check(0,4,8)) || (check(2,4,6)))
		return 1;
	return 0;
}
void TicTacToe::makeMove(int id){
	if(turn == 'W')
		return;
	taken[id] = turn;
	
	if(turn == 'X'){
		fields[id].setTexture(xTexture);
		turn = 'O';
	}
	else{
		fields[id].setTexture(oTexture);
		turn = 'X';
	}
	cntMoves++;
	if(hasWon()){
		turn = 'W';
		text.setString("The winner is");
		text.setPosition(45,80);
		text.setCharacterSize(35);
		square.scale(0.5,0.5);
		square.setPosition(310,83);
	}
	else if(cntMoves == 9){
		turn = 'D';
		text.setString("Draw");
		text.setPosition(80,60);
	}
	else if(turn == 'O')
		square.setTexture(oInSquareTexture);
	else
		square.setTexture(xInSquareTexture);
}
void TicTacToe::mouseButtonPressed(sf::Vector2f coordinates){
	for(int i = 0; i < 9; i++)
		if(fields[i].getGlobalBounds().contains(coordinates) && taken[i] == -1){
			makeMove(i);
			break;
		}
	if(restart.getGlobalBounds().contains(coordinates))
		restartTheGame();
}
void TicTacToe::setFieldsCordinates(){
	for(int i = 0; i < 9; i++){
		int timesX = i - (i / 3) * 3; 
		float przesun = 133.3;
		float x = 5 + (float)timesX * przesun;
		int timesY = i / 3;
		float y = 200 + 5 + (float)timesY * przesun; 
		fields[i].setTexture(nothingTexture);
		fields[i].setPosition(x,y);
	}
}
void TicTacToe::loadGraphics(){
	turn = 'O';
	cntMoves = 0;
	for(int i = 0; i < 9; i++)
		taken[i] = -1;
	square.setScale(1.0,1.0);

	boardTexture.loadFromFile("Resources/board.png");
	board = sf::Sprite(boardTexture);
	board.setPosition(0,200);

	nothingTexture.loadFromFile("Resources/nothing.png");

	oTexture.loadFromFile("Resources/O.png");
	redOTexture.loadFromFile("Resources/redO.png");
	xTexture.loadFromFile("Resources/X.png");
	redXTexture.loadFromFile("Resources/redX.png");

	oInSquareTexture.loadFromFile("Resources/OInSquare.png");
	xInSquareTexture.loadFromFile("Resources/XInSquare.png");
	square.setTexture(oInSquareTexture);
	square.setPosition(270,70);

	font.loadFromFile("Resources/youngserif.regular.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setString("Turn");
	text.setCharacterSize(80);
	text.setPosition(30,60);
	
	restartTexture.loadFromFile("Resources/restart.png");
	restart.setTexture(restartTexture);
	restart.setScale(1,0.3);
	restartText.setFont(font);
	restartText.setString("Restart");
	restartText.setFillColor(sf::Color::Black);
	restartText.setPosition(175,5);
	restartText.setCharacterSize(15);
	setFieldsCordinates();

}
void TicTacToe::startTheGame(){
	int cnt = 0;
	sf::RenderWindow window(sf::VideoMode(400,600), "TicTacToe");
	
	window.setVerticalSyncEnabled(true);
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				window.close();
			else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))  
				mouseButtonPressed(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		}
		
		window.clear(sf::Color(255,255,255));
		
		window.draw(restart);
		window.draw(board);

		for(int i = 0; i < 9; i++)
			window.draw(fields[i]);
		window.draw(restartText);
		window.draw(text);
		if(turn != 'D')
			window.draw(square);

		window.display();
	}
}

int main(){
	TicTacToe();
	return 0;
}


