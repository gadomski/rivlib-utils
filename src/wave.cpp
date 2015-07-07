#include <riegl/scanlib.hpp>
#include <riegl/wave.hpp>

#include <iostream>

#include "app.hpp"


class Wave : public scanlib::wave
{
public:

    Wave()
        : scanlib::wave(false)
          , m_kinds()
    {}

protected:

    void on_wave(waveform& wfm)
    {
        auto inserted = m_kinds.insert(scanner->kind());
        if (inserted.second) {
            switch (scanner->kind()) {
                case scanlib::scanmech::unknown:
                    std::cout << "scanmech::unknown" << std::endl;
                    break;
                case scanlib::scanmech::mirrorwheel:
                    std::cout << "scanmech::mirrorwheel" << std::endl;
                    break;
                case scanlib::scanmech::wedge:
                    std::cout << "scanmech::wedge" << std::endl;
                    break;
                case scanlib::scanmech::mirrorwheel_exitpane:
                    std::cout << "scanmech::mirrorwheel_exitpane" << std::endl;
                    break;
                case scanlib::scanmech::mirrorwheel_deflection:
                    std::cout << "scanmech::mirrorwheel_deflection" << std::endl;
                    break;
                case scanlib::scanmech::mirrorwheel_biaxial:
                    std::cout << "scanmech::mirrorwheel_biaxial" << std::endl;
                    break;
                case scanlib::scanmech::mirrorwheel_exitpane_deflection:
                    std::cout << "scanmech::mirrorwheel_exitpane_deflection" << std::endl;
                    break;
                default:
                    std::cout << "unhandled scanmech kind" << std::endl;
            }

        }
    }

private:

    std::set<scanlib::scanmech::kind_e> m_kinds;

};


class WaveApp : public App
{
public:

    WaveApp(int argc, char** argv)
        : App(argc, argv)
          , m_wave()
    {}

    void dispatch(scanlib::buffer& buf)
    {
        m_wave.dispatch(buf.begin(), buf.end());
    }

private:

    Wave m_wave;

};


int main(int argc, char** argv)
{
    WaveApp app(argc, argv);
    return app.run();
}
