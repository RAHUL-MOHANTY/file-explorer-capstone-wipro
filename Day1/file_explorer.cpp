#include <iostream>
#include <filesystem>
#include <iomanip>
#include <chrono>
#include <ctime>
using namespace std;
namespace fs = std::filesystem;

#define B "\033[34m"
#define G "\033[32m"
#define Y "\033[33m"
#define X "\033[0m"

string modTime(const fs::path &p) {
    auto ftime = fs::last_write_time(p);
    auto sys = chrono::time_point_cast<chrono::system_clock::duration>(
        ftime - fs::file_time_type::clock::now() + chrono::system_clock::now());
    time_t tt = chrono::system_clock::to_time_t(sys);
    string t = ctime(&tt);
    if (!t.empty()) t.pop_back();
    return t;
}

void showDir(const fs::path &dir) {
    cout << "\nListing: " << Y << dir.string() << X << "\n";
    cout << "----------------------------------------\n";
    for (auto &e : fs::directory_iterator(dir)) {
        cout << (fs::is_directory(e) ? B "[DIR] " : G "[FILE] ") << X
             << setw(20) << left << e.path().filename().string()
             << " " << modTime(e.path()) << "\n";
    }
}

int main() {
    try {
        fs::path cur = fs::current_path();
        showDir(cur);
        cout << "\nUse this explorer to view directory files.\n";
        cout << "Next: add cd, ls, pwd for navigation.\n";
    } catch (exception &e) {
        cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
