/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:50:39 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 19:37:48 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int g_signal_status = 0;

void print_commands_debug(t_process *p)
{
    t_cmd *c = p->commands;
    int cmd_n = 1;
    int i;

    if (!c) { printf("⚠️  No hay comandos\n"); return; }

    while (c)
    {
        printf("\n📦 BOLSA (COMANDO) #%d:\n", cmd_n++);
        
        // <--- AÑADE ESTA LÍNEA ---
        printf("   📂 FDs:  In[%d]  Out[%d]\n", c->fd_in, c->fd_out);
        // -------------------------

        i = 0;
        if (c->args)
            while (c->args[i]) { printf("   Arg[%d]: %s\n", i, c->args[i]); i++; }
        
        c = c->next;
    }
    printf("\n");
}

void	reset_utils(t_process **process)
{
	if ((*process)->line)
		free((*process)->line);
	
	ft_clear_strtok(); // Tu limpieza de tokens antigua
	
	if ((*process)->tokens)
		ft_lstclear(&(*process)->tokens, free);
	(*process)->tokens = NULL;

	// <--- NUEVO: Limpieza de la estructura de comandos
	if ((*process)->commands)
	{
		ft_free_cmds((*process)->commands);
		(*process)->commands = NULL;
	}
	// ------------------------------------------------

	if ((*process)->prompt->display)
		free((*process)->prompt->display);
	(*process)->prompt->display = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_process	*process;

	if (argc > 2)
		return (0);
	process = NULL;
	if (!init_parent(&process, argv[0], envp))
		return (0);
	while (1)
	{
		// 1. Configurar señales para el modo interactivo
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, SIG_IGN); // <---  IGNORAR Ctrl-
		// 2. Leer input (readline se quedará esperando aquí)
		ft_readinput(process);
		// 3. CHECK DE SEÑALES: ¿Nos interrumpieron mientras esperábamos en readline?
		if (g_signal_status != 0)
		{
			process->status = g_signal_status; // Actualizamos $? a 130
			g_signal_status = 0;               // Reseteamos la global
		}
		if (process->tokens)
		{
			ft_tokens_to_cmds(process);
			
			// Si se pulsó Ctrl+C durante el heredoc (parsing), cancelamos todo.
			if (g_signal_status == 130)
			{
				process->status = 130;
				g_signal_status = 0; // Reset para la próxima
				// NO EJECUTAMOS NADA, el bucle while(1) continuará y hará reset_utils
			}
			else
			// 1. Si es un builtin de padre (cd, exit...) Y no tiene pipes (|)
			if (process->commands && !process->commands->next && \
				ft_is_parent_builtin(process->commands))
			{
				// Ejecutamos y guardamos el resultado (0 o 1) en el status global
    			process->status = ft_builtins(process, process->commands);
			}
			else
			{
				// 2. Si no, al ejecutor de hijos (forks/pipes)
				ft_fork_process(process);
			}
		}

		reset_utils(&process);
	}
	return (0);
}

