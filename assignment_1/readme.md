# Assignment 1
## Task

+ Implement a simple cyclic executive
	- 3 tasks: T 1 = 50 ms, T 2 = 100 ms, and T 3 = 150 ms
	- Task bodies are provided
	- Use the mechanism you prefer for implementing the periodic event (minor cycle)

+ Some hints:
	- Compute the minor cycle
	- Compute the major cycle
	- Periodic timer firing every minor cycle
	- Every time the timer fires: Read the scheduling table => Execute the appropriate tasks => sleep until next minor cycle

**Done? Try T 1 = 60 ms, T 2 = 80 ms, T 3 = 120 ms**
