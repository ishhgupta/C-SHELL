## How to Run the shell

- enter in the directory

- rum "make"

- execute by using "./a.out"

- type ctrl-c to stop execution

## Built-In commands

-  `ls [directory-name]`

 * "ls" lists all the files in current directory
 * only argument allwoed for ls apart from -l and -a flags are directory name
 * file-names are not allowed
 * only flags -l and -a are allowed
 * works for 'ls -la' , 'ls -l -a' , 'ls -al' this things prints the files in long list format
 * multiple directories can be passed in same command arguments

-  `cd [directory]`
 * the directory containing executable is considered as home directory
 * works for "cd .." - goes to parent directory
 * works for "cd ." - remains in current directory
 * for "cd" goes to home directory
 * the command can take only one argument
 * works for "cd -", switches to previous working directory.

- `echo [arguments]`
 * 'echo' prints the empty line
 * "echo "text" prints the exact text provided as arguments
 * echo also handles the tabs

- `pwd`
 * prints the path of present working directory
 * doesnt not take any arguments

- `pinfo`
 * pinfo prints the current process related information
 * pinfo [pid] prints the process information related to given pid number

- `quit` or `CTRL-D`
 * exits the shell

- `setenv var [value]` 
 * creates an environment variable `var` if it does not exists already and assigns it the value given
- `unsetenv var`
 * destroys the environmental variable `var`

- `jobs`
 * Prints a list of all currently running jobs along with their pid in order of their creation
 * Gives the state of the job – Running, Stopped

-`kjob <jobNumber> <signalNumber>` 
 * Takes the job id of a running job and sends a signal value to that process

- `fg <jobNumber>`
 * Brings a running or a stopped background job with given job number to foreground.

- `bg <jobNumber>`
 * Changes a stopped background job to a running background job.

- `overkill`
 * Kills all background process at once.

- every command provided other than built-in commands works as per with the foreground process using execvp()
- If a command is provided with & in the end then it works in background
- command invoked with '&' doesnt work for builtin commands  

## Additional Features

- `​CTRL-Z`
 * Changes the status of currently running job to stop, and pushes it to the background.

- `CTRL-C`
 * Sends SIGINT signal to the current foreground job of the shell​.
 * If there is no foreground job, then the signal does not have any effect.

- Input-Output Redirection and Piping
 * Handles `<`, `>`, `>>` and `|` operators appropriately, wherever they are in command


## Files

- `main.c` -  contains the main while() loop and also contains the exec_curr_command() function in which all the builtin commands are executed

- `pinfo.c` - contains pinfo() : prints process related info

- `fgbg.c` contains sig_hadler(): prints message when background process gets completed, fg_proc(): for foreground processed , bg_proc(): for background processes

- `prompt.c` contains prompt() and curr_path_display()
 
- `ls.c` contains ls() and display_dir()
- `cd.c` contains cd() and pwd()
- `echo.c` contains echo() function
- `headers.h` contains all header files,global variables and function declarations
- `bg.c` contains bg() function and performs `bg` command.
- `fg.c` conatins fg() function and performs `fg` command.

- `env.c` contains set() and unset() function performing commands `setenv var[value]` , `unsetenv var` commands.

- `czhandler.c` contains `ctrlc_handler` (handles CTRL-C) and `ctrlz_handler`(handles CTRL-Z) 

- `jobs.c` contains jobs() function and performs jobs command.
- `kjob.c` contains kjob() and overkill() function and performs the corresponding commands.
- `piping.c` handles commands containing pipes.
- `redirection.c` handles redirection operators.