/* 42 Instructions

Program name minishell
Turn in files Makefile, *.h, *.c
Makefile NAME, all, clean, fclean, re
Arguments
External functs. 

-------------- INPUT HANDLING -------------------

readline

rl_clear_history, 	-> clears the history of commands
rl_on_new_line		-> 
rl_replace_line, 	->
rl_redisplay, 		->
add_history,		-> add the line to the history since we have to save the history

-------------- INPUT/OUTPUT -------------------
printf 
malloc/free, 
write

------- File and Directory Input/Output -------
access, 			-> access is using in searching for the command introduced by the user
open, 
read,
close,

--------------- Process Control ---------------
fork 						-> we'll use this command when we want to execute in child process, the command from the user
wait/waitpid/wait3/wait4 	-> waiting for zombies
exit(status)

------------------- SIGNALS -------------------
				-> using SIGNALS for CTRL+C, CTRL+Z, CTRL+\
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
execve						-> execute the user input

--------- File descriptor manipulation ----------
dup/dup2 
pipe 

---------------- ERROR HANDLING -----------------
strerror/perror

------------ Terminal Control & TTY --------------
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
✅• Display a prompt when waiting for a new command.
✅• Have a working history.
• Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).
• Avoid using more than one global variable to indicate a received signal. Consider
the implications: this approach ensures that your signal handler will not access your
main data structures.
• !!!! Not interpret unclosed quotes or special characters which are not required by the
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
✅• Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.
• Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
✅◦ ctrl-C displays a new prompt on a new line.
✅◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.
• Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
✅◦ pwd with no options
✅◦ export with no options
✅◦ unset with no options
✅◦ env with no options or arguments
✅◦ exit with no options
The readline() function can cause memory leaks. You don’t have to fix them. But
that doesn’t mean your own code, yes the code you wrote, can have memory
leaks.

Your program has to implement:
• && and || with parenthesis for priorities.
• Wildcards * should work for the current working directory.
*/

