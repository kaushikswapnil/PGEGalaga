#include"MenuHandler.h"
#include <puruGUI.h>
#include <puruGUIMenuItem.h>
#include <puruGUIText.h>
#include <puruFont.h>
#include <puruSound.h>
#include <puruSprite.h>

MenuHandler::MenuHandler(){ }
MenuHandler::~MenuHandler(){ }

void MenuHandler::LoadMainMenu(puruGUI* gui, puruFont* fnt, puruSound* snd, puruSprite* cursorspr) {
	gui->AddObject(new puruGUIMenuItem(1, fnt, snd, 400, 220, "Play"));
	gui->AddObject(new puruGUIMenuItem(2, fnt, snd, 400, 260, "Instructions"));
	gui->AddObject(new puruGUIMenuItem(3, fnt, snd, 400, 300, "Credits"));
	gui->AddObject(new puruGUIMenuItem(4, fnt, snd, 400, 340, "Exit"));
	loadGUIOptions(gui, cursorspr);
}

void MenuHandler::LoadInstructionsMenu(puruGUI *gui, puruFont *fnt, puruSound* snd, puruSprite* cursorspr) { 
	gui->AddObject(new puruGUIText(1, 400, 300, "Kill all the aliens. Avoid their bullets.", fnt));
	gui->AddObject(new puruGUIMenuItem(2, fnt, snd, 400, 400, "Back to Main Menu"));
	loadGUIOptions(gui, cursorspr);
}

void MenuHandler::LoadCreditsMenu(puruGUI *gui, puruFont *fnt, puruSound* snd, puruSprite* cursorspr) {
	gui->AddObject(new puruGUIText(1, 400, 300, "Made by Puru Kaushik.", fnt));
	gui->AddObject(new puruGUIMenuItem(2, fnt, snd, 400, 360, "Back to Main Menu"));
	loadGUIOptions(gui, cursorspr);
}

void MenuHandler::LoadGameOverMenu(puruGUI *gui, puruFont *fnt, puruSound* snd, puruSprite* cursorspr) {
	gui->AddObject(new puruGUIText(1, 400, 300, "Game Over. Press space to go back to Main Menu", fnt));
	loadGUIOptions(gui, cursorspr);
}

void MenuHandler::LoadGameWonMenu(puruGUI * gui, puruFont * fnt, puruSound* snd, puruSprite * cursorspr)
{
	puruGUIText* hgeText = new puruGUIText(1, 400, 200, "Congratulations", fnt);
	gui->AddObject(hgeText);
	puruGUIText* hgeText2 = new puruGUIText(2, 400, 300, "You have won the game.", fnt);
	gui->AddObject(hgeText2);
	puruGUIText* hgeText3 = new puruGUIText(3, 400, 400, "Press space to go back to Main Menu", fnt);
	gui->AddObject(hgeText3);
	loadGUIOptions(gui, cursorspr);
}

void MenuHandler::DeleteMainMenu(puruGUI *gui) {
	for(int i = 1; i <= 4; i++)
		gui->DelObject(i);
}

void MenuHandler::DeleteInstructionsMenu(puruGUI *gui) {
	for (int i = 1; i <= 2; i++)
		gui->DelObject(i);
}

void MenuHandler::DeleteCreditsMenu(puruGUI *gui) {
	for (int i = 1; i <= 2; i++)
		gui->DelObject(i);
}

void MenuHandler::DeleteGameOverMenu(puruGUI *gui) {
	for (int i = 1; i <= 1; i++)
		gui->DelObject(i);
}

void MenuHandler::DeleteGameWonMenu(puruGUI * gui)
{
	for (int i = 1; i <= 3; i++)
		gui->DelObject(i);
}

void MenuHandler::loadGUIOptions(puruGUI *gui, puruSprite* cursorspr) {
	gui->SetMouse(cursorspr);
	gui->SetFocus(1);
	gui->Enter();
}