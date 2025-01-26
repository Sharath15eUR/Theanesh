
#!/bin/bash

# Find the process with the highest memory usage
highest_mem_pid=$(ps -eo pid,pmem --sort=-pmem | awk 'NR==2 {print $1}')

# Get the name of the process for reference
process_name=$(ps -p "$highest_mem_pid" -o comm=)

if [[ -n "$highest_mem_pid" ]]; then
    echo "The process with the highest memory usage is PID: $highest_mem_pid ($process_name)"
    read -p "Do you want to terminate this process? (y/n): " confirm
    if [[ "$confirm" == "y" || "$confirm" == "Y" ]]; then
        # Terminate the process
        kill -9 "$highest_mem_pid"
        echo "Process $highest_mem_pid ($process_name) has been terminated."
    else
        echo "Termination canceled."
    fi
else
    echo "No processes found."
fi
