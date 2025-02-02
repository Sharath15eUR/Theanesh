#!/bin/bash

ERROR_LOG="errors.log"

log_error() {
  echo "[ERROR] $1" | tee -a "$ERROR_LOG"
}

search_directory() {
  local dir="$1"
  local keyword="$2"

  if [[ ! -d "$dir" ]]; then
    log_error "Invalid directory: $dir"
    return 1
  fi

  for file in "$dir"/*; do
    if [[ -d "$file" ]]; then
      search_directory "$file" "$keyword"  
    elif [[ -f "$file" ]]; then
      grep -q "$keyword" "$file" && echo "Found '$keyword' in $file"
    fi
  done
}

show_help() {
  cat <<EOF
Usage: $0 [options]
Options:
  -d <directory>   Directory to search recursively for a keyword
  -k <keyword>     Keyword to search in files
  -f <file>        Search for a keyword in a specific file
  --help           Display this help menu

EOF
}

validate_inputs() {
  if [[ -n "$file" && ! -f "$file" ]]; then
    log_error "File does not exist: $file"
    exit 1
  fi
  if [[ -z "$keyword" || ! "$keyword" =~ ^[a-zA-Z0-9]+$ ]]; then
    log_error "Invalid or empty keyword (must be alphanumeric)"
    exit 1
  fi
}

search_file() {
  local file="$1"
  local keyword="$2"
  if [[ -f "$file" ]]; then
    grep -q "$keyword" "$file" <<< "$keyword" && echo "Found '$keyword' in $file"
  else
    log_error "File not found: $file"
  fi
}

while getopts "d:k:f:-:" opt; do
  case $opt in
    d) directory="$OPTARG" ;;
    k) keyword="$OPTARG" ;;
    f) file="$OPTARG" ;;
    -) case "$OPTARG" in
         help) show_help; exit 0 ;;
         *) log_error "Unknown option --$OPTARG"; exit 1 ;;
       esac ;;
    ?) log_error "Invalid option: -$OPTARG"; exit 1 ;;
  esac
done

echo "Script name: $0"
echo "Number of arguments: $#"
echo "All arguments: $@"

if [[ -n "$directory" && -n "$keyword" ]]; then
  validate_inputs
  search_directory "$directory" "$keyword"
elif [[ -n "$file" && -n "$keyword" ]]; then
  validate_inputs
  search_file "$file" "$keyword"\else
  log_error "Invalid usage. Use --help for instructions."
  exit 1
fi

exit 0
