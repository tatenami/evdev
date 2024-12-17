#pragma once

#include "PadEvent.hpp"
#include "PadReader.hpp"

#include <unordered_map>

namespace pad {

  class PadEventHandler {
   protected:
    std::unordered_map<int, uint8_t> id_map;
    PadEvent    event_;
    ButtonEvent button_event_{0, button_state::OFF}; 
    AxisEvent   axis_event_{0, 0};
    int16_t     deadzone_{0};

    virtual void handleButtonEvent() = 0;
    virtual void handleAxisEvent() = 0;

   public:
    void setDeadzone(uint16_t deadzone); 
    EventType    getEventType();
    ButtonEvent& getButtonEvent();
    AxisEvent&   getAxisEvent();
    void editEvent(PadReader& reader);
  };

  inline EventType PadEventHandler::getEventType() { 
    return this->event_.type; 
  }

  inline ButtonEvent& PadEventHandler::getButtonEvent() {
    return this->button_event_;
  }

  inline AxisEvent& PadEventHandler::getAxisEvent() {
    return this->axis_event_;
  }

}