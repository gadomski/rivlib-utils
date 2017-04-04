#pragma once

#include <riegl/scanlib.hpp>

class App {
   public:
    App(int argc, char** argv);

    int run();
    inline virtual void setup() {}
    virtual void dispatch(scanlib::buffer& buf) = 0;

   private:
    int m_argc;
    char** m_argv;
};
