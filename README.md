# Elevator

Simulates an elevator traveling between floors

By Mike Henderson, June 2026

## Assumptions and limitations
I wasn't sure if the goal was to make an efficient floor-visiting algorithm,
or to just visit the floors exactly as listed, so I implemented both as options.
The strict floor schedule is the default.
The 'efficient' solution doesn't try to get too complicated about minimizing
anything, but it visits floors in order and in one direction at a time, like
a typical building elevator.

The program does no input checking and requires strictly correct input to work.
Commas are not expected in the floor list.

## Installation:
Requires a gnu toolchain with C++14 support, and make. I only verified this on
an Ubuntu 24.04 host. In bash:

`make`

This will generate the program, 'elevator'

## Usage

In bash:

`./elevator  12 2 9 1 32`

This will produce the following output:

`560 12,2,9,1,32`

Alternatively, for 'human elevator' behavior, where floors are visited in
either an up or down direction before reversing to visit the other, invoke with
`'--human'` flag and an initial direction of either `u` (up) or `d` (down):

`./elevator --human u 12 2 9 1 32`

will produce:

`510 12,32,9,2,1`

