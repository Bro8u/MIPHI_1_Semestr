
#include <iostream>
#include <cassert>
#include <chrono>
#include <cmath>
#include <sstream>
#include <string>
#include <thread>

class Timer {
public:
    Timer(std::chrono::milliseconds t) : t_(t) {
        start_ = std::chrono::steady_clock::now();
    }
    bool Expired() const {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_) <= t_) {
            return false;
        }
        else {
            return true;
        }
    }
private:
    std::chrono::steady_clock::time_point start_;
    std::chrono::milliseconds t_;
};

class TimeMeasurer {
public:
    TimeMeasurer(std::stringstream& stream) : ostream_(stream) {
        start_ = std::chrono::steady_clock::now();
    }
    ~TimeMeasurer() {
        
        //std::chrono::duration<double, std::milli> em = std::chrono::steady_clock::now() - start_;
        // std::chrono::milliseconds tim = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_);
        int ans = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_).count();
        // std::cout << ans << '\n';
        ostream_ << "Elapsed time: " << ans << " ";
        // std::stringstream a;
        // a << std::to_string(ans);
        // std::string ansStr = a.str();
        // a;
    }
private:
    std::chrono::steady_clock::time_point start_;
    std::stringstream& ostream_;    
};
