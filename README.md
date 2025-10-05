
---

## **Philosophers Mandatory Part**

### **Program Name**

`philo`

### **Objective**

Simulate the classic “Dining Philosophers” problem using threads and mutexes.
Each philosopher alternates between:

* **Eating** (needs 2 forks)
* **Sleeping**
* **Thinking**

The simulation stops if a philosopher dies or if all philosophers have eaten the required number of times.

---

### **Program Arguments**

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

* `number_of_philosophers`: total philosophers (and forks).
* `time_to_die`: max milliseconds a philosopher can go without eating.
* `time_to_eat`: milliseconds spent eating.
* `time_to_sleep`: milliseconds spent sleeping.
* `number_of_times_each_philosopher_must_eat` *(optional)*: stop when all have eaten this many times.

---

### **Rules**

1. Each philosopher is a **thread**.
2. There is **one fork per philosopher**, shared with neighbors.
3. **Fork access is protected by mutexes** to prevent conflicts.
4. **State logging**:

   ```
   timestamp_in_ms X has taken a fork
   timestamp_in_ms X is eating
   timestamp_in_ms X is sleeping
   timestamp_in_ms X is thinking
   timestamp_in_ms X died
   ```
5. **No global variables** are allowed.
6. **Simulation precision**: Death must be detected within 10ms of actual time.
7. **No data races** are allowed.

---

### **Implementation Overview**

* **Initialization**

  * Parse program arguments.
  * Create philosopher structures and fork mutexes.
  * Record simulation start time.
* **Philosopher Routine**

  * Repeatedly:

    1. Think
    2. Lock left & right forks (mutexes)
    3. Eat
    4. Unlock forks
    5. Sleep
  * Log each state change.
* **Monitoring**

  * Continuously checks if any philosopher has exceeded `time_to_die`.
  * Stops simulation if a death occurs or the optional meal goal is reached.
* **Deadlock Prevention**

  * Odd and even philosophers pick up forks in different orders.
  * Ensures no circular wait occurs.

---

### **Data Structures (Conceptual)**

* **Philosopher struct**:

  * ID, last meal time, meals eaten, reference to shared rules.
* **Rules struct**:

  * Number of philosophers, timing rules, forks (mutex array), print mutex, simulation status.

---

### **Notes**

* All heap-allocated memory is freed at the end.
* Mutexes are destroyed after use.
* All logs are thread-safe using a print mutex.
* Timing is calculated using `gettimeofday` for precision.

---
