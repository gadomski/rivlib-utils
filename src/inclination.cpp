#include <riegl/scanlib.hpp>

#include <iomanip>
#include <iostream>

#include "app.hpp"

class Inclination : public scanlib::pointcloud {
   public:
    Inclination() : scanlib::pointcloud(false) {}

   protected:
    void on_hk_incl(const scanlib::hk_incl<iterator_type>& arg) {
        scanlib::pointcloud::on_hk_incl(arg);
        float roll(arg.ROLL * 0.001);
        float pitch(arg.PITCH * 0.001);
        std::cout << std::setprecision(4) << time << "," << std::setprecision(3)
                  << roll << "," << pitch << std::endl;
    }
};

class InclinationApp : public App {
   public:
    InclinationApp(int argc, char** argv) : App(argc, argv), m_inc() {}

    void setup() {
        std::cout << "Time,Roll,Pitch" << std::endl;
        std::cout << std::fixed;
    }

    void dispatch(scanlib::buffer& buf) {
        m_inc.dispatch(buf.begin(), buf.end());
    }

   private:
    Inclination m_inc;
};

int main(int argc, char* argv[]) {
    InclinationApp app(argc, argv);
    return app.run();
}
