#include "PadData.hpp"

namespace pad {

  PadUI::PadUI(const uint8_t event_num):
    id_{event_num}
  {

  }

  uint8_t PadUI::getID() { return this->id_; }


  Button::Button(const uint8_t event_num):
    PadUI(event_num)
  {
    this->state_  = button_state::OFF;
    this->action_ = ButtonAction::None;
  }

  Button& Button::get() { return *this; }

  void Button::setState(bool state) {
    this->state_ = state;
  }

  void Button::setAction(ButtonAction action) {
    this->action_ = action;
  } 

  void Button::setEvent(ButtonEvent event) {
    ButtonAction action;

    switch (event.state) {
      case (button_state::OFF): action = ButtonAction::Release; break;
      case (button_state::ON):  action = ButtonAction::Push;    break;
    }

    this->state_  = event.state;
    this->action_ = action;
  }

  void Button::setEvent(bool state, ButtonAction action) {
    this->state_  = state;
    this->action_ = action; 
  }

  bool Button::pressed() { return this->state_; }

  bool Button::pushed() {
    if (this->action_ == ButtonAction::Push) 
      return true;
    else
      return false;
  }

  bool Button::released() {
    if (this->action_ == ButtonAction::Release) 
      return true;
    else 
      return false;
  }


  Axis::Axis(const uint8_t event_num):
    PadUI(event_num)
  {
    this->value_ = 0;
  }

  Axis& Axis::get() { return *this; }

  void Axis::setValue(int value) { this->value_ = value; }

  int Axis::getValue() { return this->value_; }



  TriggerButton::TriggerButton(uint8_t b_event_num, uint8_t a_event_num): 
    Button(b_event_num),
    depth_{a_event_num}
  {

  }

  int TriggerButton::getDepth() { return this->depth_.getValue(); }

  Axis& TriggerButton::getTriggerAxis() { return this->depth_.get(); }



  Stick::Stick(uint8_t x_event_num, uint8_t y_event_num):
    x(x_event_num),
    y(y_event_num)
  {

  }

  double Stick::angleDeg() {
    double rad = atan2(y.getValue(), x.getValue());
    return rad * (180 / M_PI);
  }

  double Stick::angleRad() {
    return atan2(y.getValue(), x.getValue());
  }


  void ButtonDataList::update(PadEventHandler& handler) {
    this->event_ = handler.getButtonEvent();
    this->list_[event_.id]->setEvent(event_);
  }

  void ButtonDataList::clear() {
    for (auto e: this->list_) {
      e.second->setEvent(button_state::OFF, ButtonAction::None);
    }
  }

  void ButtonDataList::resetAction() {
    this->list_[event_.id]->setAction(ButtonAction::None);
  }


  void AxisDataList::update(PadEventHandler& handler) {
    this->event_ = handler.getAxisEvent();
    this->list_[event_.id]->setValue(event_.value);
  }

  void AxisDataList::clear() {
    for (auto e: this->list_) {
      e.second->setValue(0);
    }
  }

  // Button::Button(const int event_number): id_{event_number} {}

  // Button& Button::get() { return *this; }

  // bool Button::pressed() { return this->state_; }

  // bool Button::pushed() {
  //   if (this->action_ == ButtonAction::Push) {
  //     return true;
  //   }
  //   else 
  //     return false;
  // }

  // bool Button::released() {
  //   if (this->action_ == ButtonAction::Release)
  //     return true;
  //   else 
  //     return false;
  // }



  // Axis::Axis(int event_number): id_{event_number} {}

  // Axis& Axis::get() { return *this; }

  // int Axis::getValue() { return static_cast<int>(this->value_); }



  // TriggerButton::TriggerButton(int button_event_num, int axis_event_num):
  //   Button(button_event_num),
  //   depth_(axis_event_num)
  // {

  // }

  // int TriggerButton::getDepth() {
  //   return this->depth_.getValue();
  // }

  // Axis& TriggerButton::getAxis() {
  //   return this->depth_.get();
  // }


  // Stick::Stick(int x_event_num, int y_event_num): x(x_event_num), y(y_event_num) {}

  // void ButtonDataList::update(PadEventHandler& handler) {
  //   this->event_ = handler.getButtonEvent();
  //   ButtonAction action;

  //   switch (event_.state) {
  //     case (button_state::OFF): action = ButtonAction::Release; break;
  //     case (button_state::ON):  action = ButtonAction::Push;    break;
  //   }


  //   list_[event_.id]->state_  = event_.state;
  //   list_[event_.id]->action_ = action;
  // }

  // void ButtonDataList::resister(Button& button) {
  //   if (button.id_ >= list_.size()) {
  //     list_.resize(button.id_ + 1, nullptr);
  //   }
  //   list_[button.id_] = &button;
  // }

  // void ButtonDataList::resetAction() {
  //   list_[event_.id]->action_ = ButtonAction::None;
  // }

  // void ButtonDataList::clear() {
  //   for (auto b: list_) {
  //     b->state_  = button_state::OFF;
  //     b->action_ = ButtonAction::None;
  //   }
  // }



  // void AxisDataList::update(PadEventHandler& handler) {
  //   this->event_ = handler.getAxisEvent();

  //   list_[event_.id]->value_ = event_.value;
  // }

  // void AxisDataList::resister(Axis& axis) {
  //   if (axis.id_ >= list_.size()) {
  //     list_.resize(axis.id_ + 1, nullptr);
  //   }
  //   list_[axis.id_] = &axis;
  // }

  // void AxisDataList::clear() {
  //   for (auto a: list_) {
  //     a->value_ = 0;
  //   }
  // }
}