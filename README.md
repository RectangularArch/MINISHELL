# MINISHELL

<!-- ![Alt Text](https://github.com/RectangularArch/Image-storage/blob/master/minishell/ezgif.com-gif-maker%20(1).gif) -->

<p align="center">
  <img width="800" height="600" src="https://github.com/RectangularArch/Image-storage/blob/master/minishell/ezgif.com-gif-maker%20(1).gif">
</p>

## Introduction
Experience in implementing a command interpreter (with limited functionality) used in operating systems of the unix family.

## Launch and setup

```
git clone git@github.com:RectangularArch/MINISHELL.git
```

Using `make` in project directory will build the executable `minishell` file. Use `./minishell` to run the programm.

## Available options

• Show a prompt when waiting for a new command;

• Have a working History;

• Search and launch the right executable (based on the PATH variable or by using relative or absolute path);

• `’` and `"` works like in bash;

• `<` `<<` `>` `>>` redirections available;

• `|` like pipes in bash;

• `;` like semicolons in bash;

• Environment variables ($ followed by characters) expands to their values;

• `$?` expands to the exit status of the most recently executed foreground pipeline;

• `ctrl-C` `ctrl-D` `ctrl-\` works like in bash;


• Builtins implemented:

  ◦ `echo` with option `-n`;

  ◦ `cd` with only a relative or absolute path;

  ◦ `pwd` with no options;

  ◦ `export` with no options;

  ◦ `unset` with no options;

  ◦ `env` with no options or arguments;

  ◦ `exit` with no options;

## Conclusion

This two-person project was done with [Cwilliam](https://github.com/SailorWilliam).

I was responsible for the parsing, argument checking, environment variables and redirection.

[Cwilliam](https://github.com/SailorWilliam) took care of the built-in functions, execution, piping and signal handling.
