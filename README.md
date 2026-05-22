# About

A test suite for **libft**, a 42 project.

> *"Program testing can be used to show the presence of bugs, but never to show their absence!"*
>
> -- Edsger W. Dijkstra, *Notes on Structured Programming*, 1970

## Quick start

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

## References

- 42 (school)
  https://en.wikipedia.org/wiki/42_(school)

- Notes on structured programming
  https://www.cs.utexas.edu/~EWD/transcriptions/EWD02xx/EWD249/EWD249.html