#include "types.h"
#include "pstat.h"

struct stat;

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

// per-process state available for user programs
struct uproc {
    uint            sz;             // size of process memory (bytes)
    char            state[6];          // process state
    int             pid;            // process id
    int             ppid;           // parent process pid
    char            name[16];       // process name (debugging)
    int     num_syscalls;
};

// system calls
int fork(void);
int exit(int) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(char*, int);
int mknod(char*, short, short);
int unlink(char*);
int fstat(int fd, struct stat*);
int link(char*, char*);
int mkdir(char*);
int chdir(char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);

int getprocs(struct uproc*);
int getpinfo(struct pstat *);

int thread_create(uint* thread, void* (*start_routine)(void*), void* arg);
int thread_join(uint thread);
int thread_exit();

int waitpid(int);

int barrier_init(int);
int barrier_check(void);

void sleepChan(int);
int getChannel(void);
void sigChan(int);
void sigOneChan(int);

struct lock{
    int lockvar;
    int isInitiated;
};

struct condvar{
    int var;
    int isInitiated;
};  

struct semaphore{
    int ctr;
    struct lock l;
    struct condvar cv;
    int isInitiated;
};

// ulib.c
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
int printf(int, char*, ...); //Assignment 4 says void printf()
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);

//assignment 03:
int pgpte(void *va); // returns the PTE for the given virtual address
int ugetpid(void);
int kpt(void);

// Assignment 4:
void initiateLock(struct lock* l);
void acquireLock(struct lock* l);
void releaseLock(struct lock* l);
void initiateCondVar(struct condvar* cv);
void condWait(struct condvar* cv, struct lock* l);
void broadcast(struct condvar* cv);
void semInit(struct semaphore* s, int initVal);
void semUp(struct semaphore* s);
void semDown(struct semaphore* s); 