<h1 align="center">Philosophers</h1>

<p align="center">
    <em>This project has been created as part of the 42 curriculum by antabord.</em>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c"/>
  <img src="https://img.shields.io/badge/School-42-black?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Unix-System-orange?style=for-the-badge&logo=linux"/>
</p>

<h2>Project Overview</h2>
<p>This project is a concurrency simulation based on the classic Dining Philosophers problem. The goal is to learn how to handle resourse sharing between threads, using <a href="#mutexes"><strong>mutexes</strong></a> to avoid <a href="#race-condition"><strong>race-conditions</strong></a>, <a href="#deadlock"><strong>deadlock</strong></a> or <a href="#starvation"><strong>starvation</strong></a> which are just simptoms of missmanaged resources.</p>

<h3>Estrutura do projeto</h3>

<pre>
philosophers/
├── README.md
└── philo/
    ├── Makefile
    ├── include/
    │   ├── philo.h
    │   └── structs.h
    └── src/
        ├── p_meal_check.c			## monitor thread
        ├── p_monitor.c
        ├── p_routine.c				## main loop execution
        ├── p_single_philo.c		## exeption
        ├── p_threads.c
        └── p_threads.o
</pre>

<h3>Running the project</h3>

Follow these steps to compile project.

```bash
git clone git@github.com:antabord1806/philosophers.git philosophers
cd philosophers
make re
```
Now run it.

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

<ul>
    <li><strong>number_of_philosophers</strong> --> Total number of philosophers participating in the simulation. Determines how many threads are created.</li>
    <li><strong>time_to_die</strong> --> Time in milliseconds a philosopher can go without eating before dying. If a philosopher doesn’t grab a fork in this time, they die.</li>
    <li><strong>time_to_eat</strong> --> Time in milliseconds a philosopher spends eating. During this time, they hold the forks they grabbed.</li>
    <li><strong>time_to_sleep</strong> --> Time in milliseconds a philosopher spends sleeping after eating. They release the forks during this period.</li>
    <li><strong>number_of_times_each_philosopher_must_eat</strong> (optional) --> The simulation stops after each philosopher has eaten this many times. If omitted, the simulation continues until a philosopher dies.</li>
</ul>

<h2>Key Concepts</h2>
<ul>
    <li><h3 id="race-condition">Race Condition</h3></li>
        <p>When two or more threads try to access th same data, and beacause it was not sicronized, their beahvior is unpredictable, undefined behaviour. In this application when several philosophers thry to grab the same fork, depending on the one that grabs it first, the remaining might wait it out, sleep, or die, and there is no way to know what happens</p>
    <li><h3 id="deadlock">Deadlock</h3></li>
        <p>A deadlock occurs when two or more threads are waiting indefinitely for resources held by each other, and none can proceed. In this case happens when all philosophers are waiting at the same time for the one next to them to drop a fork, none of them are able to eat, leading to their eventual demise</p>
    <li><h3 id="starvation">Starvation</h3></li>
        <p>When some threads are never getting acess to the data they need, while others are just cycling it amongst eachother. In this context a philosopher never gets to grab a fork while the others do</p>
    <li><h3 id="mutexes">Mutexes</h3></li>
        <p>In the mandatory part of the project mutexes present themselves as the solution for the problems listed above, they are a synchronization tool used to protect shared resources so that only one thread can access them at a time. The moment a philosopher takes a fork, all the others are forced to wait (think) for it to drop it, therefore they are not always trynig to grab the forks at once</p>
</ul>
		
		pthread_mutex_lock(&mutex);		#mutex locked by only one philo;
		shared_data = updated_value;	#data between locking and unlocking mutex is protected;
		pthread_mutex_unlock(&mutex);	#ulocking mutex;

<
