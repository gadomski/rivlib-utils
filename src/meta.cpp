#include <iostream>
#include <riegl/scanlib.hpp>
#include "app.hpp"

class MetaApp : public App {
   public:
    MetaApp(int argc, char** argv) : App(argc, argv), m_pointcloud() {}

    void dispatch(scanlib::buffer& buf) {
        m_pointcloud.dispatch(buf.begin(), buf.end());
    }

    virtual void teardown() {
        m_pointcloud.write_meta(std::cout, true);
    }

   private:
    scanlib::pointcloud m_pointcloud;
};

int main(int argc, char** argv) {
    MetaApp app(argc, argv);
    return app.run();
}
