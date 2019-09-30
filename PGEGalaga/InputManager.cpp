#include "stdafx.h"
#include "InputManager.h"
#include"GameStateManager.h"
#include"Input_KeyEvent.h"
#include <strsafe.h>
#include <PuruGameSystem.h>

InputManager* InputManager::m_inputManagerInstance{ nullptr };

InputManager::InputManager() : Publisher(), Singleton(), m_pge(nullptr)
{
}

InputManager * InputManager::GetInstance()
{
	if (!m_inputManagerInstance) {
		m_cs.Lock();
		if(!m_inputManagerInstance)
			m_inputManagerInstance = new InputManager();
		m_cs.Unlock();
	}
	return m_inputManagerInstance;
}

InputManager::~InputManager()
{
	ShutDown();
	m_pressedKeys.clear();
}

void InputManager::DestroyInstance()
{
	if (m_inputManagerInstance)
		delete m_inputManagerInstance;
	m_inputManagerInstance = nullptr;
}

void InputManager::ShutDown()
{
	if (m_bStart) {
		m_bStart = false;
		WaitForSingleObject(m_handleInputThread, INFINITE);
		CloseHandle(m_handleInputThread);
	}
}

bool InputManager::Initiate(PuruGameSystem* _pge)
{
	m_pge = _pge;
	if (!m_pge)
	{
		return false;
	}
	m_handleInputThread = CreateThread(NULL, 0, GetInputThread, this, 0, NULL);
	if (!m_handleInputThread)
	{
		return false;
	}
	return true;
}

DWORD InputManager::GetInputThread(LPVOID lpParam)
{
	InputManager* inputManager = (InputManager*)lpParam;
	while (inputManager->m_bStart) {
		
		if (InputManager::GetInstance()->m_pge->Input_IsKeyDown(PGEK_ESCAPE)) {
			inputManager->m_pressedKeys[PGEK_ESCAPE] = true;
			Input_KeyEvent keyEvent(PGEK_ESCAPE, true);
			inputManager->PublishEvent(&keyEvent);
		}


		if (InputManager::GetInstance()->m_pge->Input_IsKeyDown(PGEK_LEFTARROW)) {
			if (inputManager->m_pressedKeys.find(PGEK_LEFTARROW) == inputManager->m_pressedKeys.end()) {
				inputManager->m_pressedKeys[PGEK_LEFTARROW] = true;
				Input_KeyEvent keyEvent(PGEK_LEFTARROW, true);
				inputManager->PublishEvent(&keyEvent);
			}
			else if (inputManager->m_pressedKeys[PGEK_LEFTARROW] == false) {
				inputManager->m_pressedKeys[PGEK_LEFTARROW] = true;
				Input_KeyEvent keyEvent(PGEK_LEFTARROW, true);
				inputManager->PublishEvent(&keyEvent);
			}
		}
		else {
			if (inputManager->m_pressedKeys.find(PGEK_LEFTARROW) != inputManager->m_pressedKeys.end()) {
				if (inputManager->m_pressedKeys[PGEK_LEFTARROW] == true) {
					inputManager->m_pressedKeys[PGEK_LEFTARROW] = false;
					Input_KeyEvent keyEvent(PGEK_LEFTARROW, false);
					inputManager->PublishEvent(&keyEvent);
				}
			}
		}

		if (InputManager::GetInstance()->m_pge->Input_IsKeyDown(PGEK_RIGHTARROW)) {
			if (inputManager->m_pressedKeys.find(PGEK_RIGHTARROW) == inputManager->m_pressedKeys.end()) {
				inputManager->m_pressedKeys[PGEK_RIGHTARROW] = true;
				Input_KeyEvent keyEvent(PGEK_RIGHTARROW, true);
				inputManager->PublishEvent(&keyEvent);
			}
			else if (inputManager->m_pressedKeys[PGEK_RIGHTARROW] == false) {
				inputManager->m_pressedKeys[PGEK_RIGHTARROW] = true;
				Input_KeyEvent keyEvent(PGEK_RIGHTARROW, true);
				inputManager->PublishEvent(&keyEvent);
			}
		}
		else {
			if (inputManager->m_pressedKeys.find(PGEK_RIGHTARROW) != inputManager->m_pressedKeys.end()) {
				if (inputManager->m_pressedKeys[PGEK_RIGHTARROW] == true) {
					inputManager->m_pressedKeys[PGEK_RIGHTARROW] = false;
					Input_KeyEvent keyEvent(PGEK_RIGHTARROW, false);
					inputManager->PublishEvent(&keyEvent);
				}
			}
		}

		if (InputManager::GetInstance()->m_pge->Input_IsKeyDown(PGEK_SPACE)) {
			inputManager->m_pressedKeys[PGEK_SPACE] = true;
			Input_KeyEvent keyEvent(PGEK_SPACE, true);
			inputManager->PublishEvent(&keyEvent);
		}
		else
			inputManager->m_pressedKeys[PGEK_SPACE] = false;

	}
	return 0;
}

void InputManager::SetStart(bool _start)
{
	m_bStart = _start;
}

void InputManager::PublishEvent(Event * _event)
{
	/*int j = m_subscriber.size();*/
	unsigned int i = 0;
	while (i < m_subscriber.size()) {
		(m_subscriber.at(i))->ListenToEvent(_event);
		++i;
	}
}

void InputManager::AddSubscriber(Subscriber * _subscriber)
{
	m_cs.Lock();
	std::vector<Subscriber*>::iterator itSubscriber;
	itSubscriber = std::find(m_subscriber.begin(), m_subscriber.end(), _subscriber);
	if (itSubscriber == m_subscriber.end())
		m_subscriber.push_back(_subscriber);
	m_cs.Unlock();
}

void InputManager::RemoveSubscriber(Subscriber * _subscriber)
{
	m_cs.Lock();
	std::vector<Subscriber*>::iterator itSubscriber;
	itSubscriber = std::find(m_subscriber.begin(), m_subscriber.end(), _subscriber);
	if (itSubscriber != m_subscriber.end()) {
		itSubscriber = m_subscriber.erase(itSubscriber);
	}
	m_cs.Unlock();
}
