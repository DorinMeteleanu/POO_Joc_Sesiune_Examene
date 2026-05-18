#include "gameManager.h"
#include <ctime>
#include <cstdlib>

int main() {
    srand(time(0));
    GameManager::getInstanta()->pornesteJocul();
    return 0;
}