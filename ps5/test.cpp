#include <iostream>
#include <ps5.hpp>

using namespace std;
using namespace pad;

int main() {

  ps5::DualSense ps5(Connect::USB);

  Button& target = ps5.PS.get();
  Button& stop = ps5.Option.get();
  Axis& axis1 = ps5.Rstick.x.get();
  Axis& axis2 = ps5.Rstick.y.get();

  while (ps5.isConnected()) {
    ps5.update();

    // if (target.pushed()) {
    //   cout << "Button (ID: " << static_cast<int>(target.getID()) << ") "
    //        << "pushed!" << endl;
    // }
    // else if (target.released()) {
    //   cout << "Button (ID: " << static_cast<int>(target.getID()) << ") "
    //        << "released!" << endl;
    // }

    cout << "x: " << axis1.getValue() << " y: " << axis2.getValue() 
         << " DEG: " << ps5.Rstick.angleDeg() << " RAD: " << ps5.Rstick.angleRad() << endl;

    usleep(1000);

    if (stop.pushed()) break; 
  } 

  return 0;
}