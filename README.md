# Philosophers

Multithreading simulation of the classic Dining Philosophers problem using pthreads and mutexes. Focus on synchronization, deadlock avoidance, and precise timing.

## Run
```bash
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
