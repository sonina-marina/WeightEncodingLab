#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include "WeightedCode.h"
#include "UI.h"

int main() {
    MainWindow window(640, 510, "Расширенный код Хэмминга");

    window.show();

    return Fl::run();
}

// int main() {
//     WeightedCode obj;
//     obj.coding("10110001");
//     std::cout << "coding passed\n";
//     obj.checking("10110001111");
//     std::cout << "\nchecking passed\n";
// }