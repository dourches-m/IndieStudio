//
// InputManager.hpp for indie_studio in /home/hurlu/rendu/
//
// Made by Hugo Willaume
// Login   <hugo.willaume@epitech.eu>
//
// Started on  Wed May 31 16:43:16 2017 Hugo Willaume
// Last update Fri Jun 16 10:42:14 2017 Hugo Willaume
//


#ifndef                INDIE_InputManager_HPP
# define               INDIE_InputManager_HPP

# include 		<OGRE/Ogre.h>
# include 		<OIS/OISJoyStick.h>
# include 		"OIS/OIS.h"
# include		"InputLinker.hpp"
# include		"EntitiesManager.hpp"
# include		"MenuManager.hpp"

namespace game
{

  class InputManager : public OIS::KeyListener, public OIS::JoyStickListener, public OIS::MouseListener,
		       public Ogre::FrameListener, public Ogre::WindowEventListener
  {
  public:
    InputManager();
    ~InputManager();

    void launch(Ogre::RenderWindow *window, Ogre::Root *root, bool keyboard,
		bool sticks, bool buffered, EntitiesManager *entities);
    void capture();

    // WindowEvents Callbacks
    void windowClosed(Ogre::RenderWindow* rw);
    void windowResized(Ogre::RenderWindow* rw);

    // Getters
    OIS::Keyboard *getKeyboard() const;
    OIS::Mouse *getMouse() const;

    void setMenuManager(MenuManager *menuManager);

    InputLinker inputLinker;
  private:
    // Keyboard Callbacks
    bool keyPressed(const OIS::KeyEvent& ke);
    bool keyReleased(const OIS::KeyEvent& ke);

    // Joystick Callbacks
    bool buttonPressed(const OIS::JoyStickEvent &arg, int button);
    bool buttonReleased(const OIS::JoyStickEvent &arg, int button);
    bool axisMoved(const OIS::JoyStickEvent &arg, int axis);

    // Mouse Callbacks
    bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
    bool mouseMoved(const OIS::MouseEvent& evt);

    void updateSticksStates();

    // FrameRendering function
    bool frameRenderingQueued(const Ogre::FrameEvent& fe) override;

    game::AMovableEntity::e_action getStickDirection(const OIS::Axis &axisX, const OIS::Axis &axisY);

    OIS::InputManager *_inputManager;
    OIS::Keyboard *_keyboard;
    std::vector<OIS::JoyStick*> _sticks;
    OIS::Mouse *_mouse;
    Ogre::RenderWindow *_window;
    std::vector<OIS::JoyStickState> _sticksStates;
    EntitiesManager	*_entities;
    MenuManager *_menuManager;
  };
}
#endif                /* !INDIE_InputManager_HPP */
