#include <riegl/scanlib.hpp>

#include <iostream>

#include "app.hpp"


class Units : public scanlib::pointcloud
{
public:

    Units()
        : scanlib::pointcloud(false)
    {}

protected:

    void on_units(const scanlib::units<iterator_type>& arg)
    {
        scanlib::pointcloud::on_units(arg);
        std::cout << "here" << std::endl;
    }

};


class UnitsApp : public App
{
public:

    UnitsApp(int argc, char** argv)
        : App(argc, argv)
        , m_units()
    {}

    void dispatch(scanlib::buffer& buf)
    {
        m_units.dispatch(buf.begin(), buf.end());
    }

private:

    Units m_units;

};


int main(int argc, char** argv)
{
    UnitsApp app(argc, argv);
    return app.run();
}
