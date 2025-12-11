awk '
  BEGIN { RS="---[ \t]*\n" }
  NF {
    cmd="python solver.py"
    print | cmd
    close(cmd)
  }
' output.txt \
| awk '
  /^[0-9]+$/ {                      # keep only pure-integer lines
    sum += $0
  }
  END { print sum }
'
