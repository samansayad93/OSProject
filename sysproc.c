#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

//this is change
int
sys_set_limit(void)
{
  int cpu_limit,mem_limit;
  if(argint(0, &cpu_limit) < 0 || argint(1, &mem_limit) < 0)
    return -1;
  
  struct proc *p = myproc();
  
  // Validate limit
  if(cpu_limit < 0 || cpu_limit > 100)
    return -1;
  
  // Strict enforcement
  p->cpu_limit = cpu_limit;
  p->cpu_usage_ms = 0;
  p->last_check_tick = ticks;

  if(mem_limit < 0)
    return -1;
  
  p->memory_limit = mem_limit;
  p->current_memory_used = 0;
  
  return 0;
}

int sys_change_memory_usage(void){
  int size;
  struct proc *p;
  if(argint(0, &size) < 0)
    return 0;
  
  p = myproc();
  if(p->memory_limit <= 0)
    return 1;
  if(p->current_memory_used + size > p->memory_limit){
      cprintf("Memory allocation denied: current = %d, size = %d, limit = %d\n",
              p->current_memory_used, size, p->memory_limit);
    return 0;
  }
  p->current_memory_used += size;
  if(p->current_memory_used < 0)
    p->current_memory_used = 0;
  cprintf("Checking memory allocation: current = %d, size = %d, limit = %d\n", 
      p->current_memory_used, size, p->memory_limit);
  return 1;
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
