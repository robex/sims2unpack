## sims2unpack
Unpack .package files used in The Sims 2. This does not decompress the files if they are compressed!

####Compilation
```make```

It should compile fine under Windows too, use MinGW or compile the single C file manually.

####Usage
```
usage: ./sims2unpack [file.packed]
	files are dumped in the current directory as out.[number], be aware!
```
The reason files are dumped with these ugly filenames is that there are simply no filenames inside the archive.