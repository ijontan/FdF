# FdF

## Table of Contents

- [FdF](#fdf)
  - [Table of Contents](#table-of-contents)
  - [About ](#about-)
  - [Getting Started ](#getting-started-)
    - [Prerequisites](#prerequisites)
    - [Installing](#installing)
  - [Usage ](#usage-)

## About <a name = "about"></a>

A project from 42-cursus aims to write a wireframe renderer.

## Getting Started <a name = "getting_started"></a>

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. 

### Prerequisites
1. Linux(preferably debian based) or MacOs.
2. minilibx 


### Installing

if you want to run this on window, need to setup a virtual machine.
1. install minilibx
2. clone the project with

```sh
git clone --recurse-submodules https://github.com/ijontan/minishell.git
```
or

```sh
git clone https://github.com/ijontan/minishell.git
git submodule init
git submodule update
```

## Usage <a name = "usage"></a>

build with
```sh
make 
```

run with

```sh
./fdf maps/example.fdf
```

