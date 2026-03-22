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
<p>This project is a concurrency simulation based on the classic Dining Philosophers problem. The goal is to learn how to handle resourse sharing between threads, using mutexes to avoid race-conditions, deadlock or starvation which are just simptoms of missmanaged resources.</p>

<ul>
    <li><h3>Race Condition</h3></li>
        <p>When two or more threads try to access th same data, and beacause it was not sicronized, their beahvior is unpredictable, undefined behaviour. In this application when several philosophers thry to grab the same fork, depending on the one that grabs it first, the remaining might wait it out, sleep, or die, and there is no way to know what happens</p>
    <li><h3>Deadlock</h3></li>
        <p>A deadlock occurs when two or more threads are waiting indefinitely for resources held by each other, and none can proceed. In this case happens when all philosophers are waiting at the same time for the one next to them to drop a fork, none of them are able to eat, leading to their eventual demise</p>
    <li><h3>Starvation</h3></li>
        <p>When some threads are never getting acess to the data they need, while others are just cycling it amongst eachother. In this context a philosopher never gets to grab a fork while the others do</p>
    <li><h3>Mutexes</h3></li>
        <p>In the mandatory part of the project mutexes present themselves as the solution for the problems listed above, they are a synchronization tool used to protect shared resources so that only one thread can access them at a time. The moment a philosopher takes a fork, all the others are forced to wait (think) for it to drop it, therefore they are not always trynig to grab the forks at once</p>
    <pre align="left"> 
        pthread_mutex_unlock(pi->time_mutex);
	    printf_msg(pi, timetstamp, "has taken a fork");
        pthread_mutex_lock(&pi->fork[second].m);
    </pre>
</ul>


