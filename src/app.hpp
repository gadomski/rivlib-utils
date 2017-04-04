#pragma once

#include <riegl/scanlib.hpp>

class App {
   public:
    App(int argc, char** argv);

    int run();
    virtual void setup() {}
    virtual void dispatch(scanlib::buffer& buf) = 0;
    virtual void teardown() {}

   private:
    int m_argc;
    char** m_argv;
};
