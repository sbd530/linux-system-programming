# Hardlink

## Create Hardlink file 

```bash
$ ln hello_world hello_hardlinked
$ ls -l
# -rw-rw-r-- 2 don don     6 Aug  4 13:00 hello_world
# -rw-rw-r-- 2 don don     6 Aug  4 13:00 hello_hardlinked
```

## Check file status

### Original file

- `Inode`: 921713, `Links`: 2, `Size`: 6

```bash
$ stat hello_world
#   File: hello_world
#   Size: 6               Blocks: 8          IO Block: 4096   regular file
# ...
```

### Hardlinked file

- `Inode`: 921713, `Links`: 2, `Size`: 6   

```bash
$ stat hello_hardlinked
#   File: hello_hardlinked
#   Size: 6               Blocks: 8          IO Block: 4096   regular file
# Device: 802h/2050d      Inode: 921713      Links: 2
# ...
```

### After original file changed

```bash
$ cat hello_world
# hello
# world
$ cat hello_hardlinked
# hello
# world
```

# Softlink

## Create Softlink file 

- `syslinked_file -> original_file`

```bash
$ ln -s hello_world hello_symlinked
$ ls -l
# -rw-rw-r-- 2 don don     6 Aug  4 13:00 hello_world
# lrwxrwxrwx 1 don don    11 Aug  4 13:10 hello_symlinked -> hello_world
```

## Check file status

### Original file

- `Inode`: 921713, `Links`: 2, `Size`: 12

```bash
$ stat hello_world 
#   File: hello_world
#   Size: 12              Blocks: 8          IO Block: 4096   regular file
# Device: 802h/2050d      Inode: 921713      Links: 2
```

### Softlinked file

- `Inode`: 921714, `Links`: 1, `Size`: 11
  - Different file size: softlinked file only knows the path of original file

```bash
$ stat hello_symlinked 
#   File: hello_symlinked -> hello_world
#   Size: 11              Blocks: 0          IO Block: 4096   symbolic link
# Device: 802h/2050d      Inode: 921714      Links: 1
```