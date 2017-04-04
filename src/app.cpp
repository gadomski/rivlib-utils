#include "app.hpp"

App::App(int argc, char** argv) : m_argc(argc), m_argv(argv) {}

int App::run() {
    try {
        if (m_argc != 2) {
            std::cerr << "Usage: " << m_argv[0] << " <input-uri>" << std::endl;
            return 1;
        }
        std::shared_ptr<scanlib::basic_rconnection> rc;
        rc = scanlib::basic_rconnection::create(m_argv[1]);
        rc->open();

        scanlib::decoder_rxpmarker dec(rc);
        scanlib::buffer buf;

        setup();

        for (dec.get(buf); !dec.eoi(); dec.get(buf)) {
            dispatch(buf);
        }

        rc->close();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (...) {
        std::cerr << "Unknown exception" << std::endl;
        return 3;
    }

    return 0;
}
