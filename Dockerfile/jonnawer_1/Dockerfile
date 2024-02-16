FROM ubuntu:latest
EXPOSE 22

# Установка необходимых пакетов
RUN apt-get update; \
    apt-get -y upgrade; \
    echo "root:root" | chpasswd; \
    apt install -y curl; \
    apt install -y gcc; \
    apt install -y make; \
    apt install -y clang-format; \
    apt install -y vim; \
    apt install -y openssh-server; \
    # service ssh start; \
    apt-get install -y iputils-ping; \
    apt install -y iproute2

# CMD service ssh start