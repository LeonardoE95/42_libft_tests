# About

A test suite for **libft**, a 42 project.

> *"Program testing can be used to show the presence of bugs, but never to show their absence!"*
>
> -- Edsger W. Dijkstra, *Notes on Structured Programming*, 1970

## Quick start

Clone the repository

```
$ git clone git@github.com:LeonardoE95/42_libft_tests.git
$ cd 42_libft_tests
```

Save the path to the libft source code

```
$ make setup SRC=~/libft/src/
```

Test all functions. Functions not currently implemented will be skipped. 

```
$ make test
```

Test a specific function

```
$ make test-ft_strlen
$ make test-memset
```

Cleanup

```
$ make clean
```

If you forget the commands just write `make` to get a help
menu. Notice in the output the `SRC = ` line specifies the current
value for the source directory.

```
[leo@work 42_libft_tests]$ make

  Save source path
    make setup SRC=~/libft/src/

  Run all tests
    make test

  Test a single function
    make test-ft_strlen

  Clean object files
    make clean

  SRC = /home/leo/42/libft/src

/* *************************************************************************** */
/*                                                                             */
/*                                                         :::      ::::::::   */
/*                                                       :+:      :+:    :+:   */
/*  The mystery of life isn't a problem to solve,      +:+ +:+         +:+     */
/*  but a reality to experience.                     +#+  +:+       +#+        */
/*                                                 +#+#+#+#+#+   +#+           */
/*                                                      #+#    #+#             */
/*                                                     ###   ####.fr           */
/*                                                                             */
/* *************************************************************************** */
```

## References

- 42 (school)
  https://en.wikipedia.org/wiki/42_(school)

- Notes on structured programming
  https://www.cs.utexas.edu/~EWD/transcriptions/EWD02xx/EWD249/EWD249.html