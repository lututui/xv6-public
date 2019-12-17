

# Scheduling and Memory Management
**University of Monitoba: March 18, 2016, Noon.**

## Task 1: Scheduling Policies

Scheduling is a basic and important facility of any operating system. The scheduler must satisfy several conflicting objectives: fast process response time, good throughput for background jobs, avoidance of process starvation, reconciliation of the needs of low-priority and high-priority processes, and so on. The set of rules used to determine when and how to select a new process to run is called a scheduling policy.

You first need to understand the current scheduling policy. Locate it in the code and try to answer the following questions:

* Which process the policy chooses to run?
* What happens when a process returns from I/O?
* What happens when a new process is created ?
* When/how often the scheduling takes place?

First, change the current scheduling code so that swapping out running processes will be done every quanta size (measured in clock ticks) instead of every clock tick.

```c
#define QUANTA <int value>
```

Add this line to **param.h** and initialize the value of QUANTA to 5.

In the next part of the assignment you will add four different scheduling policies in addition to the existing policy.
Add these policies by using the C preprocessing abilities.

Tip: You should read about `#IFDEF` macros. These can be set during compilation by gcc (see http://gcc.gnu.org/onlinedocs/cpp/Ifdef.html)

Modify the Makefile to support ‘SCHEDFLAG’.
Obs. A macro for quick compilation of the appropriate scheduling scheme. Thus the following line will invoke the xv6 build with Round Robin scheduling:

```bash
make qemu SCHEDFLAG=FRR
```

The default value for SCHEDFLAG should be DEFAULT (in the Makefile).

Tip: you can (and should!) read more about the make utility [here](http://www.opussoftware.com/tutorial/TutMakefile.htm).


### Policy 1: Default policy (SCHEDFLAG=DEFAULT)

Represents scheduling policy currently implemented at xv6.

### Policy 2: FIFO Round Robin (SCHEDFLAG=FRR)
This policy will extend the previous default policy. In this policy the decision of which process will run next will be on a First In-First Out basis. When a process finishes running for QUANTA time, created or finishes waiting for I/O it is considered to be the
last process to arrive and wait for its next turn to run.

### Policy 3: First Come First Served (SCHEDFLAG=FCFS)
This is a non-preemptive policy. Process that gets CPU runs until it no longer needs the CPU (yield / finish/ blocked). This policy is somewhat like FIFO Round Robin with infinite quanta.


## Task 2: Sanity Test
In this task  you will add applications which test the impact of each scheduling policy.  Similar to several built-in user space programs in xv6 (e.g., ls, grep, echo, etc.), you can add your own user space programs to xv6.

### Task 2.1: Test 1 – FIFO Round Robin Sanity Test

Add  a  program called **FRRsanity**.  This  program  will  fork  10  child  processes.  Each  child process will print 1000 times (each time in a new line): `child <pid> prints for the <i> time`, where `<pid>` is that child’s pid, and `<i>` is the iteration number. After the child process  prints 1000  times,  it  will  exit. The  parent process  will  wait  until all  of  its children exit, and only after they all exit, it print the waiting time, running time and turnaround time of each child.



### Task 2.2: Test 2 – First Come First Served Sanity Test

Add  a  program called FCFSsanity.  This  program  will  fork  10  child  processes.  Each  child process will print 1000 times (each time in a new line): `child <pid> prints for the <i> time`, where `<pid>` is that child’s pid, and `<i>` is the iteration number. After the child process  prints 1000  times,  it  will  exit. The  parent process  will  wait  until all  of  its children exit, and only after they all exit, it print the waiting time, running time and turnaround time of each child.

## Introduction
Memory management and memory abstraction is one of the most important features of any operating system. In this assignment we will examine how xv6 handles memory and attempt to extend it.

To help get you started we will provide a brief overview of the memory management facilities of xv6. We strongly encourage you to read this section while examining the relevant xv6 files (vm.c, mmu.h,kalloc.c, etc).

Memory in xv6 is managed in pages (and frames) where each such page is 4096 (=212) bytes long. Each process has its own page table which is used to translate virtual to physical addresses.

The virtual address space can be significantly larger than the physical memory. In xv6, the process address space is 232 bytes long while the physical memory is limited to 16MB only. When a process attempts to access some address in its memory (i.e. provides a 32 bit virtual address) it must first seek out the relevant page in the physical memory. xv6 uses the first (leftmost) 20 bits to locate the relevant Page Table Entry (PTE) in the page table. The PTEwill contain the physical location of the frame – a 20 bits frame address (within the physical memory). These 20 bits will point to the relevant frame within the physical memory. To locate the exact address within the frame, the 12least significant bits of the virtual address, which represent the in-frame offset, are concatenated to the 20 bitsretrieved from the PTE. Roughly speaking, this process can be described by the following illustration:




Maintaining a page table may require significant amount of memory as well, so a two level page table is used. The following figure describes the process in which a virtual address translates into a physical one:





Each process has a pointer to its page directory (line 59, proc.h). This is a single page sized (4096 bytes) directory which contains the page addresses and flags of the second level table(s). This second level table is spanned across multiple pages which are very much like the page directory.

When seeking an address the first 10 bits will be used to locate the correct entry within the page directory (by using the macro PDX(va)). The physical frame address can be found within the correct index of the second level table (accessible via the macro PTX(va)). As explained earlier, the exact address may be found with the aid of the 12 LSB (offset).

At this point you should go over the xv6 documentation on this subject, particularly, Chapter 2(http://www.cs.umanitoba.ca/%7Ecomp4430/readings/book-rev8.pdf).


# Scheduling and Memory Management
**University of Monitoba: March 18, 2016, Noon.**

## Task 1: Scheduling Policies

Scheduling is a basic and important facility of any operating system. The scheduler must satisfy several conflicting objectives: fast process response time, good throughput for background jobs, avoidance of process starvation, reconciliation of the needs of low-priority and high-priority processes, and so on. The set of rules used to determine when and how to select a new process to run is called a scheduling policy.

You first need to understand the current scheduling policy. Locate it in the code and try to answer the following questions:

* Which process the policy chooses to run?
* What happens when a process returns from I/O?
* What happens when a new process is created ?
* When/how often the scheduling takes place?

First, change the current scheduling code so that swapping out running processes will be done every quanta size (measured in clock ticks) instead of every clock tick.

```c
#define QUANTA <int value>
```

Add this line to **param.h** and initialize the value of QUANTA to 5.

In the next part of the assignment you will add four different scheduling policies in addition to the existing policy.
Add these policies by using the C preprocessing abilities.

Tip: You should read about `#IFDEF` macros. These can be set during compilation by gcc (see http://gcc.gnu.org/onlinedocs/cpp/Ifdef.html)

Modify the Makefile to support ‘SCHEDFLAG’.
Obs. A macro for quick compilation of the appropriate scheduling scheme. Thus the following line will invoke the xv6 build with Round Robin scheduling:

```bash
make qemu SCHEDFLAG=FRR
```

The default value for SCHEDFLAG should be DEFAULT (in the Makefile).

Tip: you can (and should!) read more about the make utility [here](http://www.opussoftware.com/tutorial/TutMakefile.htm).


### Policy 1: Default policy (SCHEDFLAG=DEFAULT)

Represents scheduling policy currently implemented at xv6.

### Policy 2: FIFO Round Robin (SCHEDFLAG=FRR)
This policy will extend the previous default policy. In this policy the decision of which process will run next will be on a First In-First Out basis. When a process finishes running for QUANTA time, created or finishes waiting for I/O it is considered to be the
last process to arrive and wait for its next turn to run.

### Policy 3: First Come First Served (SCHEDFLAG=FCFS)
This is a non-preemptive policy. Process that gets CPU runs until it no longer needs the CPU (yield / finish/ blocked). This policy is somewhat like FIFO Round Robin with infinite quanta.


## Task 2: Sanity Test
In this task  you will add applications which test the impact of each scheduling policy.  Similar to several built-in user space programs in xv6 (e.g., ls, grep, echo, etc.), you can add your own user space programs to xv6.

### Task 2.1: Test 1 – FIFO Round Robin Sanity Test

Add  a  program called **FRRsanity**.  This  program  will  fork  10  child  processes.  Each  child process will print 1000 times (each time in a new line): `child <pid> prints for the <i> time`, where `<pid>` is that child’s pid, and `<i>` is the iteration number. After the child process  prints 1000  times,  it  will  exit. The  parent process  will  wait  until all  of  its children exit, and only after they all exit, it print the waiting time, running time and turnaround time of each child.



### Task 2.2: Test 2 – First Come First Served Sanity Test

Add  a  program called FCFSsanity.  This  program  will  fork  10  child  processes.  Each  child process will print 1000 times (each time in a new line): `child <pid> prints for the <i> time`, where `<pid>` is that child’s pid, and `<i>` is the iteration number. After the child process  prints 1000  times,  it  will  exit. The  parent process  will  wait  until all  of  its children exit, and only after they all exit, it print the waiting time, running time and turnaround time of each child.

## Introduction
Memory management and memory abstraction is one of the most important features of any operating system. In this assignment we will examine how xv6 handles memory and attempt to extend it.

To help get you started we will provide a brief overview of the memory management facilities of xv6. We strongly encourage you to read this section while examining the relevant xv6 files (vm.c, mmu.h,kalloc.c, etc).

Memory in xv6 is managed in pages (and frames) where each such page is 4096 (=212) bytes long. Each process has its own page table which is used to translate virtual to physical addresses.

The virtual address space can be significantly larger than the physical memory. In xv6, the process address space is 232 bytes long while the physical memory is limited to 16MB only. When a process attempts to access some address in its memory (i.e. provides a 32 bit virtual address) it must first seek out the relevant page in the physical memory. xv6 uses the first (leftmost) 20 bits to locate the relevant Page Table Entry (PTE) in the page table. The PTEwill contain the physical location of the frame – a 20 bits frame address (within the physical memory). These 20 bits will point to the relevant frame within the physical memory. To locate the exact address within the frame, the 12least significant bits of the virtual address, which represent the in-frame offset, are concatenated to the 20 bitsretrieved from the PTE. Roughly speaking, this process can be described by the following illustration:

![image](https://user-images.githubusercontent.com/17522256/71013677-d3166200-20cf-11ea-9dba-50f920b354a7.png)

Maintaining a page table may require significant amount of memory as well, so a two level page table is used. The following figure describes the process in which a virtual address translates into a physical one:


![image](https://user-images.githubusercontent.com/17522256/71013914-e295ab00-20cf-11ea-97cb-0fd775218118.png)


Each process has a pointer to its page directory (line 59, proc.h). This is a single page sized (4096 bytes) directory which contains the page addresses and flags of the second level table(s). This second level table is spanned across multiple pages which are very much like the page directory.

When seeking an address the first 10 bits will be used to locate the correct entry within the page directory (by using the macro `PDX(va)`). The physical frame address can be found within the correct index of the second level table (accessible via the macro `PTX(va)`). As explained earlier, the exact address may be found with the aid of the 12 LSB (offset).

At this point you should go over the xv6 documentation on this subject, particularly, [Chapter 2](http://www.cs.umanitoba.ca/%7Ecomp4430/readings/book-rev8.pdf).

Tip: before proceeding further we strongly recommend that you go over the code again. Now, attempt to answer questions such as:

* How does the kernel know which physical pages are used and unused?
* What data structures are used to answer this question?
* Where do these reside?
* Does xv6 memory mechanism limit the number of user processes?
* What is the lowest number of processes xv6 can ‘have’ at the same time?

## Task 3 - Null pointer protection
Many software exceptions occur when trying to dereference null points (accessing memory at location 0). While in certain situations it may be desirable to access the memory at address 0, it usually points to a bug in the code. For this reason modern operating systems crash after dereferencing a null pointer, making it quicker to find bugs. xv6, on the other hand, does not offer such protection and allows access to address 0, which contains the program’s text segment (go ahead and try to tamper with it).

Your task is to implement such functionality for user programs (and fork_test). To do so, make sure that the first memory page is never used (unallocated), and that the text segment begins at the second page. Find and update all the relevant places. Note that the Makefile needs to be updated as well, have a look at flag `-T`.

As a simple sanity test, write a small user program that prints out the contents of memory address 0. While this should work before the changes, when you have completed this task, accessing the memory at that location should cause an error.

## Task 4 - Protection of read-only segments
The protection described in Task 3 is not the only protection missing in xv6. Another common protection is to set segments such as the text segment as read only. An ELF file specifies which segments should be loaded as read only, however, the current makefile in xv6 links programs so that all the different sections have the same program header, and read-write-execute permissions. This stands in contrast to the way programs are usually linked. Use readelf to compare executable files built for xv6 and other regular executable files in your Linux operating system.

You should also update the Makefile (along with several other files of course). Have a look at the -N linker flag and how it relates to the information described in the previous paragraph. Make sure to handle alignment issues that may arise. Also, be sure not to allow a read-only page to become writeable following a fork command. The readelf command should prove rather useful.

As a simple sanity test, write a user program that tries to violate the new protection. In order to do so, try and rewrite program commands. Remember that the name of a function in C is actually a pointer. More specifically, the variable main is just a pointer to the location of the beginning of the code of function main. Use main as a pointer and try to read and write new values to that location. Before your change both of these operations should execute well. After adding protection, reading the code of main should work, while writing over it should cause an error.

# Acknowledgements
This assignment is borrowed from Operating Systems course (OS142) at Ben-Gurion University of Negev, Israel.


# How To Run

 1. Default scheduling
```bash
	make
	make qemu
```
	
2. FIFO Round Robin (FRR) scheduling
```bash
	make
	make qemu SCHEDFLAG=FRR
```

3. First Come First Served (FCFS) scheduling
```bash
	make
	make qemu SCHEDFLAG=FCFS
```

#### Task 2.1: Test 1 – FIFO Round Robin Sanity Test
 * Run xv6 with FRR scheduling. Within xv6, run `TestSchedSanity`.
```bash
		make
		make qemu SCHEDFLAG=FRR
		./TestSchedSanity
```		
#### Task 2.2: Test 2 – First Come First Served Sanity Test
* Run xv6 with FCFS scheduling. Within xv6, run `TestSchedSanity`.
```bash
		make
		make qemu SCHEDFLAG=FCFS
		./TestSchedSanity
```		

#### Task 3 - Null pointer protection
* Run xv6 with any scheduling. Within xv6, run `nullDereference`
```bash
		./nullDereference
```
#### Task 4 - Protection of read-only segments
* Run xv6 with any scheduling. Within xv6, run `mainWrite`
```bash
		./mainWrite
```
