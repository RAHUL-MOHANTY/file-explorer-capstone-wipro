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
    auto ft = fs::last_write_time(p);
    auto sctp = chrono::time_point_cast<chrono::system_clock::duration>(
        ft - fs::file_time_type::clock::now() + chrono::system_clock::now());
    time_t tt = chrono::system_clock::to_time_t(sctp);
    string t = ctime(&tt);
    if (!t.empty()) t.pop_back();
    return t;
}

void showDir(const fs::path &p) {
    cout << "\nListing: " << Y << p.string() << X << "\n";
    cout << "------------------------------------------\n";
    for (auto &e : fs::directory_iterator(p)) {
        cout << (fs::is_directory(e) ? B "[DIR] " : G "[FILE] ") << X
             << e.path().filename().string() << "\n";
    }
}

void searchFile(const fs::path &p, const string &name) {
    bool found = false;
    for (auto &e : fs::recursive_directory_iterator(p)) {
        if (e.path().filename().string().find(name) != string::npos) {
            cout << G << "Found: " << e.path().string() << X << "\n";
            found = true;
        }
    }
    if (!found) cout << R << "No match found\n" << X;
}

void fileInfo(const fs::path &p) {
    if (!fs::exists(p)) { cout << R << "Not found\n" << X; return; }
    cout << "\nFile Info\n";
    cout << "------------------------------------------\n";
    cout << "Name : " << G << p.filename().string() << X << "\n";
    cout << "Type : " << (fs::is_directory(p) ? "Directory" : "File") << "\n";
    if (!fs::is_directory(p))
        cout << "Size : " << fs::file_size(p) << " bytes\n";
    cout << "Modified : " << modTime(p) << "\n";
}

int main() {
    fs::path cur = fs::current_path();
    string cmd, a1;

    cout << "Type 'start' for commands.\n\n";
    while (true) {
        cout << Y << cur.string() << X << " $ ";
        cin >> cmd;

        if (cmd == "ls") showDir(cur);
        else if (cmd == "search") { cin >> a1; searchFile(cur, a1); }
        else if (cmd == "info") { cin >> a1; fileInfo(cur / a1); }
        else if (cmd == "start")
            cout << "Commands: ls, search <name>, info <file>, start, exit\n";
        else if (cmd == "exit") break;
        else cout << R << "Unknown command\n" << X;
    }
    return 0;
}
