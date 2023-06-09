FROM ubuntu:18.04

LABEL rkm="Rekunov_Mikhail_221_354 <@Flooxik>"

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Установка пакетов QT
RUN apt-get update   
RUN apt-get install qt5-default -y   
RUN apt-get install qtbase5-dev -y   
RUN apt-get install qt5-qmake   
RUN apt-get install build-essential -y 

# Создание папки для проекта
WORKDIR /root/Rekunov_Mikhail_221_353

# Копирование всех файлов
COPY . .

# Компиляция проекта 
RUN qmake echoServer.pro
RUN make

CMD ["./echoServer"]

EXPOSE 33333

# docker build -t name:latest -f ManagerServer.Dockerfile .
# docker run -p 33333:33333 name:latest
# docker container commit "Container ID" name:latest
# docker tag name:latest dockerUser/name:latest
# docker push dockerUser/name:latest
