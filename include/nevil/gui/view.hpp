#ifndef _NAME_GUI_VIEW_HPP_
#define _NAME_GUI_VIEW_HPP_

#include <iostream>
#include <QtGui>
#include <QKeyEvent>
#include <enki/viewer/Viewer.h>
#include "nevil/trial_controller.hpp"

namespace nevil
{
  class view : public Enki::ViewerWidget
  {
   public:
    view(QWidget *parent = 0);
    explicit view(nevil::trial_controller *controller, QWidget *parent = 0);
    view(const nevil::view &rhs) = delete;
    view(nevil::view &&rhs) noexcept = delete;

    virtual void timerEvent(QTimerEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void sceneCompletedHook();

    nevil::view &operator=(const nevil::view &rhs) = delete;
    nevil::view &operator=(nevil::view &&rhs) noexcept = delete;

   protected:
    nevil::trial_controller *_controller;
    int _frame_number;
    int _skip_frame;
    bool _pause_gui;
  };
}

#endif  // _NAME_GUI_VIEW_HPP_
