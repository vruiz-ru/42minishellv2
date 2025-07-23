/*
Program name minishell
Turn in files Makefile, *.h, *.c
Makefile NAME, all, clean, fclean, re
Arguments
External functs. 

-------------- INPUT HANDLING -------------------

readline,   
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
0.[STRCMP] !! all checks between strings (user input, commands, etc.) should be done with ft_strcmp!!!

1.[CREATE FILE]  since we've got to save the user's input into a history file, is better to do this at the start of the program
	so we want to use open() with flags O_WRONLY | O_APPEND | O_CREAT, 0644 (permissions) 
			ex. int fd = open(HISTORY, O_WRONLY | O_APPEND | O_CREAT, 0644)

2.[GNL FROM HISTORY]  then, we extract the last row (last user input) with GETNEXTLINE.

3.[CHECKING ARGS/TOKENS]  checking the input/tokens (what tokens actually stand for is the command, its flags, and path/input)

checked 4. [STRTOK] Implemented

5.[BUILTINS]  builtin commands:			
	* parsing the built ins commands should be done into a separate function that will returns 0 if there was a problem and > 0 if there are none.
	I.		cd command:		Change current working directory (use chdir())
				protect returns
				print required arguments (token)/if its not, we are going back to the start cwd
				chdir returns 0 if success
				don't forget to implement ../../../ (thought: counting sequence "../" and then backward as many folders as sequence are)
	
	II.		pwd command:	Print current directory (use getcwd())
				getcwd(buffer_str, buffer_size) -> buffer size is usual 4096
				store the result of getcwd into a string for better usecase
					ex: char	*store_cwd = getcwd(NULL, 0); -> will show the current work directory
				don't manage the rest of arguments (tokens) after pwd
				don't forget to free the store_cwd string after use;
	
	III.	echo command:	Print arguments to stdout
				treat the flag -n properly -> deletes the \n char
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
				treat the variable within '$VAR' literally, 
				instead of "$VAR" or $VAR which prints the value of that specific variable (in case of variable doesn't exists, will print a new line char)
				.----------------------------------------------.
				| $$ - print parent process id with getppid(); |
				'----------------------------------------------'
				the differences between getpid and getppid is that the getpid returns the id of the current instance execution and get ppid returns the id of the whole process of file we are working on
				
	IV.		env command:	Print all environment variables
				should be stipulated on the main
	V.		exit command is a simple EXIT_SUCCESS/FAILURE (Exit the shell)
	VI.		setenv & unsetenv commands:	Set or unset environment variables 
				* should be call before shell builts, right after parse input
				* setenv represents adding/changing a variable to the environment (char **env)
				* unsetenv delete a variable from environment (char **env)
				* setting a new variable to the env implies to extend the env map by one. 
					- That means we have to count the variables and alloc a new env with the new variable string.
					- if the variable exists, just change the value, if not, create a new one
					- for the sake of robustness, the name of variable should be as the others from env, if not, print a message	
	VII.	clear command:	Clear screen (printf("\033[H\033[J"))
	VIII.	which command:	Shows the path of the argument. Ex. which ls -> /usr/bin/ls
				* we want to look into a TOKENIZED PATH (the path of everything)
		.---------------------------------------------------------------.
		| history command:		Optional — store & print input commands |
		'---------------------------------------------------------------'

[IMPLEMENTING SIGNAL HANDLER]	EXIT/SUSPEND ANY ONGOING PROCESS SIGNALS 

								SIGINT (CTRL + C) - EXIT
								SIGTSTP (CTRL + Z) - SUSUPENDS


6.[DESIGN IDEA] not to forget to implement the current working directory inside of command line as we navigate thru the shell

7.[FUNCTION OF UTILS]
	get_path of token: 	-> usage WHICH builtin
						-> usage in executor/child process
						->DRY!! (don't repeat yourself) 		

8. [CHILD PROCESS TO EXECVE]
	-> have to adding a listner of signals
	-> in the child process we have to execute the commands of userinput after checking it
	-> have to divide into a map the paths of PATH variable.
	-> have to append the command of user input
	-> have to check the access of the command: if (access(path, X_OK) == 0) then execve *X_OK is the flag to check if we are granted with execute permission*
*/

