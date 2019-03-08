# Assignment 2

William Wood

woodw221@gmail.com

## Purpose

Familiarize ourselves with threads and how to properly use them

## Program Descriptions

### Program 2-1

This program is an implementation of our thread safe linked list queue.
Does not have a main section as it is used in conjunction with prog2-2

### Program 2-2

This program takes 2 command line arguments, the number of primes you wish to print,
and the number of bits you wish to have as a starting point for your prime integers.
This program then creates 4 threads to generate prime numbers that are printed out after
a short sleep.

## Compiling

Compile this program with gcc prog2_1.c prog2_2.c -lgmp -lpthread

## Usage

./prog2_2 1 1 // prints 2


