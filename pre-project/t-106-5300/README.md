An example to get you started with pre-project
==============================================

This repository is for you to get started. Refer noppa and course wiki (link in noppa) for more information what to do. These files are related to development environment on Linux.


Git
---

Git is suggested to be used for project management. It helps you to share code on car-project state and also keeps history of code versions. Remember to tag or branch working version of your code, so when you try to demo on last day, you know which version did work.

You can click `Fork` on [home page](/t-106-5300/example) to fork this project and use this gitlab as git remote. Alternatively you can press [Download](/t-106-5300/example/repository/archive) to get a copy of these files.

For more help with git, use the google...


Requirements
------------

All these development tool requirements are fulfilled in exercise lab, so you can skip this part if you are working there.

On Windows you need to refer the course wiki for help. Course assistance do not provide any help with Windows tools or development environments. Actual coding on Windows is similar, thus help is provided for that.

With Linux based systems following packages are needed:

debian & ubuntu | description
--- | ---
gcc-avr | Compiler and other utilities
avr-libc | C libraries
avrdude | Used to program the AVR device
yaamake | Required to use `Makefile` (read more below). Packages for yaamake are not yet in distribution repositories so get it from [github source](https://github.com/raphendyr/yaamake)


Files
-----

### .gitignore

This file contains files to be ignored by git. These files contain build result and other binary files. You should not put this type of files in git.

### Makefile

`Makefile` contains definitions and rules for the `make` program. This project uses `yaamake` to do all the heavy lifting so the `Makefile` is quite sort. More information and configuration variables can be viewed with `make help`.

When you change the `simpleled.c` filename to something else or add another source file, you need to edit `SRC` line in this file.

### Makefile.alternative

This is an alternative makefile that can be used without yaamake. If you want to use this instead the former, then rename this file to `Makefile` (overwrite the other file). If you dom't want to replace the other you can run `make -f Makefile.alternative` instead of `make`.

You can use this makefile if you don't want to or can't use yaamake.

### simpleled.c

This is the example source file that demonstrates some basic things. This is far from a complete solution for the pre-project, but works for testing the development environment.


Yaamake makefile usage
----------------------

Makefile uses yaamake makefile system to simplify things. Yaamake contains all the information how to do things and `Makefile` only configurations for them.

### Actions

command | description
--: | ---
`make` | runs `make build`
`make build` | compiles and links your source files
`make clean` | removes all build files (created by above command)
`make program_check` | validate that avr device is connected and is programmable
`make program` | program the AVR board (remember to connect the usb cable first)
`make help` | yaamake's help message about these commands and variables to be defined in `Makefile`
`make listen` | can be used to open serial listener (can be used to listen serial bytes send from your avr program. For that you need to implement USART functions. google `avr usart`)


### Created files

All of this files are more or less useless to you. Basically these are used to get your code to the actual aVR device. You get rid of these by running `make clean`

This files are listed here, to give some reference.

command | description
--: | ---
`simpleled.elf` | Binary in ELF format (result of compiling and linking)
`simpleled.hex` | Binary in hex format (raw binary bytes as hex). This is used to program the device.
`simpleled.lss` | Disassembly (assembly code matched to your c code) Some what human readable, compared to elf and hex.
`simpleled.map` | Object map
`simpleled.sym` | Symbol map
`.cache/*` | Build support files (object files, dependencies, etc.)


Alternative makefile
--------------------

Alternative makefile is easy to extend, but offers less features. It is totally sufficient to pass the project.

### Actions

command | description
--: | ---
`make` | compiles and links your source files
`make clean` | removes all build files (created by above command)
`make program_check` | validate that avr device is connected and is programmable
`make program` | program the AVR board (remember to connect the usb cable first)
`make sizedummy` | prints some size statistics of your binary

### Created files

command | description
--: | ---
`simpleled.elf` | same as above
`simpleled.hex` | same as above
`simpleled.d` | source file dependencies for Makefile
`simpleled.o` | compiled source file (object file)