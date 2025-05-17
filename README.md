# Operating-System-Stimulator
Nexis Operating System 🖥️

Welcome to Nexis OS, a mini operating system simulator built in C++ as a semester project. Nexis demonstrates core OS concepts like multitasking, resource management, and process scheduling, complete with interactive applications. 🚀

# Overview
Nexis OS simulates a POSIX-compliant operating system, managing tasks across multiple cores with dynamic scheduling and FIFO-based inter-process communication. It includes a suite of applications like Calculator, Hangman, Calendar, and Notepad, each running in separate xterm windows for a user-friendly experience.

# Key Features
🛠️ Multitasking: Handles concurrent tasks using ready and waiting queues.
📊 Resource Monitoring: Tracks RAM, storage, and core availability.
🔄 FIFO Communication: Facilitates process termination and resource deallocation.
📱 Applications: Includes Calculator, Hangman, Calendar, Clock, Notepad, Tower of Hanoi, and more.
🔧 Kernel/User Modes: Supports administrative resource updates and standard operations.
⏰ Dynamic Scheduling: Assigns tasks to cores efficiently.

# Working Environment
Developed on Ubuntu WSL with Visual Studio 2022, using:
- g++ for compilation
- xterm for running applications
- CMake for build management

# Prerequisites
- Ubuntu (or WSL on Windows) with g++ and make installed
- xterm for running applications (sudo apt-get install xterm)
- Basic POSIX-compliant environment
- [Optional] CMake for build automation

# Installation
- Clone the Repository:
git clone https://github.com/zonia7867/Operating-System-Stimulator.git
cd NexisOS

Compile the Project:
g++ main.cpp -o main
Note: Individual application files (e.g., calculator.cpp, hangman.cpp) are compiled automatically by main.cpp when needed. Ensure all .cpp files are in the same directory.

# Install Dependencies:
sudo apt-get update
sudo apt-get install xterm

# Usage
Run the OS:
./main

# Interact with Nexis:
Select Kernel Mode (0) to modify resource needs or User Mode (1) for standard operation.
Enter system specs (RAM, HDD, cores, threads).
Choose from 16 options, including apps like Calculator 🧮, Hangman 🎮, Calendar 📅, or terminate the OS.
Applications launch in separate xterm windows.

# Exit:
Select option 16 to terminate the OS, which closes all xterm instances and deallocates resources.

# Project Structure

main.cpp: Core OS logic for scheduling, resource management, and app launching.
calculator.cpp: Simple arithmetic calculator.
calender.cpp: Displays a monthly calendar.
hangman.cpp: Classic word-guessing game.
Other application files (e.g., towerofhanoi.cpp, notepad.cpp) for additional features.

Feel free to fork this repository, submit issues, or create pull requests to enhance Nexis OS. Contributions are welcome!
Happy exploring with Nexis OS! 🌟 For questions or feedback, open an issue or reach out.
