# 📄 Text Document Compression – Huffman Coding


This project implements the **Huffman coding** algorithm for lossless compression of text documents. The goal is to reduce the file size while preserving the ability to fully reconstruct the original content.

## 🧠 Overview

Huffman coding is a classic data compression algorithm that assigns shorter binary codes to more frequent characters and longer codes to less frequent ones. This results in a reduced overall file size without any data loss.

Key features:

- Analyzes character frequency in a text file
- Builds a Huffman tree
- Generates a Huffman code dictionary
- Compresses the input text into binary format
- Decompresses the binary back to the original text

---

## 🔧 Build Instructions

In the provided folder, create a directory named `build`:

```bash
mkdir build
cd build
cmake ..
make
```

### 📌 Usage
Run the program with one of the following options along with the path to the file:

- compression ("c")
```bash 
./huffman c ../file.txt
```
The output will be a compressed file named `<filename>_c.bin`.

- decompression ("d")
```bash 
./huffman d ../file.bin
```
The output will be a decompressed file named `<filename>_d.txt`.

A sample file (`file.txt`) generated in Polish is included in the folder to test the program.

---

## ⚙️ Requirements
- C++11 or newer (C++14 or C++17 recommended)  
- CMake 3.26 or newer

---

### 📝 License

MIT License © 2025 Michau-H
