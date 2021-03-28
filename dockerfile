FROM alpine
RUN apk update && apk add nano && apk add build-base
COPY ./hello.s hello.s
COPY ./laba3.c laba3.c
RUN chmod ugo+x hello.s
