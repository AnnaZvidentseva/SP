FROM alpine
RUN apk update && apk add nano && apk add build-base
COPY ./IP.cpp IP.cpp
COPY ./ping.cpp ping.cpp
RUN g++ -o IP IP.cpp
RUN g++ -o ping ping.cpp
