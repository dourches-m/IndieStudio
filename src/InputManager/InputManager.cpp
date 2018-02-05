//
// InputManager.cpp for cpp_indie_studio in /home/baldas/Prog/repos/tek2/cpp/cpp_indie_studio/src/InputManager
// 
// Made by Hugo Baldassin
// Login   <baldas@epitech.net>
// 
// Started on  Thu Jun  1 11:31:49 2017 Hugo Baldassin
// Last update Sun Jun 18 17:54:58 2017 Hugo Willaume
//

#include <chrono>
#include "InputManager.hpp"

game::InputManager::InputManager():
  inputLinker(NULL, false),
  _inputManager(nullptr),
  _keyboard(nullptr),
  _mouse(nullptr),
  _window(nullptr)
{
}

void game::InputManager::launch(Ogre::RenderWindow *window, Ogre::Root *root, bool keyboard,
				bool sticks, bool buffered, game::EntitiesManager *entities)
{
  OIS::ParamList pl;
  size_t windowHnd = 0;
  std::ostringstream windowHndStr;

  _entities = entities;
  Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
  window->getCustomAttribute("WINDOW", &windowHnd);
  windowHndStr << windowHnd;
  pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
  _inputManager = OIS::InputManager::createInputSystem(pl);
  _mouse = static_cast<OIS::Mouse*>(_inputManager->createInputObject(OIS::OISMouse, buffered));
  _mouse->setEventCallback(this);
  if (keyboard)
  {
    _keyboard = static_cast<OIS::Keyboard*>(_inputManager->createInputObject(OIS::OISKeyboard, buffered));
    _keyboard->setEventCallback(this);
  }
  if (sticks)
  {
    for (int i = 0; i < _inputManager->getNumberOfDevices(OIS::OISJoyStick); ++i)
    {
      _sticks.push_back(static_cast<OIS::JoyStick*>(_inputManager->createInputObject(OIS::OISJoyStick, buffered)));
      _sticks.back()->setEventCallback(this);
    }
    _sticksStates.resize(_sticks.size());
  }
  _window = window;
  root->addFrameListener(this);
  Ogre::WindowEventUtilities::addWindowEventListener(_window, this);
  windowResized(window);
}

// -----------------------------------------------------------------------------
game::InputManager::~InputManager()
{
  delete _keyboard;
  delete _mouse;
  for (auto it: _sticks)
    delete it;
  Ogre::WindowEventUtilities::removeWindowEventListener(_window, this);
}

// -----------------------------------------------------------------------------
void game::InputManager::capture()
{
  _mouse->capture();
  if (_keyboard)
    _keyboard->capture();
  if (_sticks.size())
    for (auto it: _sticks)
      it->capture();
}

// -----------------------------------------------------------------------------
bool game::InputManager::keyPressed(const OIS::KeyEvent &ke)
{
  inputLinker.sendKeyboardEvent(ke);
  return true;
}

// -----------------------------------------------------------------------------
bool game::InputManager::keyReleased(const OIS::KeyEvent &ke)
{
  inputLinker.sendKeyboardEvent(ke);
  return true;
}

// -----------------------------------------------------------------------------
bool game::InputManager::buttonPressed(const OIS::JoyStickEvent &evt, int button)
{
  unsigned int i;

  updateSticksStates();
  (void)evt;
  for (i = 0; i < _sticks.size(); ++i)
    {
      if (_sticksStates[i].mButtons[button])
	inputLinker.sendStickButtonEvent(i, button);
    }
    return true;
}

// -----------------------------------------------------------------------------
bool game::InputManager::buttonReleased(const OIS::JoyStickEvent &evt, int id)
{
  (void)evt;
  (void)id;
  return true;
}

// -----------------------------------------------------------------------------
bool game::InputManager::axisMoved(const OIS::JoyStickEvent &, int )
{
  unsigned int i;
  AMovableEntity::e_action dir;

  updateSticksStates();
  for (i = 0; i < _sticks.size(); ++i)
    if ((dir = getStickDirection(_sticksStates[i].mAxes[0], _sticksStates[i].mAxes[1])) != -1)
      inputLinker.sendStickAxisEvent(i, dir);
  return true;
}

// -----------------------------------------------------------------------------
bool game::InputManager::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
  if (_menuManager->isingame)
  {
    int alives = 0;
    for (auto it: _entities->players)
    {
      if (!it->isDead())
	alives++;
    }
    if (alives <= 1)
      return false;
  }
  capture();
  if (!_menuManager->pause)
  {
    inputLinker.setPlaying(!_menuManager->pause);
    if (_menuManager->play)
    {
      inputLinker.initPlayersMaps();
      _menuManager->play = false;
    }
    _entities->phys_act(fe.timeSinceLastFrame);
    _entities->animate(fe.timeSinceLastFrame);
  }
  else
    inputLinker.setPlaying(false);
  if (_window->isClosed() || _menuManager->stop)
    return false;
  return true;
}

