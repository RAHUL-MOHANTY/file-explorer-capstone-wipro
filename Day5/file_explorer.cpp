#include <iostream>
#include <filesystem>
#include <fstream>
#include <map>
#include <vector>
#include <string>
using namespace std;
namespace fs = std::filesystem;

map<string, string> col = {
    {"dir", "\033[34m"},
    {"file", "\033[32m"},
    {"reset", "\033[0m"}
};

vector<string> history;

void loadCfg() {
    ifstream cfg("config.txt");
    string k, v;
    while (cfg >> k >> v) col[k] = v;
}

void showDir(const fs::path &p) {
    cout << "\nListing: " << p.string() << "\n";
    cout << "-----------------------------------\n";
    for (auto &e : fs::directory_iterator(p)) {
        cout << (fs::is_directory(e) ? col["dir"] + "[DIR]" : col["file"] + "[FILE]")
             << " " << e.path().filename().string() << col["reset"] << "\n";
    }
}

void changePerm(const fs::path &p, const string &perm) {
    try {
        if (!fs::exists(p)) {
            cout << "File not found\n";
            return;
        }
        int mode = stoi(perm, 0, 8);
        fs::permissions(
            p,
            static_cast<fs::perms>(mode),
            fs::perm_options::replace
        );

        cout << "Permissions changed for: " << p.filename().string() << "\n";
    } 
    catch (exception &e) {
        cout << "Error changing permissions: " << e.what() << "\n";
    }
}

void showHistory() {
    if (history.empty()) {
        cout << "No commands yet.\n";
        return;
    }
    for (size_t i = 0; i < history.size(); ++i)
        cout << i + 1 << ": " << history[i] << "\n";
}

void clearScreen() {
    system("clear");
}

int main() {
    loadCfg();
    fs::path cur = fs::current_path();
    string cmd, a1, a2;

    cout << "Type 'start' for commands.\n\n";
    while (true) {
        cout << cur.string() << " $ ";
        cin >> cmd;
        history.push_back(cmd);

        if (cmd == "ls") showDir(cur);
        else if (cmd == "chmod") { cin >> a1 >> a2; changePerm(cur / a1, a2); }
        else if (cmd == "history") showHistory();
        else if (cmd == "clear") clearScreen();
        else if (cmd == "start")
            cout << "Commands: ls, chmod <file> <perm>, history, clear, start, exit\n";
        else if (cmd == "exit") break;
        else cout << "Unknown command\n";
    }
    return 0;
}
