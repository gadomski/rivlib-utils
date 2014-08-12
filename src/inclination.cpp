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
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <input-uri>" << std::endl; 
            return 1;
        }
        std::shared_ptr<scanlib::basic_rconnection> rc;        
        rc = scanlib::basic_rconnection::create(argv[1]);
        rc->open();

        scanlib::decoder_rxpmarker dec(rc);
        Inclination inc;
        scanlib::buffer buf;

        for (dec.get(buf); !dec.eoi(); dec.get(buf))
        {
            inc.dispatch(buf.begin(), buf.end());
        }

        rc->close();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 2;
    }
    catch (...)
    {
        std::cerr << "Unknown exception" << std::endl;
        return 3;
    }

    return 0;
}
