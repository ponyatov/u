# [[u]] language

System starts as zero VM container compiles 1+ `.u` files passed from command line:
```sh
$ ./bin/u lib/u.u
```

# comment

```u
#!/usr/bin/env u
# ^^^ shebang can be used at file start to run it as executable script

# line comment
```

## label

- global = colon definition code block
	- looks like `: name` (space is optional comparing to Forth)
	- hold in module symbol table
		- can be dumped into separate debug symbols file, or
		- compiled into bytecode to use on-device (dynamic linking, debug)
```u
# global labels 
:init 
```
- local
	- looks like `name:` (assembly-like label syntax)
	- used for local (recursive) calls and (un)conditional jumps while compiling control structures and state machines
	- hold in compiler-only table (local to current definition block)
		- will be cleared by `;` or next global label define
```u
# local labels table 
# used
jump_here:
```

## `;`

- stop current code block definition
	- compile [[u/ret|ret]] command
	- clear local labels table
