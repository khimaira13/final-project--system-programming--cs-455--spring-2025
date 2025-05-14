# Spring 2025 System Programming — Final Project

## Written Portion

### 1. Describe what happens to memory released by the OS with regard to virtual memory

When a program ends or frees memory, the OS marks that virtual memory as available. The actual physical memory might not be cleared right away, but it gets reassigned to other processes when needed. The virtual address space is basically reset or reclaimed.

---

### 2. In a C program, why does `argv[argv]` return `NULL`?

it’s because argv[argc] is always NULL by definition. So if you do argv[argc], you are accessing the end of the array, which is set to NULL to mark the end of arguments.

---

### 3. When a system call is made the CPU changes from user mode to kernel mode. Why?

Because user programs aren’t allowed to directly access hardware or critical memory. System calls request the kernel to do something for the program (like read a file), and the CPU switches to kernel mode so it can safely perform that task.

---

### 4. Explain the relationship between the return value of a system call and the global variable `errno`

When a system call fails, it usually returns -1 and sets the global variable errno to a number that tells you what went wrong. So you check the return value first, and if it's -1, then look at errno for the actual reason.

---

### 5. Consider the following C program. The variables and functions get allocated to which memory segments? Write your answers in comments to the right of each item

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX 128

char my_string[MAX]; // .bss (uninitialized global)
char class_name[] = "System Programming"; // .data (initialized global)
int global_integer = 3; // .data (initialized global)

void print_global() { // .text (code)
  printf("%d\n", global_integer);
}

int square(int x) { // .text (code)
  int result = x * x; // stack

  return result;
}

int main (int argc, char *argv[]) {
  char *dynamic_memory; // stack (pointer only)
  dynamic_memory = malloc(MAX); // heap
  free(dynamic_memory);
  dynamic_memory = NULL;

  return 0;
}
```

---

### 6. Explain the difference between `malloc`, `calloc`, `realloc`

malloc(size) allocates memory but doesn't clear it.

calloc(num, size) allocates memory and sets it all to 0.

realloc(ptr, new_size) changes the size of an existing allocation — it might move the memory if needed.

---

### 7. Explain the difference between `brk` and `sbrk`. Why is `malloc` a better option of `brk`, and `sbrk`?

brk and sbrk directly control the program’s heap by changing where it ends. They’re low-level and tricky to use safely. malloc is better because it uses brk/sbrk or mmap under the hood, handles alignment, bookkeeping, and is just safer overall.

---

### 8. Explain why a shadow password file is needed

The original /etc/passwd file is world-readable, which is not safe for storing password hashes. The shadow file (/etc/shadow) keeps those hashes in a separate file that only root can read, making it more secure.

---

### 9. What is the numeric equivalent of the `README.md` file’s permission bits below, and what is the command to give the file full access, across the board?

```sh
-rw-r--r-- 1  johnnythunders  staff  3476 May  1 11:57 README.md
```

Numeric equivalent: 644
To give full access: chmod 777 README.md

---

### 10. What does `kill -9 1` do? Explain in detail

The command kill -9 1 sends signal number 9, known as SIGKILL, to the process with PID 1. The kill command is used to send a signal to a specific process, and the number 9 specifies the SIGKILL signal, which forces the process to terminate immediately without allowing it to handle the signal or perform any cleanup. PID 1 refers to the first process started by the system during boot, typically init or systemd, which manages other processes on the system.
