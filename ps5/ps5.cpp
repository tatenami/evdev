#include "ps5.hpp"

namespace pad {

  namespace ps5 {

    const uint16_t default_deadzone = 5;

    PS5Handler::PS5Handler() {
      id_map[BTN_SOUTH]  = id::cross;
      id_map[BTN_EAST]   = id::circle;
      id_map[BTN_NORTH]  = id::triangle;
      id_map[BTN_WEST]   = id::square;
      id_map[BTN_TL]     = id::L1;
      id_map[BTN_TR]     = id::R1;
      id_map[BTN_TL2]    = id::L2;
      id_map[BTN_TR2]    = id::R2;
      id_map[BTN_SELECT] = id::create;
      id_map[BTN_START]  = id::option;
      id_map[BTN_MODE]   = id::ps;
      id_map[BTN_THUMBL] = id::L3;
      id_map[BTN_THUMBR] = id::R3;

      id_map[ABS_X]  = id::leftX;
      id_map[ABS_Y]  = id::leftY;
      id_map[ABS_RX] = id::rightX;
      id_map[ABS_RY] = id::rightY;
      id_map[ABS_Z]  = id::L2depth;
      id_map[ABS_RZ] = id::R2depth;
      id_map[ABS_HAT0X] = id::crossX;
      id_map[ABS_HAT0Y] = id::crossY;
    }

    void PS5Handler::handleCrossXData(int32_t val) {
      if (val > 0) {
        this->pre_crossXid_ = id::right;
        button_event_ = {id::right, button_state::ON};
      }
      else if (val < 0)  {
        this->pre_crossXid_ = id::left;
        button_event_ = {id::left, button_state::ON};
      }
      else {
        switch (this->pre_crossXid_) {
          case (id::right): button_event_.id = id::right; break;
          case (id::left):  button_event_.id = id::left;  break;
        }
        button_event_.state = button_state::OFF;
      }
    }

    void PS5Handler::handleCrossYData(int32_t val) {
      if (val > 0) {
        this->pre_crossXid_ = id::down;
        button_event_ = {id::down, button_state::ON};
      }
      else if (val < 0)  {
        this->pre_crossXid_ = id::up;
        button_event_ = {id::up, button_state::ON};
      }
      else {
        switch (this->pre_crossXid_) {
          case (id::down): button_event_.id = id::down; break;
          case (id::up):   button_event_.id = id::up;  break;
        }
        button_event_.state = button_state::OFF;
      }
    }

    void PS5Handler::handleAxisEvent() {
      int32_t val = event_.value;
      uint8_t id  = id_map[event_.code]; 

      switch (id) {
        case (id::crossX): {
          event_.type = EventType::Button;
          handleCrossXData(val);
          return;
        }
        case (id::crossY): {
          event_.type = EventType::Button;
          handleCrossYData(val);
          return;
        }
      }

      if (id != id::L2depth && id != id::R2depth) {
        val -= 128;
      }

      switch (id) {
        case (id::leftY):
        case (id::rightY): {
          val *= -1;
        }
        default: {
          if (abs(val) < deadzone_) val = 0;
          axis_event_.id = id;
          axis_event_.value = val;
        }
      }
    }

    void PS5Handler::handleButtonEvent() {
      button_event_.id = id_map[event_.code];

      switch (event_.value) {
        case 0: {
          button_event_.state = button_state::OFF;
          break;
        }
        case 1: {
          button_event_.state = button_state::ON;
          break;
        }
      }
    }

    DualSense::DualSense(Connect mode) {
      std::string device_name;

      switch (mode) {
        case (Connect::USB): device_name = dev::usb; break;
        case (Connect::Bluetooth): device_name = dev::bluetooth; break;
      }

      buttons_.attach(Cross);
      buttons_.attach(Circle);
      buttons_.attach(Triangle);
      buttons_.attach(Square);
      buttons_.attach(L1);
      buttons_.attach(R1);
      buttons_.attach(L2);
      buttons_.attach(R2);
      buttons_.attach(Create);
      buttons_.attach(Option);
      buttons_.attach(PS);
      buttons_.attach(L3);
      buttons_.attach(R3);
      buttons_.attach(Left);
      buttons_.attach(Right);
      buttons_.attach(Up);
      buttons_.attach(Down);

      axes_.attach(Lstick.x);
      axes_.attach(Lstick.y);
      axes_.attach(Rstick.x);
      axes_.attach(Rstick.y);
      axes_.attach(L2.getTriggerAxis());
      axes_.attach(R2.getTriggerAxis());

      this->is_connected_ = reader_.connect(device_name);
      this->handler_->setDeadzone(default_deadzone);

      if (!reader_.isConnected()) {
        std::cout << "Fail to init Controller" << std::endl;
        reader_.disconnect();
      }
      else {
        std::cout << "Controller is initialized" << std::endl;
      }
    }

    DualSense::~DualSense() {
      std::cout << "Device is disconnected" << std::endl;
    }

    void DualSense::update() {
      this->is_connected_ = reader_.isConnected();
      buttons_.resetAction();

      bool event_flag = reader_.readEvent();

      if (event_flag == true) {
        handler_->editEvent(reader_);
        
        switch (handler_->getEventType()) {
          case (EventType::Button): {
            buttons_.update(*handler_);
            break;
          }
          case (EventType::Axis): {
            axes_.update(*handler_);
            break;
          }
        }

      }
    }

  }

}
