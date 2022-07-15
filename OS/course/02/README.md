

# Text Processing

## Lectures
    - https://skelet.ludost.net/OS/KN_2018/L2b_shell_intro_01.03.2018.webm
    - https://skelet.ludost.net/OS/KN_2018/L4b_redirection_pipeline_13.03.2019.webm
    - https://skelet.ludost.net/OS/KN_2018/L5a_bash_expansions_22.03.2018.webm
    - https://skelet.ludost.net/OS/KN_2018/L5b_bash_filename_expansion_22.03.2018.webm

## Commands
    - grep
    - cat
    - cut
    - head
    - tail
    - tr
    - sort
    - echo 
    - paste 
    - wc
    - uniq
    - sed
    - awk
    
## Piping

    cat a.txt | grep foobar

    cut -d: -f6 /etc/passwd|sort|uniq -c|sort -rn

## Stream redirection

    - < : stdin from file
    - > : stdout to file
    - >> : stdout to file (append)
    - 2> : stderr to file (overwrite)
    - 2>> : stderr to file (append)
    - &> : both stdout and stderr


### Stdin , stdout and stderr
