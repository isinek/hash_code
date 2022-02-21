# Traffic signaling

## Introduction
The world's rst traffic light dates back to 1868. It was installed in London to control
traffic for... horse-drawn vehicles! Today, traffic lights can be found at street
intersections in almost every city in the world, making it safer for vehicles to go
through them.

traffic lights have at least two states, and use one color (usually red) to signal "stop",
and another (usually green) to signal that cars can proceed through. The very rst
traffic lights were manually controlled. Nowadays they are automatic, meaning that
they have to be carefully designed and timed in order to optimize the overall travel
time for all the paicipants in traffic.

## Task
Given the description of a city plan and planned paths for all cars in that city,
optimize the schedule of traffic lights to minimize the total amount of time spent in
traffic, and help as many cars as possible reach their destination before a given
deadline.

## Problem description
### City plan
The city plan consists of one-way streets and intersections. Each street:
- is identied by a unique name,
- leads from one intersection to another,
- does not contain any intersections in between (if two streets need to cross outside an intersection, a bridge or tunnel is used),
- has a xed amount of time L it takes a car to get from the beginning of the street to the end. If it takes L seconds to drive through a street and a car enters it at time T it will arrive at the end of the street precisely at T+L, independently of how many cars are on the street.

Note that while the streets are one-way, it is still possible to have two one-way
streets connecting two intersections in opposite directions (see intersections 0 and
2 and a-street and b-street in Figure 1). However, there will never be two streets
connecting two intersections in the same direction.

Each intersection:
- has a unique integer ID (for example 0, 1, 2 ...),
- has at least one street that comes into it, and at least one street coming out of it.

### Traffic lights
There is a traffic light at the end of every street (just before the intersection). Each
traffic light has two states: a green light indicates that the cars from that street can
cross the intersection and head towards any other street, while a red light indicates
that the cars from that street need to stop. At most one traffic light will be green at
each intersection at any given time. While the light is green for an incoming street,
only cars from this street will be allowed to enter the intersection (and move to any
outcoming street), all other cars have to wait.

#### Queuing up
When the light at the end of a street is red, arriving cars queue up waiting for the
light to turn green. When the light is green, one car can cross the intersection
every second. This means that if a green light for a given street lasts for T i
2
seconds then only the rst T i cars from that street will continue their travel (see
Figure 2). Others will need to wait for the following green light.

#### Schedule
For each intersection we can set a traffic light schedule. The traffic light schedule
determines the order and duration of green light for the incoming streets of the
intersection and repeats itself until the end of the simulation. The schedule is a list
of pairs: incoming street and duration. Each street can appear at most once in
3
the schedule. The schedule can ignore some of the incoming streets – those will
never get a green light.

The traffic light schedule is controlled by your submissions. You don't have to
specify the schedule of all traffic lights. By default all lights on all intersections
are red (yes, cars stuck there will have to wait until the end of simulation).

### Cars
Each car is described by the path (a sequence of streets) it is going to drive
through. The paths are dened by the input datasets and can't be altered. In the
input datasets we guarantee that each car can go through a single intersection at
most once

Initially, all cars sta at the end of the rst street in their path, waiting for the green
light (in case the traffic light is red), or ready to move (if it's green). If two cars sta
at the end of the same street, the car listed rst in the input le goes rst. Each car
then follows a given path, while obeying the traffic lights, and needs to reach the
end of the last street in that path.

Cars are queued up at the end of each street. The rst car in the queue can cross
the intersection immediately aer the light turns green. There is no delay while a car
passes through an intersection. Cars aer that cross the intersection one aer
another, one car every second.

When a car enters the last street of its path, it completes its drive until the end of
the street and then is immediately removed from it. This means that the car does
not queue up at the end of the last street of its path and does not enter the
intersection at the end of it.

## Input data set
### File format
Each input data set is provided in a plain text le. The le contains only ASCII
characters with lines ending with a single '\n' character (also called “UNIX-style” line
endings). When multiple numbers are given in one line, they are separated by a
single space between each two numbers.
- The rst line contains ve numbers:
	- an integer D (1 ≤ D ≤ 10 4) - the duration of the simulation, in seconds,
	- an integer I (2 ≤ I ≤ 10 5) - the number of intersections (with IDs from 0 to I -1 ),
	- an integer S (2 ≤ S ≤ 10 5) - the number of streets,
	- an integer V (1 ≤ V ≤ 10 3) - the number of cars,
	- an integer F (1 ≤ F ≤ 10 3) - the bonus points for each car that reaches its destination before time D.
- The next S lines contain descriptions of streets. Each line contains:
	- two integers B and E (0 ≤ B < I , 0 ≤ E < I ) - the intersections at the start and the end of the street, respectively,
	- the street name (a string consisting of between 3 and 30 lowercase ASCII characters a -z and the character - ),
	- an integer L (1 ≤ L ≤ D ) - the time it takes a car to get from the beginning to the end of that street.
- The next V lines describe the paths of each car. Each line contains:
	- an integer P (2 ≤ P ≤ 10 3) - the number of streets that the car wants to travel,
	- followed by P names of the streets: The car stas at the end of the rst street (i.e. it waits for the green light to move to the next street) and follows the path until the end of the last street. The path of a car is always valid, i.e. the streets will be connected by intersections.

### Example

| Input                 | Description |
| ----------------------|-------------|
| 6 4 5 2 1000          | The simulation lasts 6 seconds, there are 4 intersections, 5 streets, and 2 cars; and a car scores 1000 points for reaching the destination on time. |
| 2 0 rue-de-londres 1  | Street rue-de-londres starts at intersection 2, ends at 0, and it takes L=1 seconds to go from the beginning to the end. |
| 0 1 rue-d-amsterdam 1 | Street rue-d-amsterdam starts at intersection 0, ends at 1 and has L=1. |
| 3 1 rue-d-athenes 1   | Street rue-d-athenes starts at intersection 3, ends at 1 and has L=1. |
| 2 3 rue-de-rome 2     | Street rue-de-rome starts at intersection 2, ends at 3 and has L=2. |
| 1 2 rue-de-moscou 3   | Street rue-de-moscou starts at intersection 1, ends at 2, and has L=3. |
| 4 rue-de-londres rue-d-amsterdam rue-de-moscou rue-de-rome | The first car starts at the end of rue-de-londres and then follows the given path. |
| 3 rue-d-athenes rue-de-moscou rue-de-londres | The second car starts at the end of rue-d-athenes and then follows the given path. |
