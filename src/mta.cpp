#include <rivmtaifc.h>

#include <iomanip>
#include <iostream>
#include <vector>


int main(int argc, char* argv[])
{
    scanifc_csz filename = "/projects/2014-09-25-Whites/2014-09-25-WhiteMtns.riproject/ScanPos002/140925_191412.rxp";
    scanifc_float32_t maxrange = 10000;
    scanifc_uint32_t buffersize = 65536;

    rivmta_handle handle;
    scanifc_bool endOfFrame;
    scanifc_uint32_t count;
    scanifc_uint64_t bytesRead;

    std::vector<scanifc_xyz32> xyz32(buffersize);
    std::vector<scanifc_time_ns> time(buffersize);
    std::vector<scanifc_uint8_t> confidence(buffersize);
    std::vector<scanifc_attributes> attributes(buffersize);

    try
    {
        if (rivmtaifc_rivmta_open(filename, 0, maxrange, &handle) != 0)
        {
            std::cerr << "Problem!" << std::endl;
            return -1;
        }

        do
        {
            if (rivmtaifc_rivmta_read(handle,
                                      buffersize,
                                      xyz32.data(),
                                      attributes.data(),
                                      time.data(),
                                      confidence.data(),
                                      &count,
                                      &endOfFrame) != 0)
            {
                std::cerr << "Problem!" << std::endl;
                return -1;
            }

            if (rivmtaifc_rivmta_tellg(handle, &bytesRead) != 0)
            {
                std::cerr << "Problem!" << std::endl;
                return -1;
            }

            for (scanifc_uint32_t i = 0; i < count; ++i)
            {
                std::cout << xyz32[i].x << "," <<
                             xyz32[i].y << "," <<
                             xyz32[i].z << "," <<
                             attributes[i].amplitude <<
                             std::endl;
            }
        } while (count != 0 || endOfFrame != 0);

        if (rivmtaifc_rivmta_close(handle) != 0)
        {
            std::cerr << "Problem!" << std::endl;
            return -1;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    catch (...)
    {
        std::cout << "Unknown error" << std::endl;
        return -1;
    }

    return 0;
}
