# 🗂 File Explorer – Linux Capstone Project (C++)

### 💡 Overview

The _File Explorer Capstone Project_ is a Linux-based, terminal-driven file management system developed using _C++17_.  
It replicates the functionality of a Linux shell — allowing users to _navigate, **create, **move, **copy, and **analyze files and directories_ through command-line commands.

Built and tested on _Ubuntu (via WSL2)_ using _VS Code, this project demonstrates expertise in **Linux System Programming, **C++ STL, and \*\*filesystem operations_.

---

## 🧠 Objective

To design and implement a _simple command-line File Explorer_ that performs fundamental file and directory operations in Linux — while reinforcing system-level programming concepts in C++.

---

## ⚙ Technologies Used

| Tool / Technology    | Purpose                           |
| -------------------- | --------------------------------- |
| _C++17 STL_          | Core programming language         |
| _Filesystem Library_ | File and directory handling       |
| _WSL2 (Ubuntu)_      | Linux runtime environment         |
| _VS Code_            | Code editor & build environment   |
| _Makefile_           | Build automation                  |
| _Git & GitHub_       | Version control and documentation |

---

## 🗓 Day-wise Progress

### 🟩 _Day 1 – Basic Setup & Commands_

_Implemented Commands:_

- pwd → Print working directory
- ls → List files/folders
- exit → Exit the program

_Highlights:_

- Project setup and environment configuration
- Tested basic shell commands in C++
- Implemented Makefile for compilation

---

### 🟨 _Day 2 – Directory Navigation & File Creation_

_Implemented Commands:_

- cd <dir> → Change directory
- mkdir <dir> → Create directory
- touch <file> → Create a new file

_Highlights:_

- Introduced std::filesystem::current_path()
- Added exception handling for invalid directories
- Practiced argument parsing and validation

---

### 🟦 _Day 3 – File Manipulation & Information Retrieval_

_Implemented Commands:_

- cp <src> <dest> → Copy file
- mv <src> <dest> → Move or rename file
- rm <file> → Remove file
- info <file> → Display file information

_Highlights:_

- Used std::filesystem::copy, rename, remove
- Implemented chrono for last modified time
- Improved error handling and input validation

---

### 🟪 _Day 4 – Search, Tree & Help_

_Implemented Commands:_

- search <name> → Search recursively for file/folder
- info -> Information for respective file/folder
- start → Show command guide

_Highlights:_

- Recursive directory traversal using std::filesystem::recursive_directory_iterator
- Implemented info command to fetch file size, type, and timestamps
- Added color-coded output to differentiate files and folders

---

### 🟥 _Day 5 – History, Clear & Exit Confirmation_

_Implemented Commands:_

- history → Show executed commands
- clear → Clear terminal screen
- chmod <file> <perm> → Change file permissions
- start → command list
- exit → With user confirmation

_Highlights:_

- Implemented command history vector
- Enhanced UI/UX with custom color scheme (configurable via config.txt)
- Added runtime configuration for directory, file, and reset colors
- Final testing and UI polish

_Example config.txt:_

| dir \033[36m |
| file \033[33m |
| reset \033[0m |

---

## 📸 Project Screenshots

|   Day   | Description                                           | Screenshot                     |
| :-----: | :---------------------------------------------------- | :----------------------------- |
| _Day 1_ | Basic setup                                           | ![Day 1](Screenshots/Day1.png) |
| _Day 2_ | Navigation – ls,pwd,cd                                | ![Day 2](Screenshots/Day2.png) |
| _Day 3_ | File management – cp, mv, rm, info,mkdir,touch        | ![Day 3](Screenshots/Day3.png) |
| _Day 4_ | Search & info – search & info                         | ![Day 4](Screenshots/Day4.png) |
| _Day 5_ | Final version – chmod,config.txt,history, clear, exit | ![Day 5](Screenshots/Day5.png) |

---

## 🧩 Project Structure

```
file-explorer-capstone/
├── DAY1/
│ ├── file_explorer.cpp
│ └── README1.md
├── DAY2/
│ ├── file_explorer.cpp
│ └── README2.md
├── DAY3/
│ ├── file_explorer.cpp
│ ├── README3.md
│ ├── copy.txt
│ └── final.txt
├── DAY4/
│ ├── file_explorer.cpp
│ └── README4.md
├── DAY5/
│ ├── file_explorer.cpp
│ ├── README5.md
│ └── config.txt
├── src/
│ └── file_explorer.cpp # Final merged version
├── screenshots/
│ ├── DAY1.png
│ ├── DAY2.png
│ ├── DAY3.png
│ ├── DAY4.png
│ └── DAY5.png
├── Makefile
├── README.md
├── config.txt
└── .gitignore
```

---

## 💻 Build & Run Instructions

### 🔧 Build

bash
make

### ▶ Run

bash
./file_explorer

### 🧹 Clean

bash
make clean

---

## 🧪 Example Session

bash

```
pwd
ls
mkdir test
cd test
touch day3.txt
info day3.txt
cp day3.txt copy.txt
mv backup.txt
exit
```

---

## 👨‍💻 Author

_Rahul Mohanty_  
🌐 [GitHub Profile](https://github.com/RAHUL-MOHANTY)

---

## 🏁 Conclusion

This project demonstrates a practical understanding of:

- Linux filesystem operations
- Command-line interface development
- Modern C++17 features and STL
- Structured software design and documentation

💡 Capstone Project successfully implemented from Day 1 to Day 5 — fully functional and ready for demonstration!