#include <stdio.h>
#include <limits.h>
#include "libft/libft.h"
#define CHECK_MARK  "✅"
#define CROSS_MARK  "❌"

// Suppress unused warnings
#define SEP printf("-----------------------------\n");

void test_char()
{
    char c = 'A';
    char nul = '\0';
	int mine, orig;
    SEP
    printf("Char tests:\n");
    orig = printf("orig: [%c]\n", c);
    mine = ft_printf("mine: [%c]\n", c);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%5c]\n", c);
    mine = ft_printf("mine: [%5c]\n", c);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%-5c]\n", c);
    mine = ft_printf("mine: [%-5c]\n", c);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%c] (nul)\n", nul);
    mine = ft_printf("mine: [%c] (nul)\n", nul);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%5c] (nul)\n", nul);
    mine = ft_printf("mine: [%5c] (nul)\n", nul);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
}

void test_string()
{
    char *s = "hello";
    char *null_str = NULL;
	int mine, orig;

    SEP
    printf("String tests:\n");
    orig = printf("orig: [%s]\n", s);
    mine = ft_printf("mine: [%s]\n", s);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%.3s]\n", s);
    mine = ft_printf("mine: [%.3s]\n", s);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%8.4s]\n", s);
    mine = ft_printf("mine: [%8.4s]\n", s);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%-10s]\n", s);
    mine = ft_printf("mine: [%-10s]\n", s);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%.0s]\n", s);
    mine = ft_printf("mine: [%.0s]\n", s);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%.0s] (null)\n", null_str);
    mine = ft_printf("mine: [%.0s] (null)\n", null_str);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%s] (null)\n", null_str);
    mine = ft_printf("mine: [%s] (null)\n", null_str);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
}

void test_signed_int()
{
    int pos = 42;
    int neg = -42;
    int zero = 0;
	int mine, orig;

    SEP
    printf("Signed int tests:\n");
    orig = printf("orig: [%d]\n", pos);
    mine = ft_printf("mine: [%d]\n", pos);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%d]\n", neg);
    mine = ft_printf("mine: [%d]\n", neg);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%+d]\n", pos);
    mine = ft_printf("mine: [%+d]\n", pos);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [% d]\n", pos);
    mine = ft_printf("mine: [% d]\n", pos);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%5d]\n", pos);
    mine = ft_printf("mine: [%5d]\n", pos);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%05d]\n", pos);
    mine = ft_printf("mine: [%05d]\n", pos);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%+08d]\n", pos);
    mine = ft_printf("mine: [%+08d]\n", pos);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%-8d]\n", neg);
    mine = ft_printf("mine: [%-8d]\n", neg);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%.0d]\n", zero);
    mine = ft_printf("mine: [%.0d]\n", zero);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%8.4d]\n", pos);
    mine = ft_printf("mine: [%8.4d]\n", pos);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [INT_MAX: %d]\n", INT_MAX);
    mine = ft_printf("mine: [INT_MAX: %d]\n", INT_MAX);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [INT_MIN: %d]\n", INT_MIN);
    mine = ft_printf("mine: [INT_MIN: %d]\n", INT_MIN);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
	orig = printf("orig: [%+08d]\n", 99);
	mine = ft_printf("mine: [%+08d]\n", 99);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
}

