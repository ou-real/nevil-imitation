#include "nevil/gui/view.hpp"

nevil::view::view(QWidget *parent)
  : Enki::ViewerWidget(new Enki::World(), parent)
  {}

nevil::view::view(nevil::trial_controller *controller, QWidget *parent)
  : Enki::ViewerWidget(controller->get_world(), parent)
  , _controller(controller)
  , _frame_number(0)
  , _skip_frame(15)
  , _pause_gui(false)
{
  pos.setX(-world->w * 1.3);
  pos.setY(-world->h * 0.5);
  altitude = world->h * 0.6;
  pitch = M_PI/5;
  yaw = -M_PI;
  startTimer(0);
}

void nevil::view::timerEvent(QTimerEvent *event)
{
  if (!_controller->run())
    QApplication::quit();

  if (_pause_gui)
    return;

  if (_frame_number == _skip_frame)
  {
    updateGL();
    _frame_number = 0;
  }
  ++_frame_number;
}

void nevil::view::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_P)
  {
    _pause_gui = !_pause_gui;
    if (_pause_gui)
      std::cout << "Pausing GUI" << std::endl;
    else
      std::cout << "Resuming GUI" << std::endl;
  }
  else if (event->key() == Qt::Key_Up)
  {
    if (_skip_frame <= 29)
      ++_skip_frame;
    _frame_number = 0;
    std::cout << "-Speeding simulation: " << _skip_frame << " skipped frames" << std::endl;
  }
  else if (event->key() == Qt::Key_Down)
  {
    if (_skip_frame >= 1)
      --_skip_frame;
    _frame_number = 0;
    std::cout << "-Slowing simulation: "<< _skip_frame <<" skipped frames "<< std::endl;
  }
}

void nevil::view::sceneCompletedHook()
{
  glColor3d(0, 0, 0);
  // Top left
  renderText(10, 15, tr("Press p to pause/unpause the gui"));
  renderText(10, 35, tr("Press Up and Down arrow keys to speed up and slow down the simulation"));

  // Top right
  renderText(10, height()-50, tr("Rotate camera by moving mouse while pressing ctrl/cmd+left mouse button"));
  renderText(10, height()-30, tr("Move camera on x/y by moving mouse while pressing ctrl/cmd+shift+left mouse button"));
  renderText(10, height()-10, tr("Move camera on z by moving mouse while pressing ctrl/cmd+shift+right mouse button"));
}
