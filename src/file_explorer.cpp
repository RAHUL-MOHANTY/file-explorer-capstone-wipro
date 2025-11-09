#include <bits/stdc++.h>
#include <filesystem>
#include <chrono>
using namespace std;
namespace fs = std::filesystem;

vector<string> history;


void listDir() {
    for (auto &e : fs::directory_iterator(fs::current_path())) {
        cout << (fs::is_directory(e) ? "[DIR]  " : "[FILE] ") 
             << e.path().filename().string() << "\n";
    }
}

void showPwd() { cout << fs::current_path().string() << "\n"; }

void changeDir(const string &path) {
    try { fs::current_path(path); }
    catch (...) { cout << "cd: no such directory\n"; }
}

void makeDir(const string &d) {
    try {
        if (fs::create_directory(d)) cout << "Directory created: " << d << "\n";
        else cout << "mkdir: already exists or failed\n";
    } catch (...) { cout << "mkdir: failed\n"; }
}

void makeFile(const string &f) {
    ofstream file(f);
    if (file) cout << "File created: " << f << "\n";
    else cout << "touch: failed\n";
}

void copyFile(const string &src, const string &dest) {
    try {
        fs::copy(src, dest, fs::copy_options::overwrite_existing | fs::copy_options::recursive);
        cout << "Copied " << src << " → " << dest << "\n";
    } catch (...) { cout << "cp: failed\n"; }
}

void moveFile(const string &src, const string &dest) {
    try {
        fs::rename(src, dest);
        cout << "Moved " << src << " → " << dest << "\n";
    } catch (...) { cout << "mv: failed\n"; }
}

void removeFile(const string &t) {
    try {
        if (fs::remove_all(t)) cout << "Removed: " << t << "\n";
        else cout << "rm: not found\n";
    } catch (...) { cout << "rm: failed\n"; }
}

void fileInfo(const string &f) {
    if (!fs::exists(f)) { cout << "info: not found\n"; return; }
    auto t = fs::last_write_time(f);
    auto sys = chrono::time_point_cast<chrono::system_clock::duration>(
        t - fs::file_time_type::clock::now() + chrono::system_clock::now());
    time_t tt = chrono::system_clock::to_time_t(sys);
    cout << "File: " << f << "\n";
    cout << "Type: " << (fs::is_directory(f) ? "Directory" : "File") << "\n";
    if (!fs::is_directory(f)) cout << "Size: " << fs::file_size(f) << " bytes\n";
    cout << "Modified: " << ctime(&tt);
}

void searchFile(const fs::path &p, const string &name) {
    for (auto &e : fs::recursive_directory_iterator(p))
        if (e.path().filename().string().find(name) != string::npos)
            cout << e.path().string() << "\n";
}

void printTree(const fs::path &path, string indent = "") {
    for (auto &e : fs::directory_iterator(path)) {
        cout << indent << "|-- " << e.path().filename().string();
        if (fs::is_directory(e)) {
            cout << "/\n";
            printTree(e.path(), indent + "   ");
        } else cout << "\n";
    }
}

void showHistory() {
    if (history.empty()) { cout << "No commands yet.\n"; return; }
    for (size_t i = 0; i < history.size(); ++i)
        cout << i + 1 << ": " << history[i] << "\n";
}

void clearScreen() { system("clear"); }

void showHelp() {
    cout << "\nCommands:\n"
         << " pwd               → Show current directory\n"
         << " ls                → List files & folders\n"
         << " cd <dir>          → Change directory\n"
         << " mkdir <dir>       → Create directory\n"
         << " touch <file>      → Create file\n"
         << " cp <src> <dest>   → Copy file/folder\n"
         << " mv <src> <dest>   → Move or rename\n"
         << " rm <target>       → Delete file/folder\n"
         << " info <file>       → File details\n"
         << " find <name>       → Search recursively\n"
         << " tree              → Display folder tree\n"
         << " history           → Show all commands used\n"
         << " clear             → Clear screen\n"
         << " help              → Show this help\n"
         << " exit              → Exit explorer\n\n";
}

// ---------- Main ---------- //
int main() {
    cout << "RahulFileExplorer (Final Build)\n";
    cout << "Type 'help' to view commands.\n\n";

    string line;
    while (true) {
        cout << fs::current_path().string() << " $ ";
        getline(cin, line);
        if (line.empty()) continue;
        history.push_back(line);

        stringstream ss(line);
        string cmd, a1, a2;
        ss >> cmd >> a1 >> a2;

        if (cmd == "pwd") showPwd();
        else if (cmd == "ls") listDir();
        else if (cmd == "cd") changeDir(a1);
        else if (cmd == "mkdir") makeDir(a1);
        else if (cmd == "touch") makeFile(a1);
        else if (cmd == "cp") copyFile(a1, a2);
        else if (cmd == "mv") moveFile(a1, a2);
        else if (cmd == "rm") removeFile(a1);
        else if (cmd == "info") fileInfo(a1);
        else if (cmd == "find") searchFile(fs::current_path(), a1);
        else if (cmd == "tree") printTree(fs::current_path());
        else if (cmd == "history") showHistory();
        else if (cmd == "clear") clearScreen();
        else if (cmd == "help") showHelp();
        else if (cmd == "exit") {
            cout << "Exit? (y/n): ";
            string c; getline(cin, c);
            if (c == "y" || c == "Y") break;
        }
        else cout << "Unknown command\n";
    }

    cout << "Goodbye, Rahul!\n";
    return 0;
}
