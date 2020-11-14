#include "StartWindow.h""

StartWindow::StartWindow() {

}

StartWindow::~StartWindow() {

}

void StartWindow::runWindow() {
	window.create(sf::VideoMode(400, 300), "Mill Game Options");
}