#!/bin/bash

# Setup script for sysmon project
# This script installs required dependencies for building the project

set -e  # Exit on error

echo "Setting up sysmon dependencies..."

# Detect OS and install dependencies accordingly
if command -v apt-get &> /dev/null; then
    # Debian/Ubuntu
    echo "Detected Debian/Ubuntu system"
    echo "Installing dependencies: build-essential, libncurses-dev..."
    sudo apt-get update
    sudo apt-get install -y build-essential libncurses-dev

elif command -v yum &> /dev/null; then
    # RedHat/CentOS/Fedora
    echo "Detected RedHat-based system"
    echo "Installing dependencies: gcc, make, ncurses-devel..."
    sudo yum groupinstall -y "Development Tools"
    sudo yum install -y ncurses-devel

elif command -v pacman &> /dev/null; then
    # Arch Linux
    echo "Detected Arch Linux system"
    echo "Installing dependencies: base-devel, ncurses..."
    sudo pacman -S --noconfirm base-devel ncurses

elif command -v brew &> /dev/null; then
    # macOS
    echo "Detected macOS system"
    echo "Installing dependencies: gcc, ncurses..."
    brew install gcc ncurses

else
    echo "Error: Unsupported package manager"
    echo "Please install the following manually:"
    echo "  - GCC compiler"
    echo "  - GNU Make"
    echo "  - ncurses development libraries"
    exit 1
fi

echo "✓ Dependencies installed successfully"
echo "✓ Run 'make build' to compile the project"
