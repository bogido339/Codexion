*This project has been created as part of the 42 curriculum by mbougajd.*

# Codexion

## Description
**Codexion** is a concurrency simulation project designed to explore the complexities of multi-threading, resource contention, and task scheduling. Inspired by the classic "Dining Philosophers" problem, this project simulates a high-pressure environment where multiple programmers (**Coders**) must share a limited number of hardware keys (**Dongles**) to complete their tasks. 

The primary goal of the project is to manage thread synchronization efficiently, ensuring that coders can strictly follow their routine (Compiling, Debugging, Refactoring) without encountering deadlocks or dying from "burnout" due to resource starvation. The simulation implements advanced scheduling algorithms (FIFO and EDF) to intelligently distribute the dongles.

## Instructions
### Compilation & Installation
The project includes a `Makefile` for easy compilation. Ensure you have `cc` or `gcc` and `make` installed.

1. Clone the repository and navigate into it:
   git clone <your_repo_link>
   cd codexion

2. Compile the executable:
   make

### Execution
Run the program with the following 8 mandatory arguments:
./codexion [number_of_coders] [time_to_burnout] [time_to_compile] [time_to_debug] [time_to_refactor] [number_of_compiles_required] [dongle_cooldown] [scheduler]

*Example:* `./codexion 5 800 200 200 200 7 50 edf`

## Blocking cases handled
To ensure a stable and accurate simulation, several concurrency issues were addressed:
* **Deadlock prevention & Coffman’s conditions:** Circular wait is prevented during the initial push to the dongles. Coders with odd IDs and even IDs request dongles in different orders, or are managed strictly by the scheduler's heap structure to ensure multiple threads do not lock resources in a circular dependency.
* **Starvation prevention:** Implemented through the `scheduler` parameter (`fifo` or `edf`). The scheduling logic ensures that dongles are granted based on strict priority (e.g., Earliest Deadline First based on `last_compile_time`), guaranteeing that no coder is infinitely bypassed.
* **Cooldown handling:** Managed by checking the time elapsed since a dongle was `last_released` against the `dongle_cooldown` configuration before allowing it to be acquired again.
* **Precise burnout detection:** Handled by a dedicated monitor thread that continuously polls the `last_compile_time` of every coder. If the time elapsed exceeds `time_to_burnout`, it instantly flags the simulation to stop.
* **Log serialization:** Console output is strictly protected by a `print_mutex` to prevent scrambled text, ensuring that every coder's status log is printed chronologically and atomically.

## Thread synchronization mechanisms
The implementation relies heavily on POSIX thread primitives to ensure safe memory access and coordination:
* **`pthread_mutex_t`:** Extensively used throughout the project to protect shared state.
    * **Resource Coordination:** Each dongle has an `availability_mutex` to protect its `is_available` flag and a `heap_mutex` to safely manage the priority queue of coders waiting for it.
    * **State Monitoring:** The `compile_mutex` protects reads and writes to a coder's `compile_count` and `last_compile_time`. This prevents race conditions where a coder might update their compile time at the exact moment the monitor thread is checking for burnout.
    * **Simulation Control:** A global `stop_simulation_mutex` acts as a thread-safe flag. When the monitor detects a burnout or all compiles are finished, it safely locks and sets this flag, and all coder threads cleanly exit their routines upon reading it.
* **Race Condition Prevention:** By strictly wrapping variable reads and writes inside mutex locks (e.g., using helper functions like `get_compile_time` and `update_compile_time`), the architecture guarantees that no two threads can simultaneously modify or read a partially updated state.

## Resources
* **References:**
  * POSIX Threads Programming (Lawrence Livermore National Laboratory)
  * Operating System Concepts (Silberschatz, Galvin, Gagne) - Chapters on Concurrency and Deadlocks.
  * The Dining Philosophers Problem and Coffman's conditions.
* **Use of AI:** Artificial Intelligence (Google Gemini) was utilized strictly as a "Code Architect" to review the project's file structure and function names. AI was used to suggest a cleaner, modular architecture (enforcing the Single Responsibility Principle and a maximum of 5 functions per file) and to generate better `snake_case` naming conventions for readability. AI did *not* write the core logical algorithms or synchronization mechanisms.