// -----------------------------------------------------------------------------
void game::InputManager::windowClosed(Ogre::RenderWindow *rw)
{
  if(rw == _window)
  {
    if(_inputManager)
    {
      _inputManager->destroyInputObject(_keyboard);
      _inputManager->destroyInputObject(_mouse);
      _mouse = nullptr;
      _keyboard = nullptr;
      for (unsigned int i = 0; i < _sticks.size(); ++i)
	_inputManager->destroyInputObject(_sticks[i]);
      _sticks.resize(0);
      OIS::InputManager::destroyInputSystem(_inputManager);
      _inputManager = 0;
    }
  }
}

// -----------------------------------------------------------------------------
void game::InputManager::windowResized(Ogre::RenderWindow *rw)
{
  unsigned int width, height, depth;
  int left, top;
  rw->getMetrics(width, height, depth, left, top);

  const OIS::MouseState &ms = _mouse->getMouseState();
  ms.width = width;
  ms.height = height;
}

// -----------------------------------------------------------------------------
game::AMovableEntity::e_action game::InputManager::getStickDirection(const OIS::Axis &axisX,
								     const OIS::Axis &axisY)
{
  if (axisY.abs < -28000 && axisX.abs > -10000 && axisX.abs < 10000)
    return AMovableEntity::MOVE_UP;
  if (axisY.abs > 28000 && axisX.abs > -10000 && axisX.abs < 10000)
    return AMovableEntity::MOVE_DOWN;
  if (axisX.abs > 28000 && axisY.abs > -10000 && axisY.abs < 10000)
    return AMovableEntity::MOVE_RIGHT;
  if (axisX.abs < -28000 && axisY.abs > -10000 && axisY.abs < 10000)
    return AMovableEntity::MOVE_LEFT;
  return AMovableEntity::e_action::NO_MOVE;
}

// -----------------------------------------------------------------------------
void game::InputManager::updateSticksStates()
{
  for (unsigned int i = 0; i < _sticks.size(); ++i)
    _sticksStates[i] = _sticks[i]->getJoyStickState();
}

// -----------------------------------------------------------------------------
bool game::InputManager::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{

  if (_menuManager->actualMenu == "MainMenu")
  {
    if (_menuManager->_sdkTrayManagers[0]->injectMouseDown(evt, id))
      return true;
  }
  else if (_menuManager->actualMenu == "GameMenu")
  {
    if (_menuManager->_sdkTrayManagers[1]->injectMouseDown(evt, id))
      return true;
  }
  else if (_menuManager->actualMenu == "PauseMenu")
  {
    if (_menuManager->_sdkTrayManagers[2]->injectMouseDown(evt, id))
      return true;
  }
  return true;
}

// -----------------------------------------------------------------------------
bool game::InputManager::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
  if (_menuManager->actualMenu == "MainMenu")
  {
    if (_menuManager->_sdkTrayManagers[0]->injectMouseUp(evt, id))
      return true;
  }
  else if (_menuManager->actualMenu == "GameMenu")
  {
    if (_menuManager->_sdkTrayManagers[1]->injectMouseUp(evt, id))
      return true;
  }
  else if (_menuManager->actualMenu == "PauseMenu")
  {
    if (_menuManager->_sdkTrayManagers[2]->injectMouseUp(evt, id))
      return true;
  }
  return true;
}

// -----------------------------------------------------------------------------
bool game::InputManager::mouseMoved(const OIS::MouseEvent &evt)
{
  if (_menuManager->actualMenu == "MainMenu")
  {
    if (_menuManager->_sdkTrayManagers[0]->injectMouseMove(evt))
      return true;
  }
  else if (_menuManager->actualMenu == "GameMenu")
  {
    if (_menuManager->_sdkTrayManagers[1]->injectMouseMove(evt))
      return true;
  }
  else if (_menuManager->actualMenu == "PauseMenu")
  {
    if (_menuManager->_sdkTrayManagers[2]->injectMouseMove(evt))
      return true;
  }
  return true;
}

// -----------------------------------------------------------------------------
OIS::Keyboard *game::InputManager::getKeyboard() const
{
  return _keyboard;
}

// -----------------------------------------------------------------------------
OIS::Mouse *game::InputManager::getMouse() const
{
  return _mouse;
}

void game::InputManager::setMenuManager(MenuManager *menuManager)
{
  _menuManager = menuManager;
}
