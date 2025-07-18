# Store Management System

A Qt6 desktop application for managing store transactions with UDP broadcasting capabilities.

## Features

- Add and manage customers
- Add items (Books and Magazines) to inventory
- Create transactions linking customers with items
- Broadcast transaction data over UDP network
- Built-in UDP receiver for monitoring broadcasts
- Backup and restore items functionality

## Requirements

- Qt6
- C++17 compatible compiler
- CMake 3.16 or higher

## Build Instructions

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

### Basic Operations
1. **Add Customer**: `Data → Add Customer` (Ctrl+U)
2. **Add Items**: Click "Add item" in toolbar (Ctrl+I)
3. **Create Transaction**: Click "Create transaction" in toolbar (Ctrl+T)

### Network Features
- **Start Broadcasting**: `Network → Start Broadcasting`
- **Open UDP Receiver**: `Network → Open UDP Receiver`

### Data Management
- **Restore Items**: `Data → Restore Items` - Restores items from backup

## Keyboard Shortcuts

- Ctrl+U: Add Customer
- Ctrl+I: Add Item  
- Ctrl+T: Create Transaction
- Ctrl+Q: Exit

## About

Store Management System v1.0  
COS3711 Assignment 2  
Built with Qt6 and C++