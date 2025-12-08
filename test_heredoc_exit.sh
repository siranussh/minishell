#!/bin/bash
(
  sleep 0.2
  # Send Ctrl+C (SIGINT) to the minishell process
  pkill -SIGINT minishell
  sleep 0.1
  echo "echo \$?"
  sleep 0.1
  echo "exit" 
) | ./minishell << 'INPUT'
cat << END
INPUT
