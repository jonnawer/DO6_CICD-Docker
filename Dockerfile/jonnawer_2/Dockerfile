FROM ubuntu:latest
EXPOSE 22
# Установка необходимых пакетов
RUN apt-get update; \
    apt-get -y upgrade; \
    echo "root:root" | chpasswd; \
    # adduser -y user && echo "user:user" | chpasswd; \
    #  useradd -m  user && echo "user:user" | chpasswd; \
    apt install -y openssh-server; \
    # service ssh start; \
    apt-get install -y iputils-ping; \
    apt install -y iproute2