# sysmon - System Monitor

A terminal-based system monitoring tool written in C using ncurses.

## Features

- Real-time CPU monitoring
- Memory usage tracking
- Disk usage information
- Process monitoring
- Network statistics

## Requirements

- GCC compiler
- GNU Make
- ncurses development libraries

## Installation

### Quick Setup (Automated)

Run the setup script to automatically install all dependencies:

```bash
make setup
```

This will detect your operating system and install the required packages.

### Manual Setup

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install -y build-essential libncurses-dev
```

**Fedora/RHEL/CentOS:**
```bash
sudo yum groupinstall -y "Development Tools"
sudo yum install -y ncurses-devel
```

**Arch Linux:**
```bash
sudo pacman -S base-devel ncurses
```

**macOS:**
```bash
brew install gcc ncurses
```

## Building

After installing dependencies, build the project:

```bash
make build
```

Or simply:

```bash
make
```

## Running

```bash
./sysmon
```

## Cleaning

To remove compiled files:

```bash
make clean
```

## Project Structure

```
.
├── include/          # Header files
│   ├── cpu.h
│   ├── disk.h
│   ├── display.h
│   ├── memory.h
│   ├── network.h
│   └── process.h
├── src/              # Source files
│   ├── main.c
│   ├── cpu.c
│   ├── disk.c
│   ├── display.c
│   ├── memory.c
│   ├── network.c
│   └── process.c
├── Makefile
├── setup.sh
└── README.md
```

## Troubleshooting

- If compilation fails with `fatal error: ncurses.h: No such file or directory`, run `make setup` to install dependencies
- Ensure you have write permissions to the project directory
- On some systems, you may need to run `make setup` with sudo privileges

## Development Notes

- The project uses ncurses for terminal UI rendering
- All source files are located in `src/` with headers in `include/`
- Use `make clean` before rebuilding after major changes
