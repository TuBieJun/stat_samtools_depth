### Description
A simple tool to stat the pos number with different depth from  samtools depth result file. The result can be easy used to get the coverage norm.

### Compile
```
gcc -O2 stat_samtools_depth.c -o stat_samtools_depth
```

### Usage

```
stat_samtools_depth <in_samtools_depth_result.txt> > stat_result
```