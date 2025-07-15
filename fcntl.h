#ifndef _LINUX_FCNTL_H
#define _LINUX_FCNTL_H

/*
 * Note: This file is stripped down to the bare minimum needed for the current
 * project Types of directory notifications that may be requested.
 */
#define DN_ACCESS 0x00000001    /* File accessed */
#define DN_MODIFY 0x00000002    /* File modified */
#define DN_CREATE 0x00000004    /* File created */
#define DN_DELETE 0x00000008    /* File removed */
#define DN_RENAME 0x00000010    /* File renamed */
#define DN_ATTRIB 0x00000020    /* File changed attibutes */
#define DN_MULTISHOT 0x80000000 /* Don't remove notifier */

#define AT_FDCWD                                                               \
    -100                          /* Special value used to indicate            \
                                     openat should use the current             \
                                     working directory. */
#define AT_SYMLINK_NOFOLLOW 0x100 /* Do not follow symbolic links.  */
#define AT_REMOVEDIR                                                           \
    0x200                       /* Remove directory instead of                 \
                               unlinking file.  */
#define AT_SYMLINK_FOLLOW 0x400 /* Follow symbolic links.  */

#endif
