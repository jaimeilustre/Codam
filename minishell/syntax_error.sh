# COLORS
BOLD='\033[1m'
RED='\e[31m'
GRN='\e[32m'
RC='\e[m'

# VARS

PROJECT_DIR=$HOME/Projects/minishell_git
MINISHELL=$PROJECT_DIR/db_minishell
ECHO='echo -e'

# INIT

make -C $PROJECT_DIR debug
export LSAN_OPTIONS=suppressions=$PROJECT_DIR/asan_minishell.supp

# Quotes and Space
Q="'"
QQ="\""
S=" "

$ECHO ${BOLD}"\nSyntax error case: "${RC}
env $MINISHELL << eof
echo 1 "$Q"
$Q

echo 2 "$Q$Q$Q$Q$Q$Q$Q"
$Q$Q$Q$Q$Q$Q$Q

echo 3 '"'
$QQ

echo 4 "  $Q"
  $Q

echo 5 "  $Q$Q$S$S"
  $Q$S$S

echo 6 '  "'
  $QQ

echo 7 '  "$S$S'
  $QQ$S$S

echo 8 "echo hi $Q"
echo hi $Q

echo 9 'echo hi "'
echo hi $QQ

echo 10 "echo${Q}hi"
echo${Q}hi

echo 11 'echo"hi'
echo${QQ}hi

echo 12 '('
(

echo 13 ')'
)

echo 13 '  ('
  (

echo 14 '  )'
  )

echo 15 '()'
()

echo 16 '()()()()()'
()()()()()

echo 17 '((((()))))'
((((()))))

echo 18 '(()'
(()

echo 19 '))(('
))((

echo 20 '(())))'
(())))

echo 21 '|'
|

echo 22 '|||'
|||

echo 23 '| | |'
| | |

echo 24 ' | | | '
 | | |$S

echo 25 '|a||a'
|a||a

echo 26 'a||a|'
a||a|

echo 27 'a| |a| '
a| |a|$S

echo 28 'echo |'
echo |

echo 29 'echo|'
echo|

echo 30 '/bin/echo |'
/bin/echo |

echo 32 '/bin/echo|'
/bin/echo|

echo 33 'echo | echo |echo |' ======
echo | echo |echo |

echo 34 'echo|echo|echo|'
echo|echo|echo|

echo 35 '||'
||

echo 36 '|| ||'
|| ||

echo 37 '|| ||$S'
|| ||$S

echo 38 ' || ||'
 || ||

echo 39 ' || ||$S'
 || ||$S

echo 40 'echo||'
echo||

echo 41 'echo||$S'
echo||$S

echo 42 'echo ||'
echo ||

echo 43 '|| echo'
|| echo

echo 44 '/bin/echo||'
/bin/echo||

echo 45 '/bin/echo ||'
/bin/echo ||

echo 46 'echo||echo||'
echo||echo||

echo 47 'echo || echo ||$S'
echo || echo ||$S

echo 48 '||a||a'
||a||a

echo 49 'a||a||'
a||a||

echo 50 'a|| ||a||$S'
a|| ||a||$S

echo 51 '&&'
&&

echo 52 'echo&&'
echo&&

echo 53 'echo&&$S'
echo&&$S

echo 54 '&&echo'
&&echo

echo 55 '&&a&&a&&b'
&&a&&a&&b

echo 56 ' &&a&&a&&b'
 &&a&&a&&b

echo 57 '   && a&&a &&b$S'
   && a&&a &&b$S

echo 58 'echo | echo ||'
echo | echo ||

echo 59 'echo | echo &&'
echo | echo &&

echo 60 '&& echo hi | echo bye'
&& echo hi | echo bye

echo 61 '|| echo hi | echo bye'
|| echo hi | echo bye

echo 62 'echo &|'
echo &|

echo 63 'echo |&'
echo |&

echo 64 '|& echo'
|& echo

echo 65 '&| echo'
&| echo

echo 66 '(&& echo)'
(&& echo)

echo 67 '(|echo)'
(|echo)

echo 68 '(||echo)'
(||echo)

echo 69 '(echo &&)'
(echo &&)

echo 70 '(echo |)'
(echo |)

echo 71 '(echo &&)'
(echo &&)

echo 72 '(||||echo)'
(||||echo)

echo 73 '(echo && echo'
(echo && echo

echo 74 '(echo || echo'
(echo || echo

echo 75 '(echo | echo'
(echo | echo

echo 76 '(echo&&echo'
(echo&&echo

echo 78 '(echo||echo'
(echo||echo

echo 79 '(echo|echo'
(echo|echo

echo 80 'echo&&echo)'
echo&&echo)

echo 81 'echo||echo)'
echo||echo)

echo 82 'echo|echo)'
echo|echo)

echo 83 '(((echo hi | echo bye))'
(((echo hi | echo bye))

echo 84 '(((echo 1 | echo 2))&&echo 3'
(((echo 1 | echo 2))&&echo 3

echo 85 '((echo 1 | echo 2))&&echo 3)'
((echo 1 | echo 2))&&echo 3)

echo 86 '&& echo 1 && echo 2'
&& echo 1 && echo 2

echo 87 '|| echo 1 || echo 2'
|| echo 1 || echo 2

echo 88 '&&(echo 1 || echo 3)'
&&(echo 1 || echo 3)

echo 89 '||(echo 1 || echo 3)'
||(echo 1 || echo 3)

echo 90 'echo (hi)'
echo (hi)

echo 91 '(echo (hi))'
(echo (hi))

echo 92 '(((echo (hi))))'
(((echo (hi))))

echo 93 '(&& ((echo hi)))'
(&& ((echo hi)))

echo 94 '(&& (echo hi))'
(&& (echo hi))

echo 95 '(&& (echo hi)&&echo bye)'
(&& (echo hi)&&echo bye)
eof
