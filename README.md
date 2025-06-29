# PADP Lab Programs

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://github.com/TALAPANENIVARSHITHCHOWDARY/Padp_Lab_Programs)
[![Shell](https://img.shields.io/badge/Scripts-Shell-green.svg)](https://github.com/TALAPANENIVARSHITHCHOWDARY/Padp_Lab_Programs)
[![GitHub](https://img.shields.io/badge/GitHub-Repository-black.svg)](https://github.com/TALAPANENIVARSHITHCHOWDARY/Padp_Lab_Programs)

## 📋 Overview

This repository contains comprehensive lab programs for **PADP (Parallel Architecture and Distributed Programming)** course. The programs demonstrate various concepts of parallel computing, distributed systems, and high-performance computing using C programming language.

## 🗂️ Repository Structure

```
Padp_Lab_Programs/
├── Program1/          # [Program Description]
├── Program2/          # [Program Description]
├── Program3/          # [Program Description]
├── Program4/          # [Program Description]
├── Program5/          # [Program Description]
├── Program6/          # [Program Description]
├── Program7/          # [Program Description]
├── .gitattributes     # Git attributes configuration
└── README.md          # This file
```

## 🚀 Programs Overview

| Program | Topic | Description | Key Concepts |
|---------|-------|-------------|--------------|
| Program1 | | | |
| Program2 | | | |
| Program3 | | | |
| Program4 | | | |
| Program5 | | | |
| Program6 | | | |
| Program7 | | | |

## 🛠️ Prerequisites

- **GCC Compiler** - For compiling C programs
- **Linux/Unix Environment** - Recommended for running parallel programs
- **OpenMP** - For parallel programming (if applicable)
- **MPI** - For distributed computing (if applicable)
- **POSIX Threads** - For multi-threading (if applicable)

## 📦 Installation & Setup

1. **Clone the repository:**
   ```bash
   git clone https://github.com/TALAPANENIVARSHITHCHOWDARY/Padp_Lab_Programs.git
   cd Padp_Lab_Programs
   ```

2. **Navigate to any program directory:**
   ```bash
   cd Program1
   ```

3. **Compile the program:**
   ```bash
   gcc -o program program.c
   # For OpenMP programs:
   gcc -fopenmp -o program program.c
   # For MPI programs:
   mpicc -o program program.c
   ```

4. **Run the program:**
   ```bash
   ./program
   # For MPI programs:
   mpirun -np 4 ./program
   ```

## 🔧 Compilation Instructions

### Standard C Programs
```bash
gcc -o output_file source_file.c
```

### OpenMP Programs
```bash
gcc -fopenmp -o output_file source_file.c
```

### MPI Programs
```bash
mpicc -o output_file source_file.c
mpirun -np [number_of_processes] ./output_file
```

### Pthread Programs
```bash
gcc -pthread -o output_file source_file.c
```

## 📊 Key Topics Covered

- **Parallel Programming Concepts**
  - Shared Memory Programming
  - Distributed Memory Programming
  - Hybrid Programming Models

- **Synchronization Mechanisms**
  - Locks and Mutexes
  - Semaphores
  - Barriers

- **Parallel Algorithms**
  - Parallel Sorting
  - Matrix Operations
  - Numerical Computations

- **Performance Analysis**
  - Speedup Calculations
  - Efficiency Measurements
  - Load Balancing

## 🚀 Technologies Used

- ![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white) **C Programming Language**
- ![OpenMP](https://img.shields.io/badge/OpenMP-0078D4?style=flat&logo=openmp&logoColor=white) **OpenMP** (if applicable)
- ![MPI](https://img.shields.io/badge/MPI-FF6B6B?style=flat&logo=mpi&logoColor=white) **Message Passing Interface** (if applicable)
- ![Shell](https://img.shields.io/badge/Shell-4EAA25?style=flat&logo=gnu-bash&logoColor=white) **Shell Scripts**

## 📈 Learning Outcomes

After completing these programs, you will understand:

- ✅ Fundamentals of parallel and distributed computing
- ✅ Implementation of parallel algorithms
- ✅ Performance optimization techniques
- ✅ Synchronization and communication in parallel systems
- ✅ Load balancing and scalability concepts

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👨‍💻 Author

**Varshith Chowdary Talapaneni**
- GitHub: [@TALAPANENIVARSHITHCHOWDARY](https://github.com/TALAPANENIVARSHITHCHOWDARY)
- Email: [Your Email] (Add your email if you want)

## 🙏 Acknowledgments

- Course Instructor and Teaching Assistants
- Parallel Computing Community
- Open Source Contributors

## 📚 Additional Resources

- [OpenMP Documentation](https://www.openmp.org/specifications/)
- [MPI Documentation](https://www.mpi-forum.org/docs/)
- [Parallel Computing Books and Tutorials]

---

⭐ **If you find this repository helpful, please give it a star!** ⭐
