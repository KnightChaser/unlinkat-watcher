# unlinkat-watcher

It detects which processes delete which files **in real time** in Linux via eBPF(extended Berkeley Packet Filter)!
I used LSM(Linux Security Module)'s [`path_unlink`](https://github.com/torvalds/linux/blob/155a3c003e555a7300d156a5252c004c392ec6b0/include/linux/lsm_hook_defs.h#L91) hook.

If you or other processes delete files, `unlinkat-watcher` will print the log simultaneously.

Prepare eBPF development environment(including `libbpf` package) on your Linux computer, 
and enable LSM(Linux Security Module) in your grub configuration, and hit `make` to build this project.

### Screenshot

<img width="2538" height="1139" alt="Screenshot from 2025-07-15 17-01-45" src="https://github.com/user-attachments/assets/bb9d3ad6-6655-41c7-a078-1235d75d6115" />

<img width="1654" height="1238" alt="image" src="https://github.com/user-attachments/assets/97b42217-272e-4084-a515-8efbe3464a98" />


### Reference

https://github.com/KnightChaser/lsm-bpf-capture-path
