#include <riegl/scanlib.hpp>




class Inclination : public scanlib::pointcloud
{

public:

    Inclination()
        : scanlib::pointcloud(false)
    {}

protected:

    void on_inclination_wyler(const scanlib::inclination_wyler<iterator_type>& arg)
    {
        std::cout << "Here" << std::endl;
    }

};


int main(int argc, char* argv[])
{
    std::cout << "here" << std::endl;
    return 0;
}
