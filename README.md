# 🔍 Inverted Search

A C-based implementation of an **Inverted Search Engine** that builds an inverted index from multiple text files, enabling fast and efficient keyword searching. This project demonstrates core concepts of **Data Structures**, **Hashing**, **Linked Lists**, **Dynamic Memory Allocation**, and **File Handling** in C.

---

## 📌 Table of Contents

* Overview
* Features
* Technologies Used
* Project Structure
* How It Works
* Compilation
* Execution
* Sample Output
* Learning Outcomes
* Author

---

## 📖 Overview

An **Inverted Search** is a search technique that maps each unique word to the files in which it appears. Instead of scanning every file during a search, the program first creates an inverted index, allowing words to be located quickly and efficiently.

This project accepts multiple text files as input, creates an indexed database, and provides options to search, display, save, and update the database.

---

## ✨ Features

* Create an inverted index from multiple text files.
* Validate input files before indexing.
* Efficient searching using hashing.
* Display the complete indexed database.
* Save the database to a file.
* Update the database from a previously saved file.
* Modular and well-structured implementation.
* Fast keyword lookup.

---

## 🛠️ Technologies Used

* C Programming
* Data Structures
* Hash Tables
* Linked Lists
* Dynamic Memory Allocation
* File Handling
* GCC Compiler
* Makefile
* Linux

---

## 📂 Project Structure

```text
Inverted_Search/
│
├── main.c
├── create_database.c
├── display_database.c
├── file_validation.c
├── hash_function.c
├── insert_last.c
├── save_database.c
├── search.c
├── update_database.c
├── inverted_Search.h
├── Makefile
├── file1.txt
├── file2.txt
└── README.md
```

---

## ⚙️ How It Works

1. Read multiple text files.
2. Validate the files.
3. Extract every word from each file.
4. Generate a hash key based on the first character.
5. Store words in a hash table.
6. Maintain file names and occurrence counts using linked lists.
7. Search any word in constant average time.
8. Save or reload the database whenever required.

---

## 🚀 Compilation

Using Makefile:

```bash
make
```

Or compile manually:

```bash
gcc *.c -o inverted_search
```

---

## ▶️ Execution

```bash
./inverted_search file1.txt file2.txt
```

You can provide multiple text files as command-line arguments.

---

## 📋 Menu

```text
------------- MENU -------------

1. Create Database
2. Display Database
3. Search
4. Save Database
5. Update Database
6. Exit
```

---

## 📸 Sample Output

```text
------------- MENU -------------

1. Create Database
2. Display Database
3. Search
4. Save Database
5. Update Database
6. Exit

Enter your choice : 1

Database created successfully.

Enter your choice : 3

Enter the word to search : embedded

Word Found!

File Name : file1.txt
Word Count : 5
```

---

## 🎯 Learning Outcomes

This project helped in understanding:

* Hash Tables
* Linked Lists
* File Processing
* Dynamic Memory Allocation
* Searching Algorithms
* Data Structures in C
* Modular Programming
* Makefile Usage

---

## 👨‍💻 Author

**Shubham Shivpujimath**

**GitHub:** https://github.com/ShubhamShivpujimath

**LinkedIn:** https://www.linkedin.com/in/shubham-shivapujimath-063b79208

---

## ⭐ Support

If you found this project useful, please consider giving it a **Star ⭐** on GitHub.
