FROM alpine
RUN apk update && apk add nano && apk add build-base
COPY ./hello.s hello.s
RUN chmod ugo+x hello.s
ENTRYPOINT bin/sh