void test_unsigned_int()
{
    unsigned int uval = 12345;
    unsigned int umax = UINT_MAX;
	int mine, orig;

    SEP
    printf("Unsigned int tests:\n");
    orig = printf("orig: [%u]\n", uval);
    mine = ft_printf("mine: [%u]\n", uval);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%010u]\n", uval);
    mine = ft_printf("mine: [%010u]\n", uval);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%10.6u]\n", uval);
    mine = ft_printf("mine: [%10.6u]\n", uval);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%.0u]\n", 0);
    mine = ft_printf("mine: [%.0u]\n", 0);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%u] (UINT_MAX)\n", umax);
    mine = ft_printf("mine: [%u] (UINT_MAX)\n", umax);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
}

void test_hex()
{
    int val = 255;
    int zero = 0;
	int	mine, orig;

    SEP
    printf("Hex tests:\n");
    orig = printf("orig: [%x]\n", val);
    mine = ft_printf("mine: [%x]\n", val);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%#x]\n", val);
    mine = ft_printf("mine: [%#x]\n", val);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%#X]\n", val);
    mine = ft_printf("mine: [%#X]\n", val);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%08x]\n", val);
    mine = ft_printf("mine: [%08x]\n", val);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%8.4x]\n", val);
    mine = ft_printf("mine: [%8.4x]\n", val);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%.0x]\n", zero);
    mine = ft_printf("mine: [%.0x]\n", zero);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%#x] (zero)\n", zero);
    mine = ft_printf("mine: [%#x] (zero)\n", zero);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%#08x]\n", 42);
	mine = ft_printf("mine: [%#08x]\n", 42);
    if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
	orig = printf("orig: [%#-15.10x]\n", 123456);
	mine = ft_printf("mine: [%#-15.10x]\n", 123456);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%# 010.5X]\n", 255);
	mine = ft_printf("mine: [%# 010.5X]\n", 255);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%#020.15x]\n", 1234);
	mine = ft_printf("mine: [%#020.15x]\n", 1234);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
}

void test_pointer()
{
    int x = 42;
    void *ptr = &x;
    void *nil = NULL;
	int	mine, orig;

    SEP
    printf("Pointer tests:\n");
    orig = printf("orig: [%p]\n", ptr);
    mine = ft_printf("mine: [%p]\n", ptr);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%-20p]\n", ptr);
    mine = ft_printf("mine: [%-20p]\n", ptr);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%20p]\n", ptr);
    mine = ft_printf("mine: [%20p]\n", ptr);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [NULL: %p]\n", nil);
    mine = ft_printf("mine: [NULL: %p]\n", nil);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
}

void test_mixed_flags()
{
    int nums[] = {0, 1, 42, 123456, -42};
	int	mine, orig;
    SEP
    printf("Mixed flag tests:\n");

    orig = printf("orig: [%#08x]\n", nums[2]);
    mine = ft_printf("mine: [%#08x]\n", nums[2]);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);

    orig = printf("orig: [%#-15.10x]\n", nums[3]);
    mine = ft_printf("mine: [%#-15.10x]\n", nums[3]);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%+08d]\n", nums[2]);
    mine = ft_printf("mine: [%+08d]\n", nums[2]);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%+-9d]\n", nums[4]);
    mine = ft_printf("mine: [%+-9d]\n", nums[4]);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [% 05d]\n", nums[1]);
    mine = ft_printf("mine: [% 05d]\n", nums[1]);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%#020.15x]\n", nums[3]);
    mine = ft_printf("mine: [%#020.15x]\n", nums[3]);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%# 010.5X]\n", nums[2]);
    mine = ft_printf("mine: [%# 010.5X]\n", nums[2]);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%#-12.6x]\n", nums[2]);
    mine = ft_printf("mine: [%#-12.6x]\n", nums[2]);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
    orig = printf("orig: [%#x]\n", nums[0]);
    mine = ft_printf("mine: [%#x]\n", nums[0]);
	if (orig == mine)
		ft_printf("%s\n", CHECK_MARK);
	else
		printf("%s\n", CROSS_MARK);
	
}

int main()
{
    test_char();
    test_string();
    test_signed_int();
    test_unsigned_int();
    test_hex();
    test_pointer();
	test_mixed_flags();
    return 0;
}

