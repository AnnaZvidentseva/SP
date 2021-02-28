FROM alpine 
RUN apk update && apk add nano
COPY ./SP1.sh SP1.sh
RUN chmod ugo+x SP1.sh
ENTRYPOINT /bin/sh
