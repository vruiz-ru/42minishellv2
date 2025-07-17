/*
Program name minishell
Turn in files Makefile, *.h, *.c
Makefile NAME, all, clean, fclean, re
Arguments
External functs. 

-------------- INPUT HANDLING -------------------

readline -  
rl_clear_history, 
rl_on_new_line,
rl_replace_line, 
rl_redisplay, 
add_history,

-------------- INPUT/OUTPUT -------------------
printf 
malloc/free, 
write

------- File and Directory Input/Output -------
access, 
open, 
read,
close,

--------------- Process Control ---------------
fork 
wait/waitpid/wait3/wait4 
exit(status)

------------------- SIGNALS -------------------
signal,
sigaction, 
sigemptyset, 
sigaddset, 
kill, 

---------- File System and Directory ---------- 

getcwd/chdir = get/change directory 
stat/lstat/fstat = get file status
unlink = deletes a file 
opendir/readdir/closedir = aplicabulty on directory stream

----------------- EXECUTION --------------------
execve

--------- File descriptor manipulation ----------
dup/dup2 
pipe 

---------------- ERROR HANDLING -----------------
strerror/perror

------------ Terminal Contorl & TTY --------------
isatty 
ttyname 
ttyslot 
ioctl

------------------ ENVIRONMENT ------------------
getenv

--------- Terminal capabilities ----------------
tcsetattr 
tcgetattr 
tgetent 
tgetflag
tgetnum 
tgetstr 
tgoto 
tputs

Your shell should:
• Display a prompt when waiting for a new command.
• Have a working history.
• Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).
• Avoid using more than one global variable to indicate a received signal. Consider
the implications: this approach ensures that your signal handler will not access your
main data structures.
• Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).
• Handle ’ (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.
• Handle " (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for $ (dollar sign).
• Implement redirections:
◦ < should redirect input.
◦ > should redirect output.
◦ << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
◦ >> should redirect output in append mode.
• Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
• Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.
• Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.
• Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
The readline() function can cause memory leaks. You don’t have to fix them. But
that doesn’t mean your own code, yes the code you wrote, can have memory
leaks.

Your program has to implement:
• && and || with parenthesis for priorities.
• Wildcards * should work for the current working directory.
*/

/* auxiliary ideas for implementing the prototype of the project

1.  since we've got to save the user's input into a history file, is better to do this at the start of the program
	so we want to use open() with flags O_WRONLY | O_APPEND | O_CREAT, 0644 (permissions) 
			ex. int fd = open(HISTORY, O_WRONLY | O_APPEND | O_CREAT, 0644)

2.  then, we extract the last row (last user input) with GETNEXTLINE.

3.  checking the input/tokens (what tokens actually stand for is the command, its flags, and path/input)

4.  we are parsing the with strtok() - stands for string tokenizing or split() of our libft. 
			ex  char **tokens = ft_split(args, " ").
				while (args) if *args *tokens = *args;
				*toket[LAST_IDX] = NULL; 

5.  builtin commands:
	I.		cd [dir]			Change current working directory (use chdir())
	II.		exit	            Exit the shell (use exit())
	III.	pwd					Print current directory (use getcwd())
	IV.		echo [args...]		Print arguments to stdout
	V.		setenv / unsetenv	Set or unset environment variables
	VI.		env					Print all environment variables
	VII.	clear				Clear screen (printf("\033[H\033[J"))
	VIII.	help				Custom — show list of built-ins supported
		.---------------------------------------------------------------.
		| history				Optional — store & print input commands |
		'---------------------------------------------------------------'


EXIT/SUSPEND ANY ONGOING PROCESS SIGNALS 

SIGINT (CTRL + C) - EXIT
SIGTSTP (CTRL + Z) - SUSUPENDS

6.	parsing the built ins commands should be done into a separate function that will returns 0 if there was a problem and > 0 if there are none.
	I.		cd command:
				protect returns
				print required arguments (token)/if its not, we are going back to the start cwd
				chdir returns 0 if success
				don't forget to implement ../../../ (thought: counting sequence "../" and then backward as many folders as sequence are)
	II.		pwd command:
				getcwd(buffer_str, buffer_size) -> buffer size is usual 4096
				store the result of getcwd into a string for better usecase
					ex: char	*store_cwd = getcwd(NULL, 0); -> will show the current work directory
				don't manage the rest of arguments (tokens) after pwd
				don't forget to free the store_cwd string after use;
	III.	echo command:
				treate the flag -n properly -> quit the \n char
				doesn't recognize simple backslash
					ex: echo \new -> new
						echo \\new -> \new
				expect a closing " if there is one
					ex: 1.echo sadas" -> > (for continuation and after we put " will outputs) in this case: 	sadas
																											: command not found
						2. echo "
						> asdsa
						> asdasdsa
						> adsadsa
						> adasdsadsa
						> adsadas
						> "
					output:	\n (because the " is on the line with echo and its empty)
						asdsa
						asdasdsa
						adsadsa
						adasdsadsa
						adsadas
						\n (becaue the closing " its on the last row and its empty)
						3. treat the variable within '$VAR' literally, instead of "$VAR" or $VAR which prints the value of that specific variable (in case of variable doesn't exists, will print a new line char)
	IV.		env command should be stipulated on the main
	V.		exit command is a simple EXIT_SUCCESS/FAILURE

7. not to forget to implement the current working directory inside of command line as we navigate thru the shell
8. implementing our own strtok involves kinda ft_split, but every time calling the strtok on the string to be tokenized, the string will have the value - strtok'times. Split combined with static variables (gnl)
9. while command implementing:
	-> beside searching into a builtin structure commands, we want to search another commands inside of kernel (usr/bin) so we want to look into a TOKENIZED PATH
	

*/

_