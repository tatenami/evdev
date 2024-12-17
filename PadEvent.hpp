#pragma once

#include <stdint.h>

namespace pad {

  enum class EventType {
    None, Button, Axis
  };

  struct PadEvent {
    EventType type;
    uint16_t  code;
    int32_t   value;
  };
  
  namespace button_state {
    const bool ON  = true;
    const bool OFF = false;
  }

  enum class ButtonAction {
    None, Push, Release
  };

  struct ButtonEvent {
    uint8_t  id;
    bool state;
  };

  struct AxisEvent {
    uint8_t id;
    int value;
  };

}