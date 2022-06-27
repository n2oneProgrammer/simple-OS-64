FROM randomdude/gcc-cross-x86_64-elf

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y nasm
RUN apt-get install -y build-essential
RUN apt-get install -y bison
RUN apt-get install -y flex
RUN apt-get install -y libgmp3-dev
RUN apt-get install -y libmpc-dev
RUN apt-get install -y libmpfr-dev
RUN apt-get install -y texinfo
VOLUME /root/env
WORKDIR /root/env