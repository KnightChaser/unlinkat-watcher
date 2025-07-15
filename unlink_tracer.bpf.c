// unlink_tracer.bpf.c
#include "unlink_tracer.h"
#include "vmlinux.h"
#include <bpf/bpf_core_read.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

char LICENSE[] SEC("license") = "GPL";

struct {
    __uint(type, BPF_MAP_TYPE_RINGBUF);
    __uint(max_entries, 1 << 20); /* 1 MiB */
} events SEC(".maps");

// NOTE:
// https://github.com/torvalds/linux/blob/155a3c003e555a7300d156a5252c004c392ec6b0/include/linux/lsm_hook_defs.h#L91C1-L91C77
// LSM_HOOK(int, 0, path_unlink, const struct path *dir, struct dentry *dentry)
SEC("lsm.s/path_unlink")
int BPF_PROG(trace_path_unlink, struct path *dir, struct dentry *dentry) {
    struct event *e;
    unsigned int filename_len;

    e = bpf_ringbuf_reserve(&events, sizeof(*e), 0);
    if (!e) {
        return 0;
    }

    __builtin_memset(e, 0, sizeof(*e));

    // Obtain process information
    e->pid = bpf_get_current_pid_tgid() >> 32;
    bpf_get_current_comm(&e->process_name, sizeof(e->process_name));

    // Get the path of the parent directory from the 'dir' argument
    if (bpf_d_path(dir, e->dir_path, sizeof(e->dir_path)) < 0) {
        bpf_ringbuf_discard(e, 0);
        return 0;
    }

    // Get the filename of the delted entry from the 'dentry' argument,
    // after checking out the file name length
    filename_len = BPF_CORE_READ(dentry, d_name.len);
    if (filename_len >= sizeof(e->filename)) {
        // Ensure proper null termination
        filename_len = sizeof(e->filename) - 1;
    }
    bpf_probe_read_kernel(&e->filename, filename_len, dentry->d_name.name);
    e->filename[filename_len] = '\0'; // Null-terminate the filename

    bpf_ringbuf_submit(e, 0);
    return 0;
}
