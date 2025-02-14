Expect AST

```c

typedef struct s_action
{
	int		type;
	char	*val; // echo "ha $hahaha" <---
	struct t_action *left;
	struct t_action *right;
} t_action;

```

Tokenizer; identifing the words into tokens

Parser: check for correct syntax (like missing quotes)
+ Handle single cmd, followed by pipes.
+ Expand variables.
+ If variable doesn't exist don't exit (empty string return).
+ No need to check if cmd exist or arguments are valid.
+ Maintain the order of left to right prompt. (left needs to be executed first).
+ val will be cmd + args.

Interperter:
+ prompt (with pwd)
+ echo + export (maybe unset)
+ pipes
