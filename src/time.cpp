#include <riegl/scanlib.hpp>

#include <iomanip>
#include <iostream>

#include "app.hpp"

class Time : public scanlib::pointcloud {
   public:
    Time() : scanlib::pointcloud(false) {}

   protected:
    void on_echo_transformed(scanlib::pointcloud::echo_type echo) {
        scanlib::pointcloud::on_echo_transformed(echo);
        for (scanlib::pointcloud::target_count_type i = 0; i < this->target_count; ++i) {
            auto target = this->targets[i];
            std::cout <<
                std::fixed <<
                std::setprecision(3) << target.vertex[0] <<
                "," << target.vertex[1] <<
                "," << target.vertex[2] <<
                std::setprecision(9) << "," << target.time <<
                std::endl;
        }
    }
};

class TimeApp : public App {
   public:
    TimeApp(int argc, char** argv) : App(argc, argv), m_time() {}

    void setup() {
        std::cout << "X,Y,Z,Time" << std::endl;
    }

    void dispatch(scanlib::buffer& buf) {
        m_time.dispatch(buf.begin(), buf.end());
    }

   private:
    Time m_time;
};

int main(int argc, char** argv) {
    TimeApp app(argc, argv);
    return app.run();
}
