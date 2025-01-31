#!/bin/bash

if [ "$#" -ne 3 ]; then
  echo "Usage: $0 <source_directory> <backup_directory> <file_extension>"
  exit 1
fi

SOURCE_DIR="$1"
BACKUP_DIR="$2"
FILE_EXT="$3"

if [ ! -d "$SOURCE_DIR" ]; then
  echo "Source directory does not exist. Please provide a valid directory."
  exit 1
fi

if [ ! -d "$BACKUP_DIR" ]; then
  echo "Backup directory does not exist. Creating it..."
  mkdir -p "$BACKUP_DIR" || { echo "Failed to create backup directory."; exit 1; }
fi

FILES=($SOURCE_DIR/*$FILE_EXT)

if [ "${#FILES[@]}" -eq 0 ]; then
  echo "No files with extension '$FILE_EXT' found in source directory."
  exit 0
fi

echo "Files to back up:"
for file in "${FILES[@]}"; do
  if [ -f "$file" ]; then
    echo "$(basename "$file") - Size: $(du -h "$file" | cut -f1)"
  fi
done

export BACKUP_COUNT=0
TOTAL_SIZE=0

for file in "${FILES[@]}"; do
  if [ -f "$file" ]; then
    dest_file="$BACKUP_DIR/$(basename "$file")"
    if [ -f "$dest_file" ]; then
      # Only overwrite if the source file is newer
      if [ "$file" -nt "$dest_file" ]; then
        cp "$file" "$dest_file"
        echo "Updated: $(basename "$file")"
      else
        echo "Skipped (Up-to-date): $(basename "$file")"
        continue
      fi
    else
      cp "$file" "$dest_file"
      echo "Backed up: $(basename "$file")"
    fi
    ((BACKUP_COUNT++))
    FILE_SIZE=$(stat -c%s "$file")
    TOTAL_SIZE=$((TOTAL_SIZE + FILE_SIZE))
  fi
done

REPORT_FILE="$BACKUP_DIR/backup_report.log"
{
  echo "Backup Summary Report"
  echo "-----------------------"
  echo "Total files processed: $BACKUP_COUNT"
  echo "Total size of files backed up: $(numfmt --to=iec $TOTAL_SIZE)"
  echo "Backup directory: $BACKUP_DIR"
} > "$REPORT_FILE"

echo "Backup completed successfully. Report saved to $REPORT_FILE"
