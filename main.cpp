#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

int main()
{
    io_service io;
    serial_port port(io);

    // 시리얼 포트 설정
    port.open("/dev/ttyUSB1");
    port.set_option(serial_port_base::baud_rate(38400));
    port.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
    port.set_option(serial_port_base::parity(serial_port_base::parity::none));
    port.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
    port.set_option(serial_port_base::character_size(8));

    string datName = "GNGLL";

    while (true)
    {
        boost::asio::streambuf buffer;
        read_until(port, buffer, '\n'); // Read data until a newline character is encountered

        istream is(&buffer);
        string data;
        getline(is, data);

        if (data.length() >= 6 && data.substr(1, 5) == datName) // Check if data has at least 6 characters
        {
            size_t pos1 = data.find(",");
            size_t pos2 = data.find(",", pos1 + 1);
            if (pos1 != string::npos && pos2 != string::npos)
            {
                float data2 = stof(data.substr(pos1 + 1, pos2 - pos1 - 1));
                float data3 = stof(data.substr(pos2 + 1));

                cout << "gps on" << endl;
                float x = data2 * 0.01;
                float y = data3 * 0.01;
                cout << "x: " << x << endl;
                cout << "y: " << y << endl;
            }
            else
            {
                cout << "data invalid" << endl;
            }
        }
        else
        {
            cout << "data invalid" << endl;
        }
    }


    return 0;
}