/* auxiliary ideas for implementing the prototype of the project
✅[STRCMP] !! all checks between strings (user input, commands, etc.) should be done with ft_strcmp!!!

✅[CHECKING ARGS/TOKENS]  checking the input/tokens (what tokens actually stand for is the command, its flags, and path/input)

✅[STRTOK] Implemented

5.[BUILTINS]  builtin commands:
	✅"~" = /home/user. Whenever our minishell will see that will replace it with the mentioned path		
	✅* parsing the built ins commands should be done into a separate function that will returns 0 if there was a problem and > 0 if there are none.
	✅* every bulitin command should operate in the original process, not a child
	✅		cd command:		Change current working directory (use chdir())
	✅II.		pwd command:	Print current directory (use getcwd())
				getcwd(buffer_str, buffer_size) -> buffer size is usual 4096
				store the result of getcwd into a string for better usecase
					ex: char	*store_cwd = getcwd(NULL, 0); -> will show the current work directory
				don't manage the rest of arguments (tokens) after pwd
				don't forget to free the store_cwd string after use;
	✅🚫III.	echo command:	Print arguments to stdout
				*   treat the flag -n properly -> deletes the \n char
				*   doesn't recognize simple backslash
						ex: echo \new -> new
							echo \\new -> \new
				*   expect a closing " if there is one
						ex: 1.echo sadas" -> > (for continuation and after we put " will outputs) in this case: 	sadas
																												: command not found
							2. echo "
							> asdsa
							> asdasdsa
							> adsadsa
							> adasdsadsa
							> adsadas
							> "
					[OUTPUT]\n (because the " is on the line with echo and its empty)
							asdsa
							asdasdsa
							adsadsa
							adasdsadsa
							adsadas
							\n (becaue the closing " its on the last row and its empty)
				*	treat the variable within '$VAR' literally, 
				*	instead of "$VAR" or $VAR which prints the value of that specific variable (in case of variable doesn't exists, will print a new line char)
		!!!!		other example with {} special char
						$> foo=4
						$> echo $foo
						4
						$> echo ${foo}d
						4d
				*	echo $? will print the exit status of the last executed cmd
				.----------------------------------------------.
				| $$ - print parent process id with getppid(); |
				'----------------------------------------------'
				🚫 -> not resolved >> > < << cases
				🚫 -> implement variables $? $$   
						$0  The name of the current shell or script
						$1, $2, ...	Positional parameters
						$#	Number of positional arguments
						$@ / $*	All positional arguments
						$!	PID of the most recent background command
						$_	Last argument of the previous command
				
				the differences between getpid and getppid is that the getpid returns the id of the current instance execution and get ppid returns the id of the whole process of file we are working on
	✅IV.		env command:	Print all environment variables
				should be stipulated on the main
	✅V.		exit command is a simple EXIT_SUCCESS(0)/FAILURE(nonzero) (Exit the shell)
	✅VI.		setenv & unsetenv commands:	Set or unset environment variables 
				* should be call before shell builts, right after parse input
				* setenv represents adding/changing a variable to the environment (char **env)
				* unsetenv delete a variable from environment (char **env)
				* setting a new variable to the env implies to extend the env map by one. 
					- That means we have to count the variables and alloc a new env with the new variable string.
					- if the variable exists, just change the value, if not, create a new one
					- for the sake of robustness, the name of variable should be as the others from env, if not, print a message	
	✅VII.	clear command:	Clear screen (printf("\033[H\033[J"))
	✅IX.		 export ->	transfer a shell variable in env variable making available to child process
					->	if you are entering into a subshell (name of shell and should be entering into a child process)
					the variable exported its written into memory and coudl be available for child process, if not exported
					the variable shouldn't be available for the subshell
					example:
						$>	MYVAR=123
						$>	echo $MYVAR      
						123
						$>	bash             
						$>	echo $MYVAR      
						(nothing because we were entered into a subshell with $> bash)
						$>	exit  
						(returning to the prev shell)	
						$>	export MYVAR=123
						$>	bash     
						$>	echo $MYVAR
						$>	exit
		.---------------------------------------------------------------.
	✅  | history command:		Optional — store & print input commands |
		'---------------------------------------------------------------'

[IMPLEMENTING SIGNAL HANDLER]	EXIT/SUSPEND ANY ONGOING PROCESS SIGNALS 

							✅  SIGINT (CTRL + C) - EXIT
							✅  CTRL + D - SENDS EOF
								CTRL + / - UNDO


✅6.[DESIGN IDEA] not to forget to implement the current working directory inside of command line as we navigate thru the shell

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

9. Steps into executing a command from path:
	I.		shell forks itself
	II. 	parent waits for child to finish
	II.5	(a good practice is to close stdin and stdout file description because if it's open, can interfere with the execution of commands)
			(we need to remember that everything in linux is a file, and if its a file will be fd opens and we need to close the fd after each user)
	III.	child exec's the command after it checks its availability of the command:._ if the command exists in bin folder
																					  \ if we have access to the command

10. [SPECIAL CHARS]:
		# ' " \ $ < > ( ) ! | & ; space newline
		*	-> (match any char) ex. find *.c -> will find every .c file (adas.c, asdsadsa.c, dasdasda.c)
		~	-> the replacement of home path (/home/user) 
		?	-> (match any single char) ex. find ?.c -> will find every file .c that case one char as name (a.c, b.c, x.c)
		' ' -> quotes every enclosed metachar
		" " -> quotes all metachars but $ \ ! * @ 

11. /dev/null to learn about this file

12. the differences between user input: cmd1; cmd2; cmd3 -> runs a command right after the previous one finish
										cmd1 | cmd2 | cmd3 -> the input of the previous cmd its passed to the next cmd (and so on)

13. [BONUS]
		ideas to do with the values of exit statuses:
		-> implementing the bonus as:
						-> cmd1 && cmd2 = if cmd1 returns exit status SUCCESS, then cmd2 its running 
						-> cmd1 || cmd2 = if cmd1 returns exit status FAILURE, then cmd2 its running, contrarly cmd2 is not running if cmd1 have exit SUCCESS 
14. [NON BUILTINS COMMANDS]
		*idea* should first check the arguments, and then do the normal behavior

15. [JOB CONTROL IMPLEMENTING]
	-> background job 
		* when entering in the background you have to put '&' on the end of the command
		* after pressing enter, the command will run into background and you don't have to wait for the command to finish for 
		start using the terminal in the foreground
			ex using: when downloading stuff and you stil want to use the terminal for other things 
	-> foreground job
		* keeps the terminal busy until the command is done

	ideas of implementing the '&' trigger for background?
		* cr
*/
