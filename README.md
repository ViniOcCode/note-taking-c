# What is note-taking-c?

Note Taking in C is what the name suggests, a note taking application all made in C.

# Why?

This was made just for a project to the Final Project of CS50 2025 of Harvard!

Most of the code, i has clueless of what i was doing, therefor, if you find something horrendous and awful that violates all of principles of code, you are more than invite to do yours alterations!

# Docker!

Compiling in C it's a bit tedious, so i have a docker image that installs all of you need to run inside a container!

### How to use it

First of all, you have to be sure you have docker correctly installed!

In you prefered terminal, run the following commands:

```bash

$ git clone https://github.com/ViniOcCode/note-taking-c.git
$ cd note-taking-c
$ docker run --rm -v $(pwd):/app -it vinioc/note-taking-c bash

```
