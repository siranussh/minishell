#!/bin/bash
(
  sleep 0.1
  # Send Ctrl+C (SIGINT) to the minishell process
  pkill -SIGINT minishell
  sleep 0.1
  echo "exit" 
) | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp ./minishell << 'INPUT'
cat << END
INPUT
