# Mounting the VeraCrypt container off server

## Linux

### Using `sshfs` to mount the folder locally

Use your preferred package manager to install `sshfs`:

```bash
# apt-get install sshfs
```

To actually mount the remote filesystem:

```bash
$ sshfs <username>@capstone1.computing.clemson.edu:/data/ <mountpoint> -o allow_other,ro
<prompt for password>
```

You can mount the folder as read-write, however, Veracrypt will 
slow down dramatically when reencrypting the container and 
transferring the container back onto the server. __Be careful when
multiple people are attempting to write to the container at the 
same time__:

```bash
$ sshfs <username>@capstone1.computing.clemson.edu:/data/ <mountpoint> -o allow_other
<prompt for password>
```

### Use Veracrypt to mount the container

You should know how to do this.

### Use Veracrypt to close the container.

This is where Veracrypt slows down if you have enabled read-write mode.

### Unmounting

```bash
$ fusermount -u <mountpoint>
```

## MacOS

### Using `sshfs` to mount the folder locally

Install [FUSE for macOS](https://osxfuse.github.io/)

Install [SSHFS](https://github.com/osxfuse/osxfuse/wiki/SSHFS) in the FUSE repo

Then mount similar to Linux:

```bash
$ sshfs <username>@capstone1.computing.clemson.edu:/data/ <mountpoint> -o allow_other,ro
<prompt for password>
```
### Use Veracrypt to mount the container

You should know how to do this.

### Use Veracrypt to close the container.

This is where Veracrypt slows down if you have enabled read-write mode.

### Unmounting

```bash
$ umount <mountpoint>
```

## Windows

Install [sshfs-win](https://github.com/billziss-gh/sshfs-win)

### Using `sshfs` to mount the folder locally

In your command prompt:

```
> net use <drive letter>: \\sshfs\<user>@capstone1.computing.clemson.edu\..\..
<prompt for password>
```

### Use Veracrypt to mount the container

You should know how to do this.

### Use Veracrypt to close the container.

This is where Veracrypt slows down if you have enabled read-write mode.

### Unmounting

```
> net use <drive letter>: /delete
```
