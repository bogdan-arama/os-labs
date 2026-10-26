# Operating Systems – laboratory works

Bogdan Aramă, FAF-242 · Technical University of Moldova, FCIM · 2026–2027

All labs were done on Ubuntu 26.04 (VirtualBox). The xv6 labs use
[mit-pdos/xv6-riscv](https://github.com/mit-pdos/xv6-riscv) at revision `06aad25`,
built with `riscv64-linux-gnu-gcc` and run in QEMU 10.2.

| Lab | Topic | Track | What is in the folder |
|-----|-------|-------|-----------------------|
| [lab1](lab1) | The OS as a resource manager | A – Linux | `report.md`, Word report |
| [lab2](lab2) | Meet the OS you will build | B – xv6 | `sleep.c`, `Makefile`, `notes.md`, Word report |
| [lab3](lab3) | Shell, pipes and text filters | A – Linux | `oneliners.sh`, `report.sh`, Word report |
| [lab4](lab4) | The xv6 shell from the outside | B – xv6 | `sleep.c`, `args.c`, `args_linux.c`, `Makefile`, Word report |
| [lab5](lab5) | The file system with your own hands | A – Linux | `report.md` (Word report together with lab 6) |
| [lab6](lab6) | Inside the xv6 file system | B – xv6 | `mystat.c`, `find.c`, `Makefile`, `notes.md`, Word report for labs 5–6 |
| [lab7](lab7) | Processes, redirection, a pipe | A – Linux | `run.c`, `zombie.c`, `redirect.c`, `pipeline.c`, `pipeline3.c`, `report.md` |
| [lab8](lab8) | The same calls inside xv6 | B – xv6 | `run.c`, `pingpong.c`, `primes.c`, `Makefile`, `notes.md`, Word report for labs 7–8 |

Screenshots used in the reports are in each lab's `img/` folder.

## Building the xv6 programs

Copy the `.c` files of a lab into `~/xv6-riscv/user/` and the lab's `Makefile` over the one in
`~/xv6-riscv`, then:

```bash
cd ~/xv6-riscv && make qemu
```

Leave QEMU with `Ctrl-A`, then `X`.

## Running the Linux programs

```bash
cd lab3 && cp oneliners.sh report.sh ~/os-lab3/ && cd ~/os-lab3 && chmod +x report.sh && bash oneliners.sh && ./report.sh access.log
```

```bash
cd lab7 && for f in run zombie redirect pipeline pipeline3; do gcc -Wall -Wextra -o $f $f.c; done
```
