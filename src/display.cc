#include "display.h"

Display::Display(std::string playerClass, std::string file, int height, int width, bool generate) {
    game = std::make_shared<Game>(playerClass, file, height, width, generate);
}
