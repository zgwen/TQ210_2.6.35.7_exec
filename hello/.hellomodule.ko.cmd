cmd_/work/mymodules/hello/hellomodule.ko := arm-linux-ld -EL -r  -T /work/linux/scripts/module-common.lds --build-id -o /work/mymodules/hello/hellomodule.ko /work/mymodules/hello/hellomodule.o /work/mymodules/hello/hellomodule.mod.o