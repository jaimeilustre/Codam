## 🐚 Minishell

### Description
Minishell is a minimal Unix shell written in C, replicating basic Bash behavior such as command execution, pipes, redirections, environment variables, and signal handling.

### Requirements
- Linux or macOS
- cc
- make
- readline library

### Build
```bash
make
```

### Run
```bash
./minishell
```

Once launched, you can execute commands similar to Bash:
```bash
ls -l | grep minishell
echo $HOME
```

### Clean
```bash
make clean      # removes object files
make fclean     # removes object files and executable
make re         # rebuilds the project
```