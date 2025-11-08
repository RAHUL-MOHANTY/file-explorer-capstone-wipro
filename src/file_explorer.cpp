#include <iostream>
#include <filesystem>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <ctime>
using namespace std;
namespace fs = std::filesystem;

#define B  "\033[34m"
#define G  "\033[32m"
#define Y  "\033[33m"
#define R  "\033[31m"
#define X  "\033[0m"

// --- Day 1: File Listing ---
string modTime(const fs::path &p) {
    auto ftime = fs::last_write_time(p);
    auto sys = chrono::time_point_cast<chrono::system_clock::duration>(
        ftime - fs::file_time_type::clock::now() + chrono::system_clock::now()
    );
    time_t tt = chrono::system_clock::to_time_t(sys);
    string t = ctime(&tt);
    if (!t.empty()) t.pop_back();
    return t;
}

void showDir(const fs::path &dir) {
    cout << "\nListing: " << Y << dir.string() << X << "\n";
    cout << "-----------------------------------------\n";
    for (auto &e : fs::directory_iterator(dir)) {
        cout << (fs::is_directory(e) ? B "[DIR] " : G "[FILE]") << X << setw(20)
             << left << e.path().filename().string() << " " << modTime(e.path()) << "\n";
    }
}

// --- Day 2 + 3 ---
int main() {
    fs::path cur = fs::current_path();
    string cmd, a1, a2;

    cout << "Type 'help' for commands.\n\n";

    while (true) {
        cout << Y << cur.string() << X << " $ ";
        cin >> cmd;

        if (cmd == "ls") showDir(cur);

        else if (cmd == "pwd") cout << "Dir: " << G << cur.string() << X << "\n";

        else if (cmd == "cd") {
            cin >> a1;
            fs::path t = (a1 == "..") ? cur.parent_path() : cur / a1;
            if (fs::exists(t) && fs::is_directory(t)) {
                cur = fs::canonical(t);
                cout << "Changed to " << G << cur.string() << X << "\n";
            } else cout << R << "No such directory\n" << X;
        }

        else if (cmd == "touch") {
            cin >> a1;
            fs::path f = cur / a1;
            if (fs::exists(f)) cout << Y << "File exists\n" << X;
            else {
                ofstream out(f);
                cout << G << "File created: " << a1 << X << "\n";
            }
        }

        else if (cmd == "mkdir") {
            cin >> a1;
            fs::path d = cur / a1;
            if (!fs::exists(d)) {
                fs::create_directory(d);
                cout << G << "Dir created: " << a1 << X << "\n";
            } else cout << Y << "Dir already exists\n" << X;
        }

        else if (cmd == "rm") {
            cin >> a1;
            fs::path t = cur / a1;
            fs::path tr = fs::path(getenv("HOME")) / ".trash";
            fs::create_directories(tr);
            if (fs::exists(t)) {
                fs::rename(t, tr / t.filename());
                cout << R << "Moved to Trash\n" << X;
            } else cout << R << "No such file or dir\n" << X;
        }

        else if (cmd == "cp") {
            cin >> a1 >> a2;
            fs::path s = cur / a1, d = cur / a2;
            if (!fs::exists(s)) { cout << R << "Not found\n" << X; continue; }
            try {
                if (fs::is_directory(s)) fs::copy(s, d, fs::copy_options::recursive);
                else fs::copy_file(s, d, fs::copy_options::overwrite_existing);
                cout << G << "Copied\n" << X;
            } catch (...) { cout << R << "Copy failed\n" << X; }
        }

        else if (cmd == "mv") {
            cin >> a1 >> a2;
            fs::path s = cur / a1, d = cur / a2;
            if (fs::exists(s)) {
                fs::rename(s, d);
                cout << G << "Moved\n" << X;
            } else cout << R << "Not found\n" << X;
        }

        else if (cmd == "help") {
            cout << "\nCommands:\n"
                 << " ls           - list\n"
                 << " pwd          - show current\n"
                 << " cd <dir>     - change dir\n"
                 << " touch <f>    - create file\n"
                 << " mkdir <d>    - make dir\n"
                 << " rm <f|d>     - move to trash\n"
                 << " cp <s> <d>   - copy\n"
                 << " mv <s> <d>   - move/rename\n"
                 << " help         - help\n"
                 << " exit         - quit\n";
        }

        else if (cmd == "exit") {
            cout << G << "Bye!\n" << X;
            break;
        }

        else cout << R << "Unknown command\n" << X;
    }
    return 0;
}

