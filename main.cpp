// main.cpp

#include "App.h"

int main(){
    auto& tc = termChat::App::getInstance();

    return tc.run();
}
