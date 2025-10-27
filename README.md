# 🕓 Time-Travelling File System

## Overview
This project implements a simplified, **in-memory version control system** inspired by Git.  
It supports file versioning, branching, snapshots, rollbacks, and system-wide analytics — all built entirely **from scratch** using custom implementations of:
- **Trees** → to maintain version history  
- **HashMaps** → for fast version lookups  
- **Heaps** → for analytics (recently edited files, biggest version trees)  

> Developed as part of **COL106: Data Structures and Algorithms (IIT Delhi)**

---

## System Architecture
Each file is represented by a structure containing:
- **Version Tree** — each node (`TreeNode`) represents a file version.  
- **Custom HashMap** — maps version IDs to corresponding tree nodes.  
- **Heap Structures** — track “recently modified” and “largest” files.

### Each Version Node (`TreeNode`) Contains:
- `int version_id`  
- `string content`  
- `string message` (for snapshots)  
- `time_t created_timestamp`  
- `time_t snapshot_timestamp`  
- `TreeNode* parent`  
- `vector<TreeNode*> children`

---

## Build Instructions
### Requirements
- C++17 or newer  
- `g++` compiler  
- Unix-like environment (Linux, macOS, or WSL)

### Compilation
```bash
chmod +x build.sh
./build.sh
```

This generates an executable named `program`.

### Run
```bash
./program
```

You’ll enter the interactive shell:
```
Time-Travelling File System CLI
Enter a command (type 'EXIT' to quit)
```

---

## Command Reference

### 🔧 Core File Operations
| Command | Description |
|----------|-------------|
| `CREATE <filename>` | Create a new file with version `0` (root snapshot). |
| `READ <filename>` | Display the content of the active version. |
| `INSERT <filename> <content>` | Append text to file. |
| `UPDATE <filename> <content>` | Replace file content. |
| `SNAPSHOT <filename> <message>` | Create a snapshot with message. |
| `ROLLBACK <filename> [versionID]` | Restore to a previous version (or parent if none given). |
| `HISTORY <filename>` | Show all snapshots along the active path (ID, timestamp, message). |

### 📊 System-Wide Analytics
| Command | Description |
|----------|-------------|
| `RECENT_FILES <num>` | List top `<num>` files by last modification time. |
| `BIGGEST_TREES <num>` | List top `<num>` files by total version count. |

### 🚪 Exit
```
EXIT
```

---

## Error Handling
All invalid inputs are handled gracefully with clear error messages.

| Scenario | Error Message |
|-----------|----------------|
| Unknown command | `Error: Unknown command.` |
| Missing filename | `Error: No filename provided.` |
| Duplicate filename | `Error: File <filename> already exists.` |
| File not found | `Error: File <filename> not found.` |
| Invalid version ID | `Error: Version ID not found.` |
| Missing parameter (e.g. num in RECENT_FILES) | `Error: Number of entries not specified.` |
| Negative number | `Error: Invalid number of entries.` |
| Extra arguments | `Error: Too many arguments for command.` |

---

## Assumptions & Limitations
- **Unique Filenames** — filenames act as unique keys.
- **Sequential Version IDs** — assigned starting from `0` per file.
- **Snapshots are Immutable** — cannot be modified after creation.
- **No STL Containers** — all data structures implemented manually.
- **Memory Leaks** — raw pointers used; memory not reclaimed on exit.
- **Deterministic Heap Ordering** — tie-breaking based on lexicographical filename order.

---

## Example Session
```
> CREATE file1
> INSERT file1 Hello
> SNAPSHOT file1 First snapshot
> UPDATE file1 World
> SNAPSHOT file1 Second snapshot
> HISTORY file1
ID: 0 | Snapshot: First snapshot | Timestamp: ...
ID: 1 | Snapshot: Second snapshot | Timestamp: ...
> RECENT_FILES 1
file1
> EXIT
```

---

## Authors
**Name:** Aryan Patel  
**Course:** COL106 – Data Structures and Algorithms  
**Institution:** Indian Institute of Technology, Delhi  
