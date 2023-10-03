#include <iostream>
#include <bitset>
#include <vector>
#include <ostream>

using namespace std;

class IPAddress {
    private:
        std::vector<int> ipOctets;
        std::vector<int> smOctets;

    public:
        IPAddress(std::vector<int> a, std::vector<int> b) {     // loads all parts of the given vectors into ipandsm Octets
            ipOctets = {a.at(0), a.at(1), a.at(2), a.at(3)};
            smOctets = {b.at(0), b.at(1), b.at(2), b.at(3)};
        }

        std::vector<int> calculateNetworkAddress(){             // and against the subnet mask
            int a = (ipOctets.at(0) & smOctets.at(0));
            int b = (ipOctets.at(1) & smOctets.at(1));
            int c = (ipOctets.at(2) & smOctets.at(2));
            int d = (ipOctets.at(3) & smOctets.at(3));
            
            return std::vector<int>{a, b, c, d};
        }

        std::vector<int> calculateBroadcastAddress(){           // or against the inverse subnet mask
            int a = (ipOctets.at(0) | (~(smOctets.at(0)) & 0xFF));
            int b = (ipOctets.at(1) | (~(smOctets.at(1)) & 0xFF));
            int c = (ipOctets.at(2) | (~(smOctets.at(2)) & 0xFF));
            int d = (ipOctets.at(3) | (~(smOctets.at(3)) & 0xFF));
            
            return std::vector<int>{a, b, c, d};
        }

        std::pair<std::vector<int>, std::vector<int>> calculatevalidIPAddressRange(){ // returning a pair of the ranges? was it that easy?
            std::vector<int> a = calculateNetworkAddress();
            std::vector<int> b = calculateBroadcastAddress();
            return std::make_pair(a, b);
        }
};

int main() {
    std::vector<int> a = {0,0,0,0};
    std::vector<int> b = {0,0,0,0};
    string ip;
    int mask;
    std::cout << "Enter an IPv4 address [xxx.xxx.xxx.xxx]:\n";
    std::cin >> ip;

    bool ipValid = false;
    while (ipValid == false) { // General error checking before getting into knitty gritty, any other errors will close the program
        ipValid = true;
        if (ip.length() > 15 || ip.length() < 7) {  // error checking overall length of ip 
            ipValid = false;
        } 
        int periods = 0;

        for (int i = 0; i < ip.length(); i++) { // error # of periods 
            if (ip.at(i) == '.') {
                periods++;
            }
        }
        if (periods != 3) {  
            ipValid = false;
        }

        if (ipValid == false) {
            std::cout << "Dude, you entered the IP wrong..." << endl;
            std::cout << "Enter an IPv4 address [xxx.xxx.xxx.xxx]:\n";
            std::cin >> ip;
        } else {
            ipValid = true;
        }
    }

    int back = 0;                                   // adding values to ipOctets with whatever string ip gets passed in and parsed through by the '.' delimiter
    int octs[4];

    for (int i = 0; i < 3; i++) {
        int front = back;
        while (ip.at(front) != '.') { 
            front++;
        }
        int num = stoi(ip.substr(back, front));
        if (num < 0 || num > 255) {                 // checking the internal numbers to make sure they're in the range
            std::cout << "Just start over at this point... smh. Internal number wasn't in range of 0-255" << endl;
            return 1;
        }
        octs[i] = num;
        back = front + 1;
    }

    int num2 = stoi(ip.substr(back, ip.length()));  // last trailing numbers
    if (num2 < 0 || num2 > 255) {                     // checking the internal numbers to make sure they're in the range
            std::cout << "Just start over at this point... smh. Internal number wasn't in range of 0-255" << endl;
            return 1;
        }
    octs[3] = num2; 
    
    for (int i = 0; i < 4; i++) {
        a.at(i) = octs[i];
    }

    std::cout << "Enter a subnet mask [1-32]:" << endl;
    std::cin >> mask;

    while (mask < 1 || mask > 32) {
        std::cout << "Dude, you entered a mask outside of the subnet range..." << endl;
        std::cout << "Enter a subnet mask [1-32]:" << endl;
        std::cin >> mask;
    }

    string maskBuilder = "00000000";                // using a binary string representation to slowly build each binary number meant for smOctets and pushing it into it
    int count = 0;
    
    for (int i = 0; i < mask; i++) {
        if (i % 8 == 0 && i != 0) {
            b.at(count) = stoi(maskBuilder, nullptr, 2);
            count++;
            maskBuilder = "00000000";
        }
        maskBuilder.at(i % 8) = '1';
    }
    b.at(count) = stoi(maskBuilder, nullptr, 2);
    
    maskBuilder = "00000000";                       // pushing empty bits
    while (b.size() < 4) {
        b.at(count) = stoi(maskBuilder, nullptr, 2);
        count++;
    }
    
    IPAddress womp(a, b);
    
    std::vector<int> NA = womp.calculateNetworkAddress();
    cout << "Network Address: " << NA.at(0) << "." << NA.at(1) << "." << NA.at(2) << "." << NA.at(3) << endl;
    std::vector<int> BA = womp.calculateBroadcastAddress();
    cout << "Broadcast Address: " << BA.at(0) << "." << BA.at(1) << "." << BA.at(2) << "." << BA.at(3) << endl;
    cout << "Valid IP Address Range: " << NA.at(0) << "." << NA.at(1) << "." << NA.at(2) << "." << NA.at(3) << " - " << BA.at(0) << "." << BA.at(1) << "." << BA.at(2) << "." << BA.at(3) << endl;
    
    womp.calculatevalidIPAddressRange();
    return 0;
}
