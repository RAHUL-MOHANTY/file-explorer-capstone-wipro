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
#define R "\033[31m"
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
    cout << "-----------------------------------------\n";
    for (auto &e : fs::directory_iterator(dir)) {
        cout << (fs::is_directory(e) ? B "[DIR] " : G "[FILE] ") << X
             << setw(20) << left << e.path().filename().string()
             << " " << modTime(e.path()) << "\n";
    }
}

int main() {
    fs::path cur = fs::current_path();
    string cmd, arg;

    cout << "Type 'start' for commands.\n\n";
    while (true) {
        cout << Y << cur.string() << X << " $ ";
        cin >> cmd;

        if (cmd == "ls") showDir(cur);
        else if (cmd == "pwd") cout << "Dir: " << G << cur.string() << X << "\n";
        else if (cmd == "cd") {
            cin >> arg;
            fs::path t = (arg == "..") ? cur.parent_path() : cur / arg;
            if (fs::exists(t) && fs::is_directory(t)) {
                cur = fs::canonical(t);
                cout << "Changed to " << G << cur.string() << X << "\n";
            } else cout << R << "No such directory\n" << X;
        }
        else if (cmd == "exit") break;
        else if (cmd == "start")
            cout << "Commands: ls, pwd, cd <dir>, start, exit\n";
        else cout << R << "Unknown command\n" << X;
    }
    return 0;
}
